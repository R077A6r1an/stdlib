#ifndef stdlib_string_included
#define stdlib_string_included

#include <stddef.h>

extern void* memcpy(void*, const void*, size_t);
//extern void* memmove(void*, const void*, size_t);               //TODO
//extern char* strcpy(char*, const char*);                        //TODO
//extern char* strncpy(char*, const char*, size_t);               //TODO
//extern char* strcat(char*, const char*);                        //TODO
//extern char* strncat(char*, const char*, size_t);               //TODO
extern int memcmp(const void*, const void*, size_t);
extern int strcmp(const char*, const char*);
//extern int strcoll(const char*, const char*);                   //TODO
extern int strncmp(const char*, const char*, size_t);
//size_t strxfrm(char*, const char*);        // std functions,
//void* memchr(const void*, int, size_t);    // maybe not used
//extern char* strrchr(const char*, int);                         //TODO
//extern char* strchr(const char*, int);                          //TODO
extern void* memset(void*, int, size_t);
extern size_t strlen(const char*);
//extern size_t strnlen(const char*, int);                        //TODO

//extern char* strtok(char*, const char*);                        //TODO
//extern char* strdup(const char*);                               //TODO

#endif
