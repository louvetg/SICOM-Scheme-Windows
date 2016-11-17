#include "primitive.h"


/**
*@fn void init_tab_form(char tab_form[NB_FORM][STRLEN])
*
*@brief Rempli un tableau contenant les noms des différentes formes qui seront intégrées à l'environnement meta.
*
*@param char tab_form[NB_FORM][STRLEN]) tableau allant contenir les noms de formes.
*/

void init_tab_prim(char tab_form[NB_PRIM][STRLEN]){
	strcpy(tab_form[0],"-");
}

/**
*@fn void init_tab_form(char tab_form[NB_FORM][STRLEN])
*
*@brief Rempli un tableau contenant les "adresse" des différentes formes qui seront intégrées à l'environnement meta.
*Les adresses sont des entiers qui seront utiliser dans le switch contenant les fonction C.
*
*@param uint num_tab_form[NB_FORM]) tableau allant contenir les "adresse" des formes.
*/

void init_add_tab_prim(adress tab_add_form[NB_PRIM]){
	tab_add_form[0].addtype = ADD_PRIMITIVE;
	tab_add_form[0].this.forme = *moins;
}




object* moins (object* o){
	if (o == obj_empty_list)
	{
		WARNING_MSG("Le calcul est vide");
		return NULL;
	}
	object* obj_sous = make_object();
	obj_sous->type = SFS_NUMBER;
	obj_sous->this.number.this.integer = car(o)->this.number.this.integer ;
	o = cdr (o);
	while (o != obj_empty_list)
	{
		obj_sous->this.number.this.integer = obj_sous->this.number.this.integer  -  car(o)->this.number.this.integer;
		o = cdr(o);
	}
	return obj_sous;
}


