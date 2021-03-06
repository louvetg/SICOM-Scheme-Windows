#ifndef _FORME_H_
#define _FORME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "object.h"
#include "eval.h"

#define NB_FORM 6

void init_tab_form(char tab_form[NB_FORM][STRLEN]);
void init_add_tab_form(adress tab_add_form[NB_FORM]);
object* quote (object* o);
object* and (object* o);
object* or (object* o);
object* define(object* o, object* obj_meta);
object* set(object* o, object* obj_meta);
object* si(object* o);

#ifdef __cplusplus
}
#endif

#endif /* _FORME_H_ */
