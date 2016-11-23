
/**
 * @file repl.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:13:02 2012
 * @brief Main REPL for SFS.
 *
 * Main REPL for SFS.
 */



#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "object.h"
#include "read.h"
#include "eval.h"
#include "print.h"
#include "mem.h"

/* mode d'interaction avec l'interpreteur (exemple)*/
typedef enum {INTERACTIF,SCRIPT} inter_mode;


void usage_error( char *command ) {

    fprintf( stderr, "Usage: %s [file.scm]\n   If no file is given, executes in Shell mode.", command );
}



object* obj_true;
object* obj_false;
object* obj_empty_list;
object* obj_meta;
object* obj_undef;
object* obj_current;



void init_interpreter(char tab_form[NB_FORM][STRLEN], object* (*forme[NB_FORM])(object*), char tab_prim[NB_PRIM][STRLEN], object* (*prim[NB_PRIM])(object*)) {
    init_tab_form(tab_form);
    init_add_tab_form(forme);
	init_tab_prim(tab_prim);
	init_add_tab_prim(prim);

    obj_empty_list      = init_empty_list();
    obj_true			= init_true();
    obj_false			= init_false();
    obj_undef			= init_undef();
    obj_meta            = init_meta_environnement();
	obj_current			= init_curr_environnement();
	obj_meta			= init_meta_env(tab_form, obj_meta, forme, tab_prim, prim);
}

int main ( int argc, char *argv[] ) {

    char     input[BIGSTRING];
    uint*    pos;
    pos = calloc(1,sizeof(uint));
    *pos = 0;
    object*   output = NULL;
    object*   sexpr = NULL;
    inter_mode mode;
    FILE *   fp = NULL; /* le flux dans lequel les commande seront lues : stdin (mode shell) ou un fichier */
    
    char tab_form[NB_FORM][STRLEN];
	object* (*forme[NB_FORM])(object*);

	char tab_prim[NB_PRIM][STRLEN];
	object* (*prim[NB_PRIM])(object*);

	init_interpreter(tab_form, forme, tab_prim, prim);
	
    /*par defaut : mode shell interactif */
    fp = stdin;

	mode = INTERACTIF;


    while ( 1 ) {
        input[0]='\0';
        *pos = 0;
        output = NULL;
        sexpr = NULL;
        uint Sexpr_err;
	
		

        Sexpr_err = sfs_get_sexpr( input, fp );
	
        if ( S_OK != Sexpr_err) {           
            /*sinon on rend la main à l'utilisateur*/
            continue;
        }

        if ( 0 == strlen( input ) ) {
            continue;
        }

      	printf("--------debut lecture--------\n");
	
        *pos  = 0;
	printf("Fonction delete_space -- Chaine initiale : %s\n",input);
        Delete_space(input);
	printf("Fonction delete_space -- Chaine final : %s\n",input);
        sexpr = sfs_read( input, pos );
        if ( NULL == sexpr ) {
            /* si fichier alors on sort*/
            if (mode == SCRIPT) {
                fclose( fp );
                /*macro ERROR_MSG : message d'erreur puis fin de programme ! */
                ERROR_MSG("Invalid S-expression --- Aborts");
            }
            /*sinon on rend la main à l'utilisateur*/
            continue ;
        }
	printf("-------read done-------\n");
        output = sfs_eval( sexpr );
        if( NULL == output) {
            /* si fichier alors on sort*/
            if (mode == SCRIPT) {
                fclose( fp );
                /*macro ERROR_MSG : message d'erreur puis fin de programme ! */
                ERROR_MSG("Error while evaluating input --- Aborts");
            }
            /*sinon on rend la main à l'utilisateur*/
            continue ;
        }

        printf( "==> " );
        sfs_print( output );
        printf( "\n" );
    }

    if (mode == SCRIPT) {
        fclose( fp );
    }
    exit( EXIT_SUCCESS );
}
