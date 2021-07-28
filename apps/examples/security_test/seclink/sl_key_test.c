/****************************************************************************
 *
 * Copyright 2020 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/

#include <tinyara/config.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <tinyara/seclink.h>
#include <tinyara/seclink_drv.h>
#include <stress_tool/st_perf.h>
#include "sl_test.h"
#include "sl_test_usage.h"

static char *g_command[] = {
#ifdef SL_KEY_TEST_POOL
#undef SL_KEY_TEST_POOL
#endif
#define SL_KEY_TEST_POOL(command, type, func) command,
#include "sl_key_table.h"
};

#ifdef SL_KEY_TEST_POOL
#undef SL_KEY_TEST_POOL
#endif
#define SL_KEY_TEST_POOL(command, type, func) \
	extern void func(sl_options *opt);
#include "sl_key_table.h"

static sl_test_func g_func_list[] = {
#ifdef SL_KEY_TEST_POOL
#undef SL_KEY_TEST_POOL
#endif
#define SL_KEY_TEST_POOL(command, type, func) func,
#include "sl_key_table.h"
};

typedef enum {
#ifdef SL_KEY_TEST_POOL
#undef SL_KEY_TEST_POOL
#endif
#define SL_KEY_TEST_POOL(command, type, func) type,
#include "sl_key_table.h"
	SL_KEY_TYPE_MAX,
	SL_KEY_TYPE_ERR = -1
} sl_key_type_e;

static int _parse_command(sl_options *opt)
{
	int argc = opt->argc;
	char **argv = opt->argv;

	if (argc < 4) {
		return -1;
	}
	opt->count = atoi(argv[3]);

	if (strncmp(argv[2], "all", strlen("all") + 1) == 0) {
		return SL_KEY_TYPE_MAX;
	}

	for (int i = 0; i < SL_KEY_TYPE_MAX; i++) {
		if (strncmp(argv[2], g_command[i], strlen(g_command[i]) + 1) == 0) {
			return (sl_key_type_e)i;
		}
	}
	return SL_KEY_TYPE_ERR;
}

static void _run_all(sl_options *opt)
{
	for (int i = 0; i < SL_KEY_TYPE_MAX; i++) {
		g_func_list[i](opt);
	}
}

/*
 * Key
 * Injected key slot range 0~31
 * tp1x: 0~7
 * RAM key slot range 32~63
 * tp1x: 32~63
 */
void sl_handle_key(sl_options *opt)
{
	printf("ToDo\n");
	return;
}
