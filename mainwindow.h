#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include "computer_manager.h"
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void ReadInfoForStart();
    void CreateDialogWindow(
        const std::string& title,
        std::function<bool(const std::string&)> && callback,
        const std::string& defaultValue = "");
    void CreateCountOfDaysLabel(size_t countOfDays);
    void CreateMarginPercentageLabel(double marginPercentage);
    void CreateDiscountLabel(double discount);
    void CreateCountOfMedicamentsLabel(size_t countOfMedicaments);
    void CreateCurrentDayLabel(int32_t currentDay);
    void CreateProfitLabel(double profit);
    void CreateTollLabel(double toll);
    void CreateEndLabel();
    void CreateProcessedApplicationsTitleLabel();
    void CreateNotProcessedApplicationsTitleLabel();
    void CreateWarehouseTitleLabel();
    void CreateOrdersTitleLabel();

    void CreateWarehouseTableWidget();
    void CreateOrdersTableWidget();
    void CreateProcessedApplicationsTableWidget();
    void CreateNotProcessedApplicationsTableWidget();
    void UpdateWarehouseTableData();
    void UpdateOrdersTableData();
    void UpdateProcessedApplicationsTableData();
    void UpdateNotProcessedApplicationsTableData();
    void echoChanged(int index);

private slots:
    void HandleStartButton();
    void HandleNextDayButton();
    void HandleGoToLastDayButton();

private:
    std::unique_ptr<QPushButton> StartButton;
    std::unique_ptr<QPushButton> NextDayButton;
    std::unique_ptr<QPushButton> GoToLastDayButton;
    std::unique_ptr<QLabel> ProfitLabel;
    std::unique_ptr<QLabel> TollLabel;
    TComputerManager ComputerManager;
    std::unique_ptr<QTableWidget> WarehouseTableWidget;
    QStringList WarehouseTableHeader;
    std::unique_ptr<QTableWidget> OrdersTableWidget;
    QStringList OrdersTableHeader;
    std::unique_ptr<QTableWidget> ProcessedApplicationsTableWidget;
    QStringList ProcessedApplicationsTableHeader;
    std::unique_ptr<QTableWidget> NotProcessedApplicationsTableWidget;
    QStringList NotProcessedApplicationsTableHeader;
    std::unique_ptr<QLabel> CountOfDaysLabel;
    std::unique_ptr<QLabel> MarginPercentageLabel;
    std::unique_ptr<QLabel> DiscountLabel;
    std::unique_ptr<QLabel> CountOfMedicamentsLabel;
    std::unique_ptr<QLabel> CurrentDayLabel;
    std::unique_ptr<QLabel> EndLabel;
    std::unique_ptr<QLabel> ProcessedApplicationsTitleLabel;
    std::unique_ptr<QLabel> NotProcessedApplicationsTitleLabel;
    std::unique_ptr<QLabel> WarehouseTitleLabel;
    std::unique_ptr<QLabel> OrdersTitleLabel;
};

#endif // MAINWINDOW_H
