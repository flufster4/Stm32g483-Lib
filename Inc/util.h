#ifndef UTIL_H
#define UTIL_H

    typedef char int8_t;
    typedef short int16_t;
    typedef int int32_t;
    typedef long long int64_t;

    typedef unsigned char uint8_t;
    typedef unsigned short uint16_t;
    typedef unsigned int uint32_t;
    typedef unsigned long long uint64_t;

    typedef volatile unsigned char reg8_t;
    typedef volatile unsigned short reg16_t;
    typedef volatile unsigned int reg32_t;
    typedef volatile unsigned long long reg64_t;

    #ifndef __STDBOOL_H_
        #define bool _Bool
        #define true 1
        #define false 0
    #endif

#endif //UTIL_H
