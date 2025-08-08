//
// Created by Oleg Vrublevsky on 8/8/25.
//

#include "../../../Inc/stm/sys/Device.h"

namespace stm32::system::device {

    DeviceWaferCoordinates getDeviceWaferCoordinates() {
        auto* uidr = reinterpret_cast<const volatile uint32_t*>(0x1FFF'7590);
        return DeviceWaferCoordinates{
            static_cast<uint16_t>(*uidr & 0xFFFF),
            static_cast<uint16_t>((*uidr & (0xFFFF << 16)) >> 16),
        };
    }

    uint8_t getDeviceWaferNumber() {
        auto* uidr = reinterpret_cast<const volatile uint32_t*>(0x1FFF'7594);
        return static_cast<uint8_t>(*uidr & 0xFF);
    }

     const char* getDeviceLotNumber() {
        static char lotNumber[8];

        auto* uidr = reinterpret_cast<const volatile uint32_t*>(0x1FFF'7594);
        auto* uidr2 = reinterpret_cast<const volatile uint32_t*>(0x1FFF'7598);

        lotNumber[0] = static_cast<char>((*uidr >> 8) & 0xFF);
        lotNumber[1] = static_cast<char>((*uidr >> 16) & 0xFF);
        lotNumber[2] = static_cast<char>((*uidr >> 24) & 0xFF);
        lotNumber[3] = static_cast<char>(*uidr2 & 0xFF);
        lotNumber[4] = static_cast<char>((*uidr2 >> 8) & 0xFF);
        lotNumber[5] = static_cast<char>((*uidr2 >> 16) & 0xFF);
        lotNumber[6] = static_cast<char>((*uidr2 >> 24) & 0xFF);
        lotNumber[7] = '\0';

        return lotNumber;
    }

    uint16_t getDeviceFlashSize() {
        auto* fsdr = reinterpret_cast<const volatile uint32_t*>(0x1FFF'75E0);
        return static_cast<uint16_t>(*fsdr & 0xFFFF);
    }

    DevicePackage getDevicePackage() {
        auto* pdr = reinterpret_cast<const volatile uint32_t*>(0x1FFF'7500);
        return static_cast<DevicePackage>(*pdr & 0x1F);
    }

}