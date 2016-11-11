
/**
 * @file mem.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:06:23 2012
 * @brief Memory wrappers for malloc/free.
 *
 * Memory wrappers for malloc/free.
 */

#include "mem.h"




void *sfs_malloc( size_t size ) {

    return malloc( size );
}

void  sfs_free( void *ptr ) {

    free( ptr );
}

object * init_environnement(){
	obj_meta = make_object();
	obj_meta->type = SFS_PAIR;
	obj_meta->this.pair.car = obj_empty_list;
	obj_meta->this.pair.cdr = obj_empty_list;
	return obj_meta;
}

object * init_meta_env(char tab_form[NB_FORM][STRLEN], object* obj_meta, adress tab_add_form[NB_FORM] ){
	uint k = NB_FORM;
	uint j = NB_PRIM;
	uint i;
	object** list_pair_symb;
	object** symb;
	object** pair_symb;
	object** num;

	symb = calloc(k+j, sizeof(object*));
	for (i = 0; i < k+j; i++){ 
		symb[i] = calloc(1, sizeof(object*));
		symb[i]->type = SFS_SYMBOL; 
	}

	num = calloc(k+j, sizeof(object*));
	for (i = 0; i < k+j; i++){ 
		num[i] = calloc(1, sizeof(object*));
		num[i]->type = SFS_ADRESS;
	}

	list_pair_symb  = calloc(k, sizeof(object*));
	for (i = 0; i < k+j; i++){ list_pair_symb[i] = calloc(1, sizeof(object*)); }

	pair_symb = calloc(k, sizeof(object*));
	for (i = 0; i < k+j; i++){ pair_symb[i] = calloc(1, sizeof(object*)); }

	for (i = 0; i < k; i++){
		
		printf("%d_Contenu du tableau initial -- symb: %s, adresse: %d --\n",i,tab_form[i], tab_add_form[i]);
		symb[i]->type = SFS_SYMBOL;
		strcpy(symb[i]->this.symbol, tab_form[i]);

		num[i]->type = SFS_ADRESS;
		num[i]->this.adress = tab_add_form[i]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */
		printf("%d_Creation des objects -- symb: %s\n",i,symb[i]->this.symbol, num[i]->this.adress);

		pair_symb[i]->type = SFS_PAIR;
		pair_symb[i]->this.pair.car = symb[i]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */	
		pair_symb[i]->this.pair.cdr = num[i]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */

		printf("%d_Creation memoire de %s a l'adresse %d\n",i, pair_symb[i]->this.pair.car->this.symbol, pair_symb[i]->this.pair.cdr->this.adress);   

		list_pair_symb[i]->type = SFS_PAIR;
		list_pair_symb[i]->this.pair.car = pair_symb[i]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */
		list_pair_symb[i]->this.pair.cdr = obj_empty_list; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */
		if (i > 0){ list_pair_symb[i - 1]->this.pair.cdr = list_pair_symb[i]; }
		else { obj_meta->this.pair.car = list_pair_symb[i]; }
	}
	return obj_meta;
}

