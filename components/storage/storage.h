/* SD card and FAT filesystem example.
   This example uses SPI peripheral to communicate with SD card.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#ifndef __STORAGE_T__
#define __SOTRAGE_T__

// #include <driver/spi_master.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>
// #include <sd_test_io.h>

#include "bsp.h"

#define EXAMPLE_MAX_CHAR_SIZE 64
#define STOR_PREFIX "FT_"

void storage_init(char *);
void storage_write(char *);
void storage_read(void);
void storage_flush();
FILE *storage_fetch();
void storage_demo(void);

#endif