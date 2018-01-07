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
        src/adder64.cpp
        src/and_device.cpp
        src/and_not_device.cpp
        src/and_not_device3.cpp
        src/and_not_device4.cpp
        src/carry4.cpp
        src/carry64.cpp
        src/clock.cpp
        src/common.cpp
        src/document.cpp
        src/full_adder.cpp
        src/iface.cpp
        src/logic_device.cpp
    main.cpp
        src/no_devices.cpp
        src/not_device.cpp
        src/or_device.cpp
        src/or_not_device.cpp
        src/or_not_device3.cpp
        src/or_not_device4.cpp)
