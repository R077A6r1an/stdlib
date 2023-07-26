//XXX: The entire file is based on Linux code at arch/x86/boot/string.c
#include <stddef.h>
#include <stdbool.h>

#ifdef __GCC_ASM_FLAG_OUTPUTS__
#define CC_SET(c) "\n\t/* output condition code " #c "*/\n"
#define CC_OUT(c) "=@cc" #c
#else
#define CC_SET(c) "\n\tset" #c " %[_cc_" #c "]\n"
#define CC_OUT(c) [_cc_ ## c] "=qm"
#endif

#define in_memcpy(d,s,l) __builtin_memcpy(d,s,l)
#define in_memset(d,c,l) __builtin_memset(d,c,l)

int memcmp(const void *s1, const void *s2, size_t len) {
  bool diff;
  asm("repe; cmpsb" CC_SET(nz) : CC_OUT(nz) (diff), "+D" (s1), "+S" (s2), "+c" (len));
  return diff;
}

void* memset(void* ptr, int s, size_t t) {
  return in_memset(ptr, s, t);
}

void* memcpy(void* s1, const void* s2, size_t size) {
  return in_memcpy(s1, s2, size);
}
