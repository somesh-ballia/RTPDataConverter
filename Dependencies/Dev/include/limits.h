
/* Copyright (c) Microsoft Corporation. All rights reserved. */
/***
 *limits.h - implementation dependent values
 *
 * Purpose:
 *      Contains defines for a number of implementation dependent values
 *      which are commonly used in C programs.
 * Reference:
 *      ISO/IEC 9899 : 1990 (E) "Programming languages -- C "
 *      Section 7.1.5 "Limits <float.h> and <limits.h>" pag 98.
 *      Section 5.2.4.2.1 "Sizes of integral types <limits.h>" pagg 13-14
 *
 */

#ifndef _INC_LIMITS
#define _INC_LIMITS

/* BUGBUG this really belongs with the compiler but.. */
#ifdef _MSC_VER
/* the correct, extensible way */
#define _I8_(n)   n##i8
#define _I16_(n)  n##i16
#define _I32_(n)  n##i32
#define _I64_(n)  n##i64
#define _I128_(n) n##i128
#else
/* oldies rule */
#define _I8_(n)   n
#define _I16_(n)  n
#define _I32_(n)  n##L
#define _I64_(n)  n##LL
#define _I128_(n) n##LLL  /* just a joke (you get it, right ?) */
#endif


#define CHAR_BIT          8              /* number of bits in a char */
#define SCHAR_MIN       (-128)           /* minimum signed char value */
#define SCHAR_MAX         127            /* maximum signed char value */
#define UCHAR_MAX         0xff           /* maximum unsigned char value */

#ifndef _CHAR_UNSIGNED
#define CHAR_MIN        SCHAR_MIN        /* mimimum char value */
#define CHAR_MAX        SCHAR_MAX        /* maximum char value */
#else
#define CHAR_MIN          0
#define CHAR_MAX        UCHAR_MAX
#endif  /* _CHAR_UNSIGNED */

#define MB_LEN_MAX        1              /* max. # bytes in multibyte char */
#define SHRT_MIN        (-32768)         /* minimum (signed) short value */
#define SHRT_MAX          32767          /* maximum (signed) short value */
#define USHRT_MAX         0xffff         /* maximum unsigned short value */
#define INT_MIN         (-2147483647-1)  /* minimum (signed) int value */
#define INT_MAX           2147483647     /* maximum (signed) int value */
#define UINT_MAX          0xffffffff     /* maximum unsigned int value */
#define LONG_MIN        (-2147483647L-1) /* minimum (signed) long value */
#define LONG_MAX          2147483647L    /* maximum (signed) long value */
#define ULONG_MAX         0xffffffffUL   /* maximum unsigned long value */

#undef _INTEGRAL_MAX_BITS
#define _INTEGRAL_MAX_BITS _UINTSIZE     /* compat with windows way */

#if     _INTEGRAL_MAX_BITS >= 8
#define _I8_MIN         (-_I8_(127)-1)   /* minimum signed 8 bit value */
#define _I8_MAX           _I8_(127)      /* maximum signed 8 bit value */
#define _UI8_MAX          _I8_(0xffu)    /* maximum unsigned 8 bit value */
#endif

#if     _INTEGRAL_MAX_BITS >= 16
#define _I16_MIN        (-_I16_(32767)-1)/* minimum signed 16 bit value */
#define _I16_MAX          _I16_(32767)   /* maximum signed 16 bit value */
#define _UI16_MAX         _I16_(0xffffu) /* maximum unsigned 16 bit value */
#endif

#if     _INTEGRAL_MAX_BITS >= 32
#define _I32_MIN        (-_I32_(2147483647)-1) /* minimum signed 32 bit value*/
#define _I32_MAX          _I32_(2147483647)  /* maximum signed 32 bit value */
#define _UI32_MAX         _I32_(0xffffffffu) /* maximum unsigned 32 bit value*/
#endif

#if     _INTEGRAL_MAX_BITS >= 64
/* minimum signed 64 bit value */
#define _I64_MIN        (_I64_(-9223372036854775807)-1)
/* maximum signed 64 bit value */
#define _I64_MAX          _I64_(9223372036854775807)
/* maximum unsigned 64 bit value */
#define _UI64_MAX         _I64_(0xffffffffffffffffu)
#endif

#if     _INTEGRAL_MAX_BITS >= 128
/* minimum signed 128 bit value */
#define _I128_MIN       (-_I128_(170141183460469231731687303715884105727)-1)
/* maximum signed 128 bit value */
#define _I128_MAX         _I128_(170141183460469231731687303715884105727)
/* maximum unsigned 128 bit value */
#define _UI128_MAX        _I128_(0xffffffffffffffffffffffffffffffffu)
#endif

#endif  /* _INC_LIMITS */

