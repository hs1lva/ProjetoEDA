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
	int idVertice;
	float distancia;
	struct Adjacente* proximo;
}Adjacente;

//Grafo
typedef struct Vertice {
	int idVertice;
	char cidade[TAM_CIDADE];
	struct Vertice* proximo;
	struct Adjacente* adjacentes;
	int visitado;
	int predecessor;
	float distancia;
	int numAdjacentes;
}Vertice;

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
int lerGrafoCSV(Vertice** grafo, char* nomeFicheiro);
int lerVerticesBin(Vertice** grafo);
int lerAdjacentesBin(Vertice* grafo);

// Funções para guardar ficheiros .bin
int guardarBackupVertices(Vertice* grafo);
int guardarBackupAdjacentes(Vertice* grafo);

// Funções para criar
Vertice* criarVertice(int idVertice, char cidade[]);
Adjacente* criarAdjacente(int idVertice, float distancia);
Fila* criarFila();

// Funções para inserir
Vertice* inserirVertice(Vertice* grafo, Vertice* novo);
Vertice* inserirAdjacente(Vertice* grafo, int origem, Adjacente* novoAdjacente);
int inserirElemFinalFila(Fila* fila, Vertice* vertice);

// Funções para imprimir
void imprimirGrafo(Vertice* grafo);
int verificarInt();

// Funções para remover ou limpar
Vertice* removerElemFila(Fila* fila);
int filaVazia(Fila* fila);
int limparCamposGrafo(Vertice* grafo);

// Funções de pesquisa
Vertice* pesquisarVerticePorID(Vertice* grafo, int idVertice);
Vertice* pesquisarVerticePorNomeCidade(Vertice* grafo, const char* cidade);
int pesquisarEmLargura(Vertice* grafo, int origem, int destino);