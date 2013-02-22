/*
 * CBuffer.h
 *
 *  Created on: 2012. 3. 27.
 *      Author: JMS
 */

#ifndef CBUFFER_H_
#define CBUFFER_H_

#include "GlobalConsts.h"
#include "BaseTypes.h"

class CBuffer {
public:
	CBuffer();
	~CBuffer();

	void Clear(void);
	BOOL CopyBuffer(U8 *pu8Buf, S32 s32Length);
	BOOL CanBeRead(void);
	U8* GetPBuffer(void);
	S32 GetMaxSize(void);
	BOOL SetIndex(S32 s32Index);
	S32 GetLength(void);
	BOOL SetLength(S32 s32Length);
	S32 GetIndex(void);

	BOOL ReadU8(U8 *pu8);		// throw(CMSDPException);
	BOOL ReadS8(S8 *ps8);
	BOOL ReadU16(U16 *pu16);
	BOOL ReadS16(S16 *ps16);
	BOOL ReadU24(U32 *pu32);
	BOOL ReadS24(S32 *ps32);
	BOOL ReadU32(U32 *pu32);
	BOOL ReadS32(S32 *ps32);
	BOOL ReadF32(F32 *pf32);
	BOOL ReadU64(U64 *pu64);
	BOOL ReadS64(S64 *ps64);
	BOOL ReadF64(F64 *pf64);
	BOOL ReadU48(U64 *pf64);
	BOOL ReadU56(U64 *pf64);

private:
	U8  m_u8Buffer[L_BUFFER];
	S32 m_s32Length;
	S32 m_s32Index;			// current value of a buffer
};

#endif /* CBUFFER_H_ */
