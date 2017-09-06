/**
* @file      debug.c
* @brief     This module realize the opreation of the loudspeaker.
* @details   This module contains open and close and set nature of the loudspeaker.
* @author    zy
* @date      2017/06/15
* @version   HMI-T001
* @par Copyright (c)
*      keluofeite
* @par History:
*
*   version: author, date, desc\n
*/

#ifndef HMI_ERROR_LEVEL
#define HMI_ERROR_LEVEL

extern void hmi_debug(const char *msg, ...);

#define HMI_ERROR(x, ...) hmi_debug(x, ##__VA_ARGS__) 

#ifdef HMI_DEBUG_LEVEL 
#define HMI_DEBUG(x, ...) hmi_debug(x, ##__VA_ARGS__)
#else 
#define HMI_DEBUG(x, ...) NULL
#endif

#endif
