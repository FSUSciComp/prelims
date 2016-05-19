#ifndef EXPORT_RKM_DLL_H
#define EXPORT_RKM_DLL_H

#ifdef RKLIB_EXPORTS
#define RKMDLL __declspec(dllexport)
#else
#define RKMDLL __declspec(dllimport)
#endif

//#define RKDLL extern "C" _declspec(dllexport)



#endif
