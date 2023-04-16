/*****************************************************************//**
 * \file   localizacao.h
 * \brief  Header para localiza��es
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#pragma once

#include "clientes.h"
#include "meios.h"

#define TAM_GEO 30

typedef struct No {
    char geocodigo[TAM_GEO]; // geoc�digo (what3words.com)
    float latitude;
    float longitude;
    ClienteListaPtr clientes;
    MeiosMobilidadeListaPtr meiosMobilidade;
    struct Aresta* prox; // pr�xima aresta
} No;

typedef struct Aresta {
    float peso;
    No* destino;
    struct Aresta* prox; // pr�xima aresta
} Aresta;

typedef struct Grafo {
    No* inicio;
    int numVertices;
} Grafo;

// Estrutura para a lista de meios de mobilidade el�trica
typedef struct MeioMobilidadeListaFiltrada {
    MeioMobilidade meioMobilidade;
    struct MeioMobilidadeListaFiltrada* proxmeiomobilidadelista; // pr�ximo meio de mobilidade na lista ligada
} MeiosMobilidadeListaFiltrada, * MeiosMobilidadeListaFiltradaPtr;

float calcularDistancia(float x1, float y1, float x2, float y2);

MeiosMobilidadeListaFiltradaPtr listarMeiosPorTipoERaio(Cliente cliente, MeiosMobilidadeListaPtr listaMeios, char* tipo, float raio);

