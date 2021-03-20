cmake_minimum_required(VERSION 3.17)
project(usbhid_map C)

set(CMAKE_C_STANDARD 99)

add_executable(joystick-test EXCLUDE_FROM_ALL joystick-test.c usbhid_map.h usbhid_map.c)
add_executable(mouse-test EXCLUDE_FROM_ALL mouse-test.c usbhid_map.h usbhid_map.c)

add_library(usbhid_map usbhid_map.h usbhid_map.c)
target_include_directories(usbhid_map PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )