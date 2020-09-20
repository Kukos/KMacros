#ifndef KPRIMITIVES_H
#define KPRIMITIVES_H

/*
    This is the private header for the KMacros.

    This header constains C11 Generic makro used to check primitive type

    Do not include it directly

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com
    LICENCE: GPL3
*/

#ifndef KMACROS_H
#error "Never include <kmacros/kprimitives.h> directly, use <kmacros/kmacros.h> instead."
#endif

/**
 * This enum represents all primitive types that can be deducted by _Generic
 * Please note that const, volatile, static are skipped, so const int is compatible with int
 *
 * You can store type in enum to use functions _FROM_ENUM later.
 * This is so useful when you have gnu extension.
 * You can use it in choose_expr because type == enum is const expr
 */
typedef enum KPRIMITIVES_ENUM
{
    KPRIMITIVES_ENUM_BOOL,
    KPRIMITIVES_ENUM_CHAR,
    KPRIMITIVES_ENUM_SIGNED_CHAR,
    KPRIMITIVES_ENUM_UNSIGNED_CHAR,
    KPRIMITIVES_ENUM_SHORT,
    KPRIMITIVES_ENUM_UNSIGNED_SHORT,
    KPRIMITIVES_ENUM_INT,
    KPRIMITIVES_ENUM_UNSIGNED_INT,
    KPRIMITIVES_ENUM_LONG,
    KPRIMITIVES_ENUM_UNSIGNED_LONG,
    KPRIMITIVES_ENUM_LONG_LONG,
    KPRIMITIVES_ENUM_UNSIGNED_LONG_LONG,
    KPRIMITIVES_ENUM_FLOAT,
    KPRIMITIVES_ENUM_DOUBLE,
    KPRIMITIVES_ENUM_LONG_DOUBLE,
    KPRIMITIVES_ENUM_NON_PRIMITIVE
} kprimitives_enum_t;

/**
 * Use this type to store printf format for primitive types
 */
typedef const char* kprimitives_pfmt_t;
#define KPRIMITIVES_PFMT_BOOL               "%u"
#define KPRIMITIVES_PFMT_CHAR               "%c"
#define KPRIMITIVES_PFMT_SIGNED_CHAR        "%c"
#define KPRIMITIVES_PFMT_UNSIGNED_CHAR      "%c"
#define KPRIMITIVES_PFMT_SHORT              "%hd"
#define KPRIMITIVES_PFMT_UNSIGNED_SHORT     "%hu"
#define KPRIMITIVES_PFMT_INT                "%d"
#define KPRIMITIVES_PFMT_UNSIGNED_INT       "%u"
#define KPRIMITIVES_PFMT_LONG               "%ld"
#define KPRIMITIVES_PFMT_UNSIGNED_LONG      "%lu"
#define KPRIMITIVES_PFMT_LONG_LONG          "lld"
#define KPRIMITIVES_PFMT_UNSIGNED_LONG_LONG "%llu"
#define KPRIMITIVES_PFMT_FLOAT              "%f"
#define KPRIMITIVES_PFMT_DOUBLE             "%lf"
#define KPRIMITIVES_PFMT_LONG_DOUBLE        "%Lf"
#define KPRIMITIVES_PFMT_NON_PRIMITIVE      "%p"

/**
 * Use this type to store name for primitive types
 * You can use it mostly for debug like print type name in macro
 */
typedef const char* kprimitives_name_t;
#define KPRIMITIVES_NAME_BOOL               "bool"
#define KPRIMITIVES_NAME_CHAR               "char"
#define KPRIMITIVES_NAME_SIGNED_CHAR        "signed char"
#define KPRIMITIVES_NAME_UNSIGNED_CHAR      "unsigned char"
#define KPRIMITIVES_NAME_SHORT              "short"
#define KPRIMITIVES_NAME_UNSIGNED_SHORT     "unsigned short"
#define KPRIMITIVES_NAME_INT                "int"
#define KPRIMITIVES_NAME_UNSIGNED_INT       "unsigned int"
#define KPRIMITIVES_NAME_LONG               "long"
#define KPRIMITIVES_NAME_UNSIGNED_LONG      "unsigned long"
#define KPRIMITIVES_NAME_LONG_LONG          "long long"
#define KPRIMITIVES_NAME_UNSIGNED_LONG_LONG "unsigned long long"
#define KPRIMITIVES_NAME_FLOAT              "float"
#define KPRIMITIVES_NAME_DOUBLE             "double"
#define KPRIMITIVES_NAME_LONG_DOUBLE        "long double"
#define KPRIMITIVES_NAME_NON_PRIMITIVE      "non-primitive"

/**
 * Use this macro to obtain kprimitives_enum_t from variable
 * This works like const expr
 */
