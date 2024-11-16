cmake_minimum_required(VERSION 3.10)

# Укажите имя проекта
project(USBDeviceList)

# Установите стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Укажите исполняемый файл
add_executable(Lab6 Main.cpp)

# Подключите библиотеку libusb-1.0
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

# Установите пути вручную, если необходимо
link_directories(/opt/homebrew/lib)
include_directories(/opt/homebrew/include)

# Добавьте библиотеки
target_include_directories(Lab6 PRIVATE ${LIBUSB_INCLUDE_DIRS})
target_link_libraries(Lab6 PRIVATE /opt/homebrew/lib/libusb-1.0.dylib)
