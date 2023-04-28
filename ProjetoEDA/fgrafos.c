/*****************************************************************//**
 * \file   fgrafos.c
 * \brief  Fun��es com utiliza��es de grafos
 * 
 * \author hugo2
 * \date   April 2023
 *********************************************************************/

#include "grafos.h"

#pragma warning(disable:4996) //n�o chatear com _s 

int numVertices = 0; // Contagem de v�rtices

// Pesquisa um v�rtice pelo nome da origem
Vertice* pesquisaVertice(char* origem) {
    for (int i = 0; i < numVertices; i++) {
        if (strcmp(vertices[i]->origem, origem) == 0) {
            return vertices[i];
        }
    }
    return NULL;
}

// Pesquisa um destino na lista de adjac�ncias de um v�rtice
Adj* pesquisaAdjacente(Adj* listaadj, char* destino) {
    for (Adj* adj = listaadj; adj != NULL; adj = adj->prox) {
        if (strcmp(adj->destino, destino) == 0) {
            return adj;
        }
    }
    return NULL;
}

// Adiciona uma origem � lista de v�rtices
Vertice* adicionaVertice(char* origem) {
    if (pesquisaVertice(origem) == NULL) {
        Vertice* v = malloc(sizeof(Vertice));
        v->origem = strdup(origem); // C�pia da string origem, que permanece na mem�ria mesmo ap�s a sa�da do loop.
        v->listaadj = NULL;
        vertices[numVertices++] = v;
    }
}

// Adiciona um destino � lista de adjac�ncias de um v�rtice
Adj* adicionaAdjacente(Vertice* v, char* destino, float peso) {
    Adj* adj = malloc(sizeof(Adj));
    adj->destino = strdup(destino); // C�pia da string destino, que permanece na mem�ria mesmo ap�s a sa�da do loop.
    adj->peso = peso;
    adj->prox = v->listaadj;
    v->listaadj = adj;
}

// L� o ficheiro CSV e cria os v�rtices e adjac�ncias
int lerGrafoCSV(char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo %s\n", nomeArquivo);
        return 0; // Falha
    }

    char linha[100];

    fgets(linha, 100, arquivo); // L� e descarta a primeira linha (cabe�alho)

    while (fgets(linha, 100, arquivo) != NULL) {
        char* origem = strtok(linha, ",");
        char* destino = strtok(NULL, ",");
        float peso = atof(strtok(NULL, ",\n")); // Atof para converter essa string em float

        Vertice* vertice = NULL;
        for (int i = 0; i < numVertices; i++) {
            if (strcmp(vertices[i]->origem, origem) == 0) {
                vertice = vertices[i];
                break;
            }
        }

        if (vertice == NULL) {
            vertice = (Vertice*)malloc(sizeof(Vertice));
            vertice->origem = strdup(origem);
            vertice->listaadj = NULL;
            vertices[numVertices++] = vertice;
        }

        Adj* adjacente = pesquisaAdjacente(vertice->listaadj, destino);
        if (adjacente == NULL) {
            adjacente = (Adj*)malloc(sizeof(Adj));
            adjacente->destino = strdup(destino);
            adjacente->peso = peso;
            adjacente->prox = vertice->listaadj;
            vertice->listaadj = adjacente;
        }
    }

    fclose(arquivo);
    return 1; // Sucesso
}

// Imprime o grafo
void imprimeGrafo() {
    for (int i = 0; i < numVertices; i++) {
        printf("%s:\n", vertices[i]->origem);
        for (Adj* adj = vertices[i]->listaadj; adj != NULL; adj = adj->prox) {
            printf("  %s (%.1f)\n", adj->destino, adj->peso);
        }
    }
}