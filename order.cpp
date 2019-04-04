#include "order.h"

uint64_t TOrder::GetTelephoneNumber() const {
    return TelephoneNumber;
}

void TOrder::SetTelephoneNumber(uint64_t number) {
    TelephoneNumber = number;
}

std::string TOrder::GetAddress() const {
    return Address;
}

void TOrder::SetAddress(const std::string& address) {
    Address = address;
}

bool TOrder::HasDiscountCardNumber() const {
    return DiscountCardNumber != std::nullopt;
}

std::optional<uint64_t> TOrder::GetDiscountCardNumber() const {
    return DiscountCardNumber;
}

void TOrder::SetDiscountCardNumber(uint64_t number) {
    DiscountCardNumber = number;
}


void TOrder::SetCustomerInfo(const TRegularCustomer& customer) {
    SetTelephoneNumber(customer.GetTelephoneNumber());
    SetAddress(customer.GetAddress());
    SetDiscountCardNumber(customer.GetDiscountCardNumber());
}

std::vector<TMedInOrder> TOrder::GetGoods() const {
    return Goods;
}

void TOrder::AddGood(const TMedInOrder& good) {
    Goods.push_back(good);
}

namespace std {
    size_t hash<TOrder>::operator()(const TOrder &order) const {
        std::stringstream numSs;
        numSs << order.GetTelephoneNumber();
        return std::hash<std::string>()(order.GetAddress() + numSs.str());
    }
}

bool operator==(const TOrder& lhs, const TOrder& rhs) {
    return lhs.GetAddress() == rhs.GetAddress();
}
