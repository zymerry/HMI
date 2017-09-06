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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void hmi_debug(const char *msg, ...)
{
  va_list ap;
   va_start(ap, msg);
   vfprintf(stdout, msg, ap);
   va_end(ap);
}


