#include "regular_customer.h"

TRegularCustomer::TRegularCustomer(
        const std::string& name,
        const std::string& address,
        uint64_t discountCardNumber,
        uint64_t telephoneNumber)
    : Name(name)
    , Address(address)
    , DiscountCardNumber(discountCardNumber)
    , TelephoneNumber(telephoneNumber)
{}

    
void TRegularCustomer::AddRegularMedicaments(const TRegularMedicament& regularMedicament) {
    RegularMedicaments.push_back(regularMedicament);
}
    

uint64_t TRegularCustomer::GetTelephoneNumber() const {
    return TelephoneNumber;
}

std::string TRegularCustomer::GetAddress() const {
    return Address;
}

uint64_t TRegularCustomer::GetDiscountCardNumber() const {
    return DiscountCardNumber;
}

std::vector<TRegularMedicament> TRegularCustomer::GetRegularMedicaments() const {
    return RegularMedicaments;
}
