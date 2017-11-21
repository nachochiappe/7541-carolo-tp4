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
	TPalabra *palabra = (TPalabra*) malloc(sizeof(TPalabra));
	if (!palabra) return (1);
	TPalabraGlosario *palabra_nueva, *palabra_existente;
	int encontre_palabra = 0;

	TParser *parser = PA_Crear(documento, arch_config);

	AB_Crear(&g->ABGlosario, sizeof(TPalabraGlosario));

	PA_SigPalabra(parser, &palabra, 1);
	while (palabra) {
		palabra_nueva = (TPalabraGlosario*) malloc(sizeof(TPalabraGlosario));
		if (!palabra_nueva) return (1);
		strcpy(palabra_nueva->palabra, palabra->palabra);
		palabra_nueva->cant_apariciones = 1;
		ls_Insertar(&palabra_nueva->detalles_palabra, LS_SIGUIENTE, &palabra->detalles_palabra);
		if (AB_Vacio(g->ABGlosario)) {
			AB_Insertar(&g->ABGlosario, RAIZ, palabra_nueva);
		}
		else {
			while (encontre_palabra == 0) {
				AB_ElemCte(g->ABGlosario, &palabra_existente);
				if (strcmp(palabra_existente->palabra, palabra_nueva->palabra) == 0) {
					palabra_existente->cant_apariciones++;
					ls_Insertar(&palabra_existente->detalles_palabra, LS_SIGUIENTE, &palabra->detalles_palabra);
				}
				else if (strcmp(palabra_existente->palabra, palabra_nueva->palabra) < 0) {
					// me muevo para la derecha
					if (AB_MoverCte(&g->ABGlosario, DER) == FALSE) {
						//inserto palabra nueva
						AB_Insertar(&g->ABGlosario, DER, &palabra_nueva);
						encontre_palabra = 1;
					}
				}
				else {
					// me muevo para la izquierda
					if (AB_MoverCte(&g->ABGlosario, IZQ) == FALSE) {
						//inserto palabra nueva
						AB_Insertar(&g->ABGlosario, IZQ, &palabra_nueva);
						encontre_palabra = 1;
					}
				}
			}
		}
		PA_SigPalabra(parser, &palabra, 0);
	};
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
