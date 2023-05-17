/*****************************************************************//**
 * \file   grafos.h
 * \brief  Header para localiza��es utilizando os grafos
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
	float distancia; // Armazenar a dist�ncia do v�rtice em rela��o � origem. Na fun��o pesquisarEmLargura serve para armazenar a dist�ncia percorrida at� chegar no v�rtice atual. 
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

// Fun��es para ler ficheiros .csv e ficheiros .bin
int carregarFicheiroGrafo(Vertice** grafo, char* nomeficheiro);
int lerGrafoCSV(Vertice** grafo, FILE* nomeficheiro);
int lerVerticesBin(Vertice** grafo, char* nomeficheiro);
int lerAdjacentesBin(Vertice* grafo, char* nomeficheiro);

// Fun��es para guardar ficheiros .bin
int guardarBackupVertices(Vertice* grafo, char* nomeficheiro);
int guardarBackupAdjacentes(Vertice* grafo, char* nomeficheiro);

// Fun��es para criar
Vertice* criarVertice(int idvertice, char cidade[]);
Adjacente* criarAdjacente(int idvertice, float distancia);
Fila* criarFila();

// Fun��es para inserir
Vertice* inserirVertice(Vertice* grafo, Vertice* novo);
Vertice* inserirAdjacente(Vertice* grafo, int origem, Adjacente* novoadjacente);
int inserirElemFinalFila(Fila* fila, Vertice* vertice);

// Fun��es para imprimir
void imprimirGrafo(Vertice* grafo);
int verificarInt();

// Fun��es para remover ou limpar
Vertice* removerElemFila(Fila* fila);
int filaVazia(Fila* fila);
int limparCamposGrafo(Vertice* grafo);

// Fun��es de pesquisa
Vertice* pesquisarVerticePorID(Vertice* grafo, int idvertice);
Vertice* pesquisarVerticePorNomeCidade(Vertice* grafo, const char* cidade);
int pesquisarEmLargura(Vertice* grafo, int origem, int destino);

// Fun��es para fase 3)
float calcularDistanciaEntreVertices(Vertice* origem, Vertice* destino);
