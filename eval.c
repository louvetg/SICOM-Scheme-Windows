
/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"


object* car(object * o){
	return o->this.pair.car;
}

object* cdr(object * o){
	return o->this.pair.cdr;
}

uint test_auto_eval(object* o){
	if (o->type == SFS_NUMBER){ return SFS_NUMBER; }
	if (o->type == SFS_BOOLEAN){ return SFS_BOOLEAN; }
	if (o->type == SFS_STRING){ return SFS_STRING; }
	if (o->type == SFS_CHARACTER){ return SFS_CHARACTER; }
	if (o->type == SFS_UNDEF){ return SFS_UNDEF; }
	return 0xFF;
}

object* test_symb(object* o){
	printf("Test forme -- \n");
	if (o->type != SFS_SYMBOL){ return NULL; }
	printf("L'objet est de type symbole\n");

	uint k = 0;
	uint end = 0;
	int cond = 1;
	object* m;
	object* s;

	m = car(obj_meta);

	do{
		if (car(car(m))->type == SFS_SYMBOL){
		printf("Symbole stocké en mémoire: %s \n",car(car(m))->this.symbol);
			if (strcmp(car(car(m))->this.symbol, o->this.symbol) == 0){
				cond = 0;
				s = car(m);
			}
		}
		else{
			printf("L'element stocke n'est pas de type symbole\n");
		}
		if (cdr(m) == obj_empty_list && cond == 1){
			cond = 0;
			end = 1;
		}
		m = cdr(m);


	} while (cond);

	if (end){ return NULL; }

	return s;
}

/**
*@fn object* forme(object* o, uint tst_form, object* obj_meta)
*
*@brief Lien à travers un switch entre les adresses les fonction C des formes.
*
*@param object* o pointeur vers un objet de type pair dont le car est une forme connu.
*@param uint tst_form entier contenant "l'adresse" de la forme.
*@param object* obj_meta pointeur vers un objet dont le cdr.
*/

object* all_symb(object* o, adress tst_form, object* obj_meta){
	switch (tst_form.addtype){
	case  ADD_FORME:
		return (*tst_form.this.forme)(o);
		break;
	case ADD_MEM_FORME:
		return (*tst_form.this.mem_forme)(o, obj_meta);
		break;
	case ADD_PRIMITIVE:
		return (*tst_form.this.prim)(o);
	default:
		printf("Forme inconnue erreur\n");
		return NULL;
		break;
	}
}


void ajout_tete_env(object* o, object* env){
	object* obj = make_object();
	obj->type = SFS_PAIR;
	obj->this.pair.cdr = env->this.pair.car;
	obj->this.pair.car = o;
	env->this.pair.car = obj;
}


object* sfs_eval(object * input, int prim ){

	object* obj = input;
	uint atm = 1;


	uint tst_auto = test_auto_eval(obj);
		if (tst_auto != 0xFF){
			return input;
		}
	
	if (obj->type == SFS_PAIR){
			obj = car(obj);
			atm = 0;
		}

	object*  tst_symb = test_symb(obj);
	if (tst_symb == NULL){
		if(atm){
			printf("%s, n'est pas stocké en mémoire\n", obj->this.symbol);
			return NULL;
		}
		else{printf("Car de la liste n'est pas une fonction\n");}
		return NULL;
	}
	if (cdr(tst_symb)->type == SFS_ADRESS){
		if(atm){
			printf("Expression invalide pour %s\n", obj->this.symbol);
			return NULL;
		}
		return all_symb(input, cdr(tst_symb)->this.adress, obj_meta);			
	}
	else{ 
		return obj_cpy(cdr(tst_symb));
	}

}
