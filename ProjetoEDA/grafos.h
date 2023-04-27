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

#define N 100

typedef struct Adj {
    char cidadeAdj[N];
    float peso;  //dist para peso
    struct Adj* prox;
} Adj;

typedef struct Vertice { //GRAFO
    char cidade[N];
    Adj* listaAdj; //adj para listaAdj
    struct Vertice* prox;
} Vertice;

Vertice* lerGrafoCSV(char* nomeArquivoCSV);

//Vertice* lerGrafoBinario(char* nomeArquivoBinario);

Vertice* criaVertice(char* cidade);
Adj* criaAdjacente(char* cidade, float peso);

Vertice* inserirVertice(Vertice* grafo, Vertice* novo);
Vertice* insereAdjacente(Vertice* grafo, char* origem, char* destino, float peso);

Vertice* pesquisaVertice(Vertice* grafo, char* cidade);
Adj* pesquisaAdjacente(Adj* adjacencia, char* cidade);

void mostraGrafo(Vertice* grafo);
