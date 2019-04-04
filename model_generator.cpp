#include "model_generator.h"
#include "string_helpers.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>

TModelGenerator::TModelGenerator(size_t countOfDays, double marginPercentage, double discount)
    : CountOfDays(countOfDays)
    , MarginPercentage(marginPercentage)
    , Discount(discount)
    , RandGen(3647376)
{
}

void TModelGenerator::StartModel() {
    CurrentDay = 0;
    Profit = 0;
    Toll = 0;
}

void TModelGenerator::SetCountOfDays(int32_t countOfDays) {
    CountOfDays = countOfDays;
}

int32_t TModelGenerator::GetCountOfDays() const {
    return CountOfDays;
}

TDate TModelGenerator::GetCurrentDay() const {
    return TDate(CurrentDay);
}

double TModelGenerator::GetMarginPercentage() const {
    return MarginPercentage;
}

void TModelGenerator::SetMarginPercentage(double value) {
    MarginPercentage = value;
}

double TModelGenerator::GetDiscount() const {
    return Discount;
}
void TModelGenerator::SetDiscount(double value) {
    Discount = value;
}

double TModelGenerator::GetProfit() const {
    return Profit;
}

void TModelGenerator::UpdateProfit(double profit) {
    Profit += profit;
}

double TModelGenerator::GetToll() const {
    return Toll;
}

void TModelGenerator::UpdateToll(double toll) {
    Toll += toll;
}

bool TModelGenerator::IsEndOfSimulation() const {
    return CountOfDays <= CurrentDay;
}

void TModelGenerator::NextDay() {
    if (CountOfDays > CurrentDay) {
        ++CurrentDay;
    }
}

void TModelGenerator::SetCountOfMedicaments(size_t countOfMedicaments) {
    CountOfMedicaments = countOfMedicaments;
}


std::vector<TOrder> TModelGenerator::GenerateOrders() {
    std::uniform_int_distribution<size_t> countOfOrdersDist(1, 6);
    std::uniform_int_distribution<size_t> countOfGoodsDist(1, 3);
    std::uniform_int_distribution<size_t> medIdDist(0, CountOfMedicaments - 1);

    std::uniform_int_distribution<size_t> isNotRegular(0, 4);
    std::cout << RegularCustomers.size() << std::endl;
    std::uniform_int_distribution<size_t> regularCustomerIdDist(0, RegularCustomers.size() - 1);

    std::uniform_int_distribution<uint64_t> telephoneDist(1000000, 99999999);
    std::vector<TOrder> result;
    size_t countOfOrders = countOfOrdersDist(RandGen);
    size_t countOfGoods = countOfGoodsDist(RandGen);
    for (size_t i = 0; i < countOfOrders; ++i) {
        uint64_t telephoneNumber = telephoneDist(RandGen);
        TOrder order;
        if (isNotRegular(RandGen)) {
            order.SetTelephoneNumber(telephoneNumber);
            order.SetAddress("Russia, Moscow");
        } else {
            order.SetCustomerInfo(RegularCustomers[regularCustomerIdDist(RandGen)]);
        }

        std::unordered_set<size_t> alreadyInOrder;
        for (size_t j = 0; j < countOfGoods; ++j) {
            size_t medIdShift = medIdDist(RandGen);
            size_t countOfOneMedId = countOfGoodsDist(RandGen);
            if (alreadyInOrder.find(medIdShift) == alreadyInOrder.end()) {
                order.AddGood(TMedInOrder(MedicamentsIds[medIdShift], countOfOneMedId));
                alreadyInOrder.insert(medIdShift);
            } else {
                --j;
            }
        }
        result.push_back(order);
    }
    return result;
}

size_t TModelGenerator::GetCountOfMedicaments() const {
    return CountOfMedicaments;
}

std::vector<TRegularCustomer> TModelGenerator::GenerateRegularCustomers() {
    std::uniform_int_distribution<size_t> countOfGoodsDist(1, 3);
    std::uniform_int_distribution<size_t> periodDist(5, 20);
    std::uniform_int_distribution<size_t> medIdDist(0, CountOfMedicaments - 1);
    std::uniform_int_distribution<size_t> countDist(1, 4);
    std::ifstream customersFile("/Users/nadya73/pharmacy_qt/data/customers.txt");
    std::string line;

    uint64_t discountCardNumber;
    uint64_t telephoneNumber;

    while (getline(customersFile, line)) {
        std::istringstream lineSs(line);
        std::vector<std::string> tokens;
        std::string token;
        while (getline(lineSs, token, '\t')) {
            tokens.push_back(token);
        }

        if (tokens.size() != 4) {
            continue;
        }

        discountCardNumber = FromString<uint64_t>(tokens[2]);
        telephoneNumber = FromString<uint64_t>(tokens[3]);

        TRegularCustomer customer(tokens[0], tokens[1], discountCardNumber, telephoneNumber);
        for (size_t i = 0; i < countOfGoodsDist(RandGen); ++i) {
            size_t period = periodDist(RandGen);
            size_t medId = medIdDist(RandGen);
            size_t count = countDist(RandGen);

            TRegularMedicament regularMedicament(MedicamentsIds[medId], period, count);
            customer.AddRegularMedicaments(regularMedicament);
        }

        RegularCustomers.push_back(customer);
    }
    return RegularCustomers;
}

std::unordered_map<TMedicamentId, TMedicamentInfo> TModelGenerator::GenerateStartWarehouseState() {
    std::ifstream medicamentsFile("/Users/nadya73/pharmacy_qt/data/medicaments.txt");
    std::unordered_map<TMedicamentId, TMedicamentInfo> result;
    std::string line;

    int32_t medType;
    double dose;
    int32_t unitOfMeasure;
    double tradePrice;
    int32_t group;
    size_t storageLife;

    std::uniform_int_distribution<size_t> dist(6, 20);
    std::uniform_int_distribution<size_t> distUpdate(2, 4);
    size_t countOfMed = 0;
    while (getline(medicamentsFile, line)) {
        std::istringstream lineSs(line);
        std::vector<std::string> tokens;
        std::string token;
        while (getline(lineSs, token, '\t')) {
            tokens.push_back(token);
        }
        if (tokens.size() != 7) {
            std::cerr << "Bad medicament in medicaments.txt" << countOfMed << std::endl;
            continue;
        }
        medType = FromString<int32_t>(tokens[1]);
        dose = FromString<double>(tokens[2]);
        unitOfMeasure = FromString<int32_t>(tokens[3]);
        tradePrice = FromString<double>(tokens[4]);
        group = FromString<int32_t>(tokens[5]);
        storageLife = FromString<size_t>(tokens[6]);

        std::uniform_int_distribution<size_t> distStorageLife(storageLife / 6 * 5, storageLife);

        size_t count = dist(RandGen);
        size_t updateCount = distUpdate(RandGen);

        TMedicamentId medId = {tokens[0], static_cast<EMedType>(medType), TDose(dose, static_cast<EUnitOfMeasure>(unitOfMeasure))};
        result[medId] = TMedicamentInfo(static_cast<EMedGroup>(group), tradePrice, storageLife, updateCount, count);

        const auto& curStorageLife = distStorageLife(RandGen);
        result[medId].AddParty(TMedicamentParty(count, static_cast<int32_t>(curStorageLife) - storageLife, curStorageLife));

        MedicamentsIds.push_back(medId);
        ++countOfMed;
        if (countOfMed >= CountOfMedicaments) {
            break;
        }
    }
    return result;
}
