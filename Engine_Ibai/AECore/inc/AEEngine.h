// ---------------------------------------------------------------------------
// Project Name		:	Alpha Engine
// File Name		:	AEEngine.h
// Author			:	Sun Tjen Fam
// Creation Date	:	2008/01/31
// Purpose			:	the main include file for the Alpha engine
// History			:
// - 2008/01/31		:	- initial implementation
// ---------------------------------------------------------------------------

#ifndef AE_ENGINE_H
#define AE_ENGINE_H

// C standard libraries
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cmath>
#ifdef AE_DBG_MEMORY
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>

	#ifdef _DEBUG
	   #ifndef DBG_NEW
		  #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		  #define new DBG_NEW
	   #endif
	#endif  // _DEBUG

	#define AE_CHECK_LEAKS() _CrtDumpMemoryLeaks()
	#define AE_CHECK_MEMORY()									\
	{															\
		if(_heapchk()!=_HEAPOK)									\
			DebugBreak();										\
	}
#else
	#define AE_CHECK_LEAKS()
	#define AE_CHECK_MEMORY()
#endif

// STL STRUCTS
#include <string>
#include <stack>	
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

// WIN32
//#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define AE_UNUSED(p) ((void)(p))

// ---------------------------------------------------------------------------
// typdef types

typedef char				s8;
typedef unsigned char		u8;
typedef signed short		s16;
typedef unsigned short		u16;
typedef signed long			s32;
typedef unsigned long		u32;
typedef signed long long	s64;
typedef unsigned long long	u64;
typedef float				f32;
typedef double				f64;

// ---------------------------------------------------------------------------
// Alpha engine includes

#include "AEDebug.h"
#include "AEMath.h"
#include "AEUtil.h"
#include "AEFrameRateController.h"
#include "AESystem.h"
#ifndef AE_NO_GFX
	#include "AEGraphics.h"
#endif
#include "AEInput.h"
#include "AEGameStateMgr.h"

// ---------------------------------------------------------------------------

#endif // ENGINE_H

