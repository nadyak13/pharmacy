#pragma once

#include "pharm_firm.h"
#include "medicament_warehouse.h"
#include "model_generator.h"
#include "base_of_regular_customers.h"
#include <iostream>
#include <memory>


class TMedicamentWarehouse;
class MainWindow;

struct TProcessedOrders {
    std::vector<TOrder> Orders;
    TDate Date;
};

class TComputerManager {
public:
    TComputerManager();

    void Start();

    void NextDay();

    double ProcessOrders(std::vector<TOrder>& orders);

    std::unordered_map<TMedicamentId, TMedicamentInfo> GetMedicamentsFromWarehouse() const;

    std::vector<TProcessedOrders> GetProcessedOrders() const;
    std::set<TApplicationForMedicament> GetProcessedApplications() const;
    std::set<TApplicationForMedicament> GetNotProcessedApplications() const;

private:
    std::shared_ptr<TMedicamentWarehouse> Warehouse;
    TBaseOfRegularCustomers BaseOfRegularCustomers;
    std::shared_ptr<TPharmFirm> PharmFirm;
    std::vector<TProcessedOrders> ProcessedOrders;
    std::set<TApplicationForMedicament> ProcessedApplications;
};