#define KPRIMITIVES_GET_ENUM_FROM_VAR(var) \
    _Generic((var), \
             _Bool:              KPRIMITIVES_ENUM_BOOL, \
             char:               KPRIMITIVES_ENUM_CHAR, \
             signed char:        KPRIMITIVES_ENUM_SIGNED_CHAR, \
             unsigned char:      KPRIMITIVES_ENUM_UNSIGNED_CHAR, \
             short:              KPRIMITIVES_ENUM_SHORT, \
             unsigned short:     KPRIMITIVES_ENUM_UNSIGNED_SHORT, \
             int:                KPRIMITIVES_ENUM_INT, \
             unsigned int:       KPRIMITIVES_ENUM_UNSIGNED_INT, \
             long:               KPRIMITIVES_ENUM_LONG, \
             unsigned long:      KPRIMITIVES_ENUM_UNSIGNED_LONG, \
             long long:          KPRIMITIVES_ENUM_LONG_LONG, \
             unsigned long long: KPRIMITIVES_ENUM_UNSIGNED_LONG_LONG, \
             float:              KPRIMITIVES_ENUM_FLOAT, \
             double:             KPRIMITIVES_ENUM_DOUBLE, \
             long double:        KPRIMITIVES_ENUM_LONG_DOUBLE, \
             default:            KPRIMITIVES_ENUM_NON_PRIMITIVE \
    )

/**
 * Use this macro to obtain kprimitives_enum_t from type
 * This works like const expr
 */
#define KPRIMITIVES_GET_ENUM_FROM_TYPE(type) KPRIMITIVES_GET_ENUM_FROM_VAR((type){0})


/**
 * Check if enum / variable / type is primitive (pointer is not a primitive type)
 */
#define KPRIMITIVES_ENUM_IS_PRIMITIVE(e)      (e != KPRIMITIVES_ENUM_NON_PRIMITIVE)
#define KPRIMITIVES_VAR_IS_PRIMITIVE(var)     (KPRIMITIVES_ENUM_IS_PRIMITIVE(KPRIMITIVES_GET_ENUM_FROM_VAR(var)))
#define KPRIMITIVES_TYPE_IS_PRIMITIVE(type)   (KPRIMITIVES_ENUM_IS_PRIMITIVE(KPRIMITIVES_GET_ENUM_FROM_TYPE(type)))

/**
 * Check if enum / variable / type is not primitive (pointer is not a primitive type)
 */
#define KPRIMITIVES_ENUM_ISNOT_PRIMITIVE(e)      (!KPRIMITIVES_ENUM_IS_PRIMITIVE(e))
#define KPRIMITIVES_VAR_ISNOT_PRIMITIVE(var)     (!KPRIMITIVES_VAR_IS_PRIMITIVE(var))
#define KPRIMITIVES_TYPE_ISNOT_PRIMITIVE(type)   (!KPRIMITIVES_TYPE_IS_PRIMITIVE(type))

/**
 * Check if enum / variable / type is pointer.
 * Because non primitive can be struct, union, array or pointer this is useful
 * when you are sure that user pass primitive or pointer
 */
#define KPRIMITIVES_ENUM_PROBABLY_POINTER(e)     KPRIMITIVES_ENUM_ISNOT_PRIMITIVE(e)
#define KPRIMITIVES_VAR_PROBABLY_POINTER(var)    KPRIMITIVES_VAR_ISNOT_PRIMITIVE(var)
#define KPRIMITIVES_TYPE_PROBABLY_POINTER(type)  KPRIMITIVES_TYPE_ISNOT_PRIMITIVE(type)

/**
 * Use this macro to obtain printf format to type related to given enum
 * i.e for KPRIMITIVES_ENUM_INT it returns "%d"
 *
 * This cannot be concatenate to another " " in printf.
 * printf("VAR = " KPRIMITIVES_GET_PFMT_FROM_ENUM(KPRIMITIVES_ENUM_INT), 10) will not compile.
 *
 * To create printf fmt you need to write this "%d" to buffer using i.e snprintf
 *
 * @params[in] e - one of the KPRIMITIVES value
 */
#define KPRIMITIVES_GET_PFMT_FROM_ENUM(e) \
    (const char*[]){[KPRIMITIVES_ENUM_BOOL]               = KPRIMITIVES_PFMT_BOOL, \
                    [KPRIMITIVES_ENUM_CHAR]               = KPRIMITIVES_PFMT_CHAR, \
                    [KPRIMITIVES_ENUM_SIGNED_CHAR]        = KPRIMITIVES_PFMT_SIGNED_CHAR, \
                    [KPRIMITIVES_ENUM_UNSIGNED_CHAR]      = KPRIMITIVES_PFMT_UNSIGNED_CHAR, \
                    [KPRIMITIVES_ENUM_SHORT]              = KPRIMITIVES_PFMT_SHORT, \
                    [KPRIMITIVES_ENUM_UNSIGNED_SHORT]     = KPRIMITIVES_PFMT_UNSIGNED_SHORT, \
                    [KPRIMITIVES_ENUM_INT]                = KPRIMITIVES_PFMT_INT, \
                    [KPRIMITIVES_ENUM_UNSIGNED_INT]       = KPRIMITIVES_PFMT_UNSIGNED_INT, \
                    [KPRIMITIVES_ENUM_LONG]               = KPRIMITIVES_PFMT_LONG, \
                    [KPRIMITIVES_ENUM_UNSIGNED_LONG]      = KPRIMITIVES_PFMT_UNSIGNED_LONG, \
                    [KPRIMITIVES_ENUM_LONG_LONG]          = KPRIMITIVES_PFMT_LONG_LONG, \
                    [KPRIMITIVES_ENUM_UNSIGNED_LONG_LONG] = KPRIMITIVES_PFMT_UNSIGNED_LONG_LONG, \
                    [KPRIMITIVES_ENUM_FLOAT]              = KPRIMITIVES_PFMT_FLOAT, \
                    [KPRIMITIVES_ENUM_DOUBLE]             = KPRIMITIVES_PFMT_DOUBLE, \
                    [KPRIMITIVES_ENUM_LONG_DOUBLE]        = KPRIMITIVES_PFMT_LONG_DOUBLE, \
                    [KPRIMITIVES_ENUM_NON_PRIMITIVE]      = KPRIMITIVES_PFMT_NON_PRIMITIVE, \
                   }[e]

