/*****************************************************************//**
 * \file   fcamiao.c
 * \brief  Funções para o camião
 * 
 * \author hugo2
 * \date   May 2023
 *********************************************************************/

#include "meios.h"
#include "camiao.h"

/**
@brief Cria um novo camião.
@return Apontador para o novo camião.
*/
Camiao* criarCamiao() {
    Camiao* camiao = (Camiao*)malloc(sizeof(Camiao));
    if (camiao != NULL) {
        camiao->autonomia = 0.0;
        camiao->capacidade = 0;
    }
    return camiao;
}

/**
* @brief Destrói um camião previamente alocado.
* @param camiao Apontador para o camião a ser destruído.
*/
void destruirCamiao(Camiao* camiao) {
    free(camiao);
}

/**
* @brief Imprime os dados de um camião.
* @param camiao Apontador para o camião a ser impresso.
*/
void imprimirCamiao(Camiao* camiao) {
    printf("Autonomia do camiao: %.2f km\n", camiao->autonomia);
    printf("Capacidade do camiao: %d meios de mobilidade eletrica\n", camiao->capacidade);
}

/**
* @brief Conta quantos meios de mobilidade de um dado tipo existem na lista.
* @param listaMeiosMobilidade Apontador para a lista de meios de mobilidade.
* @param tipo String contendo o tipo de meio de mobilidade a ser contado.
* @return Número de meios de mobilidade do tipo especificado.
*/
int contarMeiosMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, char tipo[]) {
    int count = 0;
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade;

    while (atual != NULL) {
        if (strcmp(atual->meioMobilidade.tipo, tipo) == 0) {
            count++;
        }
        atual = atual->proxmeiomobilidadelista;
    }

    return count;
}

/**
@brief Recolhe meios de mobilidade elétrica do tipo especificado pelo utilizador.
@param grafo Apontador para o grafo.
@param listaMeiosMobilidade Apontador para a lista de meios de mobilidade elétrica.
@param camiao Apontador para a estrutura que representa o camião de recolha.
@param tipo Tipos de meios de mobilidade elétrica a serem recolhidos.
@return void
*/
void recolherMobilidadeEletrica(Vertice* grafo, MeiosMobilidadeListaPtr listaMeiosMobilidade, Camiao* camiao, char tipo[]) {
    int numRecolhidos = 0;
    int posicaoAtualCamiao = 1; // posicao inicial do camiao
    int numMeiosMobilidade = contarMeiosMobilidade(listaMeiosMobilidade, tipo);

    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade;

    while (atual != NULL && numRecolhidos < numMeiosMobilidade) {
        if (atual->meioMobilidade.autonomia < 50 && strcmp(atual->meioMobilidade.tipo, tipo) == 0) {
            float distancia = pesquisarEmLargura(grafo, posicaoAtualCamiao, atual->meioMobilidade.localizacao);

            float pesoMeioMobilidade = 0;
            if (strcmp(atual->meioMobilidade.tipo, "Carro") == 0) {
                pesoMeioMobilidade = 1000; //1000kg por carro
            }
            else if (strcmp(atual->meioMobilidade.tipo, "Bicicleta") == 0) {
                pesoMeioMobilidade = 6.5;
            }
            else if (strcmp(atual->meioMobilidade.tipo, "Mota") == 0) {
                pesoMeioMobilidade = 50;
            }
            else if (strcmp(atual->meioMobilidade.tipo, "Skate") == 0) {
                pesoMeioMobilidade = 4;
            }

            if (camiao->capacidade + pesoMeioMobilidade > 23000) { //camiao com 23toneladas de carga max.
                printf("Não é possível recolher meio de mobilidade elétrica com ID %d, o camião não tem capacidade suficiente.\n", atual->meioMobilidade.id);
                break;
            }

            printf("Recolher meio de mobilidade elétrica com ID %d.\n", atual->meioMobilidade.id);
            posicaoAtualCamiao = atual->meioMobilidade.localizacao;
            camiao->capacidade += pesoMeioMobilidade;
            numRecolhidos++;
        }

        atual = atual->proxmeiomobilidadelista;
    }

    float distanciaEstacaoRecolha = pesquisarEmLargura(grafo, posicaoAtualCamiao, 1);
    printf("Retornar camião à estação de recolha. Distância percorrida: %.2f metros.\n", distanciaEstacaoRecolha);
    printf("O camião recolheu %d veículos.\n", numRecolhidos);
    posicaoAtualCamiao = 0;

    destruirCamiao; //limpar memoria camiao
}