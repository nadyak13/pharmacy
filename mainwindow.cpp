#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QApplication>
#include <QDesktopWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QLineEdit>
#include <iostream>
#include <QGroupBox>
#include <QComboBox>
#include <QGridLayout>
#include <QInputDialog>
#include <functional>
#include "string_helpers.h"

MainWindow::MainWindow(QWidget* parent)
      : QMainWindow(parent)
      , StartButton(std::make_unique<QPushButton>("Старт", this))
      , NextDayButton(std::make_unique<QPushButton>("Следующий день", this))
      , GoToLastDayButton(std::make_unique<QPushButton>("Закончить моделирование", this))
      , ProfitLabel(std::make_unique<QLabel>(this))
      , TollLabel(std::make_unique<QLabel>(this))
      , WarehouseTableWidget(std::make_unique<QTableWidget>(this))
      , OrdersTableWidget(std::make_unique<QTableWidget>(this))
      , ProcessedApplicationsTableWidget(std::make_unique<QTableWidget>(this))
      , NotProcessedApplicationsTableWidget(std::make_unique<QTableWidget>(this))
      , CountOfDaysLabel(std::make_unique<QLabel>(this))
      , MarginPercentageLabel(std::make_unique<QLabel>(this))
      , DiscountLabel(std::make_unique<QLabel>(this))
      , CountOfMedicamentsLabel(std::make_unique<QLabel>(this))
      , CurrentDayLabel(std::make_unique<QLabel>(this))
      , EndLabel(std::make_unique<QLabel>(this))
      , ProcessedApplicationsTitleLabel(std::make_unique<QLabel>(this))
      , NotProcessedApplicationsTitleLabel(std::make_unique<QLabel>(this))
      , WarehouseTitleLabel(std::make_unique<QLabel>(this))
      , OrdersTitleLabel(std::make_unique<QLabel>(this)) {
    CreateWarehouseTableWidget();
    CreateOrdersTableWidget();
    CreateProcessedApplicationsTableWidget();
    CreateNotProcessedApplicationsTableWidget();

    CreateProcessedApplicationsTitleLabel();
    CreateNotProcessedApplicationsTitleLabel();
    CreateWarehouseTitleLabel();
    CreateOrdersTitleLabel();

    StartButton->setGeometry(900, 10, 200, 50);
    connect(StartButton.get(), SIGNAL (released()), this, SLOT (HandleStartButton()));

    NextDayButton->setGeometry(0, 50, 200, 50);
    connect(NextDayButton.get(), SIGNAL (released()), this, SLOT (HandleNextDayButton()));
    GoToLastDayButton->setGeometry(0, 50, 200, 50);
    connect(GoToLastDayButton.get(), SIGNAL (released()), this, SLOT (HandleGoToLastDayButton()));
}

void MainWindow::CreateCountOfDaysLabel(size_t countOfDays) {
    CountOfDaysLabel->setText(("Продолжительность моделирования: " + ToString(countOfDays)).c_str());
    CountOfDaysLabel->setGeometry(1150, 10, 400, 50);
}

void MainWindow::CreateMarginPercentageLabel(double marginPercentage) {
    MarginPercentageLabel->setText(("Величина розничной наценки: " + ToString(marginPercentage)).c_str());
    MarginPercentageLabel->setGeometry(1150, 30, 400, 50);
}

void MainWindow::CreateDiscountLabel(double discount) {
    DiscountLabel->setText(("Скидка: " + ToString(discount)).c_str());
    DiscountLabel->setGeometry(1150, 50, 400, 50);
}

void MainWindow::CreateProfitLabel(double profit) {
    ProfitLabel->setText(("Выручка: " + ToString(profit)).c_str());
    ProfitLabel->setGeometry(1150, 70, 400, 50);
}

void MainWindow::CreateTollLabel(double toll) {
    TollLabel->setText(("Потери: " + ToString(toll)).c_str());
    TollLabel->setGeometry(1150, 90, 400, 50);
}

void MainWindow::CreateCurrentDayLabel(int32_t currentDay) {
    CurrentDayLabel->setText(("Текущий день: " + ToString(currentDay)).c_str());
    CurrentDayLabel->setGeometry(1150, 110, 400, 50);
}

void MainWindow::CreateCountOfMedicamentsLabel(size_t countOfMedicaments) {
    CountOfMedicamentsLabel->setText(("Кол-во лекарств: " + ToString(countOfMedicaments)).c_str());
    CountOfMedicamentsLabel->setGeometry(1150, 130, 400, 50);
}

