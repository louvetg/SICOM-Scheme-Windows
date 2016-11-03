#include "forme.h"

/**
*@fn void init_tab_form(char tab_form[NB_FORM][STRLEN])
*
*@brief Rempli un tableau contenant les noms des différentes formes qui seront intégrées à l'environnement meta.
*
*@param char tab_form[NB_FORM][STRLEN]) tableau allant contenir les noms de formes.
*/

void init_tab_form(char tab_form[NB_FORM][STRLEN]){
	strcpy(tab_form[0],"quote");
	strcpy(tab_form[1],"set!");
	strcpy(tab_form[2],"define");
	strcpy(tab_form[3],"and");
	strcpy(tab_form[4],"or");
	strcpy(tab_form[5],"if");
}

/**
*@fn void init_tab_form(char tab_form[NB_FORM][STRLEN])
*
*@brief Rempli un tableau contenant les "adresse" des différentes formes qui seront intégrées à l'environnement meta.
*Les adresses sont des entiers qui seront utiliser dans le switch contenant les fonction C.
*
*@param uint num_tab_form[NB_FORM]) tableau allant contenir les "adresse" des formes.
*/

void init_num_tab_form(uint num_tab_form[NB_FORM]){
	num_tab_form[0] = QUOTE;
	num_tab_form[1] = SET;
	num_tab_form[2] = DEFINE;
	num_tab_form[3] = AND;
	num_tab_form[4] = OR;
	num_tab_form[5] = IF;
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

object* forme(object* o, uint tst_form, object* obj_meta){
	switch(tst_form){
	case QUOTE :
		printf("evaluation de quote\n");
		return quote(o);
		break;
	case SET:
		printf("evaluation de set!\n");
		return set(o,obj_meta);
		break;
	case DEFINE:
		printf("evaluation de define\n");
		return define(o,obj_meta);
		break;
	case AND:
		printf("evaluation de and\n");
		return and(o);
		break;
	case OR:
		printf("evaluation de or\n");
		return or(o);
		break;
	case IF:
		printf("evaluation de if\n");
		return si(o);
		break;
	default:
		printf("Forme inconnue erreur\n");
		return NULL;
		break;
	}
}

/**
*@fn object* quote(object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans quote
*/

object* define(object* o, object* obj_meta){

	object* obj_car = make_object();
	obj_car->type = SFS_SYMBOL;
	strcpy(obj_car->this.symbol, o->this.pair.cdr->this.pair.car->this.symbol) ;

	object* obj_cdr = make_object();
	obj_cdr = obj_cpy(car(cdr(cdr(o))));
	obj_cdr = sfs_eval(obj_cdr);

	if (obj_cdr == NULL){	
		return NULL;}
	
	if (cdr(cdr(cdr(o))) != obj_empty_list){ return NULL;/*erreur*/ }

	object* obj_pair = make_object();
	obj_pair->type = SFS_PAIR;
	obj_pair->this.pair.car = obj_car;
	obj_pair->this.pair.cdr = obj_cdr;
	ajout_tete_env(obj_pair, obj_meta);

return obj_undef;
}


object* set(object* o, object* obj_meta){
	object* obj = test_symb(car(cdr(o)));

	if (obj == NULL){
		printf("Variable inconnue ou de mauvaise forme\n");
		return NULL;
	}

	if(cdr(o) == obj_empty_list){
		printf("Expression invalide dans le set\n");
		return NULL;	
	}
	if(cdr(cdr(o)) == obj_empty_list){
		printf("Expression invalide dans le set\n");
		return NULL;	
	}
	if (cdr(obj)->type == SFS_ADRESS){
		printf("Ecriture impossible, %s de l'environnement meta est protégé\n",car(obj)->this.symbol);
		return NULL;
	}

	free(obj->this.pair.cdr);
	object* val = make_object();
	val->type = sfs_eval(car(cdr(cdr(o))))->type;
	val->this = sfs_eval(car(cdr(cdr(o))))->this;
	obj->this.pair.cdr = val;
	return obj_undef;
}

/**
*@fn object* quote(object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans quote
*/


object* quote(object* o){

	if (cdr(cdr(o)) != obj_empty_list){ 
		printf("quote ne prend que 1 argument. Synthaxe (quote <datum>)\n");
		return NULL; }
	{

	if ((car(o->this.pair.cdr))->type == SFS_PAIR ) { /* Cas d'une liste */
		o->this.pair.car = car(car(o->this.pair.cdr));
		o->this.pair.cdr = cdr(car(o->this.pair.cdr));
	}
	else{ /* Cas d'un atome */
		object* p = make_object();
		p->type = car(cdr(o))->type;
		p->this = car(cdr(o))->this;
		return p;
	}
	

	}
	return o;
}


/**
*@fn object* and (object* o)
*
*@brief fonction "AND"
*
*@param object* o pointeur sur la structure à évaluer
*
*@return object* o valeur évaluée: TRUE ou FALSE
*/

object* and(object* o){
	if (cdr(o) == obj_empty_list){ 
		printf("and prend 2 arguments. Synthaxe (and <test> <test>*)\n");/*Réel syntaxe (and <and>*) à voir pour remplacer*/
		return NULL; }
	object* obj_pair_pred = cdr(o);
	uint res = 1;
	uint end = 0;
	do{
		object* a = sfs_eval(obj_pair_pred->this.pair.car);
		
		if (a == obj_false){ res = 0;}

		if (cdr(obj_pair_pred) == obj_empty_list){ 
			if (res != 0){ end = 1; }
			res = 0;
		}
		else { obj_pair_pred = cdr(obj_pair_pred); }
	} while (res);
	if (end){ return obj_true; }
	return obj_false;
}

/**
*@fn object* or (object* o)
*
*@brief fonction "OR"
*
*@param object* o pointeur sur la structure à évaluer
*
*@return object* o valeur évaluée: TRUE ou FALSE
*/

object* or(object* o){
	if (cdr(o) == obj_empty_list){ 
		printf("or prend 2 arguments. Synthaxe (or <test> <test>*)\n");/*Réel syntaxe (or <and>*) à voir pour remplacer*/
		return NULL;}
	object* obj_pair_pred = cdr(o);
	uint res = 1;
	uint end = 0;
	do{
		object* a = sfs_eval(obj_pair_pred->this.pair.car);

		if (a != obj_false){res = 0;}

		if (cdr(obj_pair_pred) == obj_empty_list){
			if (res != 0){ end = 1; }
			res = 0;
		}
		else { obj_pair_pred = cdr(obj_pair_pred); }
	} while (res);
	if (end){ return obj_false; }
	return obj_true;
}

object* si(object* o){
	if (cdr(o) == obj_empty_list){ goto erreur_si; }
	object* test = sfs_eval(car(cdr(o)));

	if (cdr(cdr(o)) == obj_empty_list){ goto erreur_si; }
	object* consequent = car(cdr(cdr(o)));

	object* alternate;
	if (cdr(cdr(cdr(o))) != obj_empty_list){
		alternate = car(cdr(cdr(cdr(o))));
		if (cdr(cdr(cdr(cdr(o)))) != obj_empty_list){ goto erreur_si; }
	}
	else{ alternate = obj_undef; }

	if (test == NULL){ 
		printf("Erreur lors de l'évaluation du test\n");
		return NULL; }
	

	if (test == obj_false){return sfs_eval(alternate);}
	return sfs_eval(consequent);
	
erreur_si:
	printf("if erreur de syntaxe. Synthaxe (if <expression> <tail expression> <tail expression>) ou (if <expression> <tail expression>)\n");/*Réel syntaxe (and <and>*) à voir pour remplacer*/
	return NULL; 

}
