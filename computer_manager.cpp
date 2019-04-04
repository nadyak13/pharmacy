#include "computer_manager.h"
#include "mainwindow.h"
#include <iostream>

TComputerManager::TComputerManager()
    : Warehouse(std::make_shared<TMedicamentWarehouse>())
    , PharmFirm(std::make_shared<TPharmFirm>()) {
}

std::unordered_map<TMedicamentId, TMedicamentInfo> TComputerManager::GetMedicamentsFromWarehouse() const {
    return Warehouse->GetMedicaments();
}

void TComputerManager::Start() {
    TModelGenerator::Instance().StartModel();
    Warehouse->Init(TModelGenerator::Instance().GenerateStartWarehouseState(), PharmFirm);
    BaseOfRegularCustomers.Init(TModelGenerator::Instance().GenerateRegularCustomers());
    ProcessedOrders.clear();
    ProcessedApplications.clear();
    PharmFirm->Clear();
}

void TComputerManager::NextDay() {
    std::vector<TOrder> orders = TModelGenerator::Instance().GenerateOrders();
    const auto& regularOrders = BaseOfRegularCustomers.GetTodaysOrders();
    orders.insert(orders.end(), regularOrders.begin(), regularOrders.end());
    double toll = Warehouse->WriteOffOverdue();
    const auto& processApplcationsToday = PharmFirm->ProcessApplications();
    ProcessedApplications.insert(processApplcationsToday.begin(), processApplcationsToday.end());
    Warehouse->HandleCompletedApplications(processApplcationsToday);
    Warehouse->CheckMedicamentsCount();
    PharmFirm->PrintApplications();

    double profit = ProcessOrders(orders);
    TProcessedOrders processedOrdersToday;
    processedOrdersToday.Orders = orders;
    processedOrdersToday.Date = TModelGenerator::Instance().GetCurrentDay();
    ProcessedOrders.push_back(processedOrdersToday);
    TModelGenerator::Instance().UpdateProfit(profit);
    TModelGenerator::Instance().UpdateToll(toll);

    TModelGenerator::Instance().NextDay();
}

std::vector<TProcessedOrders> TComputerManager::GetProcessedOrders() const {
    return ProcessedOrders;
}

double TComputerManager::ProcessOrders(std::vector<TOrder>& orders) {
    double res = 0;
    for (auto& order : orders) {
        for (auto& good : order.GetGoods()) {
            TMedicamentInfo& medInfo = Warehouse->GetMedicamentInfo(good.GetMedId());
            size_t realCount = 0;
            res += medInfo.DoBuy(
                    good.GetCount(),
                    TModelGenerator::Instance().GetMarginPercentage(),
                    TModelGenerator::Instance().GetCurrentDay(),
                    order.HasDiscountCardNumber() ? TModelGenerator::Instance().GetDiscount() : 0,
                    realCount);
            good.SetCount(realCount);
        }
    }
    return res;
}

std::set<TApplicationForMedicament> TComputerManager::GetProcessedApplications() const {
    return ProcessedApplications;
}

std::set<TApplicationForMedicament> TComputerManager::GetNotProcessedApplications() const {
    return PharmFirm->GetNotProcessedApplications();
}