void MainWindow::CreateEndLabel() {
    EndLabel->setText("Моделирование окончено!");
    EndLabel->setStyleSheet("QLabel { color : red; }");
    EndLabel->setGeometry(1150, 150, 400, 50);
}

void MainWindow::CreateProcessedApplicationsTitleLabel() {
    ProcessedApplicationsTitleLabel->setText("Выполненные заявки");
    ProcessedApplicationsTitleLabel->setGeometry(1100, 350, 200, 50);
}

void MainWindow::CreateNotProcessedApplicationsTitleLabel() {
    NotProcessedApplicationsTitleLabel->setText("Текущие заявки");
    NotProcessedApplicationsTitleLabel->setGeometry(1100, 550, 200, 50);
}

void MainWindow::CreateWarehouseTitleLabel() {
    WarehouseTitleLabel->setText("Состояние склада");
    WarehouseTitleLabel->setGeometry(350, 0, 400, 20);
}

void MainWindow::CreateOrdersTitleLabel() {
    OrdersTitleLabel->setText("Выполненные заказы");
    OrdersTitleLabel->setGeometry(350, 375, 400, 20);
}

void MainWindow::ReadInfoForStart() {
    CreateDialogWindow(
        "Введите продолжительность моделирования (число дней от 10 до 25)",
        [&](const std::string& inputLine) {
            int32_t value = FromString<int32_t>(inputLine);
            if (!(value >= 10 && value <= 25)) {
                return false;
            }

            TModelGenerator::Instance().SetCountOfDays(value);
            std::cout << "Count of days was set: " << value << std::endl;

            CreateCountOfDaysLabel(static_cast<size_t>(value));
            return true;
        },
        "20"
    );

    CreateDialogWindow(
        "Введите кол-во раличных лекарств",
        [&](const std::string& inputLine) {
            size_t value = FromString<size_t>(inputLine);
            if (!(value >= 15 && value <= 35)) {
                return false;
            }
            TModelGenerator::Instance().SetCountOfMedicaments(value);
            std::cout << "Count of medicaments was set: " << value << std::endl;

            CreateCountOfMedicamentsLabel(value);
            return true;
        },
        "30"
    );

    CreateDialogWindow(
        "Введите величину розничной наценки (в процентах)",
        [&](const std::string& inputLine) {
            double value = FromString<double>(inputLine);
            if (!(value >= 0)) {
                return false;
            }

            TModelGenerator::Instance().SetMarginPercentage(value / 100);
            std::cout << "Margin Percentage was set: " << value << std::endl;

            CreateMarginPercentageLabel(value);
            return true;
        },
        "50"
    );

    CreateDialogWindow(
        "Введите размер скидки (в процентах)",
        [&](const std::string& inputLine) {
            double value = FromString<double>(inputLine);
            if (!(value >= 0)) {
                return false;
            }

            TModelGenerator::Instance().SetDiscount(value);
            std::cout << "Discount was set: " << value << std::endl;

            CreateDiscountLabel(value);
            return true;
        },
        "3"
   );

}

void MainWindow::CreateDialogWindow(
        const std::string& title,
        std::function<bool(const std::string&)> && callback,
        const std::string& defaultValue) {
    std::unique_ptr<QInputDialog> dialogWindow = std::make_unique<QInputDialog>();
    dialogWindow->resize(400, 100);
    dialogWindow->setLabelText(title.c_str());
    dialogWindow->setTextValue(defaultValue.c_str());
    dialogWindow->exec();

    while (true) {
        const std::string& inputLine = dialogWindow->textValue().toUtf8().constData();
        if (callback(inputLine)) {
            break;
        }
    }
}

void MainWindow::CreateWarehouseTableWidget() {
    WarehouseTableWidget->setRowCount(15);
    WarehouseTableWidget->setColumnCount(9);
    WarehouseTableHeader << "Название" << "Тип" << "Доза" << "Группа" << "Оптовая цена" << "Срок хранения" << "Кол-во" << "Изготовлено" << "Годен до";
    WarehouseTableWidget->setHorizontalHeaderLabels(WarehouseTableHeader);
    WarehouseTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    WarehouseTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    WarehouseTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    WarehouseTableWidget->setShowGrid(false);
    WarehouseTableWidget->setStyleSheet("QTableView {selection-background-color: grey;}");
    WarehouseTableWidget->setGeometry(0, 25, 800, 350);

    connect(WarehouseTableWidget.get(), SIGNAL(cellDoubleClicked (int, int)), this, SLOT() );
}

