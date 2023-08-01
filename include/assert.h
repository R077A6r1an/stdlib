#ifndef stdlib_assert_included
#define stdlib_assert_included

// for NULL
#include <stddef.h>
#include <stdio.h>

//FIXME: this is not really what assert should do, but in a freestanding environment it is a bit questionable to end the programm

// if you want to stop you software by a assertion, define ASSERT_HARD
#ifdef ASSERT_HART
#  define assert(x) if(x == 0) { \
                      asm volatile("cli; hlt"); \
                    }
#else
// if you dont want to terminate the process, assert will just print a error message.
// Normaly on stderr, but fprintf currently has issues.
#  define assert(x) if(x == 0) { \
                      printf("Assertion failed: function %s, file %s, line %s\n", __func__, __FILE__, __LINE__); \
                    }
#endif

#define static_assert _Static_assert

#endif
