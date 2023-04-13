/*
 * This is a header-only library for commonly used small nits
 */

#ifndef _WHEELS_H
#define _WHEELS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

// {{{ types

#ifndef _TYPE_ALIAS_DEFINED
#include <assert.h>
#include <stdint.h>
#include <stdatomic.h>

typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
static_assert(sizeof(s8) == 1, "sizeof(s8)");
static_assert(sizeof(s16) == 2, "sizeof(s16)");
static_assert(sizeof(s32) == 4, "sizeof(s32)");
static_assert(sizeof(s64) == 8, "sizeof(s64)");
static_assert(sizeof(u8) == 1, "sizeof(u8)");
static_assert(sizeof(u16) == 2, "sizeof(u16)");
static_assert(sizeof(u32) == 4, "sizeof(u32)");
static_assert(sizeof(u64) == 8, "sizeof(u64)");

typedef atomic_uchar  au8;
typedef atomic_ushort au16;
typedef atomic_uint   au32;
typedef atomic_ulong  au64;
typedef atomic_char   as8;
typedef atomic_short  as16;
typedef atomic_int    as32;
typedef atomic_long   as64;
static_assert(sizeof(au8) == 1, "sizeof(au8)");
static_assert(sizeof(au16) == 2, "sizeof(au16)");
static_assert(sizeof(au32) == 4, "sizeof(au32)");
static_assert(sizeof(au64) == 8, "sizeof(au64)");
static_assert(sizeof(as8) == 1, "sizeof(as8)");
static_assert(sizeof(as16) == 2, "sizeof(as16)");
static_assert(sizeof(as32) == 4, "sizeof(as32)");
static_assert(sizeof(as64) == 8, "sizeof(as64)");
#endif

// }}} types

// {{{ cacheline

#ifndef CSLZ
#define CLSZ (64u)
#endif

static inline void *clalloc(size_t size)
{
    size_t sz = (size / CLSZ + 1) * CLSZ;
    void *const ret = aligned_alloc(CLSZ, sz);
    memset(ret, 0, sz);
    return ret;
}

// }}} cacheline

// print error msg and force quit
static inline void panic_exit(const char *const fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    if (fmt[strlen(fmt)-1] != '\n') {
        printf("\n");
    }
    fflush(stdout);
    exit(1);
}

#ifdef __cplusplus
}
#endif

#endif
