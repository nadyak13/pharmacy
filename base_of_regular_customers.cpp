#include "base_of_regular_customers.h"
#include "model_generator.h"

#include <iostream>

void TBaseOfRegularCustomers::Init(const std::vector<TRegularCustomer>& data) {
    Data = data;
}

std::vector<TOrder> TBaseOfRegularCustomers::GetTodaysOrders() const {
    std::cout << "!" << std::endl;
    std::vector<TOrder> result;
    for (const auto& customer : Data) {
        TOrder order;
        order.SetTelephoneNumber(customer.GetTelephoneNumber());
        order.SetAddress(customer.GetAddress());
        order.SetDiscountCardNumber(customer.GetDiscountCardNumber());
        for (const auto& med : customer.GetRegularMedicaments()) {
            if (TModelGenerator::Instance().GetCurrentDay().GetDaysFromStart() % med.GetPeriod() == 1) {
                order.AddGood(TMedInOrder(med.GetMedName(), med.GetCount()));
            }
        }
        if (!order.GetGoods().empty()) {
            result.push_back(order);
        }
    }
    std::cout << "!" << std::endl;
    return result;
}

