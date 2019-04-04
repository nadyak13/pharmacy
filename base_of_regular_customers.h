#include "regular_customer.h"
#include "order.h"
#include <vector>


class TBaseOfRegularCustomers {
public:

    void Init(const std::vector<TRegularCustomer>& data);

    std::vector<TOrder> GetTodaysOrders() const;

private:
    std::vector<TRegularCustomer> Data;
};
