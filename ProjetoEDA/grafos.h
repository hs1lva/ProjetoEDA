/*****************************************************************//**
 * \file   localizacao.h
 * \brief  Header para localiza��es
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#pragma once

//fazer matriz de adjac�ncia

typedef struct GrafoNo {
    int id; // ID do n�
    char geocodigo[50]; // geoc�digo (what3words.com)
    float latitude; // latitude
    float longitude; // longitude
    int idcliente; // ID do cliente correspondente
    int idmeiomobilidade; // ID do meio de mobilidade correspondente
    struct GrafoNo* proxno; // pr�ximo n� na lista ligada de n�s do grafo
    struct GrafoAresta* proxa; // primeira aresta adjacente ao n�
} GrafoNo, * GrafoNoPtr;

typedef struct GrafoAresta {
    GrafoNoPtr destino; // n� de destino da aresta
    float peso; // peso (dist�ncia) da aresta
    struct GrafoAresta* proxima; // pr�xima aresta adjacente ao n� origem
} GrafoAresta, * GrafoArestaPtr;

typedef struct Grafo {
    GrafoNoPtr primeiro; // primeiro n� na lista ligada de n�s do grafo
    int numvertices; // n�mero de n�s no grafo
} Grafo, * GrafoPtr;

