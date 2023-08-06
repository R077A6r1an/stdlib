#include <os-dep.h>

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//XXX: Linux function at arch/x86/boot/printf.c line 18
static int skip_atoi(const char** str)  {
  int i = 0;
  while(isdigit(**str)) {
    i = i * 10 + *((*str)++) - '0';
  }
  return i;
}

//XXX: Linux defines at arch/x86/boot/printf.c line 27 following
#define ZEROPAD	1		/* pad with zero */
#define SIGN	2		/* unsigned/signed long */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SMALL	32		/* Must be 32 == 0x20 */
#define SPECIAL	64		/* 0x */

#define __do_div(n, base) ({ \
int __res; \
__res = ((unsigned long) n) % (unsigned) base; \
n = ((unsigned long) n) / (unsigned) base; \
__res; })

//XXX: Linux function at arch/x86/boot/printf.c line 41
static char *number(char *str, long num, int base, int size, int precision, int type) {
  static const char digits[16] = "0123456789ABCDEF";
  char tmp[66];
  char c, sign, locase;
  int i;
  locase = (type & SMALL);
  if (type & LEFT) {
    type &= ~ZEROPAD;
  }
  if (base < 2 || base > 16) {
    return NULL;
  }
  c = (type & ZEROPAD) ? '0' : ' ';
  sign = 0;
  if (type & SIGN) {
    if (num < 0) {
      sign = '-';
      num = -num;
      size--;
    } else if (type & PLUS) {
      sign = '+';
      size--;
    } else if (type & SPACE) {
      sign = ' ';
      size--;
    }
  }
  if (type & SPECIAL) {
    if (base == 16) {
      size -= 2;
    }else if (base == 8){
      size--;
    }
  }
  i = 0;
  if (num == 0) {
    tmp[i++] = '0';
  }else{
    while (num != 0){
      tmp[i++] = (digits[__do_div(num, base)] | locase);
    }
  }
  if (i > precision) {
    precision = i;
  }
  size -= precision;
  if (!(type & (ZEROPAD + LEFT))) {
    while (size-- > 0) {
      *str++ = ' ';
    }
  }
  if (sign) {
    *str++ = sign;
  }
  if (type & SPECIAL) {
    if (base == 8) {
      *str++ = '0';
    }else if (base == 16) {
      *str++ = '0';
      *str++ = ('X' | locase);
    }
  }
  if (!(type & LEFT)) {
    while (size-- > 0) {
      *str++ = c;
    }
  }
  while (i < precision--) {
    *str++ = '0';
  }
  while (i-- > 0) {
    *str++ = tmp[i];
  }
  while (size-- > 0) {
    *str++ = ' ';
  }
  return str;
}

