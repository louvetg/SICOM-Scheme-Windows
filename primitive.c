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
	/*strcpy(tab_form[0],"-");
	strcpy(tab_form[1],"+");
	strcpy(tab_form[2],"*");
	strcpy(tab_form[3],"/");
	strcpy(tab_form[4],"remainder");
	strcpy(tab_form[5],"=");
	strcpy(tab_form[0],"<");
	strcpy(tab_form[1],">");
	strcpy(tab_form[2],"abs");
	strcpy(tab_form[3],"null?");
	strcpy(tab_form[4],"boolean?");
	strcpy(tab_form[0],"symbol?");
	strcpy(tab_form[1],"integer?");
	strcpy(tab_form[2],"char?");
	strcpy(tab_form[3],"string?");
	strcpy(tab_form[4],"pair?");
	strcpy(tab_form[0],"cons");
	strcpy(tab_form[1],"car");
	strcpy(tab_form[2],"cdr");
	strcpy(tab_form[3],"set-car!");
	strcpy(tab_form[4],"set-cdr!");
	strcpy(tab_form[],"list");
	strcpy(tab_form[5],"eq?");
	*/strcpy(tab_form[0],"char->integer");
	strcpy(tab_form[1],"integer->char");
	strcpy(tab_form[2],"number->string");
	strcpy(tab_form[3],"string->number");
	strcpy(tab_form[4],"symbol->string");
	strcpy(tab_form[5],"string->symbol");


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
	/*tab_add_form[0].addtype = ADD_PRIMITIVE;
    tab_add_form[0].this.forme = *moins;
	tab_add_form[1].addtype = ADD_PRIMITIVE;
	tab_add_form[1].this.forme = *plus;
	tab_add_form[2].addtype = ADD_PRIMITIVE;
	tab_add_form[2].this.forme = *produit;
	tab_add_form[3].addtype = ADD_PRIMITIVE;
	tab_add_form[3].this.forme = *quotient;
	tab_add_form[4].addtype = ADD_PRIMITIVE;
	tab_add_form[4].this.forme = *remainder;
	tab_add_form[5].addtype = ADD_PRIMITIVE;
	tab_add_form[5].this.forme = *egal;
	tab_add_form[0].addtype = ADD_PRIMITIVE;
	tab_add_form[0].this.forme = *inferio;
	tab_add_form[1].addtype = ADD_PRIMITIVE;
	tab_add_form[1].this.forme = *superio;
    tab_add_form[5].addtype = ADD_PRIMITIVE;
	tab_add_form[5].this.forme = *fabs;
	tab_add_form[3].addtype = ADD_PRIMITIVE;
	tab_add_form[3].this.forme = *isnull;
	tab_add_form[4].addtype = ADD_PRIMITIVE;
	tab_add_form[4].this.forme = *isboolean;
	tab_add_form[0].addtype = ADD_PRIMITIVE;
	tab_add_form[0].this.forme = *issymbol;
	tab_add_form[1].addtype = ADD_PRIMITIVE;
	tab_add_form[1].this.forme = *isinteger;
	tab_add_form[2].addtype = ADD_PRIMITIVE;
	tab_add_form[2].this.forme = *ischar;
	tab_add_form[3].addtype = ADD_PRIMITIVE;
	tab_add_form[3].this.forme = *isstring;
	tab_add_form[4].addtype = ADD_PRIMITIVE;
	tab_add_form[4].this.forme = *ispair;
	tab_add_form[0].addtype = ADD_PRIMITIVE;
	tab_add_form[0].this.forme = *cons;
	tab_add_form[1].addtype = ADD_PRIMITIVE;
	tab_add_form[1].this.forme = *fcar;
	tab_add_form[2].addtype = ADD_PRIMITIVE;
	tab_add_form[2].this.forme = *fcdr;
	tab_add_form[3].addtype = ADD_PRIMITIVE;
	tab_add_form[3].this.forme = *setcar;
	tab_add_form[4].addtype = ADD_PRIMITIVE;
	tab_add_form[4].this.forme = *setcdr;
	tab_add_form[21].addtype = ADD_PRIMITIVE;
	tab_add_form[21].this.forme = *islist;
	tab_add_form[5].addtype = ADD_PRIMITIVE;
	tab_add_form[5].this.forme = *iseq;*/
	tab_add_form[0].addtype = ADD_PRIMITIVE;
	tab_add_form[0].this.forme = *char2integer;
	tab_add_form[1].addtype = ADD_PRIMITIVE;
	tab_add_form[1].this.forme = *integer2char;
	tab_add_form[2].addtype = ADD_PRIMITIVE;
	tab_add_form[2].this.forme = *number2string;
	tab_add_form[3].addtype = ADD_PRIMITIVE;
	tab_add_form[3].this.forme = *string2number;
	tab_add_form[4].addtype = ADD_PRIMITIVE;
	tab_add_form[4].this.forme = *symbol2string;
	tab_add_form[5].addtype = ADD_PRIMITIVE;
	tab_add_form[5].this.forme = *string2number;

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
**/
/*

object* moins (object* o){
	if (o == obj_empty_list) // Cas liste vide
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_sous = make_object();
	obj_sous->type = SFS_NUMBER;
	obj_sous->this.number.this.integer = 0;
	/*if((car(o)-> type != SFS_NUMBER) ) // Cas arguments non nombres
    {
         WARNING_MSG("Au moins un argument non entier");
         return NULL;
    }
	if (cdr(o) == obj_empty_list) // Si 1 élément: on renvoie l'inverse
	{
		obj_sous= - car(o)->this.number.this.integer;
		return obj_sous;
	}
	else
    {
      /*  if((car(cdr(o))-> type != SFS_NUMBER) ) // Cas arguments non nombres
        {
            WARNING_MSG("Au moins un argument non entier");
            return NULL;
        }
        obj_sous->this.number.this.integer = car(o)->this.number.this.integer - car(cdr(o))->this.number.this.integer;
        o = cdr(o);
        while (cdr(o) != obj_empty_list)
        {
            /*if(car(cdr(o)) != SFS_NUMBER)
            {
                WARNING_MSG("Au moins un argument non entier");
                return NULL;
            }
            obj_sous->this.number.this.integer = obj_sous->this.number.this.integer - car(cdr(o))->this.number.this.integer; //(- a b) = a-b
            if ( INT_MIN >  obj_sous->this.number.this.integer) //verif qu'on atteint pas la limite
            {
                WARNING_MSG("Overflow"); // message mais l'opération continue
            }
            o = cdr(o);
        }
	}
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
**


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
		//if (INT_MIN - o->this.number.this.integer > obj_somme)
		//{
			//WARNING_MSG("Overflow"); // message mais l'opération continue
		//}
        if(car(o) != SFS_NUMBER)
        {
            WARNING_MSG("Au moins un argument non entier");
            return NULL;
        }
		obj_somme->this.number.this.integer = car(o)->this.number.this.integer+ obj_somme->this.number.this.integer;
		if (obj_somme->this.number.this.integer > INT_MAX)
        {
          WARNING_MSG("Overflow");
        }
		o = cdr(o);
	}while (o != obj_empty_list);
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
**

object* produit (object* o){
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
	    if (INT_MIN/car(o)->this.number.this.integer > obj_produit)
		{
			WARNING_MSG("Overflow"); // message mais l'opération continue
		}
        if(car(o) != SFS_NUMBER)
        {
            WARNING_MSG("Au moins un argument non entier");
            return NULL;
        }
		obj_produit->this.number.this.integer = car(o)->this.number.this.integer* obj_produit->this.number.this.integer;
		WARNING_MSG("sortie calcul produit");
		o = cdr(o);
	}while (o != obj_empty_list);
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
**

object* quotient (object* o){
	if ((o == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if(car(o)->this.number.this.integer = 0)
    {
        WARNING_MSG("Division par 0");
        return NULL;
    }
	object* obj_divis = make_object();
	obj_divis->type = SFS_NUMBER;
	obj_divis->this.number.this.integer = 1;
    if((car(o) != SFS_NUMBER)||(car(cdr(o)) != SFS_NUMBER))
    {
         WARNING_MSG("Au moins un argument non entier");
         return NULL;
    }
	if(cdr(o) == obj_empty_list)
	{
        obj_divis->this.number.this.integer = obj_divis->this.number.this.integer/ car(o)->this.number.this.integer;
		return obj_divis;
	}
	else
	{
		obj_divis->this.number.this.integer = car(o)->this.number.this.integer/ car(cdr(o))->this.number.this.integer;
		o = cdr(o);
		while (cdr(o) != obj_empty_list)
		{
			if(obj_divis->this.number.this.integer  == 0)
			{
				WARNING_MSG("Division par 0"); // message mais l'opération continue
				return NULL;
			}
			 if(car(o) != SFS_NUMBER)
            {
                WARNING_MSG("Au moins un argument non entier");
                return NULL;
            }
			obj_divis->this.number.this.integer =obj_divis->this.number.this.integer /  car(o)->this.number.this.integer;
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
**


object* remainder (object* o){
	object* obj_reste = make_object();
	obj_reste->type = SFS_NUMBER;
	obj_reste->this.number.this.integer = 1;
	if ((o == obj_empty_list) || ( cdr(o) == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	if (cdr(cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
    if((car(o) != SFS_NUMBER) || (car(cdr(o)) != SFS_NUMBER))
    {
        WARNING_MSG("Au moins un argument non entier");
        return NULL;
    }
	obj_reste->this.number.this.integer = car(o)->this.number.this.integer % car(cdr(o))->this.number.this.integer;
	//verif que le reste est un integer-----------------------A VERIFIER
	return obj_reste;
}






/*
/**
*@fn object* egal (object* o)
*
*@brief Evalue l'égalité
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**


object* egal (object* o){
	if ((o == obj_empty_list) || ( cdr(o) == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{
        if((car(o) != SFS_NUMBER)||(car(cdr(o)) != SFS_NUMBER))
        {
            WARNING_MSG("Au moins un argument non entier");
            return NULL;
        }
		if (car(o)->this.number.this.integer == car(cdr(o))->this.number.this.integer)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (cdr(o) != obj_empty_list);
	//verif que le résultat est un bouleen-----------------------A VERIFIER
	return obj_res;
}






/*
/**
*@fn object* inferio (object* o)
*
*@brief Evalue l'infériorité
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/
/*

object* inferio (object* o){
	if ((o == obj_empty_list) || ( cdr(o) == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	object* obj_res = make_object();
	obj_res->type = SFS_NUMBER;
	object* obj_res_prec = make_object();
	obj_res_prec->type = SFS_NUMBER;
	do
	{
		if((car(o) != SFS_NUMBER)|| (car(cdr(o)) != SFS_NUMBER))
        {
            WARNING_MSG("Au moins un argument non entier");
            return NULL;
        }
		if (car(o)->this.number.this.integer < car(cdr(o))->this.number.this.integer)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else if (car(o)->this.number.this.integer > car(cdr(o))->this.number.this.integer)
		{
			obj_res=obj_false;
			return obj_res;
		}
		else
		{
			WARNING_MSG("Il y a égalité");
			return NULL;
		}
	}while (cdr(o) != obj_empty_list);
	return obj_res;
}







/**
*@fn object* superio (object* o)
*
*@brief Evalue la superiorité
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*


object* superio (object* o){
	if ((o == obj_empty_list) || ( cdr(o) == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	object* obj_res = make_object();
	obj_res->type = SFS_NUMBER;
	do
	{
        if((car(o) != SFS_NUMBER)|| (car(cdr(o)) != SFS_NUMBER))
        {
            WARNING_MSG("Au moins un argument non entier");
            return NULL;
        }
		if (car(o)->this.number.this.integer > car(cdr(o))->this.number.this.integer)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else if (car(o)->this.number.this.integer < car(cdr(o))->this.number.this.integer)
		{
			obj_res=obj_false;
			return obj_res;
		}
		else
		{
			WARNING_MSG("Il y a égalité");
			return NULL;
		}
	}while (cdr(o) != obj_empty_list);
	return obj_res;
}



/**
*@fn object* fabs (object* o)
*
*@brief Evalue la valeur absolue
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*


object* fabs (object* o){
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if ((cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	if(car(o) != SFS_NUMBER)
    {
        WARNING_MSG("Au moins un argument non entier");
        return NULL;
    }
	object* obj_abs = make_object();
	obj_abs->type = SFS_NUMBER;
	if(car(o)->this.number.this.integer <0)
	{
		obj_abs->this.number.this.integer= -car(o)->this.number.this.integer;
		return obj_abs;
	}
	else
	{
		return o;
	}
}


/*
/***********************************************************************************************************
/***********************************************************************************************************
/****
/****        Predicats
/****
/****
/**
*@fn object* isnull (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**


object* isnull (object* o){
	if (o == obj_empty_list)
	{
		return obj_true;
	}
	else
	{
		return obj_false;
	}
}




/**
*@fn object* isboolean? (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**

object* isboolean (object* o){
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}

	object* obj_res = make_object();
	do
	{ // ------------------------ A VERIFIER
		if ((car(o) == obj_true) || (car(o) == obj_false)  )
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (o != obj_empty_list);
	return obj_res;
}



/**
*@fn object* issymbol (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**

object* issymbol (object* o){
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{ // ------------------------ A VERIFIER
		if (car(o)->type == SFS_SYMBOL)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (o != obj_empty_list);
	return obj_res;
}



/**
*@fn object* isinteger (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*


object* isinteger (object* o){
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{ // ------------------------ chamA VERIFIER
		if (car(o)->type == SFS_NUMBER)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (o != obj_empty_list);
	return obj_res;
}




/**
*@fn object* ischar (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**


object* ischar (object* o){
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{ // ------------------------ A VERIFIER
		if (car(o)->type == SFS_CHARACTER)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (o != obj_empty_list);
	return obj_res;
}




/**
*@fn object* isstring (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**

object* isstring (object* o){
    if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{ // ------------------------ A VERIFIER
		if (car(o)->type == SFS_STRING)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (o != obj_empty_list);
	return obj_res;
}




/**
*@fn object* ispair (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**


object* ispair (object* o){
    if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{ // ------------------------ A VERIFIER
		if (car(o)->type == SFS_PAIR)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (o != obj_empty_list);
	return obj_res;
}


/***********************************************************************************************************
/***********************************************************************************************************
/****
/****        Manipulation de listes
/****
/****
/**
*@fn object* cons (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**

object* cons (object* o)
{
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if (cdr(cdr(o)) != obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	object* obj_cons = make_object();
	obj_cons->type = SFS_PAIR;
	// -----------------------------N'affiche pas les . entre les paires
	obj_cons->this.pair.car = car(o);
	obj_cons->this.pair.cdr = cdr(o);

}




/**
*@fn object* car (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**


object* fcar (object* o)	// ---------------- a tester si o est une liste
{
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if (cdr(o) != obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	object* obj_car = make_object();
	obj_car->type = o->type;
	obj_car=car(car(o));
	return obj_car;
}


/**
*@fn object* cdr (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**



object* fcdr (object* o)	// ---------------- a tester si o est une liste
{
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if (cdr(o) != obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	object* obj_cdr = make_object();
	obj_cdr->type = o->type;
	obj_cdr=cdr(car(o));
	return obj_cdr;
}




/**
*@fn object* setcar (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*


object* setcar (object* o)
{
	if ((o == obj_empty_list) || (cdr(o) == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	if (( car(o)->type != SFS_PAIR )||(car(cdr(o))-> type != SFS_NUMBER))
	{
		WARNING_MSG("set-car! ne s'applique pas à votre argument");
		return NULL;
	}
	object* obj_setcar = make_object();
	obj_setcar->type = SFS_PAIR;
	obj_setcar->this.pair.car= cdr(cdr(o))->this.number.this.integer;
	obj_setcar->this.pair.cdr= cdr(car(o))->this.number.this.integer;
	return obj_setcar;
}


/**
*@fn object* setcdr! (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**

object* setcdr (object* o)
{
	if ((o == obj_empty_list) || (cdr(o) == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	if (( car(o)->type != SFS_PAIR )||(car(cdr(o))-> type != SFS_NUMBER))
	{
		WARNING_MSG("set-car! ne s'applique pas à votre argument");
		return NULL;
	}
	object* obj_setcdr = make_object();
	obj_setcdr->type = SFS_PAIR;
	obj_setcdr->this.pair.car= car(car(o))->this.number.this.integer;
	obj_setcdr->this.pair.cdr= cdr(o)->this.number.this.integer;
	return obj_setcdr;
}



/*
/**
*@fn object* islist (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction



object* islist (object* o)
{
	//------------------------A FAIRE
}





/**
*@fn object* iseq (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*


object* iseq (object* o)
{
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'argument - min 1");
		return NULL;
	}
	if (cdr(cdr(o)) != obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	object* obj_eq = make_object();
	if(car(o)->type == car(cdr(o))->type)
	{
		if ( (car(o)->this.number.this.integer==car(cdr(o))->this.number.this.integer))//||(car(o)->this.character.this==car(cdr(o))->this.character.this)||(car(o)->this.strg==car(cdr(o))->this.strg)||(car(o)->this.symbol==car(cdr(o))->this.symbol))//car(o)->this == car(cdr(o)->this ))
        {
			obj_eq = obj_true;
			return obj_eq;
        }
        else
		{
			obj_eq = obj_false;
			return obj_eq;
		}
	}
}





*/
/***********************************************************************************************************
/***********************************************************************************************************
/****
/****        Conversions de types
/****
/****
/**
*@fn object* char2integer (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*
**/

