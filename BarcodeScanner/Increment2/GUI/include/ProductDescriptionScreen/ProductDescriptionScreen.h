#ifndef PRODUCTDESCRIPTIONSCREEN_H
#define PRODUCTDESCRIPTIONSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QComboBox>
#include <QString>
#include "Models/Product.h"
#include "POSController/POSController.h"

/*
 * ============================================================
 *  ProductDescriptionScreen
 *  Product description screen (read-only product details).
 * ------------------------------------------------------------
 *  WHO WRITES WHAT (function ownership):
 *    Member 4 : setupProductDescriptionScreen(), displayProductDetails(), handleCloseDescription() [EXTRA]
 *  Pre-written (getters/constructors): already done, don't touch.
 *  Rule: only edit the function bodies marked with YOUR member number.
 * ============================================================
 */

class ProductDescriptionScreen : public QWidget {
    Q_OBJECT
private:
    QLabel* productNameLabel = nullptr;
    QLabel* barcodeLabel = nullptr;
    QLabel* priceLabel = nullptr;
    QLabel* unitLabel = nullptr;
    QLabel* stockLabel = nullptr;
    QLabel* taxLabel = nullptr;
    QLabel* discountLabel = nullptr;
    QPushButton* closeButton = nullptr;
    POSController* controller = nullptr;

public:
    // ---------- PRE-WRITTEN (do not edit) ----------
    explicit ProductDescriptionScreen(POSController* controller, QWidget* parent = nullptr)
        : QWidget(parent), controller(controller) { setupProductDescriptionScreen(); }

    // ---------- ASSIGNED FUNCTIONS (declared here, written in the .cpp) ----------
    void setupProductDescriptionScreen();   // Member 4
    void displayProductDetails(const Product& product);   // Member 4

public slots:
    void handleCloseDescription();   // Member 4 (EXTRA)
};

#endif // PRODUCTDESCRIPTIONSCREEN_H
