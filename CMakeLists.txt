cmake_minimum_required(VERSION 3.5)
project(logic_monitor)

set(CMAKE_CXX_STANDARD 11)
include_directories(include)

add_executable(logic_monitor
    include/adder64.h
    include/and_device.h
    include/and_not_device.h
    include/and_not_device3.h
    include/and_not_device4.h
    include/carry4.h
    include/carry64.h
    include/clock.h
    include/common.h
    include/document.h
    include/full_adder.h
    include/iface.h
    include/logic_device.h
    include/no_devices.h
    include/not_device.h
    include/or_device.h
    include/or_not_device.h
    include/or_not_device3.h
    include/or_not_device4.h
    adder64.cpp
    and_device.cpp
    and_not_device.cpp
    and_not_device3.cpp
    and_not_device4.cpp
    carry4.cpp
    carry64.cpp
    clock.cpp
    common.cpp
    document.cpp
    full_adder.cpp
    iface.cpp
    logic_device.cpp
    main.cpp
    no_devices.cpp
    not_device.cpp
    or_device.cpp
    or_not_device.cpp
    or_not_device3.cpp
    or_not_device4.cpp)
