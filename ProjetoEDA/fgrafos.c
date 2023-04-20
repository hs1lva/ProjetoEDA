/*****************************************************************//**
 * \file   fgrafos.c
 * \brief  Funções com utilizações de grafos
 * 
 * \author hugo2
 * \date   April 2023
 *********************************************************************/

#include "grafos.h"

#pragma warning(disable:4996) //não chatear com _s 

Vertice* criaGrafo() {
    return NULL;
}

/**Vertice* lerGrafosCSV(char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return NULL;
    }

    char linha[100];
    char* token;
    Vertice* grafo = NULL;
    bool primeiraLinha = true;
    int idVertice = 0;

    while (fgets(linha, 100, arquivo) != NULL) {
        if (primeiraLinha) {
            primeiraLinha = false;
            continue;
        }
        token = strtok(linha, ",");
        idVertice = atoi(token);
        token = strtok(NULL, ",");
        Vertice* novoVertice = criaVertice(token);
        novoVertice->id = idVertice;
        while ((token = strtok(NULL, ",")) != NULL) {
            if (atoi(token) != 0) {
                int idAdjacente = atoi(token);
                token = strtok(NULL, ",");
                double distancia = atof(token);
                Vertice* adjacente = pesquisaVertice(grafo, "", NULL);
                while (adjacente != NULL) {
                    if (adjacente->id == idAdjacente) {
                        break;
                    }
                    adjacente = adjacente->prox;
                }
                if (adjacente == NULL) {
                    char nomeAdjacente[30];
                    sprintf(nomeAdjacente, "Vertice%d", idAdjacente);
                    adjacente = criaVertice(nomeAdjacente);
                    adjacente->id = idAdjacente;
                    grafo = inserirVertice(grafo, adjacente, NULL);
                }
                insereAdjacente(grafo, novoVertice, adjacente, distancia, NULL);
            }
            else {
                break;
            }
        }
    }

    fclose(arquivo);
    return grafo;
}*/


/**Vertice* lerGrafosBin(char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return NULL;
    }

    Vertice* grafo = NULL;
    int numVertices;
    fread(&numVertices, sizeof(int), 1, arquivo);
    for (int i = 0; i < numVertices; i++) {
        Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice));
        if (novoVertice == NULL) {
            printf("Erro ao alocar memoria.\n");
            return NULL;
        }
        fread(novoVertice, sizeof(Vertice), 1, arquivo);
        novoVertice->prox = NULL;
        novoVertice->adj = NULL;
        grafo = inserirVertice(grafo, novoVertice, NULL);
    }

    int numArestas;
    fread(&numArestas, sizeof(int), 1, arquivo);
    for (int i = 0; i < numArestas; i++) {
        int idOrigem, idDestino;
        double peso;
        fread(&idOrigem, sizeof(int), 1, arquivo);
        fread(&idDestino, sizeof(int), 1, arquivo);
        fread(&peso, sizeof(double), 1, arquivo);
        Vertice* origem = buscaVerticePorId(grafo, idOrigem);
        Vertice* destino = buscaVerticePorId(grafo, idDestino);
        insereAdjacente(grafo, origem, destino, peso, NULL);
    }

    fclose(arquivo);
    return grafo;
}  */


Vertice* criaVertice(char* cidade) {
    static int tot = 0;
    Vertice* novo = (Vertice*)calloc(1, sizeof(Vertice));
    if (novo == NULL) return NULL;
    novo->id = tot;
    strcpy(novo->cidade, cidade);
    novo->prox = NULL;
    novo->adj = NULL;
    tot++;
    return novo;
}

Vertice* inserirVertice(Vertice* grafo, Vertice* novo, bool* res) {
    if (grafo == NULL) {
        grafo = novo;
        *res = true;
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
            *res = true;
            novo->prox = grafo;
            grafo = novo;
        }
        else {
            novo->prox = aux;
            anterior->prox = novo;
            *res = true;
        }
        *res = true;
    }
    return grafo;
}

Vertice* pesquisaVertice(Vertice* grafo, char* cidade, bool* res) {
    Vertice* aux = grafo;
    while (aux != NULL && strcmp(aux->cidade, cidade) != 0) {
        aux = aux->prox;
    }
    if (aux == NULL) *res = false;
    else *res = true;
    return aux;
}

Vertice* insereAdjacente(Vertice* grafo, char* origem, char* destino, float peso, bool* res) {
    Vertice* origemVertice = pesquisaVertice(grafo, origem, res);
    if (origemVertice == NULL) {
        printf("Vertice de origem nao encontrado\n");
        *res = false;
        return grafo;
    }

    Vertice* destinoVertice = pesquisaVertice(grafo, destino, res);
    if (destinoVertice == NULL) {
        printf("Vertice de destino nao encontrado\n");
        *res = false;
        return grafo;
    }

    // Insere o nó adjacente no final da lista de adjacência
    Adj* novoAdj = (Adj*)malloc(sizeof(Adj));
    if (novoAdj == NULL) {
        *res = false;
        return grafo;
    }
    novoAdj->idVerticeAdj = destinoVertice->id;
    novoAdj->dist = peso;
    novoAdj->prox = NULL;

    if (origemVertice->adj == NULL) {
        origemVertice->adj = novoAdj;
    }
    else {
        Adj* ultimoAdj = origemVertice->adj;
        while (ultimoAdj->prox != NULL) {
            ultimoAdj = ultimoAdj->prox;
        }
        ultimoAdj->prox = novoAdj;
    }

    *res = true;
    return grafo;
}

void mostraGrafo(Vertice* grafo) {
    if (grafo == NULL) return;
    printf("V%d %s ->", grafo->id, grafo->cidade);
    Adj* aux = grafo->adj;
    while (aux != NULL) {
        printf(" V%d %f", aux->idVerticeAdj, aux->dist);
        aux = aux->prox;
    }
    printf("\n");
    mostraGrafo(grafo->prox);
}