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
 * DESCRIPCI�N TDA:
 * ----------------
 * Recibe un documento y un archivo de configuraci�n y a trav�s de sus primitivas se obtiene
 * cada palabra, p�gina y n�mero de l�nea de la palabra y posici�n dentro de la l�nea.
 */

/*
 * Descripci�n: Recibe el archivo a parsear y un archivo de configuraci�n. El archivo posee el
 * caracter de cambio de p�gina y los caracteres separadores de palabras.
 * Pre: Ninguna.
 * Post: El parser fue creado.
 */
TParser* PA_Crear(char *ruta_documento, char *ruta_config);

/*
 * Descripci�n: Destruye la estructura del TDA
 * Pre: El parser fue creado.
 * Post: El parser fue destruido.
 */
void PA_Destruir(TParser *parser);

/*
 * Descripci�n: Devuelve la palabra del archivo de entrada, con la pagina, l�nea y posici�n
 * en la l�nea.
 * Pre: El parser fue creado.
 * Post: Ninguna.
 */
void PA_SigPalabra(TParser *parser, TPalabra *palabra, int movim);

#endif /* PARSER_H_ */
