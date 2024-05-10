#pragma once 

#ifdef _WIN32 
#ifdef ctkGraphics_EXPORTS
#define GRAPHICS_API __declspec(export)
#else
#define GRAPHICS_API __declspec(import)
#endif 
#else
#define GRAPHICS_API 
#endif 