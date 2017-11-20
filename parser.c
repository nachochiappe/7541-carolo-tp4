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
#include "structs.h"

#define MAX_LONG_PALABRA 20
#define MAX_LINEA 256

TParser* PA_Crear(char *ruta_documento, char *ruta_config) {
	char *token;
	char linea[MAX_LINEA];
	TPalabra *palabra;
	int nro_pagina = 1, nro_linea = 1, posicion = 1;

	TParser *parser = (TParser*) malloc(sizeof(TParser));
	if (!parser) return (NULL);

	TLista *palabras = (TLista*) malloc(sizeof(TLista));
	if (!palabras) return (NULL);
	parser->palabras = *palabras;

	ls_Crear(&parser->palabras, sizeof(TPalabra));

	FILE *arch_config = fopen(ruta_config, "r");
	while (fgets(linea, sizeof(linea), arch_config)) {
		int i = 0;
		if (linea[strlen(linea) - 2] == '\r')
			linea[strlen(linea) - 2] = '\0';
		else
			linea[strlen(linea) - 1] = '\0';
		if (strcmp(linea, "[SALTO_PAGINA]") == 0) {
			while (fgets(linea, sizeof(linea), arch_config)) {
				token = strtok(linea, "=");
				if (strcmp(token, "caracter") != 0) break;
				token = strtok(NULL, "\"");
				strcpy(&parser->separadores_palabras[i], token);
				i++;
			}
		}
		else if (strcmp(linea, "[SEPARA_PALABRA]") == 0) {
			while (fgets(linea, sizeof(linea), arch_config)) {
				token = strtok(linea, "=");
				if (strcmp(token, "caracter") != 0) break;
				token = strtok(NULL, "\"");
				strcpy(&parser->separadores_palabras[i], token);
				i++;
			}
		}
	}
	fclose(arch_config);

	FILE *documento = fopen(ruta_documento, "r");
	while (fgets(linea, sizeof(linea), documento)) {
		token = strtok(linea, parser->separadores_palabras);
		while (token) {
			palabra = (TPalabra*) malloc(sizeof(TPalabra));
			strcpy(palabra->palabra, token);
			palabra->detalles_palabra.pagina = nro_pagina;
			palabra->detalles_palabra.linea = nro_linea;
			palabra->detalles_palabra.posicion = posicion;
			posicion = posicion + strlen(palabra->palabra) + 1;
			ls_Insertar(&parser->palabras, LS_SIGUIENTE, &palabra);
			token = strtok(NULL, parser->separadores_palabras);
		}
		if (linea[strlen(linea)] == parser->separadores_palabras[0]) {
			nro_pagina++;
			nro_linea = 1;
			posicion = 1;
		}
		else {
			nro_linea++;
			posicion = 1;
		}
	}
	fclose(documento);
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