object* char2integer (object* o)
{
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if ((cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	if (o->type != SFS_CHARACTER)
	{
		WARNING_MSG("Argument invalide");
		return NULL;
	}
	object* obj_tranfs = make_object();
	 obj_tranfs->type = SFS_NUMBER;
	if (car(o) <'#\a' || car(o) >'#\Z')
	{
		obj_tranfs->this.number.this.integer = sscanf("%d", o);
		return obj_tranfs;
	}
	else
	{
		WARNING_MSG("Argument invalide");
	}
		return NULL;
}



/**
*@fn object* integer2char (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/


object* integer2char (object* o)
{
 	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if ((cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	if (o->type != SFS_NUMBER)
	{
		WARNING_MSG("Argument depart mauvais type");
		return NULL;
	}
	object* obj_tranfs = make_object();
	obj_tranfs->type = SFS_CHARACTER;
	if (car(o) <126 || car(o) >0)
	{
		obj_tranfs->this.character= sscanf("%d", o->this.number.this.integer);
		return obj_tranfs;
	}
	else
	{
		WARNING_MSG("Argument invalide");
		return NULL;
	}
}




/**
*@fn object* number2string (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/


object* number2string (object* o)
{
 	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if ((cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	if (o->type != SFS_NUMBER)
	{
		WARNING_MSG("Argument invalide");
		return NULL;
	}
	object* obj_tranfs = make_object();
	obj_tranfs->type = SFS_STRING;
	obj_tranfs = sscanf("%d", o->this.number.this.integer);
	return obj_tranfs;
}




/**
*@fn object* string2number (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/


object* string2number (object* o)
{
 	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if ((cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	if (o->type != SFS_STRING)
	{
		WARNING_MSG("Argument invalide");
		return NULL;
	}
	object* obj_tranfs = make_object();
	obj_tranfs->type = SFS_NUMBER;
	obj_tranfs->this.number.this.integer = sscanf("%d", o);
	return obj_tranfs;
}




/**
*@fn object* symbol2string (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/


object* symbol2string (object* o)
{

 	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if ((cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	if (o->type != SFS_SYMBOL)
	{
		WARNING_MSG("Argument invalide");
		return NULL;
	}
	object* obj_tranfs = make_object();
	obj_tranfs->type = SFS_STRING;
	obj_tranfs = sscanf("%s", o);
	return obj_tranfs;
}



/**
*@fn object* string2symbol (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/

object* string2symbol (object* o)
{
    if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if ((cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	if (o->type != SFS_STRING)
	{
		WARNING_MSG("Argument invalide");
		return NULL;
	}
	object* obj_tranfs = make_object();
	obj_tranfs->type = SFS_SYMBOL;
	obj_tranfs->type = sscanf("%c", o);
	return obj_tranfs;
}
