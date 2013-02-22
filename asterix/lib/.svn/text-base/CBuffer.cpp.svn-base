/*
 * CBuffer.cpp
 *
 *  Created on: 2012. 3. 27.
 *      Author: JMS
 */
#include <stdio.h>
#include <string.h>
#include "CBuffer.h"

CBuffer::CBuffer(): m_s32Length(0), m_s32Index(0) {
	// TODO Auto-generated constructor stub
}

CBuffer::~CBuffer() {
	// TODO Auto-generated destructor stub
}

void CBuffer::Clear(void)
{
	m_s32Length = 0;
	m_s32Index	= 0;
}

BOOL CBuffer::CopyBuffer(U8 *pu8Buf, S32 s32Length)
{
	if (s32Length > L_BUFFER)
	{
		return FALSE;
	}
	memcpy(m_u8Buffer, pu8Buf, s32Length);		// copy data
	m_s32Length = s32Length;
	m_s32Index	= 0;

	return TRUE;
}

BOOL CBuffer::CanBeRead(void)
{
	return (m_s32Index < m_s32Length);
}

U8* CBuffer::GetPBuffer(void)
{
	return m_u8Buffer;
}

S32 CBuffer::GetMaxSize(void)
{
	return L_BUFFER;
}

BOOL CBuffer::SetIndex(S32 s32Index)
{
	if (s32Index < 0 || s32Index > L_BUFFER)
	{
		return FALSE;
	}
	m_s32Index = s32Index;

	return TRUE;
}

S32 CBuffer::GetLength(void)
{
	return m_s32Length;
}

BOOL CBuffer::SetLength(S32 s32Length)
{
	if (s32Length < 0 || s32Length > L_BUFFER)
	{
		return FALSE;
	}
	m_s32Length = s32Length;

	return TRUE;
}

S32 CBuffer::GetIndex(void)
{
	return m_s32Index;
}

BOOL CBuffer::ReadU8(U8 *pu8)		// throw(CMSDPException);
{
	if (m_s32Index < 0 || m_s32Index >= m_s32Length)
	{
		return FALSE;	// overflow
	}

	*pu8 = m_u8Buffer[m_s32Index++];

	return TRUE;
}

BOOL CBuffer::ReadS8(S8 *ps8)
{
	U8 u8;
	ReadU8(&u8);
	*ps8 = static_cast<S8>(u8);

	return TRUE;
}

BOOL CBuffer::ReadU16(U16 *pu16)
{
	*pu16 = 0;

	for (S16 s16 = 0; s16 < 2; s16++)
	{
		U8 u8;

		if (!ReadU8(&u8))
		{
			return FALSE;
		}
		*pu16 = (*pu16 << 8) + u8;
	}
	return TRUE;
}

BOOL CBuffer::ReadS16(S16 *ps16)
{
	U16 u16;
	ReadU16(&u16);
	*ps16 = static_cast<S16>(u16);

	return TRUE;
}

BOOL CBuffer::ReadU24(U32 *pu32)
{
	*pu32 = 0;

	for (S16 s16 = 0; s16 < 3; s16++)
	{
		U8 u8;
		if (!ReadU8(&u8))
		{
			return FALSE;
		}
		*pu32 = (*pu32 << 8) + u8;
	}
	return TRUE;
}

BOOL CBuffer::ReadS24(S32 *ps32)
{
	U32 u32;
	ReadU24(&u32);
	*ps32 = static_cast<S32>(u32); // | 0xFF000000);

	// Negative value
//	if (u32 & 0x00800000)
//	{
//		*ps32 |= 0xFF000000;
//	}
	return TRUE;
}

BOOL CBuffer::ReadU32(U32 *pu32)
{
	*pu32 = 0;

	for (S16 s16 = 0; s16 < 4; s16++)
	{
		U8 u8;
		if (!ReadU8(&u8))
		{
			return FALSE;
		}
		*pu32 = (*pu32 << 8) + u8;
	}
	return TRUE;
}

BOOL CBuffer::ReadS32(S32 *ps32)
{
	U32 u32;
	ReadU32(&u32);
	*ps32 = static_cast<S32>(u32);
	return TRUE;
}

BOOL CBuffer::ReadF32(F32 *pf32)
{
	*pf32 = 0;

	uval uv;
	uv.s32 = 0;

	for (S8 s8 = 3; s8 >= 0; s8--)
	{
		U8 u8;
		if (!ReadU8(&u8))
		{
			return FALSE;
		}
		uv.s8[s8] = u8;
	}
	*pf32 = uv.f32;

	return TRUE;
}

BOOL CBuffer::ReadU64(U64 *pu64)
{
	*pu64 = 0;

	for (S16 s16 = 0; s16 < 8; s16++)
	{
		U8 u8;
		if (!ReadU8(&u8))
		{
			return FALSE;
		}
		*pu64 = (*pu64 << 8) + u8;
	}
	return TRUE;
}

BOOL CBuffer::ReadU48(U64 *pu64)
{
	*pu64 = 0;

	for (S16 s16 = 0; s16 < 6; s16++)
	{
		U8 u8;
		if (!ReadU8(&u8))
		{
			return FALSE;
		}
		*pu64 = (*pu64 << 8) + u8;
	}
	return TRUE;
}
BOOL CBuffer::ReadU56(U64 *pu64)
{
	*pu64 = 0;

	for (S16 s16 = 0; s16 < 7; s16++)
	{
		U8 u8;
		if (!ReadU8(&u8))
		{
			return FALSE;
		}
		*pu64 = (*pu64 << 8) + u8;
	}
	return TRUE;
}
BOOL CBuffer::ReadS64(S64 *ps64)
{
	U64 u64;
	ReadU64(&u64);
	*ps64 = static_cast<S64>(u64);
	return TRUE;
}

BOOL CBuffer::ReadF64(F64 *pf64)
{
	*pf64 = 0;

	uval uv;
	uv.s64 = 0;

	for (S8 s8 = 7; s8 >=0; s8--)
	{
		U8 u8;
		if (!ReadU8(&u8))
		{
			return FALSE;
		}
		uv.s8[s8] = u8;
	}
	*pf64 = uv.f64;
	return TRUE;
}
