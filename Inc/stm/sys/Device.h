//
// Created by Oleg Vrublevsky on 8/8/25.
//

#pragma once
#include <cstdint>

namespace stm32::system::device {

    enum class DevicePackage : uint8_t {
        LQFP64 = 0,
        WLCSP64 = 1,
        LQFP100 = 2, //For all devices, LQFP80 for category 2 devices.
        WLCSP81 = 5, //For all devices, LQFP80 for category 3 devices.
        LQFP128 = 7, //or UFBGA121
        UFQFPN32 = 8,
        LQFP32 = 9,
        UFQFPN48 = 10,
        LQFP48 = 11,
        WLCSP49 = 12,
        UFBGA64 = 13,
        TFBGA100 = 14,
        LQFP80 = 17 //for category 4 devices ONLY
    };

    struct DeviceWaferCoordinates {
        uint16_t x, y;
    };

    [[nodiscard]] DeviceWaferCoordinates getDeviceWaferCoordinates();

    [[nodiscard]] const char* getDeviceLotNumber();

    [[nodiscard]] uint8_t getDeviceWaferNumber();

    //Returns device's flash size in KBytes.
    [[nodiscard]] uint16_t getDeviceFlashSize();

    [[nodiscard]] DevicePackage getDevicePackage();

}