void MainWindow::CreateOrdersTableWidget() {
    OrdersTableWidget->setRowCount(1);
    OrdersTableWidget->setColumnCount(6);
    OrdersTableHeader << "Дата заказа" << "Номер телефона" << "Постоянный покупатель" << "Название товара" << "Тип" << "Доза" << "Кол-во";
    OrdersTableWidget->setHorizontalHeaderLabels(OrdersTableHeader);
    OrdersTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    OrdersTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    OrdersTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    OrdersTableWidget->setShowGrid(false);
    OrdersTableWidget->setStyleSheet("QTableView {selection-background-color: grey;}");
    OrdersTableWidget->setGeometry(0, 400, 800, 350);

    connect(OrdersTableWidget.get(), SIGNAL( cellDoubleClicked (int, int) ),
            this, SLOT() );
}

void MainWindow::CreateProcessedApplicationsTableWidget() {
    ProcessedApplicationsTableWidget->setRowCount(1);
    ProcessedApplicationsTableWidget->setColumnCount(4);
    ProcessedApplicationsTableHeader << "Название" << "Тип" << "Доза" << "Кол-во";
    ProcessedApplicationsTableWidget->setHorizontalHeaderLabels(ProcessedApplicationsTableHeader);
    ProcessedApplicationsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ProcessedApplicationsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ProcessedApplicationsTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ProcessedApplicationsTableWidget->setShowGrid(false);
    ProcessedApplicationsTableWidget->setStyleSheet("QTableView {selection-background-color: grey;}");
    ProcessedApplicationsTableWidget->setGeometry(900, 400, 500, 150);

    connect(ProcessedApplicationsTableWidget.get(), SIGNAL( cellDoubleClicked (int, int) ),
            this, SLOT() );
}


void MainWindow::CreateNotProcessedApplicationsTableWidget() {
    NotProcessedApplicationsTableWidget->setRowCount(1);
    NotProcessedApplicationsTableWidget->setColumnCount(5);
    NotProcessedApplicationsTableHeader << "Название" << "Тип" << "Доза" << "Кол-во" << "Дата выполнения";
    NotProcessedApplicationsTableWidget->setHorizontalHeaderLabels(NotProcessedApplicationsTableHeader);
    NotProcessedApplicationsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    NotProcessedApplicationsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    NotProcessedApplicationsTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    NotProcessedApplicationsTableWidget->setShowGrid(false);
    NotProcessedApplicationsTableWidget->setStyleSheet("QTableView {selection-background-color: grey;}");
    NotProcessedApplicationsTableWidget->setGeometry(900, 600, 500, 150);

    connect(NotProcessedApplicationsTableWidget.get(), SIGNAL( cellDoubleClicked (int, int) ),
            this, SLOT() );
}

void MainWindow::UpdateWarehouseTableData() {
    int i = 0;
    for (const auto& med : ComputerManager.GetMedicamentsFromWarehouse()) {
        for (const auto& party : med.second.GetParties()) {
            WarehouseTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromUtf8(med.first.MedName.c_str())));
            WarehouseTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromUtf8(ToString(med.first.Type).c_str())));
            WarehouseTableWidget->setItem(i, 2, new QTableWidgetItem(
                QString::fromUtf8((ToString(med.first.Dose.GetValue()) + " " + ToString(med.first.Dose.GetUnitOfMeasure())).c_str())));
            WarehouseTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromUtf8(ToString(med.second.GetGroup()).c_str())));
            WarehouseTableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromUtf8(ToString(med.second.GetTradePrice()).c_str())));
            WarehouseTableWidget->setItem(i, 5, new QTableWidgetItem(QString::fromUtf8(ToString(med.second.GetStorageLife()).c_str())));
            WarehouseTableWidget->setItem(i, 6, new QTableWidgetItem(QString::fromUtf8(ToString(med.second.GetCount()).c_str())));
            const auto& partyManufactoreDate = ToString(party.second.GetDateOfManufacture().GetDaysFromStart());
            const auto& partyExpirationDate = ToString(party.second.GetDateOfExpiration().GetDaysFromStart());
            WarehouseTableWidget->setItem(i, 7, new QTableWidgetItem(QString::fromUtf8(partyManufactoreDate.c_str())));
            WarehouseTableWidget->setItem(i, 8, new QTableWidgetItem(QString::fromUtf8(partyExpirationDate.c_str())));
            ++i;
        }
    }
}

