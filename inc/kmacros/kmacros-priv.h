#ifndef KMACROS_PRIV_H
#define KMACROS_PRIV_H

/*
    This is the private header for the KMacros.

    Do not include it directly

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com
    LICENCE: GPL3
*/

#ifndef KMACROS_H
#error "Never include <kmacros/kmacros-priv.h> directly, use <kmacros/kmacros.h> instead."
#endif

#include "kcompiler-detect.h"

#ifdef KCOMPILER_GNUC
#include "kmacros-gnuc.h"
#else
#include "kmacros-isoc.h"
#endif

#include "kmacros-common.h"

#endif
