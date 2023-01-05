/*
** $Id: lembed.h $
** Embedded platform adaptor layer of Lua
** See Copyright Notice in lua.h
*/

#ifndef lembed_h
#define lembed_h

#include <stdarg.h>
#include <sys/types.h>

#include "luaconf.h"


#ifndef HUGE_VAL
#if defined(__GNUC__)
#define HUGE_VAL __builtin_huge_val()
#endif
#endif

#ifndef LUAEM_JMP_BUF_SIZE
#define LUAEM_JMP_BUF_SIZE (sizeof(void *) * 32)
#endif

typedef union {
  char padding[LUAEM_JMP_BUF_SIZE];
#ifdef LUAEM_JMP_BUF_TYPE
  LUAEM_JMP_BUF_TYPE buf;
#endif
} luaEm_jmp_buf;

#if !defined(__clock_t_defined) && !defined(_CLOCK_T_DECLARED)
typedef	unsigned long clock_t;
#define	__clock_t_defined
#define	_CLOCK_T_DECLARED
#endif

#define LUA_MATH_FLOOR l_mathop(floor)
#define LUA_MATH_POW l_mathop(pow)
#define LUA_MATH_FMOD l_mathop(fmod)
#define LUA_MATH_LDEXP l_mathop(ldexp)
#define LUA_MATH_FREXP l_mathop(frexp)

#define LUAEM_API_DEFS \
  LUAEM_API_DEF_EMIT(char, getlocaledecpoint, (void), ()) \
  LUAEM_API_DEF_EMIT(clock_t, clock, (void), ()) \
  LUAEM_API_DEF_EMIT(time_t, time, (time_t *tloc), (tloc)) \
  LUAEM_API_DEF_EMIT(double, LUA_MATH_FLOOR, (double x), (x)) \
  LUAEM_API_DEF_EMIT(double, LUA_MATH_POW, (double a, double b), (a, b)) \
  LUAEM_API_DEF_EMIT(double, LUA_MATH_FMOD, (double a, double b), (a, b)) \
  LUAEM_API_DEF_EMIT(double, LUA_MATH_LDEXP, (double a, int b), (a, b)) \
  LUAEM_API_DEF_EMIT(double, LUA_MATH_FREXP, (double a, int *b), (a, b)) \
  LUAEM_API_DEF_EMIT(LUA_NUMBER, str2number, (const char *s, char *endptr), (s, endptr)) \
  LUAEM_API_DEF_EMIT(char *, strpbrk, (const char *s, const char *c), (s, c)) \
  LUAEM_API_DEF_EMIT(int, setjmp, (luaEm_jmp_buf *env), (env)) \
  LUAEM_API_DEF_EMIT(void, longjmp, (luaEm_jmp_buf *env, int status), (env, status)) \
  LUAEM_API_DEF_EMIT(void, vwritestringerror, (const char *fmt, va_list ap), (fmt, ap))

typedef struct luaEm_API {
#define LUAEM_API_DEF_EMIT(tret, name, args, cargs) \
  tret (*name) args;
  LUAEM_API_DEFS
#undef LUAEM_API_DEF_EMIT
} luaEm_API;

extern luaEm_API *luaEm_APIImpl;

#if !defined(LUA_USE_C89)
#define l_inline	inline
#elif defined(__GNUC__)
#define l_inline	__inline__
#else
#define l_inline	/* empty */
#endif

#define l_sinline	static l_inline

#define LUAEM_API_DEF_EMIT(tret, name, args, cargs) \
  l_sinline tret luaEm_##name args { \
    return luaEm_APIImpl->name cargs; \
  }
LUAEM_API_DEFS
#undef LUAEM_API_DEF_EMIT

#ifndef BUFSIZ
#define	BUFSIZ 1024
#endif

/*
@@ lua_getlocaledecpoint gets the locale "radix character" (decimal point).
** Change that if you do not want to use C locales. (Code using this
** macro must include the header 'locale.h'.)
*/
#if !defined(lua_getlocaledecpoint)
#define lua_getlocaledecpoint()		(luaEm_getlocaledecpoint())
#endif

#endif
