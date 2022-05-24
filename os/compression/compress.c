/****************************************************************************
 *
 * Copyright 2022 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <tinyara/config.h>
#include <sys/types.h>
#include <debug.h>
#include <errno.h>

#include <tinyara/binfmt/compression/compress_read.h>

#if CONFIG_COMPRESSION_TYPE == LZMA
#include <tinyara/lzma/LzmaLib.h>
#elif CONFIG_COMPRESSION_TYPE == MINIZ
#include <miniz/miniz.h>
#else
#error "Wrong compression type, please check CONFIG_COMPRESSION_TYPE"
#endif

unsigned char *allocate_compress_buffer(int offset, unsigned int size)
{
	unsigned int propsSize = 0;

#if CONFIG_COMPRESSION_TYPE == LZMA
	propsSize = LZMA_PROPS_SIZE;
#endif

	unsigned char *out_buffer = (unsigned char *)kmm_malloc(size + propsSize + offset);
	return out_buffer;
}

int compress_block(unsigned char *out_buffer, long unsigned int *writesize, unsigned char *read_buffer, long unsigned int size)
{
	int ret;
#if CONFIG_COMPRESSION_TYPE == LZMA
	unsigned int propsSize = LZMA_PROPS_SIZE;
	ret = LzmaCompress(&out_buffer[LZMA_PROPS_SIZE], writesize, read_buffer, size, out_buffer, &propsSize, 0, 1 << 13, -1, -1, -1, -1, 1);
	if (ret == SZ_ERROR_FAIL) {
		dbg("Failure to compress with LZMACompress API\n");
		ret = -ret;
	}
#elif CONFIG_COMPRESSION_TYPE == MINIZ
	ret = mz_compress(out_buffer, writesize, read_buffer, size);
	if (ret != Z_OK) {
		dbg("Failure to compress with Miniz's compress API; ret = %d\n", ret);
		if (ret > 0)
			ret = -ret;
	}
#endif
	return ret;
}
