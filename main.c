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

	ls_Crear(&lResultado, sizeof(TPalabraGlosario));

	if (CrearGlosario(g, argv[1], argv[2]) != 0) return (1);

	FILE *arch_instrucciones = fopen(argv[3],"r");

	while (fgets(inst, sizeof(inst), arch_instrucciones) != NULL) {
		if (strcmp(inst, "cp ") == 0) {
			fgets(palabra, sizeof(palabra), arch_instrucciones);
			if (palabra[strlen(palabra) - 2] == '\r')
				palabra[strlen(palabra) - 2] = '\0';
			else
				palabra[strlen(palabra) - 1] = '\0';
			if (ConsultarpalabraGlosario(g, palabra, &lResultado) != 0)
				printf("La palabra \"%s\" no existe en el texto.\n", palabra);
			else {
				TPalabraGlosario *palabra_glosario = (TPalabraGlosario*) malloc(sizeof(TPalabraGlosario));
				if (!palabra_glosario) return (1);

				TDetallePalabra *detalle_palabra = (TDetallePalabra*) malloc(sizeof(TDetallePalabra));
				if (!detalle_palabra) return (1);

				printf("%s\n", palabra);

				ls_ElemCorriente(lResultado, palabra_glosario);
				printf("%d repeticiones\n", palabra_glosario->cant_apariciones);
				do {
					ls_ElemCorriente(palabra_glosario->detalles_palabra, detalle_palabra);
					printf("pagina %d linea %d posicion %d\n", detalle_palabra->pagina, detalle_palabra->linea, detalle_palabra->posicion);
				} while (ls_MoverCorriente(&palabra_glosario->detalles_palabra, LS_SIGUIENTE) == TRUE);

				ls_Vaciar(&lResultado);
				free(detalle_palabra);
				free(palabra_glosario);
			}
		}
		else if (strcmp(inst, "rp") == 0) {
			if (Ranking_palabras_Glosario(g, &lResultado) != 0) return (1);

			TPalabraGlosario *palabra_glosario = (TPalabraGlosario*) malloc(sizeof(TPalabraGlosario));
			if (!palabra_glosario) return (1);

			ls_MoverCorriente(&lResultado, LS_PRIMERO);
			do {
				ls_ElemCorriente(lResultado, palabra_glosario);
				printf("%s %d repeticiones\n", palabra_glosario->palabra, palabra_glosario->cant_apariciones);
			} while (ls_MoverCorriente(&lResultado, LS_SIGUIENTE) == TRUE);

			ls_Vaciar(&lResultado);
			free(palabra_glosario);

		}
		else
			printf("%s es una instrucción errónea.\n", inst);
	}

	if (!DestruirGlosario(g)) return (1);

	return (0);
}
