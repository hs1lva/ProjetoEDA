/*****************************************************************//**
 * \file   camiao.h
 * \brief  Header para o camiao
 * 
 * \author hugo2
 * \date   May 2023
 *********************************************************************/

#pragma once

typedef struct Camiao {
    float autonomia;
    int capacidade;
} Camiao;

Camiao* criarCamiao();

void destruirCamiao(Camiao* camiao);

void imprimirCamiao(Camiao* camiao);

int contarMeiosMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, char tipo[]);

void recolherMobilidadeEletrica(Vertice* grafo, MeiosMobilidadeListaPtr listaMeiosMobilidade, Camiao* camiao, char tipo[]);
