/*****************************************************************//**
 * \file   localizacao.h
 * \brief  Header para localizações
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#pragma once

//fazer matriz de adjacência

typedef struct GrafoNo {
    int id; // ID do nó
    char geocodigo[50]; // geocódigo (what3words.com)
    float latitude; // latitude
    float longitude; // longitude
    int idcliente; // ID do cliente correspondente
    int idmeiomobilidade; // ID do meio de mobilidade correspondente
    struct GrafoNo* proxno; // próximo nó na lista ligada de nós do grafo
    struct GrafoAresta* proxa; // primeira aresta adjacente ao nó
} GrafoNo, * GrafoNoPtr;

typedef struct GrafoAresta {
    GrafoNoPtr destino; // nó de destino da aresta
    float peso; // peso (distância) da aresta
    struct GrafoAresta* proxima; // próxima aresta adjacente ao nó origem
} GrafoAresta, * GrafoArestaPtr;

typedef struct Grafo {
    GrafoNoPtr primeiro; // primeiro nó na lista ligada de nós do grafo
    int numvertices; // número de nós no grafo
} Grafo, * GrafoPtr;

