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

/*
 * ============================================================
 *  POSMainWindow
 *  Main window: dashboard + QStackedWidget navigation.
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 1 : setupMainWindow(), showDashboard(), navigateToScreen(), handleScanNavigation(), handleOrderNavigation() [EXTRA], handleBillNavigation() [EXTRA]
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

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
    // ---------- PRE-WRITTEN (do not edit) ----------
    enum ScreenIndex { DASHBOARD = 0, SCAN = 1, ORDER = 2, DESCRIPTION = 3, BILL = 4 };
    explicit POSMainWindow(POSController* controller, QWidget* parent = nullptr)
        : QMainWindow(parent), controller(controller) { setupMainWindow(); }

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    void setupMainWindow();   // Member 1
    void showDashboard();   // Member 1
    void navigateToScreen(int screenIndex);   // Member 1

public slots:
    void handleScanNavigation();   // Member 1
    void handleOrderNavigation();   // Member 1 (EXTRA)
    void handleBillNavigation();   // Member 1 (EXTRA)
};

#endif // POSMAINWINDOW_H
