#ifndef KPREPROCESSOR_H
#define KPREPROCESSOR_H

/*
    This is the private header for the KMacros.

    This file defined some tricks connected with preprocessor

    Do not include it directly

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com
    LICENCE: GPL3
*/

#ifndef KMACROS_H
#error "Never include <kmacros/kpreprocessor.h> directly, use <kmacros/kmacros.h> instead."
#endif

/**
 * Create const char* from preprocesor token.
 * When token is a define then string will be a define name
 * When token is not a define is just a some chars including spaces (not C chars)
 * then string will be a const char* based on those chars
 *
 * Example: KTOSTRING_NAME(+) --> "+" KTOSTRING_NAME(a b c) --> "a b c"
 *
 */
#define KTOSTRING_NAME(x) #x

/**
 * Create const char* from preprocesor token.
 * When token is a define then string will be a define value expaned from defines chain
 * Some when we have define which has value from another define which has ... which has a value
 * Then this macro will create const char* from value
 *
 * When token is not a define is just a some chars including spaces (not C chars)
 * then string will be a const char* based on those chars.
 * So this is safe even if token is not a macro
 *
 * Example:
 * #define X 5
 * #define Y X
 * #define Z Y
 * KTOSTRING(Z) --> "5" KTOSTRING(Y) --> "5" KTOSTRING(X) --> "5"
 * KTOSTRING(+) --> "+"
 */
#define KTOSTRING(x)      KTOSTRING_NAME(x)

/**
 * Concatenate 2 tokens into 1.
 * It can be used to create some macro to check another macro based on some token
 * Please note that you need to use KTOSTRING macro to create const char* from tokens
 *
 * This macro does not expand value from macro
 *
 * Example:
 * KCONCAT_NAME(x, y) --> xy not "xy"
 *
 * #define XY 10
 * #define XZ 15
 *
 * int x = KCONCAT_NAME(X, Y) --> x = XY --> x = 10
 */
#define KCONCAT_NAME(x, y) x ## y

/**
 * Concatenate 2 tokens into 1.
 * It can be used to create some macro to check another macro based on some token
 * Please note that you need to use KTOSTRING macro to create const char* from tokens
 *
 * This macro expand value from macro chain. For more details please see KTOSTRING description
 *
 * Example:
 * KCONCAT(x, y) --> xy not "xy"
 *
 * #define X  10
 * #define Y  15
 *
 * int x = KCONCAT(X, Y) --> x = 1015
 */
#define KCONCAT(x, y)      KCONCAT_NAME(x, y)


/**
 * Create const char* from macro which shows as macro name and macro value
 *
 * Example:
 * #define X 10
 *
 * KMACRO_PRINT(X) --> "X = 10"
 */
#define KMACRO_PRINT(macro) #macro " = " KTOSTRING(macro)

#endif
