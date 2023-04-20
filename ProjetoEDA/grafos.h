/*****************************************************************//**
 * \file   grafos.h
 * \brief  Header para localizações utilizando os grafos
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#pragma once

#include "clientes.h"
#include "meios.h"

#define MAX_LINHA 200
#define N 20

typedef struct Adj {
    int idVerticeAdj;
    float dist;
    struct Adj* prox;
} Adj;

typedef struct Vertice {
    int id;
    char cidade[N];
    struct Vertice* prox;
    Adj* adj;
} Vertice;

Vertice* criaGrafo();

//Vertice* lerGrafosCSV(char* nomeArquivo);

//Vertice* lerGrafosBin(char* nomeArquivo);

Vertice* criaVertice(char* cidade);

Vertice* inserirVertice(Vertice* grafo, Vertice* novo, bool* res);

Vertice* pesquisaVertice(Vertice* grafo, char* cidade, bool* res);

Vertice* insereAdjacente(Vertice* grafo, char* origem, char* destino, float peso, bool* res);

void mostraGrafo(Vertice* grafo);