//XXX: Linux function at arch/x86/boot/printf.c line 113
int vsprintf(char *buf, const char *fmt, va_list args) {
  int len;
  unsigned long num;
  int i, base;
  char *str;
  const char *s;
  int flags;		/* flags to number() */
  int field_width;	/* width of output field */
  int precision;		/* min. # of digits for integers; max*/
  int qualifier;		/* 'h', 'l', or 'L' for integer fields */
  for (str = buf; *fmt; ++fmt) {
    if (*fmt != '%') {
      *str++ = *fmt;
      continue;
    }
    flags = 0;
  repeat:
    ++fmt;		/* this also skips first '%' */
    switch (*fmt) {
      case '-':
        flags |= LEFT;
        goto repeat;
      case '+':
        flags |= PLUS;
        goto repeat;
      case ' ':
        flags |= SPACE;
        goto repeat;
      case '#':
        flags |= SPECIAL;
        goto repeat;
      case '0':
        flags |= ZEROPAD;
        goto repeat;
    }
    field_width = -1;
    if (isdigit(*fmt)){
      field_width = skip_atoi(&fmt);
    }else if (*fmt == '*') {
      ++fmt;
      field_width = va_arg(args, int);
      if (field_width < 0) {
        field_width = -field_width;
        flags |= LEFT;
      }
    }
    precision = -1;
    if (*fmt == '.') {
      ++fmt;
      if (isdigit(*fmt)) {
        precision = skip_atoi(&fmt);
      }else if (*fmt == '*') {
        ++fmt;
        precision = va_arg(args, int);
      }
      if (precision < 0){ 
        precision = 0;
      }
    }
    qualifier = -1;
    if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L') {
      qualifier = *fmt;
      ++fmt;
    }
    base = 10;
    switch (*fmt) {
      case 'c':
        if (!(flags & LEFT)) {
          while (--field_width > 0){
            *str++ = ' ';
          }
        }
        *str++ = (unsigned char)va_arg(args, int);
        while (--field_width > 0) {
          *str++ = ' ';
        }
        continue;
      case 's':
        s = va_arg(args, char *);//Solved: by calling fprintf(stdio, "format %s", "String), I got by a unit test a memory runtime error. But solved cause of false stdarg usage.
        len = strnlen(s, precision);
        if (!(flags & LEFT)) {
          while (len < field_width--) {
            *str++ = ' ';
          }
        }
        for (i = 0; i < len; ++i) {
          *str++ = *s++;
        }
        while (len < field_width--) {
          *str++ = ' ';
        }
        continue;
      case 'p':
        if (field_width == -1) {
          field_width = 2 * sizeof(void *);
          flags |= ZEROPAD;
        }
        str = number(str, (unsigned long)va_arg(args, void *), 16, field_width, precision, flags);
        continue;
      case 'n':
        if (qualifier == 'l') {
          long *ip = va_arg(args, long *);
          *ip = (str - buf);
        } else {
          int *ip = va_arg(args, int *);
          *ip = (str - buf);
        }
        continue;
      case '%':
        *str++ = '%';
        continue;
      case 'o':
        base = 8;
        break;
      case 'x':
        flags |= SMALL;
      case 'X':
        base = 16;
        break;
      case 'd':
      case 'i':
        flags |= SIGN;
      case 'u':
        break;
      default:
        *str++ = '%';
        if (*fmt) {
          *str++ = *fmt;
        }else{
          --fmt;
        }
        continue;
    }
    if (qualifier == 'l') {
      num = va_arg(args, unsigned long);
    }else if (qualifier == 'h') {
      num = (unsigned short)va_arg(args, int);
      if (flags & SIGN) {
        num = (short)num;
      }
    } else if (flags & SIGN) {
      num = va_arg(args, int);
    }else{
      num = va_arg(args, unsigned int);
    }
    str = number(str, num, base, field_width, precision, flags);
  }
  *str = '\0';
  return str - buf;
}

//XXX: Linux function at arch/x86/boot/printf.c line 283
int sprintf(char *buf, const char *fmt, ...) {
  va_list args;
  int i;
  va_start(args, fmt);
  i = vsprintf(buf, fmt, args);
  va_end(args);
  return i;
}

//XXX: Linux function at arch/x86/boot/printf.c line 294
int printf(const char *fmt, ...) {
  char printf_buf[1024];
  va_list args;
  int printed;
  va_start(args, fmt);
  printed = vsprintf(printf_buf, fmt, args);
  va_end(args);
  stdout_print(printf_buf);
  return printed;
}

int fprintf(FILE* stream, const char* str, ...) {
  char buffer[1024];
  va_list args;
  if(str == NULL) {
    return -1;
  }
  va_start(args, str);
  vsprintf(buffer, str, args);
  va_end(args)
  if(stream == stdout) {
    stdout_print(buffer);
    return 0;
  }else if(stream == stdin) {
    return 0;//XXX: Think we should not write in stdin
  }else if(stream == stderr) {
    stderr_print(buffer);
    return 0;
  }
  int i = 0;
  int code = 0;
  while(buffer[i] != '\0' && code == 0) {
    // code = fputc((int)buffer[i], stream); FIXME: till now not supported, you can enable it after adding file support
    i++;
  }
  if(code != 0) {
    return -1;
  }
  return 0;
}

int asprintf(char **buffer, const char *format, ...) {
  char buffer_a[1024];
  va_list args;
  va_start(args, format);
  int out = sprintf(buffer_a, format, args);
  va_end(args);
  out = strlen(buffer_a)+1;
#ifdef MALLOC_AVAILABLE
  *buffer = (char*)malloc(out*sizeof(char));
#else
  *buffer = NULL;
#warning "Till now no support for dynamic memory management, asprintf is unuseable"
#endif
  if(buffer == NULL) {
    return 0;
  }
  for(int i = 0; i < out; i++) {
    *buffer[i] = buffer_a[i];
  }
  return out-1;
}

extern int snprintf(char * buffer, size_t size, const char * format, ...) {
  char buffer_a[1024];
  va_list args;
  va_start(args, format);
  int out = sprintf(buffer_a, format, args);
  va_end(args);
  for(int i = 0; i < size-1; i++) {
    buffer[i] = buffer_a[i];
  }
  buffer[size-1] = '\0';
  return out;
}
