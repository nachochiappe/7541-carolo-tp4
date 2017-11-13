/*
 * glosario.h
 *
 *  Created on: 1 de nov. de 2017
 *      Author: N67793
 */

#ifndef GLOSARIO_H_
#define GLOSARIO_H_

/*
 * DESCRIPCI�N TDA:
 * ----------------
 * Este TDA deber� poder devolver cualquier palabra incluida en el documento del TDA as� como
 * la cantidad de veces que aparece, pagina, l�neas y posici�n dentro del documento.
 * El TDA se implementa con un �rbol binario, el cual estar� ordenado por palabra. A su vez cada
 * palabra contendr� una lista con la p�gina, l�nea y posici�n de la palabra.
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
 * Descripci�n: Crea la estructura parseando el documento pasado por par�metro teniendo en
 * cuenta la configuraci�n para parsearlo y deja lista la estructura para su explotaci�n.
 */
int CrearGlosario(TDAGlosario *g, char *documento, char *arch_config);

/*
 * Descripci�n: Elimina la informaci�n de la estructura.
 */
int DestruirGlosario(TDAGlosario *g);

/*
 * Descripci�n: Devuelve una lista con las p�ginas, l�neas y posici�n de la palabra dentro del
 * documento del TDA. En caso de no existir la palabra devuelve error, sino true y la lista resultado
 */
int ConsultarpalabraGlosario(TDAGlosario *g, char *palabra, TLista *lResultado);

/*
 * Descripci�n: Devuelve una lista con las palabras contenidas en el TDA y la cantidad de
 * apariciones en el documento, ordenada de menor a mayor por este n�mero de apariciones.
 */
int Ranking_palabras_Glosario(TDAGlosario *g, TLista *lResultado);

#endif /* GLOSARIO_H_ */
