#pragma once
#include <cassert>
#include <Utility/Log/Log.h>

/*
* @brief ���� ó��
*/
#if VG_DEBUG
	#define FZ_ASSERT(flag, ...) { if(!(flag)) { Log.Error(__VA_ARGS__); DebugBreak(); } }
#else
	#define FZ_ASSERT(flag, ...)
#endif
