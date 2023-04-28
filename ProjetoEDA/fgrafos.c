/*****************************************************************//**
 * \file   fgrafos.c
 * \brief  Funções com utilizações de grafos
 * 
 * \author hugo2
 * \date   April 2023
 *********************************************************************/

#include "grafos.h"

#pragma warning(disable:4996) //não chatear com _s 

int numVertices = 0; // Contagem de vértices

// Pesquisa um vértice pelo nome da origem
Vertice* pesquisaVertice(char* origem) {
    for (int i = 0; i < numVertices; i++) {
        if (strcmp(vertices[i]->origem, origem) == 0) {
            return vertices[i];
        }
    }
    return NULL;
}

// Pesquisa um destino na lista de adjacências de um vértice
Adj* pesquisaAdjacente(Adj* listaadj, char* destino) {
    for (Adj* adj = listaadj; adj != NULL; adj = adj->prox) {
        if (strcmp(adj->destino, destino) == 0) {
            return adj;
        }
    }
    return NULL;
}

// Adiciona uma origem à lista de vértices
Vertice* adicionaVertice(char* origem) {
    if (pesquisaVertice(origem) == NULL) {
        Vertice* v = malloc(sizeof(Vertice));
        v->origem = strdup(origem); // Cópia da string origem, que permanece na memória mesmo após a saída do loop.
        v->listaadj = NULL;
        vertices[numVertices++] = v;
    }
}

// Adiciona um destino à lista de adjacências de um vértice
Adj* adicionaAdjacente(Vertice* v, char* destino, float peso) {
    Adj* adj = malloc(sizeof(Adj));
    adj->destino = strdup(destino); // Cópia da string destino, que permanece na memória mesmo após a saída do loop.
    adj->peso = peso;
    adj->prox = v->listaadj;
    v->listaadj = adj;
}

// Lê o ficheiro CSV e cria os vértices e adjacências
int lerGrafoCSV(char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo %s\n", nomeArquivo);
        return 0; // Falha
    }

    char linha[100];

    fgets(linha, 100, arquivo); // Lê e descarta a primeira linha (cabeçalho)

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