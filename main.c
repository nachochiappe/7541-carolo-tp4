/*
 * main.c
 *
 *  Created on: 1 de nov. de 2017
 *      Author: N67793
 */

#include <stdio.h>
#include <string.h>

#include "glosario.h"
#include "lista.h"
#include "structs.h"

int main (int argc, char *argv[]) {

	char inst[4];
	char palabra[20];
	TLista lResultado;

	TDAGlosario *g = (TDAGlosario*) malloc(sizeof(TDAGlosario));
	if (!g) return (-1);

	ls_Crear(&lResultado, sizeof(TPalabra));

	if (CrearGlosario(g, argv[1], argv[2]) != 0) return (1);

	FILE *arch_instrucciones = fopen(argv[3],"r");

	while (fgets(inst, sizeof(inst), arch_instrucciones) != NULL) {
		if (strcmp(inst, "cp ") == 0) {
			fgets(palabra, sizeof(palabra), arch_instrucciones);
			if (palabra[strlen(palabra) - 2] == '\r')
				palabra[strlen(palabra) - 2] = '\0';
			else
				palabra[strlen(palabra) - 1] = '\0';
			if (ConsultarpalabraGlosario(g, palabra, &lResultado) != 0) return (1);
		}
		else if (strcmp(inst, "rp") == 0) {
			if (Ranking_palabras_Glosario(g, &lResultado) != 0) return (1);
		}
		else
			printf("%s es una instrucción errónea.\n", inst);
	}

	if (!DestruirGlosario(g)) return (1);

	return (0);
}
