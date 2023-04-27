/*****************************************************************//**
 * \file   fgrafos.c
 * \brief  Funções com utilizações de grafos
 * 
 * \author hugo2
 * \date   April 2023
 *********************************************************************/

#include "grafos.h"

#pragma warning(disable:4996) //não chatear com _s 

Vertice* lerGrafoCSV(char* nomeArquivoCSV) {
    FILE* fp = fopen(nomeArquivoCSV, "r");
    if (fp == NULL) {
        perror("Erro ao abrir arquivo\n");
        return NULL;
    }
    Vertice* grafo = NULL;
    char linha[1024];
    while (fgets(linha, 1024, fp)) {
        char cidade[N];
        char cidadeAdj[N];
        float peso;
        if (sscanf(linha, "%[^,],%[^,],%f\n", cidade, cidadeAdj, &peso) == 3) {
            Vertice* vertice = pesquisaVertice(grafo, cidade);
            if (vertice == NULL) {
                vertice = criaVertice(cidade);
                if (vertice == NULL) {
                    perror("Erro ao criar vertice\n");
                    continue;
                }
                grafo = inserirVertice(grafo, vertice);
            }
            Adj* adjacente = pesquisaAdjacente(vertice->listaAdj, cidadeAdj);
            if (adjacente != NULL) {
                perror("Adjacência já existente\n");
                continue;
            }
            adjacente = criaAdjacente(cidadeAdj, peso);
            if (adjacente == NULL) {
                perror("Erro ao criar adjacente\n");
                continue;
            }
            vertice->listaAdj = insereAdjacente(grafo, vertice->cidade, cidadeAdj, peso);
        }
    }
    fclose(fp);
    return grafo;
}


Vertice* criaVertice(char* cidade) {
    Vertice* novo = (Vertice*)calloc(1, sizeof(Vertice));
    if (novo == NULL) return NULL;
    strcpy(novo->cidade, cidade);
    novo->prox = NULL;
    novo->listaAdj = NULL;
    return novo;
}

Adj* criaAdjacente(char* cidade, float peso) {
    Adj* novo = (Adj*)calloc(1, sizeof(Adj));
    if (novo == NULL) return NULL;
    strcpy(novo->cidadeAdj, cidade);
    novo->peso = peso;
    novo->prox = NULL;
    return novo;
}

Vertice* inserirVertice(Vertice* grafo, Vertice* novo) {
    if (grafo == NULL) {
        grafo = novo;
        return grafo;
    }
    else {
        Vertice* aux = grafo;
        Vertice* anterior = aux;
        while (aux != NULL && strcmp(aux->cidade, novo->cidade) < 0) {
            anterior = aux;
            aux = aux->prox;
        }
        if (aux == grafo) {
            novo->prox = grafo;
            grafo = novo;
        }
        else {
            novo->prox = aux;
            anterior->prox = novo;
        }
    }
    return grafo;
}


Vertice* pesquisaVertice(Vertice* grafo, char* cidade) {
    Vertice* aux = grafo;
    while (aux != NULL && strcmp(aux->cidade, cidade) != 0) {
        aux = aux->prox;
    }
    return aux;
}

Adj* pesquisaAdjacente(Adj* adjacencia, char* cidade) {
    Adj* aux = adjacencia;
    while (aux != NULL && strcmp(aux->cidadeAdj, cidade) != 0) {
        aux = aux->prox;
    }
    return aux;
}


Vertice* insereAdjacente(Vertice* grafo, char* origem, char* destino, float peso) {
    Vertice* origemVertice = pesquisaVertice(grafo, origem);
    if (origemVertice == NULL) {
        perror("Vertice de origem nao encontrado\n");
        return grafo;
    }

    Vertice* destinoVertice = pesquisaVertice(grafo, destino);
    if (destinoVertice == NULL) {
        perror("Vertice de destino nao encontrado\n");
        return grafo;
    }

    // Insere o nó adjacente no final da lista de adjacência
    Adj* novoAdj = (Adj*)malloc(sizeof(Adj));
    if (novoAdj == NULL) {
        return grafo;
    }
    strcpy(novoAdj->cidadeAdj, destino);
    novoAdj->peso = peso;
    novoAdj->prox = NULL;

    if (origemVertice->listaAdj == NULL) {
        origemVertice->listaAdj = novoAdj;
    }
    else {
        Adj* ultimoAdj = origemVertice->listaAdj;
        while (ultimoAdj->prox != NULL) {
            ultimoAdj = ultimoAdj->prox;
        }
        ultimoAdj->prox = novoAdj;
    }

    return grafo;
}



void mostraGrafo(Vertice* grafo) {
    if (grafo == NULL) return;
    printf("%s ->", grafo->cidade);
    Adj* aux = grafo->listaAdj;
    while (aux != NULL) {
        printf(" %s:%.2f", aux->cidadeAdj, aux->peso);
        aux = aux->prox;
    }
    printf("\n");
    mostraGrafo(grafo->prox);
}
