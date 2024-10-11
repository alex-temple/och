#ifndef O_DEFINES
#define O_DEFINES

#define OINLINE __attribute__((always_inline)) inline
#define ONOINLINE __attribute__((noinline))

#define OERROR -1

typedef enum { false, true } bool;
#define BOOL_TO_STRING(x) x == true ? "true" : "false"

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

_Static_assert(sizeof(i8) == 1, "i8 should be 1 byte");
_Static_assert(sizeof(i16) == 2, "i16 should be 2 bytes");
_Static_assert(sizeof(i32) == 4, "i32 should be 4 bytes");
_Static_assert(sizeof(i64) == 8, "i64 should be 8 bytes");

_Static_assert(sizeof(u8) == 1, "u8 should be 1 byte");
_Static_assert(sizeof(u16) == 2, "u16 should be 2 bytes");
_Static_assert(sizeof(u32) == 4, "u32 should be 4 bytes");
_Static_assert(sizeof(u64) == 8, "u64 should be 8 bytes");

_Static_assert(sizeof(f32) == 4, "f32 should be 4 bytes");
_Static_assert(sizeof(f64) == 8, "f64 should be 8 bytes");

typedef char* ostring;

#endif