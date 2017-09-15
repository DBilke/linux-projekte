/*
 * main.h
 *
 *  Created on: 15.09.2017
 *      Author: dbilke
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <sys/types.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
typedef unsigned char           unchar;
typedef unsigned short          ushort;
typedef unsigned int            uint;
typedef unsigned long           ulong;
struct timespec {
    time_t   tv_sec;        /* seconds */
    long     tv_nsec;       /* nanoseconds */
};
#include <my_global.h>
#include <mysql.h>

#endif /* MAIN_H_ */
