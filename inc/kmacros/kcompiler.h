#ifndef KCOMPILER_H
#define KCOMPILER_H

/*
    This is the private header for the KMacros.

    This header contains all defines connected with compilers

    Do not include it directly

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com
    LICENCE: GPL3
*/

#ifndef KMACROS_H
#error "Never include <kmacros/kcompiler.h> directly, use <kmacros/kmacros.h> instead."
#endif

#include "kcompiler-detect.h"

/* include compiler dependend defines  */
#ifdef KCOMPILER_CLANG
#include "kcompiler-clang.h"
#elif defined(KCOMPILER_GCC)
#include "kcompiler-gcc.h"
#elif defined(KCOMPILER_UNKNOWN)
#include "kcompiler-unknown.h"
#endif

#endif
