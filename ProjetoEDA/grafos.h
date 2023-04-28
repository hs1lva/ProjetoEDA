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

#define MAX_CIDADES 100

typedef struct adj {
    char* cidadeadj;
    float peso;
    struct adj* prox;
} Adj;

typedef struct vertice {
    char* cidade;
    Adj* listaadj;
} Vertice;

Vertice* vertices[MAX_CIDADES]; // Apenas dar a possibilidade de ler 100 cidades

Vertice* pesquisaVertice(char* cidade);
Adj* pesquisaAdjacente(Adj* listaAdj, char* cidadeAdj);

Vertice* adicionaVertice(char* cidade);
Adj* adicionaAdjacente(Vertice* v, char* cidadeAdj, float peso);

int lerGrafoCSV(char* nomeArquivo);

void imprimeGrafo();
