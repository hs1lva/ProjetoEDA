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

#define MAX_ORIGENS 100

typedef struct adj {
    char* destino;
    float peso;
    struct adj* prox;
} Adj;

typedef struct vertice {
    char* origem;
    Adj* listaadj;
} Vertice;

Vertice* vertices[MAX_ORIGENS]; // Apenas dar a possibilidade de ler 100 origens

Vertice* pesquisaVertice(char* origem);
Adj* pesquisaAdjacente(Adj* listaAdj, char* destino);

Vertice* adicionaVertice(char* cidade);
Adj* adicionaAdjacente(Vertice* v, char* destino, float peso);

int lerGrafoCSV(char* nomeArquivo);

void imprimeGrafo();
