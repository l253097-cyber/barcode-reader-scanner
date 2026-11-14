#ifndef ORDERSCREEN_H
#define ORDERSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QComboBox>
#include <QString>
#include "Models/OrderDetail.h"
#include "POSController/POSController.h"

/*
 * ============================================================
 *  OrderScreen
 *  Order screen: customer info, order items table, add/remove/description/generate-bill.
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 3 : setupOrderScreen(), displayOrderItems(), handleAddProduct(), handleQuantityInput(), handleGenerateBillButton() [EXTRA]
 *    Member 4 : handleDescriptionButton(), handleRemoveProduct()
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

class OrderScreen : public QWidget {
    Q_OBJECT
private:
    QLineEdit* customerNameInput = nullptr;
    QLineEdit* customerContactInput = nullptr;
    QTableWidget* orderItemsTable = nullptr;
    QLineEdit* quantityInput = nullptr;
    QPushButton* addProductButton = nullptr;
    QPushButton* removeProductButton = nullptr;
    QPushButton* descriptionButton = nullptr;
    QPushButton* generateBillButton = nullptr;
    POSController* controller = nullptr;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    explicit OrderScreen(POSController* controller, QWidget* parent = nullptr)
        : QWidget(parent), controller(controller) { setupOrderScreen(); }

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    void setupOrderScreen();   // Member 3
    void displayOrderItems(const OrderDetail* items, int count);   // Member 3

public slots:
    void handleAddProduct();   // Member 3
    void handleQuantityInput(const QString& text);   // Member 3
    void handleDescriptionButton();   // Member 4
    void handleRemoveProduct();   // Member 4
    void handleGenerateBillButton();   // Member 3 (EXTRA)
};

#endif // ORDERSCREEN_H
