#pragma once
#include <stdint.h>
#include <QString>

typedef uint32_t u32;
typedef uint64_t u64;
typedef uint8_t  u8;

// https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html#Common-Predefined-Macros
static const QString settingsTimestamp = __TIMESTAMP__;

union Settings_s {
    using size = u64;

    size    raw{0};
    char    raw_byte[sizeof(size)];
    struct {
        size wordLength : 8;
        size wordLengthLimit : 8;
        size wordLengthRandom : 1;
        size preventTriplets : 1;
        size preventDiDu : 1;
        size multipleColumn : 1;

        size col2_k     : 1;
        size col2_g     : 1;
        size col3_s     : 1;
        size col3_z     : 1;
        size col4_t     : 1;
        size col4_d     : 1;
        size col5_n     : 1;
        size col6_h     : 1;
        size col6_b     : 1;
        size col6_p     : 1;
        size col7_m     : 1;
        size col8_y     : 1;
        size col9_r     : 1;
        size col10_w    : 1;

        size smallTsu : 1;  // sokuon
        size nn : 1;

        // phonetics settings
        size useDoubleVowelSign : 1;
        size useou : 1;
    };
};
