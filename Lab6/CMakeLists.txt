cmake_minimum_required(VERSION 3.10)

project(Lab6)

# Используем pkg-config для поиска libusb
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

# Указываем пути для include и link
include_directories(${LIBUSB_INCLUDE_DIRS})
link_directories(${LIBUSB_LIBRARY_DIRS})

# Добавляем исполняемый файл
add_executable(my_program main.cpp)

# Линкуем с libusb
target_link_libraries(my_program ${LIBUSB_LIBRARIES})
