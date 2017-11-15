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
	TParser *parser = PA_Crear(documento, arch_config);
	do {
		TPalabra *palabra = (TPalabra*) malloc(sizeof(TPalabra));
		if (!palabra) return (1);
		TLista *detalles_palabra = (TLista*) malloc(sizeof(TLista));
		if (!detalles_palabra) return (1);
		palabra->detalles_palabra = *detalles_palabra;
		PA_SigPalabra(*parser, palabra);
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
