#pragma once

#include <string>
#include <optional>
#include <vector>
#include "med_in_order.h"
#include "regular_customer.h"

class TOrder {
public:

    uint64_t GetTelephoneNumber() const;
    void SetTelephoneNumber(uint64_t number);

    std::string GetAddress() const;
    void SetAddress(const std::string& address);

    bool HasDiscountCardNumber() const;

    void SetCustomerInfo(const TRegularCustomer& customer);

    std::optional<uint64_t> GetDiscountCardNumber() const;
    void SetDiscountCardNumber(uint64_t number);

    std::vector<TMedInOrder> GetGoods() const;

    void AddGood(const TMedInOrder& good);

private:
    uint64_t TelephoneNumber;
    std::string Address;
    std::optional<uint64_t> DiscountCardNumber;
    std::vector<TMedInOrder> Goods;
};


namespace std {
    template <>
    struct hash<TOrder> {
        size_t operator()(const TOrder &order) const;
    };
}

bool operator==(const TOrder& lhs, const TOrder& rhs);
