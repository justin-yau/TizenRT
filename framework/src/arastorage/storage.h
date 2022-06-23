/****************************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
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
/*
 * Copyright (c) 2010, Swedish Institute of Computer Science
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/**
 * \file
 *      The storage interface used by the database.
 * \author
 *      Nicolas Tsiftes <nvt@sics.se>
 */

#ifndef STORAGE_H
#define STORAGE_H

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <arastorage/arastorage.h>
#include "index.h"
#include "relation.h"

#define INVALID_STORAGE_ID -1
/****************************************************************************
* Public Type Definitions
****************************************************************************/
#ifdef CONFIG_ARASTORAGE_ENABLE_WRITE_BUFFER
struct insert_buffer_s {
	char file_name[DB_MAX_FILENAME_LENGTH];	/* name of tuple file */
	unsigned char *buffer;		/* write buffer */
	int data_size;				/* size of data in buffer */
};
#endif

typedef unsigned char *storage_row_t;

/****************************************************************************
* Global Function Prototypes
****************************************************************************/
db_result_t heap_generate_file(char *);
db_result_t storage_generate_file(char *);

db_result_t storage_load(relation_t *);
db_result_t storage_unload(relation_t *);

db_result_t storage_get_relation(relation_t *, char *);
db_result_t storage_put_relation(relation_t *);
db_result_t storage_drop_relation(relation_t *, int);
db_result_t storage_rename_relation(char *, char *);

db_result_t storage_put_attribute(relation_t *, attribute_t *);
db_result_t storage_get_index(index_t *, relation_t *, attribute_t *);
db_result_t storage_put_index(index_t *);
db_result_t storage_remove_index(relation_t *rel, attribute_t *attr);
db_result_t storage_get_row(relation_t *, tuple_id_t *, storage_row_t);
db_result_t storage_put_row(relation_t *, storage_row_t, uint8_t);
db_result_t storage_write_row(db_storage_id_t, storage_row_t, unsigned, char *);
db_result_t storage_get_row_amount(relation_t *, tuple_id_t *);
db_result_t storage_read_from(db_storage_id_t, void *, unsigned long, unsigned);
db_result_t storage_write_to(db_storage_id_t, void *, unsigned long, unsigned);

#ifdef CONFIG_ARASTORAGE_ENABLE_WRITE_BUFFER
db_result_t storage_write_buffer_init(void);
void storage_write_buffer_deinit(void);
db_result_t storage_flush_insert_buffer(void);
void storage_write_buffer_clean(void);
#endif

db_storage_id_t storage_open(const char *, int);
db_storage_id_t storage_close(db_storage_id_t);
db_result_t storage_remove(const char *);
db_result_t storage_rename(const char *, const char *);
off_t storage_seek(db_storage_id_t, unsigned long, int);
ssize_t storage_read(db_storage_id_t, void *, unsigned);
ssize_t storage_write(db_storage_id_t, void *, unsigned);
#ifdef CONFIG_ARASTORAGE_ENABLE_WRITE_BUFFER
ssize_t storage_get_availbyte_size(void);
#endif

#endif							/* STORAGE_H */
