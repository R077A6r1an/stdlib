#include <stddef.h>
#include <string.h>

// NOTE: no protection against buffer overflow!
size_t strlen(const char* str) {
    size_t size = 0;
    while(str[size] != '\0' /*&& sizeof(str)/sizeof(char) > size*/) {
        size++;
    }
    return size;
}

int strcmp(const char* s1, const char* s2) {
    int i1 = strlen(s1);
    int i2 = strlen(s2);
    if(i1 != i2) {
        return i1 > i2 ? i1 : i2;
    }
    i1  = 0;
    while(s1[i1] != '\0' && s2[i1] != '\0' && i2 >= i1) {
        if(s1[i1] != s2[i1]) {
            return -1;
        }
        i1++;
    }
    return 0;
}

int strncmp(const char* s1, const char*s2, size_t num) {
    int i1 = 0;
    int i2 = 0;
    while(s1[i1] != '\0' && s2[i1] != '\0' && i2 >= i1 && i1 != num) {
        if(s1[i1] != s2[i1]) {
            return -1;
        }
        i1++;
    }
    return 0;
}

size_t strnlen(const char* str, int len) {
  size_t size = 0;
  while(str[size] != '\0' && size != len) {
    size++;
  }
  return size;
}
char* strcpy(char* dest, const char* src) {
  if(!dest || !src) {
    return NULL;
  }
  size_t len = strlen(src) + 1;
  return (char*)memcpy((void*)dest, (void*)src, len);
}

char* strncpy(char* dest, const char* src, size_t len) {
  if(!dest || !src || !len) {
    return NULL;
  }
  char* out = memcpy((void*)dest, (void*)src, len);
  dest[len] = '\0';
  return out;
}

//TODO: implement all functions in include/string.h with a comment TODO after its declaration
