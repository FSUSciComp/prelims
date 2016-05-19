#ifndef EXPORT_RKM_DLL_H
#define EXPORT_RKM_DLL_H

#ifdef EXRKLIB_EXPORTS
#define ExRKMDLL __declspec(dllexport)
#else
#define ExRKMDLL __declspec(dllimport)
#endif

//#define RKDLL extern "C" _declspec(dllexport)



#endif
