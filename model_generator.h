#pragma once

#include <string>
#include <vector>
#include <time.h>
#include <unordered_map>
#include <random>
#include "order.h"
#include "medicament.h"
#include "regular_customer.h"


class TModelGenerator {
public:
    static TModelGenerator& Instance() {
        static TModelGenerator instance;
        return instance;
    }

    void StartModel();

    TDate GetCurrentDay() const;

    int32_t GetCountOfDays() const;
    void SetCountOfDays(int32_t countOfDays);

    std::vector<TOrder> GenerateOrders();

    std::unordered_map<TMedicamentId, TMedicamentInfo> GenerateStartWarehouseState();

    std::vector<TRegularCustomer> GenerateRegularCustomers();

    double GetMarginPercentage() const;
    void SetMarginPercentage(double value);

    double GetDiscount() const;
    void SetDiscount(double value);

    double GetProfit() const;
    void UpdateProfit(double profit);
    double GetToll() const;
    void UpdateToll(double toll);
    void NextDay();
    bool IsEndOfSimulation() const;
    size_t GetCountOfMedicaments() const;

    void SetCountOfMedicaments(size_t countOfMedicaments);

private:
    TModelGenerator(size_t countOfDays = 10, double marginPercentage = 0.1, double discount = 0.25);

    TModelGenerator(const TModelGenerator&) = delete;
    TModelGenerator& operator=(const TModelGenerator&) = delete;

private:
    int32_t CountOfDays;
    int32_t CurrentDay;
    size_t CountOfMedicaments = 0;
    double MarginPercentage;
    double Discount;
    std::mt19937 RandGen;
    std::vector<TMedicamentId> MedicamentsIds;
    std::vector<TRegularCustomer> RegularCustomers;
    double Profit;
    double Toll;
};

