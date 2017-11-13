/*
 * glosario.h
 *
 *  Created on: 1 de nov. de 2017
 *      Author: N67793
 */

#ifndef GLOSARIO_H_
#define GLOSARIO_H_

/*
 * DESCRIPCIÓN TDA:
 * ----------------
 * Este TDA deberá poder devolver cualquier palabra incluida en el documento del TDA así como
 * la cantidad de veces que aparece, pagina, líneas y posición dentro del documento.
 * El TDA se implementa con un árbol binario, el cual estará ordenado por palabra. A su vez cada
 * palabra contendrá una lista con la página, línea y posición de la palabra.
 */

typedef struct {
	char *palabra;
	int pagina;
	int linea;
	int posicion;
} TPalabra;

typedef struct {
	TAB ABGlosario;
} TDAGlosario;

/*
 * Descripción: Crea la estructura parseando el documento pasado por parámetro teniendo en
 * cuenta la configuración para parsearlo y deja lista la estructura para su explotación.
 */
int CrearGlosario(TDAGlosario *g, char *documento, char *arch_config);

/*
 * Descripción: Elimina la información de la estructura.
 */
int DestruirGlosario(TDAGlosario *g);

/*
 * Descripción: Devuelve una lista con las páginas, líneas y posición de la palabra dentro del
 * documento del TDA. En caso de no existir la palabra devuelve error, sino true y la lista resultado
 */
int ConsultarpalabraGlosario(TDAGlosario *g, char *palabra, TLista *lResultado);

/*
 * Descripción: Devuelve una lista con las palabras contenidas en el TDA y la cantidad de
 * apariciones en el documento, ordenada de menor a mayor por este número de apariciones.
 */
int Ranking_palabras_Glosario(TDAGlosario *g, TLista *lResultado);

#endif /* GLOSARIO_H_ */
