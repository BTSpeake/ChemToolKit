#pragma once 

#ifdef _WIN32
#ifdef ctkDataObjs_EXPORTS
#define DATA_API __declspec(dllexport)
#else
#define DATA_API __declspec(dllimport)
#endif // ctkDataObjs_EXPORTS 
#else
#define DATA_API
#endif //_WIN32 