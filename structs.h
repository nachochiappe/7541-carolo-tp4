/*
 * structs.h
 *
 *  Created on: 14 de nov. de 2017
 *      Author: N67793
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#define MAX_CANT_SEPARADORES 10
#define MAX_LONG_PALABRA 20

#include "lista.h"

typedef struct {
	int pagina;
	int linea;
	int posicion;
} TDetallePalabra;

typedef struct {
	char palabra[MAX_LONG_PALABRA];
	TDetallePalabra detalles_palabra;
} TPalabra;

typedef struct {
	char palabra[MAX_LONG_PALABRA];
	int cant_apariciones;
	TLista detalles_palabra;
} TPalabraGlosario;

typedef struct {
	TLista palabras;
	char separadores_palabras[MAX_CANT_SEPARADORES];
} TParser;

#endif /* STRUCTS_H_ */
