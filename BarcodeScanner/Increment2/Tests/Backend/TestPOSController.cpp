// Unit test for POSController (Member 5).
#include <iostream>
#include "POSController/POSController.h"

int main()
{
    ProductManager pm; OrderManager om; BillManager bm; PaymentManager pay; CameraHandler cam;
    POSController controller(&pm, &om, &bm, &pay, &cam, nullptr, nullptr, nullptr);
    std::cout << "[TestPOSController] skeleton OK\n";
    return 0;
}