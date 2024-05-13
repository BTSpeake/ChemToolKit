#pragma once 

#ifdef _WIN32 
#ifdef ctkGraphics_EXPORTS
#define GRAPHICS_API __declspec(dllexport)
#else
#define GRAPHICS_API __declspec(dllimport)
#endif 
#else
#define GRAPHICS_API 
#endif 