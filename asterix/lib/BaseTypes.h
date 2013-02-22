/*
 * BaseTypes.h
 *
 *  Created on: 2012. 3. 27.
 *      Author: JMS
 */

#ifndef BASETYPES_H_
#define BASETYPES_H_

typedef char S8;

typedef unsigned char U8;

typedef short S16;

typedef unsigned short U16;

typedef long S32;

typedef unsigned long U32;

typedef float F32;

typedef double F64;

typedef long long S64;

typedef unsigned long long U64;

typedef short BOOL;

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

typedef union {
	S8	s8[8];
	S16	s16;
	S32	s32;
	S64	s64;
	F32	f32;
	F64	f64;
} uval;

#define FLT_MIN	1.175494351e-38F

#endif /* BASETYPES_H_ */
