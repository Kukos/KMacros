#ifndef KMACROS_GNUC_H
#define KMACROS_GNUC_H

/*
    This is the private header for the KMacros.

    This file contains macros compatible with gnuC like typeof etc.
    Here put only macros which need gnu c to be better, safer etc ...

    Do not include it directly

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com
    LICENCE: GPL3
*/

#ifndef KMACROS_H
#error "Never include <kmacros/kmacros-gnuc.h> directly, use <kmacros/kmacros.h> instead."
#endif

#include "knargs.h"
#include "kpreprocessor.h"
#include "kmacros-common.h"

/* Private macros you should use KMIN and MAX instead */
#define KMIN2(a, b) \
    __extension__ \
    ({ \
        __typeof__(a) KVAR_ALMOST_UNIQUE_NAME(min2a) = (a); \
        __typeof__(b) KVAR_ALMOST_UNIQUE_NAME(min2b) = (b); \
        (void)(&KVAR_ALMOST_UNIQUE_NAME(min2a) - &KVAR_ALMOST_UNIQUE_NAME(min2b)); \
        KVAR_ALMOST_UNIQUE_NAME(min2a) <= KVAR_ALMOST_UNIQUE_NAME(min2b) ? KVAR_ALMOST_UNIQUE_NAME(min2a) : KVAR_ALMOST_UNIQUE_NAME(min2b); \
    })

#define KMIN3(a, b, c) \
    __extension__ \
    ({ \
        __typeof__(a) KVAR_ALMOST_UNIQUE_NAME(min3ab) = KMIN2(a, b); \
        __typeof__(c) KVAR_ALMOST_UNIQUE_NAME(min3c) = (c); \
        (void)(&KVAR_ALMOST_UNIQUE_NAME(min3ab) - &KVAR_ALMOST_UNIQUE_NAME(min3c)); \
        KVAR_ALMOST_UNIQUE_NAME(min3ab) <= KVAR_ALMOST_UNIQUE_NAME(min3c) ? KVAR_ALMOST_UNIQUE_NAME(min3ab) : KVAR_ALMOST_UNIQUE_NAME(min3c); \
    })

#define KMIN4(a, b, c, d) \
    __extension__ \
    ({ \
        __typeof__(a) KVAR_ALMOST_UNIQUE_NAME(min4abc) = KMIN3(a, b, c); \
        __typeof__(d) KVAR_ALMOST_UNIQUE_NAME(min4d) = (d); \
        (void)(&KVAR_ALMOST_UNIQUE_NAME(min4abc) - &KVAR_ALMOST_UNIQUE_NAME(min4d)); \
        KVAR_ALMOST_UNIQUE_NAME(min4abc) <= KVAR_ALMOST_UNIQUE_NAME(min4d) ? KVAR_ALMOST_UNIQUE_NAME(min4abc) : KVAR_ALMOST_UNIQUE_NAME(min4d); \
    })

#define KMIN5(a, b, c, d, e) \
    __extension__ \
    ({ \
        __typeof__(a) KVAR_ALMOST_UNIQUE_NAME(min5abcd) = KMIN4(a, b, c, d); \
        __typeof__(e) KVAR_ALMOST_UNIQUE_NAME(min5e) = (e); \
        (void)(&KVAR_ALMOST_UNIQUE_NAME(min5abcd) - &KVAR_ALMOST_UNIQUE_NAME(min5e)); \
        KVAR_ALMOST_UNIQUE_NAME(min5abcd) <= KVAR_ALMOST_UNIQUE_NAME(min5e) ? KVAR_ALMOST_UNIQUE_NAME(min5abcd) : KVAR_ALMOST_UNIQUE_NAME(min5e); \
    })

#define KMAX2(a, b) \
    __extension__ \
    ({ \
        __typeof__(a) KVAR_ALMOST_UNIQUE_NAME(max2a) = (a); \
        __typeof__(b) KVAR_ALMOST_UNIQUE_NAME(max2b) = (b); \
        (void)(&KVAR_ALMOST_UNIQUE_NAME(max2a) - &KVAR_ALMOST_UNIQUE_NAME(max2b)); \
        KVAR_ALMOST_UNIQUE_NAME(max2a) >= KVAR_ALMOST_UNIQUE_NAME(max2b) ? KVAR_ALMOST_UNIQUE_NAME(max2a) : KVAR_ALMOST_UNIQUE_NAME(max2b); \
    })

#define KMAX3(a, b, c) \
    __extension__ \
    ({ \
        __typeof__(a) KVAR_ALMOST_UNIQUE_NAME(max3ab) = KMAX2(a, b); \
        __typeof__(c) KVAR_ALMOST_UNIQUE_NAME(max3c) = (c); \
        (void)(&KVAR_ALMOST_UNIQUE_NAME(max3ab) - &KVAR_ALMOST_UNIQUE_NAME(max3c)); \
        KVAR_ALMOST_UNIQUE_NAME(max3ab) >= KVAR_ALMOST_UNIQUE_NAME(max3c) ? KVAR_ALMOST_UNIQUE_NAME(max3ab) : KVAR_ALMOST_UNIQUE_NAME(max3c); \
    })

#define KMAX4(a, b, c, d) \
    __extension__ \
    ({ \
        __typeof__(a) KVAR_ALMOST_UNIQUE_NAME(max4abc) = KMAX3(a, b, c); \
        __typeof__(d) KVAR_ALMOST_UNIQUE_NAME(max4d) = (d); \
        (void)(&KVAR_ALMOST_UNIQUE_NAME(max4abc) - &KVAR_ALMOST_UNIQUE_NAME(max4d)); \
        KVAR_ALMOST_UNIQUE_NAME(max4abc) >= KVAR_ALMOST_UNIQUE_NAME(max4d) ? KVAR_ALMOST_UNIQUE_NAME(max4abc) : KVAR_ALMOST_UNIQUE_NAME(max4d); \
    })

#define KMAX5(a, b, c, d, e) \
    __extension__ \
    ({ \
        __typeof__(a) KVAR_ALMOST_UNIQUE_NAME(max5abcd) = KMAX4(a, b, c, d); \
        __typeof__(e) KVAR_ALMOST_UNIQUE_NAME(max5e) = (e); \
        (void)(&KVAR_ALMOST_UNIQUE_NAME(max5abcd) - &KVAR_ALMOST_UNIQUE_NAME(max5e)); \
        KVAR_ALMOST_UNIQUE_NAME(max5abcd) >= KVAR_ALMOST_UNIQUE_NAME(max5e) ? KVAR_ALMOST_UNIQUE_NAME(max5abcd) : KVAR_ALMOST_UNIQUE_NAME(max5e); \
    })

/**
 * Returns min from at most 5 variables
 */
#define KMIN(...)            KCONCAT(KMIN, KNARGS(__VA_ARGS__))(__VA_ARGS__)

/**
 * Returns max from at most 5 variables
 */
#define KMAX(...)            KCONCAT(KMAX, KNARGS(__VA_ARGS__))(__VA_ARGS__)

#endif
