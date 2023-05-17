/*****************************************************************//**
 * \file   vgrafos.c
 * \brief  Fun��es para imprimir grafos
 * 
 * \author hugo2
 * \date   May 2023
 *********************************************************************/

#include "grafos.h"

#pragma warning(disable:4996) //n�o chatear com _s 

/**
@brief Imprime o grafo representado pela lista de adjac�ncia.
@param grafo Apontador para o primeiro v�rtice do grafo.
@return void.
*/
void imprimirGrafo(Vertice* grafo) {
    Vertice* vertice = grafo;

    while (vertice) { // Loop nos v�rtices
        printf("ID: %d\tCidade: %s\n", vertice->idvertice, vertice->cidade);

        Adjacente* adjacent = vertice->adjacentes;

        while (adjacent) { // Loop nas adjacentes
            printf("  -> ID: %d\tDistancia: %.2f\n", adjacent->idvertice, adjacent->distancia);
            adjacent = adjacent->proximo;
        }

        printf("\n");
        vertice = vertice->proximo;
    }
}
