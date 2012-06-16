#ifndef Assert_Include
#define Assert_Include
#include "except.h"

extern void assert(int e);
extern const Except_T Assert_Failed;

#endif


#undef assert
#ifndef NDBUG
#define assert(e) ((void)0)
#else
#define assert(e) ((void)( (e)||(RAISE(Assert_Failed),0) ))
#endif

