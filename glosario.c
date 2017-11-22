/*
 * glosario.c
 *
 *  Created on: 1 de nov. de 2017
 *      Author: N67793
 */

#include <stdio.h>

#include "glosario.h"
#include "lista.h"
#include "parser.h"
#include "structs.h"

int CrearGlosario(TDAGlosario *g, char *documento, char *arch_config) {
	TPalabra *palabra = (TPalabra*) malloc(sizeof(TPalabra));
	if (!palabra) return (1);
	TPalabraGlosario *palabra_nueva, *palabra_existente;
	int encontre_palabra;

	TParser *parser = PA_Crear(documento, arch_config);

	AB_Crear(&g->ABGlosario, sizeof(TPalabraGlosario));

	PA_SigPalabra(parser, palabra, 1);

	palabra_existente = (TPalabraGlosario*) malloc(sizeof(TPalabraGlosario));
	if (!palabra_existente) return (1);

	do {
		AB_MoverCte(&g->ABGlosario, RAIZ);
		encontre_palabra = 0;
		palabra_nueva = (TPalabraGlosario*) malloc(sizeof(TPalabraGlosario));
		if (!palabra_nueva) return (1);
		strcpy(palabra_nueva->palabra, palabra->palabra);
		palabra_nueva->cant_apariciones = 1;
		ls_Crear(&palabra_nueva->detalles_palabra, sizeof(TDetallePalabra));
		ls_Insertar(&palabra_nueva->detalles_palabra, LS_SIGUIENTE, &palabra->detalles_palabra);
		if (AB_Vacio(g->ABGlosario)) {
			AB_Insertar(&g->ABGlosario, RAIZ, palabra_nueva);
		}
		else {
			while (encontre_palabra == 0) {
				AB_ElemCte(g->ABGlosario, palabra_existente);
				if (strcmp(palabra_existente->palabra, palabra_nueva->palabra) == 0) {
					palabra_existente->cant_apariciones++;
					AB_ModifCte(&g->ABGlosario, palabra_existente);
					do {
						if (ls_MoverCorriente(&palabra_existente->detalles_palabra, LS_SIGUIENTE) == FALSE) break;
					} while (1);
					ls_Insertar(&palabra_existente->detalles_palabra, LS_SIGUIENTE, &palabra->detalles_palabra);
					encontre_palabra = 1;
				}
				else if (strcmp(palabra_existente->palabra, palabra_nueva->palabra) < 0) {
					// me muevo para la derecha
					if (AB_MoverCte(&g->ABGlosario, DER) == FALSE) {
						//inserto palabra nueva
						AB_Insertar(&g->ABGlosario, DER, palabra_nueva);
						encontre_palabra = 1;
					}
				}
				else {
					// me muevo para la izquierda
					if (AB_MoverCte(&g->ABGlosario, IZQ) == FALSE) {
						//inserto palabra nueva
						AB_Insertar(&g->ABGlosario, IZQ, palabra_nueva);
						encontre_palabra = 1;
					}
				}
			}
		}
	} while (PA_SigPalabra(parser, palabra, 0) == 0);
	free(palabra);
	free(palabra_existente);
	free(palabra_nueva);
	PA_Destruir(parser);
	return (0);
}

int DestruirGlosario(TDAGlosario *g) {
	AB_Vaciar(&g->ABGlosario);
	free(g);
	return (0);
}

int ConsultarpalabraGlosario(TDAGlosario *g, char *palabra, TLista *lResultado) {
	TPalabraGlosario *palabra_glosario = (TPalabraGlosario*) malloc(sizeof(TPalabraGlosario));
	if (!palabra_glosario) return (1);

	TDetallePalabra *detalle_palabra = (TDetallePalabra*) malloc(sizeof(TDetallePalabra));
	if (!detalle_palabra) return (1);

	int encontre_palabra = 0;

	AB_MoverCte(&g->ABGlosario, RAIZ);
	while (encontre_palabra == 0) {
		AB_ElemCte(g->ABGlosario, palabra_glosario);
		if (strcmp(palabra_glosario->palabra, palabra) == 0) {
			ls_Insertar(lResultado, LS_SIGUIENTE, palabra_glosario);
			encontre_palabra = 1;
		}
		else if (strcmp(palabra_glosario->palabra, palabra) < 0) {
			if (AB_MoverCte(&g->ABGlosario, DER) == FALSE) break;
		}
		else {
			if (AB_MoverCte(&g->ABGlosario, IZQ) == FALSE) break;
		}
	}
	if (encontre_palabra == 0) return (1);

	free(palabra_glosario);
	free(detalle_palabra);

	return (0);
}

int Ranking_palabras_Recursivo(TAB arbol, TLista *lResultado, int movimiento) {
	int resultadoMovimiento;
	TPalabraGlosario *palabraGlosario;
	TPalabraRanking *palabraRankingAux, *palabraRanking = (TPalabraRanking*) malloc(siezeof(TPalabraRanking));

	switch(movimiento) {
					case RAIZ:
						resultadoMovimiento = AB_MoverCte(arbol, RAIZ);
						break;
					case IZQ:
						resultadoMovimiento = AB_MoverCte(arbol, IZQ);
						break;
					case DER:
						resultadoMovimiento = AB_MoverCte(arbol, DER);
						break;
	}
	AB_ElemCte(arbol, palabraGlosario);

	if(resultadoMovimiento) {
		strcpy(palabraRanking->palabra,palabraGlosario->palabra);
		palabraRanking->cant_apariciones = palabraGlosario->cant_apariciones;

		if(ls_vacia(lResultado)) {
			ls_Insertar(lResultado, LS_PRIMERO, palabraRanking);
		}else{
			resultadoMovimiento = ls_MoverCorriente(lResultado, LS_PRIMERO);
			ls_ElemCorriente(lResultado, palabraRankingAux);
			while((palabraRankingAux->cant_apariciones > palabraRanking->cant_apariciones)
			&& resultadoMovimiento) {
				resultadoMovimiento = ls_MoverCorriente(lResultado, LS_PRIMERO);
				ls_ElemCorriente(lResultado, palabraRankingAux);
			}
			ls_Insertar(lResultado, LS_ANTERIOR, palabraRanking);
		}
		Ranking_palabras_Recursivo(arbol, lResultado, IZQ);
		Ranking_palabras_Recursivo(arbol, lResultado, DER);
	}


}

int Ranking_palabras_Glosario(TDAGlosario *g, TLista *lResultado) {
	if(!lResultado) {
		ls_Crear(lResultado, sizeof(TPalabraRanking));
	}
	else Ranking_palabras_Recursivo(g->ABGlosario, lResultado, RAIZ);
	return 0;
}
