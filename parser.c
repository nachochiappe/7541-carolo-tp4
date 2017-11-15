/*
 * parser.c
 *
 *  Created on: 1 de nov. de 2017
 *      Author: N67793
 */

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "parser.h"

#define MAX_LONG_PALABRA 20

TParser* PA_Crear(char *ruta_documento, char *ruta_config) {
	char *token;
	int cant_separadores = 0;

	TParser *parser = (TParser*) malloc(sizeof(TParser));
	if (!parser) return (NULL);

	TLista *palabras = (TLista*) malloc(sizeof(TLista));
	if (!palabras) return (NULL);
	parser->palabras = *palabras;

	ls_Crear(&parser->palabras, MAX_LONG_PALABRA);

	FILE *arch_config = fopen(ruta_config, "r");
	char linea[MAX_LONG_PALABRA];
	while (fgets(linea, sizeof(linea), arch_config)) {
		if (linea[strlen(linea) - 2] == '\r')
			linea[strlen(linea) - 2] = '\0';
		else
			linea[strlen(linea) - 1] = '\0';
		if (strcmp(linea, "[SALTO_PAGINA]") == 0) {
			while (fgets(linea, sizeof(linea), arch_config)) {
				token = strtok(linea, "=");
				if (strcmp(token, "caracter") != 0) break;
				token = strtok(NULL, "\"");
				strcpy(&parser->salto_pagina, token);
			}
		}
		else if (strcmp(linea, "[SEPARA_PALABRA]") == 0) {
			int i = 0;
			while (fgets(linea, sizeof(linea), arch_config)) {
				token = strtok(linea, "=");
				if (strcmp(token, "caracter") != 0) break;
				token = strtok(NULL, "\"");
				strcpy(&parser->separadores_palabras[i], token);
				i++;
				cant_separadores = i;
			}
		}
	}
	fclose(arch_config);

	FILE *documento = fopen(ruta_documento, "r");
	return (parser);
}

void PA_Destruir(TParser *parser) {
	ls_Vaciar(&parser->palabras);
	free(&parser->palabras);
	free(parser);
	return;
}

void PA_SigPalabra(TParser parser, TPalabra *palabra) {

}
