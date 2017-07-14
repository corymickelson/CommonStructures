//
// Created by skyslope on 7/14/17.
//

#ifndef STRUCTURES_TRY_CATCH_H
#define STRUCTURES_TRY_CATCH_H

#include <setjmp.h>

#define try do { jmp_buf ex_buf__; switch( setjmp(ex_buf__)) {case 0: while(1) {
#define catch(x) break; case x:
#define finally break; } default: {
#define endtry break; }}} while(0)
#define throw(x) longjmp(ex_buf__, x)


#endif //STRUCTURES_TRY_CATCH_H