/**
 * Use this macro to obtain printf format to type related to given variable
 * i.e for int i = 10 it returns "%d"
 *
 * This cannot be concatenate to another " " in printf.
 * printf("VAR = " KPRIMITIVES_GET_PFMT_FROM_VAR(i), i) will not compile.
 *
 * To create printf fmt you need to write this "%d" to buffer using i.e snprintf
 */
#define KPRIMITIVES_GET_PFMT_FROM_VAR(var) \
    KPRIMITIVES_GET_PFMT_FROM_ENUM(KPRIMITIVES_GET_ENUM_FROM_VAR(var))

/**
 * Use this macro to obtain printf format from type
 * i.e for int it returns "%d"
 *
 * This cannot be concatenate to another " " in printf.
 * printf("VAR = " KPRIMITIVES_GET_PFMT_FROM_TYPE(int), 10) will not compile.
 *
 * To create printf fmt you need to write this "%d" to buffer using i.e snprintf
 */
#define KPRIMITIVES_GET_PFMT_FROM_TYPE(type) \
    KPRIMITIVES_GET_PFMT_FROM_ENUM(KPRIMITIVES_GET_ENUM_FROM_TYPE(type))

/**
 * This macro returns const char* name of type saved in enum
 *
 * @params[in] e - one of the KPRIMITIVES value
 */
#define KPRIMITIVES_GET_NAME_FROM_ENUM(e) \
    (const char*[]){[KPRIMITIVES_ENUM_BOOL]               = KPRIMITIVES_NAME_BOOL, \
                    [KPRIMITIVES_ENUM_CHAR]               = KPRIMITIVES_NAME_CHAR, \
                    [KPRIMITIVES_ENUM_SIGNED_CHAR]        = KPRIMITIVES_NAME_SIGNED_CHAR, \
                    [KPRIMITIVES_ENUM_UNSIGNED_CHAR]      = KPRIMITIVES_NAME_UNSIGNED_CHAR, \
                    [KPRIMITIVES_ENUM_SHORT]              = KPRIMITIVES_NAME_SHORT, \
                    [KPRIMITIVES_ENUM_UNSIGNED_SHORT]     = KPRIMITIVES_NAME_UNSIGNED_SHORT, \
                    [KPRIMITIVES_ENUM_INT]                = KPRIMITIVES_NAME_INT, \
                    [KPRIMITIVES_ENUM_UNSIGNED_INT]       = KPRIMITIVES_NAME_UNSIGNED_INT, \
                    [KPRIMITIVES_ENUM_LONG]               = KPRIMITIVES_NAME_LONG, \
                    [KPRIMITIVES_ENUM_UNSIGNED_LONG]      = KPRIMITIVES_NAME_UNSIGNED_LONG, \
                    [KPRIMITIVES_ENUM_LONG_LONG]          = KPRIMITIVES_NAME_LONG_LONG, \
                    [KPRIMITIVES_ENUM_UNSIGNED_LONG_LONG] = KPRIMITIVES_NAME_UNSIGNED_LONG_LONG, \
                    [KPRIMITIVES_ENUM_FLOAT]              = KPRIMITIVES_NAME_FLOAT, \
                    [KPRIMITIVES_ENUM_DOUBLE]             = KPRIMITIVES_NAME_DOUBLE, \
                    [KPRIMITIVES_ENUM_LONG_DOUBLE]        = KPRIMITIVES_NAME_LONG_DOUBLE, \
                    [KPRIMITIVES_ENUM_NON_PRIMITIVE]      = KPRIMITIVES_NAME_NON_PRIMITIVE, \
                   }[e]

/**
 * This macro returns const char* name of type related to variable
 */
#define KPRIMITIVES_GET_NAME_FROM_VAR(var) \
    KPRIMITIVES_GET_NAME_FROM_ENUM(KPRIMITIVES_GET_ENUM_FROM_VAR(var))

/**
 * This macro returns const char* name of type related to type
 */
#define KPRIMITIVES_GET_NAME_FROM_TYPE(type) \
    KPRIMITIVES_GET_NAME_FROM_ENUM(KPRIMITIVES_GET_ENUM_FROM_TYPE(type))

#endif
