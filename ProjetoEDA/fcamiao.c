/*****************************************************************//**
 * \file   fcamiao.c
 * \brief  Fun��es para o cami�o
 * 
 * \author hugo2
 * \date   May 2023
 *********************************************************************/

#include "meios.h"
#include "camiao.h"

/**
@brief Cria um novo cami�o.
@return Apontador para o novo cami�o.
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
* @brief Destr�i um cami�o previamente alocado.
* @param camiao Apontador para o cami�o a ser destru�do.
*/
void destruirCamiao(Camiao* camiao) {
    free(camiao);
}

/**
* @brief Imprime os dados de um cami�o.
* @param camiao Apontador para o cami�o a ser impresso.
*/
void imprimirCamiao(Camiao* camiao) {
    printf("Autonomia do camiao: %.2f km\n", camiao->autonomia);
    printf("Capacidade do camiao: %d meios de mobilidade eletrica\n", camiao->capacidade);
}

/**
* @brief Conta quantos meios de mobilidade de um dado tipo existem na lista.
* @param listaMeiosMobilidade Apontador para a lista de meios de mobilidade.
* @param tipo String contendo o tipo de meio de mobilidade a ser contado.
* @return N�mero de meios de mobilidade do tipo especificado.
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
@brief Recolhe meios de mobilidade el�trica do tipo especificado pelo utilizador.
@param grafo Apontador para o grafo.
@param listaMeiosMobilidade Apontador para a lista de meios de mobilidade el�trica.
@param camiao Apontador para a estrutura que representa o cami�o de recolha.
@param tipo Tipos de meios de mobilidade el�trica a serem recolhidos.
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
                printf("N�o � poss�vel recolher meio de mobilidade el�trica com ID %d, o cami�o n�o tem capacidade suficiente.\n", atual->meioMobilidade.id);
                break;
            }

            printf("Recolher meio de mobilidade el�trica com ID %d.\n", atual->meioMobilidade.id);
            posicaoAtualCamiao = atual->meioMobilidade.localizacao;
            camiao->capacidade += pesoMeioMobilidade;
            numRecolhidos++;
        }

        atual = atual->proxmeiomobilidadelista;
    }

    float distanciaEstacaoRecolha = pesquisarEmLargura(grafo, posicaoAtualCamiao, 1);
    printf("Retornar cami�o � esta��o de recolha. Dist�ncia percorrida: %.2f metros.\n", distanciaEstacaoRecolha);
    printf("O cami�o recolheu %d ve�culos.\n", numRecolhidos);
    posicaoAtualCamiao = 0;

    destruirCamiao; //limpar memoria camiao
}