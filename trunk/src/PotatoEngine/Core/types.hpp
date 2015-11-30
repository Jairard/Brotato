#ifndef __POT_CORE_TYPES__
#define __POT_CORE_TYPES__

#include <cstdint>
#include <assert.h>

typedef  int8_t  poti8; // pot_i8, pot_int8 ?
typedef uint8_t  potu8; // pot_u8, pot_uint8 ?
typedef  int16_t poti16;
typedef uint16_t potu16;
typedef  int32_t poti32;
typedef uint32_t potu32;
typedef  int64_t poti64;
typedef uint64_t potu64;

typedef unsigned char potb;
typedef float  potf32;
typedef double potf64;

static_assert(sizeof(poti8) == 1, "");
static_assert(sizeof(potu8) == 1, "");
static_assert(sizeof(poti16) == 2, "");
static_assert(sizeof(potu16) == 2, "");
static_assert(sizeof(poti32) == 4, "");
static_assert(sizeof(potu32) == 4, "");
static_assert(sizeof(poti64) == 8, "");
static_assert(sizeof(potu64) == 8, "");

static_assert(sizeof(potb) == 1, "");
static_assert(sizeof(potf32) == 4, "");
static_assert(sizeof(potf64) == 8, "");

#endif
