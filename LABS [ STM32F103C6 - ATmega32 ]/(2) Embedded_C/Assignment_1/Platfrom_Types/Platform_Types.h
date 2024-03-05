/*
 * Platform_Types.h
 *
 *  Created on: Aug 2, 2023
 *      Author: MOHTERA
 */

#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

#include <stdbool.h>


#ifndef _Bool
#define _Bool unsigned char
#endif

#define CPU_TYPE CPU_TYPE_32
#define CPU_BIT_ORDER MSB_FIRST
#define CPU_BYTE_ORDER     HIGH_BYTE_FIRST

#ifndef FALSE
#define FALSE       (boolean)false
#endif


#ifndef TRUE
#define TRUE       (boolean)true
#endif


typedef _Bool                      boolean;
typedef char                       char_t;
typedef unsigned char              uint8_t;
typedef signed char                sint8_t;
typedef unsigned short             uint16_t;
typedef signed short               sint16_t;
typedef unsigned int               uint32_t;
typedef signed int                 sint32_t;
typedef unsigned long long int     uint64_t; 
typedef signed long long int       sint64_t;

typedef volatile char                       vchar_t;

typedef volatile unsigned char              vuint8_t;
typedef volatile signed char                vsint8_t;

typedef volatile unsigned short             vuint16_t;
typedef volatile signed short               vsint16_t;

typedef volatile unsigned int               vuint32_t;
typedef volatile signed int                 vsint32_t;

typedef volatile unsigned long long int     vuint64_t; 
typedef volatile signed long long int       vsint64_t;

typedef float   float32;
typedef double  float64;

#endif  /*PLATFORM_TYPES_H_ */