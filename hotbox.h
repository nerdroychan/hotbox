/*
 * This is a header-only library for commonly used small nits
 */
#pragma once

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
#define _TYPE_ALIAS_DEFINED
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

// {{{ memory

#ifndef CSLZ
#define CLSZ (64u)
#endif

#ifndef BLKSZ
#define BLKSZ (512u)
#endif

#ifndef PGSZ
#define PGSZ (4096u)
#endif

static inline void *clalloc(size_t size)
{
    size_t sz = (size / CLSZ + 1) * CLSZ;
    void *const ret = aligned_alloc(CLSZ, sz);
    memset(ret, 0, sz);
    return ret;
}

static inline void *zmalloc(size_t size)
{
    void *const m = malloc(size);
    memset(m, 0, size);
    return m;
}

// }}} memory

// {{{ bits

static const u8 byte_reverse_table[256] = {
    0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
    0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8, 0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
    0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4, 0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
    0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec, 0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
    0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2, 0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
    0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea, 0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
    0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6, 0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
    0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee, 0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
    0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1, 0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
    0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9, 0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
    0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5, 0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
    0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed, 0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
    0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3, 0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
    0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb, 0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
    0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7, 0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
    0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef, 0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff
};

static inline u16 reverse_bits_u16(u16 n)
{
    u8 *const ptr = (u8 *)&n;
    ptr[0] = byte_reverse_table[ptr[0]];
    ptr[1] = byte_reverse_table[ptr[1]];
    return (u16 )__builtin_bswap16(n);
}

static inline u32 reverse_bits_u32(u32 n)
{
    u8 *const ptr = (u8 *)&n;
    ptr[0] = byte_reverse_table[ptr[0]];
    ptr[1] = byte_reverse_table[ptr[1]];
    ptr[2] = byte_reverse_table[ptr[2]];
    ptr[3] = byte_reverse_table[ptr[3]];
    return (u32)__builtin_bswap32(n);
}

static inline u64 reverse_bits_u64(u64 n)
{
    u8 *const ptr = (u8 *)&n;
    ptr[0] = byte_reverse_table[ptr[0]];
    ptr[1] = byte_reverse_table[ptr[1]];
    ptr[2] = byte_reverse_table[ptr[2]];
    ptr[3] = byte_reverse_table[ptr[3]];
    ptr[4] = byte_reverse_table[ptr[4]];
    ptr[5] = byte_reverse_table[ptr[5]];
    ptr[6] = byte_reverse_table[ptr[6]];
    ptr[7] = byte_reverse_table[ptr[7]];
    return (u64)__builtin_bswap64(n);
}

// }}} bits

// {{{ print

static inline void fprintf_sync(FILE *f, const char *const fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(f, fmt, args);
    va_end(args);
    if (fmt[strlen(fmt)-1] != '\n') {
        printf("\n");
    }
    fflush(f);
}

#define \
    printf_sync(...) \
    do { \
        fprintf_sync(stdout, __VA_ARGS__); \
    } while (0)

// }}} print

// {{{ panic

#define \
    panic_exit(...) \
    do { \
        fflush(stdout); \
        fprintf_sync(stderr, __VA_ARGS__); \
        exit(1); \
    } while (0)

// }}} panic

#ifdef __cplusplus
}
#endif
