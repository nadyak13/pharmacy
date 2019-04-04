#include "medicament.h"
#include <vector>
#include <iostream>

TMedicamentInfo::TMedicamentInfo() {}

TMedicamentInfo::TMedicamentInfo(EMedGroup group, double tradePrice, size_t storageLife, size_t updateCount, size_t count, std::map<TDate, TMedicamentParty> parties)
    : Group(group)
    , TradePrice(tradePrice)
    , StorageLife(storageLife)
    , UpdateCount(updateCount)
    , Count(count)
    , Parties(parties)
{}

std::string ToString(EMedType medType) {
    switch (medType) {
    case EMedType::Unknown: {
        return "Неизвестен";
    }
    case EMedType::Tablets: {
        return "Таблетки";
    }
    case EMedType::Spray: {
        return "Спрей";
    }
    case EMedType::Suspension: {
        return "Суспензия";
    }
    case EMedType::Solution: {
        return "Раствор";
    }
    case EMedType::Drops: {
        return "Капли";
    }
    case EMedType::Powder: {
        return "Порошок";
    }
    default: {
        return "unknown";
    }
    }
}

std::string ToString(EMedGroup medGroup) {
    switch (medGroup) {
    case EMedGroup::CardiovascularAgent: {
        return "С-С средство";
    }
    case EMedGroup::Antibiotic : {
        return "Антибиотик";
    }
    case EMedGroup::Unknown: {
        return "Неизвестна";
    }
    case EMedGroup::Homeopathy: {
        return "Гомеопатия";
    }
    case EMedGroup::Antiviral: {
        return "Антивирусное";
    }
    case EMedGroup::Anesthetic: {
        return "Обезболивающее";
    }
    default: {
        return "unknown";
    }
    }
}

double TMedicamentInfo::GetTradePrice() const {
    return TradePrice;
}

EMedGroup TMedicamentInfo::GetGroup() const {
    return Group;
}

void TMedicamentInfo::SetCount(size_t newCount) {
    Count = newCount;
}

std::map<TDate, TMedicamentParty> TMedicamentInfo::GetParties() const {
    return Parties;
}

size_t TMedicamentInfo::GetCount() const {
    return Count;
}

void TMedicamentInfo::AddParty(const TMedicamentParty& party) {
    Parties[party.GetDateOfExpiration()] = party;
}

size_t TMedicamentInfo::GetStorageLife() const {
    return StorageLife;
}

size_t TMedicamentInfo::GetUpdateCount() const {
    return UpdateCount;
}

TMedicamentParty TMedicamentInfo::GetFirstParty() const {
    return Parties.begin()->second;
}

bool TMedicamentInfo::HasParties() const {
    return !Parties.empty();
}

double TMedicamentInfo::RemoveFirstParty() {
    if (!Parties.empty()) {
        size_t count = Parties.begin()->second.GetCount();
        TDate date = Parties.begin()->first;
        Parties.erase(date);
        return count * TradePrice;
    }
    return 0;
}

double TMedicamentInfo::DoBuy(size_t count, double marginPercentage, TDate curDay, double discount, size_t& realCount) {
    size_t stillCount = count;
    double profit = 0;
    std::vector<TDate> endedParties;
    for (auto& party : Parties) {
        if (stillCount > 0) {
            size_t partyCount = party.second.GetCount() > stillCount ? stillCount : party.second.GetCount();
            if (curDay.GetDaysFromStart() - party.first.GetDaysFromStart() < DAYS_FOR_CUTPRICE) {
                profit += 0.5 * partyCount * GetTradePrice() * (1 + marginPercentage) * (1 - discount) - partyCount * GetTradePrice();
            } else {
                std::cout << "MINUS: " << (partyCount * GetTradePrice() * marginPercentage * (1 - discount)) << std::endl;
                std::cout << partyCount << std::endl;
                std::cout << GetTradePrice() << std::endl;
                std::cout << marginPercentage << std::endl;
                std::cout << discount << std::endl;
                profit += partyCount * GetTradePrice() * marginPercentage * (1 - discount / 100);
            }
            stillCount -= partyCount;
            std::cerr << "Party count: " << partyCount << std::endl;
            party.second.ReduceCount(partyCount);
            Count -= partyCount;
            if (party.second.GetCount() == 0) {
                endedParties.push_back(party.first);
            }
        }
    }

    for (const auto& date : endedParties) {
        Parties.erase(Parties.find(date));
    }

    realCount = count - stillCount;

    return profit;
}

TMedicamentParty::TMedicamentParty() {
}

TMedicamentParty::TMedicamentParty(size_t count, TDate dateOfManufacture, TDate dateOfExpiration)
    : Count(count), DateOfManufacture(dateOfManufacture), DateOfExpiration(dateOfExpiration)
{}

size_t TMedicamentParty::GetCount() const {
    return Count;
}

TDate TMedicamentParty::GetDateOfManufacture() const {
    return DateOfManufacture;
}

TDate TMedicamentParty::GetDateOfExpiration() const {
    return DateOfExpiration;
}

void TMedicamentParty::ReduceCount(size_t count) {
    Count -= count;
}

bool operator==(const TMedicamentId& lhs, const TMedicamentId& rhs) {
    return lhs.MedName == rhs.MedName && lhs.Type == rhs.Type && lhs.Dose == rhs.Dose;
}

bool operator<(const TMedicamentId& lhs, const TMedicamentId& rhs) {
    if (lhs.MedName != rhs.MedName) {
        return lhs.MedName < rhs.MedName;
    }
    if (lhs.Type != rhs.Type) {
        return lhs.Type < rhs.Type;
    }
    return lhs.Dose.GetValue() < rhs.Dose.GetValue();
}

namespace std {
    size_t hash<TMedicamentId>::operator()(const TMedicamentId &medId) const {
        std::stringstream numSs;
        numSs << uint8_t(medId.Type) << medId.Dose.GetValue() << uint8_t(medId.Dose.GetUnitOfMeasure());
        return std::hash<std::string>()(medId.MedName + numSs.str());
    }
}
