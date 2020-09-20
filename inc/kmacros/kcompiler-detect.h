#ifndef KCOMPILER_DETECT_H
#define KCOMPILER_DETECT_H

/*
    This is the private header for the KMacros.
    It contains some logic for compiler detection

    KCOMPILER_GCC is defined when gcc has been used
    KCOMPILER_CLANG is defined when clang has been used
    KCOMPILER_UNKNOWN is defined when not gcc nor clang has been used
    KCOMPILER_GNUC is defined when compiler supports at least a subset of gnu C

    KCOMPILER_MAJOR_VERSION is a preprocessor int value i.e for gcc8 it will be 8
    KCOMPILER_MINOR_VERSION is a preprocessor int value i.e for gcc8.4 it will be 4

    Do not include it directly

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com
    LICENCE: GPL3
*/

#ifndef KMACROS_H
#error "Never include <kmacros/kcompiler-detect.h> directly, use <kmacros/kmacros.h> instead."
#endif

/* __GNUC__ is a gcc and gnuc define, so here order is important */
#ifdef __clang__

/* clang maybe with some gnu */
#define KCOMPILER_CLANG
#define KCOMPILER_MAJOR_VERSION __clang_major__
#define KCOMPILER_MINOR_VERSION __clang_minor__

#ifdef __GNUC__
#define KCOMPILER_GNUC
#endif /* #ifdef __GNUC__ */

#elif defined(__GNUC__)

/* gcc some for sure gnu */
#define KCOMPILER_GCC
#define KCOMPILER_GNUC
#define KCOMPILER_MAJOR_VERSION __GNUC__
#define KCOMPILER_MINOR_VERSION __GNUC_MINOR__

#else

/* unknown compiler maybe with gnu */
#define KCOMPILER_UNKNOWN
#define KCOMPILER_MAJOR_VERSION 0
#define KCOMPILER_MINOR_VERSION 0

#ifdef __GNUC__
#define KCOMPILER_GNUC
#endif /* #ifdef __GNUC__ */

#endif /* #ifdef __clang__ and #elif defined(__GNUC__) */

#endif /* include guard */
