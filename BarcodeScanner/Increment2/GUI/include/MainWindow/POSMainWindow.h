#ifndef POSMAINWINDOW_H
#define POSMAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include "ScanScreen/ScanScreen.h"
#include "OrderScreen/OrderScreen.h"
#include "ProductDescriptionScreen/ProductDescriptionScreen.h"
#include "BillScreen/BillScreen.h"
#include "POSController/POSController.h"

class POSMainWindow : public QMainWindow {
    Q_OBJECT
private:
    QStackedWidget* screens = nullptr;
    QPushButton* scanButton = nullptr;
    QPushButton* orderButton = nullptr;
    QPushButton* billButton = nullptr;
    QWidget* dashboardPage = nullptr;
    ScanScreen* scanScreen = nullptr;
    OrderScreen* orderScreen = nullptr;
    ProductDescriptionScreen* descriptionScreen = nullptr;
    BillScreen* billScreen = nullptr;
    POSController* controller = nullptr;

public:
    enum ScreenIndex { DASHBOARD = 0, SCAN = 1, ORDER = 2, DESCRIPTION = 3, BILL = 4 };
    explicit POSMainWindow(POSController* controller, QWidget* parent = nullptr)
        : QMainWindow(parent), controller(controller) { setupMainWindow(); }

    void setupMainWindow();
    void showDashboard();
    void navigateToScreen(int screenIndex);

public slots:
    void handleScanNavigation();
    void handleOrderNavigation();
    void handleBillNavigation();
};

#endif // POSMAINWINDOW_H