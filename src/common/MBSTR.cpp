﻿
/*
Copyright (c) 2016-present Maximus5
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#define HIDE_USE_EXCEPTION_INFO
#include "defines.h"
#include "MBSTR.h"
#include <OleAuto.h>

/* SysAllocString/SysFreeString encapsulation */

MBSTR::MBSTR(LPCWSTR asString)
{
	ms_bstr = asString ? ::SysAllocString(asString) : NULL;
}

MBSTR::~MBSTR()
{
	Free();
}

void MBSTR::Free()
{
	if (ms_bstr)
	{
		::SysFreeString(ms_bstr);
		ms_bstr = NULL;
	}
}

MBSTR::operator BSTR() const
{
	return ms_bstr;
}

MBSTR& MBSTR::operator=(LPCWSTR asString)
{
	if (asString != ms_bstr)
	{
		Free();
		ms_bstr = asString ? ::SysAllocString(asString) : NULL;
	}
	return *this;
}
