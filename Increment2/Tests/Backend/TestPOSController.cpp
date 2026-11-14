// Unit test for POSController (Member 5). Controller needs the other objects, so build them first.
#include <iostream>
#include "POSController/POSController.h"

int main()
{
    ProductManager pm; OrderManager om; BillManager bm; PaymentManager pay; CameraHandler cam;
    POSController controller(&pm, &om, &bm, &pay, &cam);
    // MEMBER 5: test handleProductDescription(), handleOrderRecording(), handleBillGeneration(), handlePayment()
    std::cout << "[TestPOSController] skeleton OK - add real tests\n";
    return 0;
}
