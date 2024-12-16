#pragma once
#ifdef KINK_PLATFORM_WINDOWS
	#ifdef KINK_BUILD_DLL
		#define KINK_API __declspec(dllexport)
	#else
		#define KINK_API __declspec(dllimport)
	#endif
#else
	#error this engine only supports windows
#endif
#define BIT(x) (1 << x)