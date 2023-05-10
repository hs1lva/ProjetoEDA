/*****************************************************************//**
 * \file   meios.h
 * \brief  Header para meios de mobilidade
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/
#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"

#define TAM_TIPO 20 //Definir tamanho char para tipo do meio de mobilidade
#define TAM_GEOMEIO 100 //Definir tamanho char para geoc�digo do meio de mobilidade

//Estrutura para meios de mobilidade
typedef struct MeioMobilidade {
    int id; // identificador �nico
    char tipo[TAM_TIPO]; // tipo do meio de mobilidade el�trica (bicicleta, trotinete, etc.)
    float autonomia; // autonomia da bateria
    float custo; // custo de aluguer por distancia(km)
    int localizacao; // localiza��o do meio de mobilidade el�trica (corresponde ao ID da cidade no grafo)
    char geocodigo[TAM_GEOMEIO]; // geoc�digo (what3words.com)
    int alugado; // Est� (1) ou n�o est� alugado (0)
} MeioMobilidade;

//Estrutura para lista de meios de mobilidade
typedef struct MeiosMobilidadeLista {
    MeioMobilidade meioMobilidade;
    struct MeiosMobilidadeLista *proxmeiomobilidadelista; // pr�ximo meio de mobilidade na lista ligada
} MeiosMobilidadeLista, *MeiosMobilidadeListaPtr;

//Declara a fun��o para ler os meio de mobilidade do arquivo CSV e outra fun��o para ler do arquivo BIN
MeiosMobilidadeListaPtr lerMeiosMobilidadeCSV(char* nomeArquivo);
MeiosMobilidadeListaPtr lerMeiosMobilidadeBin(char* nomeArquivo);

//Fun��o para escrever os meios de mobilidade no ficheiro csv
int escreverMeios(MeiosMobilidadeListaPtr listaMobilidade, char* nomeArquivo);

//Fun��o para criar um novo meio de mobilidade.
MeioMobilidade* novoMeioMobilidade(int id, char tipo[], float autonomia, float custo, int localizacao, char geocodigo[], int alugado);

//Fun��o para adicionar um novo meio de mobilidade
MeiosMobilidadeListaPtr adicionarMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, MeioMobilidade* meioMobilidade);

//Fun��o para remover um meio de mobilidade
MeiosMobilidadeListaPtr removerMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id);

//Fun��o para alterar dados de um meio de mobilidade
bool alterarMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, char tipo[], float autonomia, float custo, int localizacao, char geocodigo[], int alugado);
bool alterarTipoMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, char tipo[]);
bool alterarAutonomiaMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, float autonomia);
bool alterarCustoMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, float custo);
bool alterarLocalizacaoMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, int localizacao);
bool alterarGeocodigoMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, char geocodigo[]);
bool alterarAlugadoMeioMobilidade(MeioMobilidade* meioMobilidade);

//Fun��o para pesquisar meios de mobilidade
MeioMobilidade* pesquisarMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id);

//Fun��o para libertar a lista da mem�ria
bool libertarMeiosMobilidadeLista(MeiosMobilidadeListaPtr lista);

//Guardar backup dados meios de mobilidade
int guardarBackupMeiosMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade);

//Lista todos os meios de mobilidade em mem�ria
void listarMeiosMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade);

//Lista todos os meios de mobilidade em mem�ria ordenados pela autonomia (mais autonomia para menos)
void listarMeiosMobilidadeOrdenadosAutonomia(MeiosMobilidadeListaPtr listaMeiosMobilidade);

//Lista apenas os meios de mobilidade num determinado Geocodigo
void listarMeiosMobilidadePorLocalizacao(MeiosMobilidadeListaPtr listaMeiosMobilidade);

//Lista apenas os meios de mobilidade com bateria abaixo dos 50%
void listarMeiosMobilidadeComCargaBateriaAbaixo50(MeiosMobilidadeListaPtr listaMeiosMobilidade);

// Fun��o para pesquisar meio de mobilidade mais proximo com grafos (usa estrutura de grafos.h)
MeiosMobilidadeListaPtr pesquisarMeioMobilidadeMaisProximo(MeiosMobilidadeListaPtr listaMeiosMobilidade, Vertice* grafo, int localCliente);
void listarMeiosMobilidadeProximosCliente(MeiosMobilidadeListaPtr listaMeiosMobilidade, Vertice* grafo, int localCliente, float raio);
void mostrarMeioMobilidade(MeioMobilidade meioMobilidade, float distancia);