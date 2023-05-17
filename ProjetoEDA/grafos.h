/*****************************************************************//**
 * \file   grafos.h
 * \brief  Header para localizações utilizando os grafos
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAM_CIDADE 100

typedef struct Adjacente {
	int idvertice;
	float distancia;
	struct Adjacente* proximo;
}Adjacente;

typedef struct AdjacenteFile {
	int idvertice;
	float distancia;
}AdjacenteFile;

//Grafo
typedef struct Vertice {
	int idvertice;
	char cidade[TAM_CIDADE];
	struct Vertice* proximo;
	struct Adjacente* adjacentes;
	int visitado;
	int predecessor;
	float distancia; // Armazenar a distância do vértice em relação à origem. Na função pesquisarEmLargura serve para armazenar a distância percorrida até chegar no vértice atual. 
	int numadjacentes;
}Vertice;

typedef struct VerticeFile {
	int idvertice;
	char cidade[TAM_CIDADE];
}VerticeFile;

// Fila para ver o melhor caminho
typedef struct Fila {
	struct NodeFila* proximo;
	struct NodeFila* anterior;
} Fila;

typedef struct NodeFila {
	Vertice* vertice;
	struct NodeFila* proximo;
} NodeFila;

// Funções para ler ficheiros .csv e ficheiros .bin
int carregarFicheiroGrafo(Vertice** grafo, char* nomeficheiro);
int lerGrafoCSV(Vertice** grafo, FILE* nomeficheiro);
int lerVerticesBin(Vertice** grafo, char* nomeficheiro);
int lerAdjacentesBin(Vertice* grafo, char* nomeficheiro);

// Funções para guardar ficheiros .bin
int guardarBackupVertices(Vertice* grafo, char* nomeficheiro);
int guardarBackupAdjacentes(Vertice* grafo, char* nomeficheiro);

// Funções para criar
Vertice* criarVertice(int idvertice, char cidade[]);
Adjacente* criarAdjacente(int idvertice, float distancia);
Fila* criarFila();

// Funções para inserir
Vertice* inserirVertice(Vertice* grafo, Vertice* novo);
Vertice* inserirAdjacente(Vertice* grafo, int origem, Adjacente* novoadjacente);
int inserirElemFinalFila(Fila* fila, Vertice* vertice);

// Funções para imprimir
void imprimirGrafo(Vertice* grafo);
int verificarInt();

// Funções para remover ou limpar
Vertice* removerElemFila(Fila* fila);
int filaVazia(Fila* fila);
int limparCamposGrafo(Vertice* grafo);

// Funções de pesquisa
Vertice* pesquisarVerticePorID(Vertice* grafo, int idvertice);
Vertice* pesquisarVerticePorNomeCidade(Vertice* grafo, const char* cidade);
int pesquisarEmLargura(Vertice* grafo, int origem, int destino);

// Funções para fase 3)
float calcularDistanciaEntreVertices(Vertice* origem, Vertice* destino);