void MainWindow::UpdateOrdersTableData() {
    int i = 0;
    OrdersTableWidget->setRowCount(0);
    for (const auto& orders : ComputerManager.GetProcessedOrders()) {
        for (const auto& order : orders.Orders) {
            for (const auto& good : order.GetGoods()) {
                OrdersTableWidget->setRowCount(i + 1);

                OrdersTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromUtf8(ToString(orders.Date.GetDaysFromStart()).c_str())));
                OrdersTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromUtf8(ToString(order.GetTelephoneNumber()).c_str())));
                OrdersTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromUtf8(ToString(order.HasDiscountCardNumber()).c_str())));
                OrdersTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromUtf8(good.GetMedId().MedName.c_str())));
                OrdersTableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromUtf8(ToString(good.GetMedId().Type).c_str())));
                OrdersTableWidget->setItem(i, 5, new QTableWidgetItem(
                                                     QString::fromUtf8((ToString(good.GetMedId().Dose.GetValue()) + " " + ToString(good.GetMedId().Dose.GetUnitOfMeasure())).c_str())));
                OrdersTableWidget->setItem(i, 6, new QTableWidgetItem(QString::fromUtf8(ToString(good.GetCount()).c_str())));
                ++i;
            }
        }
    }
}

void MainWindow::UpdateProcessedApplicationsTableData() {
    int i = 0;
    ProcessedApplicationsTableWidget->setRowCount(0);
    for (const auto& application : ComputerManager.GetProcessedApplications()) {
        ProcessedApplicationsTableWidget->setRowCount(i + 1);

        ProcessedApplicationsTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromUtf8(application.GetMedId().MedName.c_str())));
        ProcessedApplicationsTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromUtf8(ToString(application.GetMedId().Type).c_str())));
        ProcessedApplicationsTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromUtf8((ToString(application.GetMedId().Dose.GetValue())
            + " " + ToString(application.GetMedId().Dose.GetUnitOfMeasure())).c_str())));
        ProcessedApplicationsTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromUtf8(ToString(application.GetCount()).c_str())));
        ++i;
    }
}

void MainWindow::UpdateNotProcessedApplicationsTableData() {
    int i = 0;
    NotProcessedApplicationsTableWidget->setRowCount(0);
    for (const auto& application : ComputerManager.GetNotProcessedApplications()) {
        NotProcessedApplicationsTableWidget->setRowCount(i + 1);

        NotProcessedApplicationsTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromUtf8(application.GetMedId().MedName.c_str())));
        NotProcessedApplicationsTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromUtf8(ToString(application.GetMedId().Type).c_str())));
        NotProcessedApplicationsTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromUtf8((ToString(application.GetMedId().Dose.GetValue())
                                                                                                + " " + ToString(application.GetMedId().Dose.GetUnitOfMeasure())).c_str())));
        NotProcessedApplicationsTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromUtf8(ToString(application.GetCount()).c_str())));
        NotProcessedApplicationsTableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromUtf8(ToString(application.GetExecutionDate().GetDaysFromStart()).c_str())));
        ++i;
    }
}

void MainWindow::HandleStartButton() {
    EndLabel->clear();
    ReadInfoForStart();
    ComputerManager.Start();
    CreateCurrentDayLabel(TModelGenerator::Instance().GetCurrentDay().GetDaysFromStart());
    WarehouseTableWidget->setRowCount(static_cast<int>(TModelGenerator::Instance().GetCountOfMedicaments()));
    UpdateWarehouseTableData();
    UpdateOrdersTableData();
    UpdateProcessedApplicationsTableData();
    UpdateNotProcessedApplicationsTableData();

    StartButton->setText("Еще раз");

    NextDayButton->setGeometry(900, 70, 200, 50);
    GoToLastDayButton->setGeometry(900, 130, 200, 50);
    CreateProfitLabel(TModelGenerator::Instance().GetProfit());
    CreateTollLabel(TModelGenerator::Instance().GetToll());
}

void MainWindow::HandleNextDayButton() {
    if (!TModelGenerator::Instance().IsEndOfSimulation()) {
        ComputerManager.NextDay();
        CreateCurrentDayLabel(TModelGenerator::Instance().GetCurrentDay().GetDaysFromStart());
        CreateProfitLabel(TModelGenerator::Instance().GetProfit());
        CreateTollLabel(TModelGenerator::Instance().GetToll());
        UpdateWarehouseTableData();
        UpdateOrdersTableData();
        UpdateProcessedApplicationsTableData();
        UpdateNotProcessedApplicationsTableData();
    } else {
        CreateEndLabel();
    }
}

void MainWindow::HandleGoToLastDayButton() {
    while (TModelGenerator::Instance().GetCurrentDay().GetDaysFromStart() < TModelGenerator::Instance().GetCountOfDays()) {
        HandleNextDayButton();
    }
    HandleNextDayButton();
}
