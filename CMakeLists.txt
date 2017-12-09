cmake_minimum_required(VERSION 3.5)
project(LogicMonitor)

set(CMAKE_CXX_STANDARD 11)

add_executable(LogicMonitor main.cpp common.cpp document.cpp include/document.h iface.cpp include/iface.h logic_device.cpp include/logic_device.h include/common.h clock.cpp include/clock.h not_device.cpp include/not_device.h carry4.cpp include/carry4.h and_not_device.cpp include/and_not_device.h and_not_device3.cpp include/and_not_device3.h and_not_device4.cpp include/and_not_device4.h or_not_device.cpp include/or_not_device.h or_not_device3.cpp include/or_not_device3.h or_not_device4.cpp include/or_not_device4.h full_adder.cpp include/full_adder.h carry64.cpp include/carry64.h no_devices.cpp include/no_devices.h adder64.cpp include/adder64.h and_device.cpp include/and_device.h or_device.cpp include/or_device.h)