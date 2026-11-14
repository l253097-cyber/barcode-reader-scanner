# Increment 2 - Who writes what (auto-generated from the skeleton)

GUI division = the FINAL list (5 members x 4 functions = 20). Functions marked EXTRA are declared in the UML
but are NOT in the final 20; they have a proposed owner so no file is left incomplete (team can drop/reassign).

## Member 1
### Backend
| File | Function | Note |
|---|---|---|
| Models/Product | updateStock() | official |
| Managers/ProductManager | findProductByBarcode() | official |
| Managers/ProductManager | findProductById() | official |
| Managers/ProductManager | getProductDescription() | official |
| Managers/ProductManager | checkAvailableQuantity() | official |
| Managers/ProductManager | deductStock() | official |
| Camera/CameraHandler | initializeCamera() | official |
| Camera/CameraHandler | checkCameraStatus() | official |
| Camera/CameraHandler | releaseCamera() | official |

### GUI
| File | Function | Note |
|---|---|---|
| MainWindow/POSMainWindow | setupMainWindow() | official |
| MainWindow/POSMainWindow | showDashboard() | official |
| MainWindow/POSMainWindow | navigateToScreen() | official |
| MainWindow/POSMainWindow | handleScanNavigation() | official |
| MainWindow/POSMainWindow | handleOrderNavigation() | EXTRA |
| MainWindow/POSMainWindow | handleBillNavigation() | EXTRA |

## Member 2
### Backend
| File | Function | Note |
|---|---|---|
| Models/Order | setOrderStatus() | official |
| Models/Order | setPaymentDetails() | official |
| Managers/OrderManager | createOrder() | official |
| Managers/OrderManager | addProductToOrder() | official |
| Managers/OrderManager | removeProductFromOrder() | official |
| Managers/OrderManager | updateProductQuantity() | official |
| Managers/OrderManager | calculateOrderSubtotal() | official |
| Managers/OrderManager | validateOrder() | official |
| FileHandlers/OrderDetailFileHandler | loadOrderDetails() | official |
| FileHandlers/OrderDetailFileHandler | parseOrderDetailRecord() | official |
| FileHandlers/OrderDetailFileHandler | serializeOrderDetailRecord() | official |

### GUI
| File | Function | Note |
|---|---|---|
| ScanScreen/ScanScreen | setupScanScreen() | official |
| ScanScreen/ScanScreen | startCameraPreview() | official |
| ScanScreen/ScanScreen | handleCaptureButton() | official |
| ScanScreen/ScanScreen | displayScanResult() | official |
| ScanScreen/ScanScreen | displayScanError() | EXTRA |

## Member 3
### Backend
| File | Function | Note |
|---|---|---|
| Models/Bill | setPaymentStatus() | official |
| Managers/BillManager | calculateSubtotal() | official |
| Managers/BillManager | calculateTotalDiscount() | official |
| Managers/BillManager | calculateTotalTax() | official |
| Managers/BillManager | calculatePayableAmount() | official |
| Managers/BillManager | generateBill() | official |
| Managers/PaymentManager | validatePayment() | official |
| Managers/PaymentManager | processPayment() | official |
| Managers/PaymentManager | updateOrderPaymentStatus() | official |
| FileHandlers/BillFileHandler | loadBills() | official |
| FileHandlers/BillFileHandler | parseBillRecord() | official |
| FileHandlers/BillFileHandler | serializeBillRecord() | official |

### GUI
| File | Function | Note |
|---|---|---|
| OrderScreen/OrderScreen | setupOrderScreen() | official |
| OrderScreen/OrderScreen | displayOrderItems() | official |
| OrderScreen/OrderScreen | handleAddProduct() | official |
| OrderScreen/OrderScreen | handleQuantityInput() | official |
| OrderScreen/OrderScreen | handleGenerateBillButton() | EXTRA |

## Member 4
### Backend
| File | Function | Note |
|---|---|---|
| Models/OrderDetail | setQuantity() | official |
| Managers/OrderDetailManager | addOrderDetail() | official |
| Managers/OrderDetailManager | getOrderDetails() | official |
| Managers/OrderDetailManager | findOrderDetail() | official |
| Managers/OrderDetailManager | updateOrderDetailQuantity() | official |
| Managers/OrderDetailManager | removeOrderDetail() | official |
| Camera/CameraHandler | captureFrame() | official |
| Camera/CameraHandler | convertFrameToImageData() | official |
| FileHandlers/OrderFileHandler | parseOrderRecord() | official |
| FileHandlers/OrderFileHandler | serializeOrderRecord() | official |

### GUI
| File | Function | Note |
|---|---|---|
| OrderScreen/OrderScreen | handleDescriptionButton() | official |
| OrderScreen/OrderScreen | handleRemoveProduct() | official |
| ProductDescriptionScreen/ProductDescriptionScreen | setupProductDescriptionScreen() | official |
| ProductDescriptionScreen/ProductDescriptionScreen | displayProductDetails() | official |
| ProductDescriptionScreen/ProductDescriptionScreen | handleCloseDescription() | EXTRA |

## Member 5 (integration)
### Backend
| File | Function | Note |
|---|---|---|
| FileHandlers/ProductFileHandler | loadProducts() | official |
| FileHandlers/ProductFileHandler | parseProductRecord() | official |
| FileHandlers/ProductFileHandler | saveProducts() | official |
| FileHandlers/ProductFileHandler | serializeProductRecord() | official |
| FileHandlers/OrderFileHandler | saveOrder() | official |
| FileHandlers/OrderFileHandler | loadOrders() | official |
| FileHandlers/OrderDetailFileHandler | saveOrderDetails() | official |
| FileHandlers/BillFileHandler | saveBill() | official |
| POSController/POSController | handleBarcodeScan() | official |
| POSController/POSController | handleProductDescription() | official |
| POSController/POSController | handleOrderRecording() | official |
| POSController/POSController | handleBillGeneration() | official |
| POSController/POSController | handlePayment() | official |

### GUI
| File | Function | Note |
|---|---|---|
| BillScreen/BillScreen | setupBillScreen() | official |
| BillScreen/BillScreen | displayBillDetails() | official |
| BillScreen/BillScreen | handlePaymentInput() | official |
| BillScreen/BillScreen | handleConfirmPayment() | official |
| BillScreen/BillScreen | displayPaymentStatus() | EXTRA |
| BillScreen/BillScreen | handlePrintOrCloseBill() | EXTRA |
