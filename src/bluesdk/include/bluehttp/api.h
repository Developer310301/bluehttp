#ifndef BLUESDK_PLATFORM_DETECTION_H
#define BLUESDK_PLATFORM_DETECTION_H

#ifdef _WIN32
    #define PLATFORM_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
    #define PLATFORM_MACOS
#elif defined(__linux__)
    #define PLATFORM_LINUX
#endif

#ifdef PLATFORM_WINDOWS
    #ifdef BUILDING_SDK
        #define BLUEHTTP_API __declspec(dllexport)
    #else
        #define BLUEHTTP_API __declspec(dllimport)
    #endif
#else
    #define BLUEHTTP_API
#endif

#ifdef __cplusplus
    #define BLUEHTTP_EXTERN_API extern "C"{
    #define BLUEHTTP_END_EXTERN_API }
#else
    #define BLUEHTTP_EXTERN_API extern {
    #define BLUEHTTP_END_EXTERN_API }
#endif

#endif //BLUESDK_PLATFORM_DETECTION_H