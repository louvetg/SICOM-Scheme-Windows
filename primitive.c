#include "primitive.h"
#include <limits.h>

/**
*@fn void init_tab_form(char tab_form[NB_FORM][STRLEN])
*
*@brief Rempli un tableau contenant les noms des différentes formes qui seront intégrées à l'environnement meta.
*
*@param char tab_form[NB_FORM][STRLEN]) tableau allant contenir les noms de formes.
*/

void init_tab_prim(char tab_form[NB_PRIM][STRLEN]){
	strcpy(tab_form[0],"-");
	strcpy(tab_form[1],"+");
	strcpy(tab_form[2], "*");
	strcpy(tab_form[3], "/");
	strcpy(tab_form[4], "remainder");
	strcpy(tab_form[5], "=");
	strcpy(tab_form[6], "-");
}

/**
*@fn void init_tab_form(char tab_form[NB_FORM][STRLEN])
*
*@brief Rempli un tableau contenant les "adresse" des différentes formes qui seront intégrées à l'environnement meta.
*Les adresses sont des entiers qui seront utiliser dans le switch contenant les fonction C.
*
*@param uint num_tab_form[NB_FORM]) tableau allant contenir les "adresse" des formes.
*/

void init_add_tab_prim(object* (*prim[NB_PRIM])(object*)){
	prim[0] = *moins;
	prim[1] = *plus;
	prim[2] = *produit;
	prim[3] = *quotient;
	prim[4] = *remainder;
	prim[5] = *egal;
}




/***********************************************************************************************************
/***********************************************************************************************************
/****
/****        Arithmétique entière
/****
/****
/**
*@fn object* moins (object* o)
*
*@brief Soustraction
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/

object* moins (object* o){
	if (o == obj_empty_list) // Cas liste vide
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_sous = make_object();
	obj_sous->type = SFS_NUMBER;
	obj_sous->this.number.this.integer = 0;
	if (cdr(o) == obj_empty_list) // Si 1 élément: on renvoie l'inverse
	{
		obj_sous= - car(o)->this.number.this.integer;
		return obj_sous;
	}
	else
	{
		obj_sous->this.number.this.integer = car(o)->this.number.this.integer - car(cdr(o))->this.number.this.integer;
		o = cdr(o);
		while (cdr(o) != obj_empty_list)
		{
			if ( (INT_MIN + o->this.number.this.integer) > obj_sous->this.number.this.integer) //verif qu'on atteint pas la limite
			{
				WARNING_MSG("Overflow"); // message mais l'opération continue
			}
		obj_sous->this.number.this.integer = obj_sous->this.number.this.integer - car(o)->this.number.this.integer; //(- a b) = a-b
		o = cdr(o);
		}
	}
	//verif que la soustraction est un integer-----------------------A VERIFIER
	return obj_sous;
}




/**
*@fn object* plus (object* o)
*
*@brief Addition
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/


object* plus (object* o){
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_somme = make_object();
	obj_somme->type = SFS_NUMBER;
	obj_somme->this.number.this.integer = 0;
	do
	{
		//verif qu'on atteint pas la limite  -----------------------A VERIFIER
		if (INT_MIN - o->this.number.this.integer > obj_somme)
		{
			WARNING_MSG("Overflow"); // message mais l'opération continue
		}
		obj_somme->this.number.this.integer = car(o)->this.number.this.integer+ obj_somme->this.number.this.integer;
		o = cdr(o);
	}while (o != obj_empty_list);
	//verif que l'addition est un integer-----------------------A VERIFIER
	return obj_somme;
}

/**
*@fn object* produit (object* o)
*
*@brief Multiplication
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/


object* produit(object* o){
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_produit = make_object();
	obj_produit->type = SFS_NUMBER;
	obj_produit->this.number.this.integer = 1;
	do
	{
		//verif qu'on atteint pas la limite -----------------------A VERIFIER
		if (INT_MIN / o->this.number.this.integer > obj_produit)
		{
			WARNING_MSG("Overflow"); // message mais l'opération continue
		}
		obj_produit->this.number.this.integer = car(o)->this.number.this.integer* obj_produit->this.number.this.integer;
		o = cdr(o);
	} while (o != obj_empty_list);
	//verif que la multiplication est un integer-----------------------A VERIFIER
	return obj_produit;
}







/**
*@fn object* quotient (object* o)
*
*@brief Division
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/


object* quotient(object* o){
	if ((o == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_divis = make_object();
	obj_divis->type = SFS_NUMBER;
	obj_divis->this.number.this.integer = 1;
	if (cdr(o) == obj_empty_list)
	{
		obj_divis->this.number.this.integer = obj_divis->this.number.this.integer / car(o)->this.number.this.integer;
		return obj_divis;
	}
	else
	{
		obj_divis->this.number.this.integer = car(o)->this.number.this.integer / car(cdr(o))->this.number.this.integer;
		o = cdr(o);
		while (cdr(o) != obj_empty_list)
		{
			//verif qu'on atteint pas la limite -----------------------A VERIFIER
			if (obj_divis->this.number.this.integer == 0)
			{
				WARNING_MSG("Division par 0"); // message mais l'opération continue
				return NULL;
			}
			obj_divis->this.number.this.integer = obj_divis->this.number.this.integer / car(o)->this.number.this.integer;
			o = cdr(o);
		}
	}
	//verif que la division est un integer-----------------------A VERIFIER
	return obj_divis;
}


/**
*@fn object* remainder (object* o)
*
*@brief Renvoi le reste d'une division
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/


object* remainder(object* o){
	object* obj_reste = make_object();
	obj_reste->type = SFS_NUMBER;
	obj_reste->this.number.this.integer = 1;
	if ((o == obj_empty_list) || (cdr(o) == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	if (cdr(cdr(o)) != obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	obj_reste->this.number.this.integer = car(o)->this.number.this.integer % car(cdr(o))->this.number.this.integer;
	//verif que le reste est un integer-----------------------A VERIFIER
	return obj_reste;
}







/**
*@fn object* egal (object* o)
*
*@brief Evalue l'égalité
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/


object* egal(object* o){
	if ((o == obj_empty_list) || (cdr(o) == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{
		if (car(o)->this.number.this.integer == car(cdr(o))->this.number.this.integer)
		{
			obj_res = obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res = obj_false;
			return obj_res;
		}
	} while (cdr(cdr(o)) != obj_empty_list);
	//verif que le résultat est un bouleen-----------------------A VERIFIER
	return obj_res;
}










