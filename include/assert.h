#ifndef stdlib_assert_included
#define stdlib_assert_included

// for NULL
#include <stddef.h>

//FIXME: this is not really what assert should do, but in a freestanding environment it is a bit questionable to end the programm

// if you want to stop you software by a assertion, define ASSERT_HARD
#ifdef ASSERT_HART
#  define assert(x) if(x == 0) { \
                      asm volatile("cli; hlt"); \
                    }
#else
#  define assert(x) x == 0
#endif

#define static_assert _Static_assert

#endif
