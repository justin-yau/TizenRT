/**
 ******************************************************************************
 *This file contains general configurations for ameba platform
 ******************************************************************************
*/

#ifndef __PLATFORM_OPTS_H__
#define __PLATFORM_OPTS_H__

#include "platform_autoconf.h"

#if defined(CONFIG_AS_AP)
#include "platform_opts_ap.h"
#elif defined(CONFIG_AS_NP)
#include "platform_opts_np.h"
#endif

#endif //__PLATFORM_OPTS_H__

