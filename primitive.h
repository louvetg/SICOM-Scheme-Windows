#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "object.h"
#include "eval.h"

#define NB_PRIM 1

void init_tab_prim(char tab_form[NB_PRIM][STRLEN]);
void init_add_tab_prim(adress tab_add_form[NB_PRIM]);

object* moins (object* o);


#ifdef __cplusplus
}
#endif

#endif /* _PRIMITIVE_H_ */
