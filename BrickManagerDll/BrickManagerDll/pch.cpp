// pch.cpp: source file corresponding to the pre-compiled header

#include "pch.h"

#ifdef BRICKMANAGER_DLL_EXPORTS
#define BRICKMANAGER_API __declspec(dllexport)
#else
#define BRICKMANAGER_API __declspec(dllimport)
#endif

// When you are using pre-compiled headers, this source file is necessary for compilation to succeed.
