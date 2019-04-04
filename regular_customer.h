#pragma once

#include <string>
#include <vector>
#include "regular_medicament.h"

class TRegularCustomer {
public:
    TRegularCustomer(const std::string& name, const std::string& address, uint64_t discountCardNumber, uint64_t telephoneNumber);

    void AddRegularMedicaments(const TRegularMedicament& regularMedicament);

    uint64_t GetTelephoneNumber() const;

    std::string GetAddress() const;

    uint64_t GetDiscountCardNumber() const;

    std::vector<TRegularMedicament> GetRegularMedicaments() const;

private:
    std::string Name;
    std::string Address;
    uint64_t DiscountCardNumber;
    uint64_t TelephoneNumber;
    std::vector<TRegularMedicament> RegularMedicaments;
};
