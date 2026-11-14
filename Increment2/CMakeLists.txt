cmake_minimum_required(VERSION 3.16)
project(BarcodePOS_Increment2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets)

# ---- Increment 1 files are REUSED from ../Increment1 (not copied) ----
# TODO (Member 5): check these file names match your Increment1 folder exactly.
set(INC1_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/../BarcodeScanner/src/BarcodeScanner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../BarcodeScanner/src/BarcodeDecoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../BarcodeScanner/src/BMPFileHandler.cpp)
set(INC1_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../BarcodeScanner/include)
file(GLOB_RECURSE BACKEND_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Backend/src/*.cpp)
file(GLOB_RECURSE GUI_SRC ${CMAKE_CURRENT_SOURCE_DIR}/GUI/src/*.cpp
                          ${CMAKE_CURRENT_SOURCE_DIR}/GUI/include/*.h)

# ---- Backend library ----
add_library(pos_backend STATIC ${BACKEND_SRC} ${INC1_SRC})
target_include_directories(pos_backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Backend/include ${INC1_DIR})
target_compile_definitions(pos_backend PUBLIC POS_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Data/")
target_link_libraries(pos_backend PUBLIC Qt6::Core Qt6::Gui Qt6::Multimedia)

# ---- GUI application ----
add_executable(POSApp main.cpp ${GUI_SRC})
target_include_directories(POSApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/include
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/include/MainWindow
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/include/ScanScreen
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/include/OrderScreen
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/include/ProductDescriptionScreen
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI/include/BillScreen)
target_link_libraries(POSApp PRIVATE pos_backend Qt6::Widgets Qt6::MultimediaWidgets)

# ---- Backend unit tests (one executable per test file) ----
enable_testing()
file(GLOB TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Backend/*.cpp)
foreach(test_file ${TEST_SRC})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE pos_backend)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
