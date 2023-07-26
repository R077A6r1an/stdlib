#ifndef stdio_std_included
#define stdio_std_included

#include <Operator/fsdev.h>
#include <stdarg.h>
#include <stddef.h>

#define FILE int

static int stderr_stream = 3;
static int stdin_stream = 1;
static int stdout_stream = 2;

static FILE* stdout = &stdout_stream;
static FILE* stdin = &stdin_stream;
static FILE* stderr = &stderr_stream;

extern int printf(const char * format, ...);

extern int sprintf(char * buffer, const char * format, ...);
extern int snprintf(char * buffer, size_t size, const char * format, ...);
extern int fprintf(FILE * fp, const char * format, ...);
extern int asprintf(char ** buffer, const char * format, ...);

//extern int vprintf(const char * format, va_list);//TODO
//extern int vsprintf(char * buffer, const char * format, va_list);
//extern int vsnprintf(char * buffer, size_t size, const char * format, va_list);//TODO
//extern int vfprintf(FILE * fp, const char * format, va_list);//TODO
//extern int vasprintf(char ** buffer, const char * format, va_list);//TODO
/*
extern int scanf(const char* fmt, ...);
extern int sscanf(const char* input, const char* fmt, ...);
extern int fscanf(FILE* f, const char* fmt, ...);

extern int vscanf(const char* fmt, va_list ap);
extern int vsscanf(const char* input, const char* fmt, va_list ap);
extern int vfscanf(FILE* f, const char* fmt, va_list ap);
*/

//extern FILE* fopen(const char* filename, const char* mode);//TODO
//extern int fclose(FILE* io_res);//TODO

//extern int fgetc(FILE* io_res);//TODO

//extern size_t fwrite(const void* src, size_t blocksize, size_t blockcount, FILE* io_res);//TODO
//extern size_t fread(char*, size_t, size_t, FILE*);//TODO
//extern int fputc(int c, FILE *io_res);//TODO
//extern int fputs(const char *str, FILE *io_res);//TODO

//extern int fseek(FILE* io_res, long int offset, int origin);//TODO

//extern int feof(FILE* io_res);//TODO
//extern int ferror(FILE* io_res);//TODO

//extern int fflush(FILE* io_res);//TODO
//extern int remove(const char* filename);//TODO
//extern int rename(const char *oldpath, const char *newpath);//TODO

//extern int puts(char* str);//TODO

#endif
