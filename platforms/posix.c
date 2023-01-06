#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <setjmp.h>

#ifdef setjmp
#define HAS_PREDEFINED_SETJMP
static inline int __orig_setjmp(jmp_buf __env) {
  return setjmp(__env);
}
#endif

#include "lembed.h"

static char getlocaledecpoint_imp() {
  return localeconv()->decimal_point[0];
}

clock_t clock_imp() {
  return clock();
}

time_t time_imp(time_t *t) {
  return time(t);
}

double floor_imp(double x) {
  return floor(x);
}

double ceil_imp(double x) {
  return ceil(x);
}

double log_imp(double x) {
  return log(x);
}

double log2_imp(double x) {
  return log2(x);
}

double log10_imp(double x) {
  return log10(x);
}

double sin_imp(double x) {
  return sin(x);
}

double cos_imp(double x) {
  return cos(x);
}

double tan_imp(double x) {
  return tan(x);
}

double asin_imp(double x) {
  return asin(x);
}

double acos_imp(double x) {
  return acos(x);
}

double atan2_imp(double x, double y) {
  return atan2(x, y);
}

double pow_imp(double a, double b) {
  return pow(a, b);
}

double fmod_imp(double a, double b) {
  return fmod(a, b);
}

double exp_imp(double x) {
  return exp(x);
}

double ldexp_imp(double a, int b) {
  return ldexp(a, b);
}

double frexp_imp(double a, int *b) {
  return frexp(a, b);
}

LUA_NUMBER str2number_imp(const char *s, const char *endptr) {
  return strtod(s, &endptr);
}

char *strpbrk_imp(const char *s, const char *c) {
  return strpbrk(s, c);
}

int setjmp_imp(luaEm_jmp_buf *env) {
#ifdef HAS_PREDEFINED_SETJMP
  int status = __orig_setjmp((void *) env);
#else
  int status = setjmp((void *) env);
#endif
  return status;
}

void longjmp_imp(luaEm_jmp_buf *env, int status) {
  longjmp((void *) env, status);
}

void *realloc_imp(void *ptr, size_t size) {
  return realloc(ptr, size);
}

void free_imp(void *ptr) {
  free(ptr);
}

void vwritestringerror_imp(const char *fmt, va_list ap) {
  vfprintf(stderr, fmt, ap);
}

void writestring_imp(const char *s, size_t size) {
  fwrite(s, sizeof(char), size, stdout);
}

void abort_imp() {
  abort();
}

static luaEm_API table = {
  .getlocaledecpoint = &getlocaledecpoint_imp,
  .clock = &clock_imp,
  .time = &time_imp,
  .floor = &floor_imp,
  .ceil = &ceil_imp,
  .log = &log_imp,
  .log2 = &log2_imp,
  .log10 = &log10_imp,
  .sin = &sin_imp,
  .cos = &cos_imp,
  .tan = &tan_imp,
  .asin = &asin_imp,
  .acos = &acos_imp,
  .atan2 = &atan2_imp,
  .pow = &pow_imp,
  .fmod = &fmod_imp,
  .exp = &exp_imp,
  .ldexp = &ldexp_imp,
  .frexp = &frexp_imp,
  .str2number = &str2number_imp,
  .strpbrk = &strpbrk_imp,
  .setjmp = &setjmp_imp,
  .longjmp = &longjmp_imp,
  .realloc = &realloc_imp,
  .free = &free_imp,
  .vwritestringerror = &vwritestringerror_imp,
  .writestring = &writestring_imp,
  .abort = &abort_imp
};

luaEm_API *luaEm_APIImpl = &table;
