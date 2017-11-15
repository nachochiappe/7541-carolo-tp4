/*
 * structs.h
 *
 *  Created on: 14 de nov. de 2017
 *      Author: N67793
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#define MAX_CANT_SEPARADORES 5

#include "lista.h"

typedef struct {
	char palabra[20];
	int cant_apariciones;
	TLista detalles_palabra;
} TPalabra;

typedef struct {
	int pagina;
	int linea;
	int posicion;
} TDetallePalabra;

typedef struct {
	TLista palabras;
	char salto_pagina;
	char separadores_palabras[MAX_CANT_SEPARADORES];
} TParser;

#endif /* STRUCTS_H_ */
