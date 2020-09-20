#ifndef KMACROS_ISOC_H
#define KMACROS_ISOC_H

/*
    This is the private header for the KMacros.

    This file contains macros compatible with ISO C so here gnu C is forbidden
    Here put only macros which can be better, safer etc ... with gnu C

    Do not include it directly

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com
    LICENCE: GPL3
*/

#ifndef KMACROS_H
#error "Never include <kmacros/kmacros-isoc.h> directly, use <kmacros/kmacros.h> instead."
#endif

/* Private macros you should use KMIN and MAX instead */
#define KMIN2(a, b)          ((a) <= (b) ? (a) : (b))
#define KMIN3(a, b, c)       (KMIN2(a, b) <= (c) ? KMIN2(a, b) : (c))
#define KMIN4(a, b, c, d)    (KMIN3(a, b, c) <= (d) ? KMIN3(a, b, c) : (d))
#define KMIN5(a, b, c, d, e) (KMIN4(a, b, c, d) <= (e) ? KMIN3(a, b, c, d) : (e))

#define KMAX2(a, b)          ((a) >= (b) ? (a) : (b))
#define KMAX3(a, b, c)       (KMAX2(a, b) >= (c) ? KMAX2(a, b) : (c))
#define KMAX4(a, b, c, d)    (KMAX3(a, b, c) >= (d) ? KMAX3(a, b, c) : (d))
#define KMAX5(a, b, c, d, e) (KMAX4(a, b, c, d) >= (e) ? KMAX3(a, b, c, d) : (e))

/**
 * Returns min from at most 5 variables
 */
#define KMIN(...)            KCONCAT(KMIN, KNARGS(__VA_ARGS__))(__VA_ARGS__)

/**
 * Returns max from at most 5 variables
 */
#define KMAX(...)            KCONCAT(KMAX, KNARGS(__VA_ARGS__))(__VA_ARGS__)

#endif