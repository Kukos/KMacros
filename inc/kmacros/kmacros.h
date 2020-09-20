#ifndef KMACROS_H
#define KMACROS_H

/* C11 has value 201112L */
#if __STDC_VERSION__ < 201112L
#error "At least C11 is required to compile code with KMacros!"
#endif

#include "kpreprocessor.h"
#include "kcompiler.h"
#include "kterminal-colors.h"
#include "kmacros-priv.h"
#include "kprimitives.h"
#include "knargs.h"
#include "kbits.h"

#endif
