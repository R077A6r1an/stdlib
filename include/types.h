/*
 * types header. Ready to use - Adrian Roß
 */

#ifndef types_std_included
#define types_std_included

#include <stddef.h>
#include <stdint.h>

typedef signed long ssize_t;

typedef uintptr_t paddr_t;
typedef void * vaddr_t;

typedef int pid_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef unsigned int tid_t;



typedef uint64_t timestamp_t;

typedef uint32_t syscall_id_t;

#endif
