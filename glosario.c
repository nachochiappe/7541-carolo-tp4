/*
 * glosario.c
 *
 *  Created on: 1 de nov. de 2017
 *      Author: N67793
 */

#include <stdio.h>

#include "glosario.h"
#include "parser.h"
#include "structs.h"

int CrearGlosario(TDAGlosario *g, char *documento, char *arch_config) {
	TPalabra palabra;
	TPalabraGlosario *palabra_nueva, *palabra_existente;
	TLista *detalles_palabra;

	TParser *parser = PA_Crear(documento, arch_config);

	AB_Crear(&g->ABGlosario, sizeof(TPalabraGlosario));
	do {
		PA_SigPalabra(*parser, &palabra);
		palabra_nueva = (TPalabraGlosario*) malloc(sizeof(TPalabraGlosario));
		detalles_palabra = (TLista*) malloc(sizeof(TLista));
		palabra_nueva->detalles_palabra = *detalles_palabra;
		strcpy(palabra_nueva->palabra, palabra.palabra);
		palabra_nueva->cant_apariciones = 1;
		ls_Insertar(&palabra_nueva->detalles_palabra, LS_SIGUIENTE, &palabra.detalles_palabra);
		if (AB_Vacio(g->ABGlosario)) {
			AB_Insertar(&g->ABGlosario, RAIZ, palabra_nueva);
		}
		else {
			AB_ElemCte(g->ABGlosario, &palabra_existente);
			if (strcmp(palabra_existente->palabra, palabra_nueva->palabra) == 0) {
				palabra_existente->cant_apariciones++;
				ls_Insertar(&palabra_existente->detalles_palabra, LS_SIGUIENTE, &palabra.detalles_palabra);
			}
		}
	} while (ls_MoverCorriente(&parser->palabras, LS_SIGUIENTE));
	PA_Destruir(parser);
	return (0);
}

int DestruirGlosario(TDAGlosario *g) {
	AB_Vaciar(&g->ABGlosario);
	free(&g->ABGlosario);
	free(g);
	return (0);
}

int ConsultarpalabraGlosario(TDAGlosario *g, char *palabra, TLista *lResultado) {

	return (0);
}

int Ranking_palabras_Glosario(TDAGlosario *g, TLista *lResultado) {

	return (0);
}
