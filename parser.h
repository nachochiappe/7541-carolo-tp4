/*
 * parser.h
 *
 *  Created on: 1 de nov. de 2017
 *      Author: N67793
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "structs.h"

/*
 * DESCRIPCIÓN TDA:
 * ----------------
 * Recibe un documento y un archivo de configuración y a través de sus primitivas se obtiene
 * cada palabra, página y número de línea de la palabra y posición dentro de la línea.
 */

/*
 * Descripción: Recibe el archivo a parsear y un archivo de configuración. El archivo posee el
 * caracter de cambio de página y los caracteres separadores de palabras.
 * Pre: Ninguna.
 * Post: El parser fue creado.
 */
TParser* PA_Crear(char *ruta_documento, char *ruta_config);

/*
 * Descripción: Destruye la estructura del TDA
 * Pre: El parser fue creado.
 * Post: El parser fue destruido.
 */
void PA_Destruir(TParser *parser);

/*
 * Descripción: Devuelve la palabra del archivo de entrada, con la pagina, línea y posición
 * en la línea.
 * Pre: El parser fue creado.
 * Post: Ninguna.
 */
void PA_SigPalabra(TParser *parser, TPalabra *palabra, int movim);

#endif /* PARSER_H_ */
