/*****************************************************************//**
 * \file   fmeios.c
 * \brief  Funções para meios de mobilidade
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "meios.h"
#include "clientes.h"

#pragma warning(disable:4996) //não chatear com _s 

/**
@brief Cria um novo meio de mobilidade
@param id o identificador do meio de mobilidade
@param tipo o tipo do meio de mobilidade
@param autonomia a autonomia do meio de mobilidade
@param custo o custo do meio de mobilidade
@param localizacao a localização atual do meio de mobilidade
@param geocodigo o geocódigo da localização atual do meio de mobilidade
@return um apontador para a estrutura do meio de mobilidade criado
*/
MeioMobilidade* novoMeioMobilidade(int id, char tipo[], float autonomia, float custo, char localizacao[], char geocodigo[], int alugado) {
    MeioMobilidade* meioMobilidade = (MeioMobilidade*)malloc(sizeof(MeioMobilidade)); // aloca memória para a estrutura do meio de mobilidade
    meioMobilidade->id = id; // atribui o identificador ao meio de mobilidade
    strcpy(meioMobilidade->tipo, tipo); // copia o tipo para o meio de mobilidade
    meioMobilidade->autonomia = autonomia; // atribui a autonomia ao meio de mobilidade
    meioMobilidade->custo = custo; // atribui o custo ao meio de mobilidade
    strcpy(meioMobilidade->localizacao, localizacao); // copia a localização para o meio de mobilidade
    strcpy(meioMobilidade->geocodigo, geocodigo); // copia o geocodigo(site para usar fase 2) para o meio de mobilidade
    meioMobilidade->alugado = alugado; // escreve se o meio de mobilidade está alugado
    return meioMobilidade; // retorna um apontador para a estrutura do meio de mobilidade criado
}


/**
@brief Adiciona um novo meio de mobilidade à lista de meios de mobilidade
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade existente
@param meioMobilidade apontador para o meio de mobilidade a ser adicionado
@return MeiosMobilidadeListaPtr apontador para a nova lista de meios de mobilidade
*/
MeiosMobilidadeListaPtr adicionarMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, MeioMobilidade* meioMobilidade) {
    // Verifica se já existe um meio de mobilidade com o mesmo id na lista
    MeiosMobilidadeListaPtr auxiliar = listaMeiosMobilidade;
    while (auxiliar != NULL) {
        if (auxiliar->meioMobilidade.id == meioMobilidade->id) {
            return listaMeiosMobilidade; //Erro! Ja existe um meio de mobilidade com esse ID
        }
        auxiliar = auxiliar->proxmeiomobilidadelista;
    }

    MeiosMobilidadeListaPtr novoMeioMobilidade = (MeiosMobilidadeListaPtr)malloc(sizeof(MeiosMobilidadeLista)); // Cria um novo nó na lista de meios de mobilidade, alocando dinamicamente espaço para o mesmo
    novoMeioMobilidade->meioMobilidade = *meioMobilidade; // Atribui o meio de mobilidade passado como parâmetro ao novo nó
    novoMeioMobilidade->proxmeiomobilidadelista = listaMeiosMobilidade; // Define o próximo nó como sendo a lista de meios de mobilidade atual
    return novoMeioMobilidade; // Retorna um apontador para o novo nó, que passa a ser o início da lista de meios de mobilidade com o novo meio de mobilidade adicionado
}


/**
@brief Remove um meio de mobilidade da lista de meios de mobilidade com base no seu ID.
@param listaMeiosMobilidade Apontador para o primeiro elemento da lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser removido.
@return MeiosMobilidadeListaPtr Apontador para o primeiro elemento da lista de meios de mobilidade, após a remoção do meio de mobilidade. Caso o meio de mobilidade não tenha sido encontrado, retorna-se a lista original.
*/
MeiosMobilidadeListaPtr removerMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // Ponteiro para o primeiro elemento da lista
    MeiosMobilidadeListaPtr anterior = NULL; // Ponteiro para o elemento anterior na lista
    while (atual != NULL) { // Loop que percorre a lista até encontrar o elemento a ser removido ou o final da lista
        if (atual->meioMobilidade.id == id) { // Se o ID do meio de mobilidade atual é igual ao ID a ser removido
            if (anterior == NULL) { // caso especial: primeiro elemento
                listaMeiosMobilidade = atual->proxmeiomobilidadelista; // Define a nova cabeça da lista
            }
            else {
                anterior->proxmeiomobilidadelista = atual->proxmeiomobilidadelista; // Conecta o elemento anterior com o próximo elemento após o atual
            }
            free(atual); // Libera a memória do elemento a ser removido
            return listaMeiosMobilidade; // Retorna a lista atualizada
        }
        anterior = atual; // Atualiza o ponteiro para o elemento anterior
        atual = atual->proxmeiomobilidadelista; // Atualiza o ponteiro para o próximo elemento na lista
    }
    return listaMeiosMobilidade; // Retorna a lista original se o elemento a ser removido não foi encontrado
}


/**
@brief Altera os dados de um meio de mobilidade existente com base no seu ID.
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser alterado.
@param tipo Tipo de meio de mobilidade.
@param autonomia Autonomia do meio de mobilidade.
@param custo Custo do meio de mobilidade.
@param localizacao Localização do meio de mobilidade.
@param geocodigo Geocódigo do meio de mobilidade.
@return true se o meio de mobilidade foi alterado com sucesso, false caso contrário.
*/
bool alterarMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, char tipo[], float autonomia, float custo, char localizacao[], char geocodigo[], int alugado) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // apontador para o início da lista
    while (atual != NULL) { // percorre a lista de meios de mobilidade
        if (atual->meioMobilidade.id == id) { // verifica se o meio de mobilidade tem o ID especificado
            strcpy(atual->meioMobilidade.tipo, tipo); // altera o tipo do meio de mobilidade
            atual->meioMobilidade.autonomia = autonomia; // altera a autonomia do meio de mobilidade
            atual->meioMobilidade.custo = custo; // altera o custo do meio de mobilidade
            strcpy(atual->meioMobilidade.localizacao, localizacao); // altera a localização do meio de mobilidade
            strcpy(atual->meioMobilidade.geocodigo, geocodigo); // altera o geocódigo do meio de mobilidade
            atual->meioMobilidade.alugado = alugado; // altera se o meio de mobilidade está ou não alugado
            return true; // retorna true indicando que o meio de mobilidade foi alterado com sucesso
        }
        atual = atual->proxmeiomobilidadelista; // avança para o próximo meio de mobilidade na lista
    }
    return false; // retorna false indicando que não foi possível encontrar o meio de mobilidade com o ID especificado
}


/**
@brief Altera o tipo de um meio de mobilidade existente com base no seu ID.
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser alterado.
@param tipo novo tipo do meio de mobilidade.
@return true se o meio de mobilidade foi alterado com sucesso, false caso contrário.
*/
bool alterarTipoMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, char tipo[]) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // apontador para o início da lista
    while (atual != NULL) { // percorre a lista de meios de mobilidade
        if (atual->meioMobilidade.id == id) { // verifica se o meio de mobilidade tem o ID especificado
            strcpy(atual->meioMobilidade.tipo, tipo); // altera o tipo do meio de mobilidade
            return true; // retorna true indicando que o meio de mobilidade foi alterado com sucesso
        }
        atual = atual->proxmeiomobilidadelista; // avança para o próximo meio de mobilidade na lista
    }
    return false; // retorna false indicando que não foi possível encontrar o meio de mobilidade com o ID especificado
}


/**
@brief Altera a autonomia de um meio de mobilidade existente com base no seu ID.
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser alterado.
@param autonomia Autonomia do meio de mobilidade.
@return true se a autonomia do meio de mobilidade foi alterada com sucesso, false caso contrário.
*/
bool alterarAutonomiaMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, float autonomia) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // apontador para o início da lista
    while (atual != NULL) { // percorre a lista de meios de mobilidade
        if (atual->meioMobilidade.id == id) { // verifica se o meio de mobilidade tem o ID especificado
            atual->meioMobilidade.autonomia = autonomia; // altera a autonomia do meio de mobilidade
            return true; // retorna true indicando que a autonomia do meio de mobilidade foi alterada com sucesso
        }
        atual = atual->proxmeiomobilidadelista; // avança para o próximo meio de mobilidade na lista
    }
    return false; // retorna false indicando que não foi possível encontrar o meio de mobilidade com o ID especificado
}


/**
@brief Altera o custo de um meio de mobilidade existente com base no seu ID.
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser alterado.
@param custo Custo do meio de mobilidade.
@return true se o meio de mobilidade foi alterado com sucesso, false caso contrário.
*/
bool alterarCustoMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, float custo) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // apontador para o início da lista
    while (atual != NULL) { // percorre a lista de meios de mobilidade
        if (atual->meioMobilidade.id == id) { // verifica se o meio de mobilidade tem o ID especificado
            atual->meioMobilidade.custo = custo; // altera o custo do meio de mobilidade
            return true; // retorna true indicando que o meio de mobilidade foi alterado com sucesso
        }
        atual = atual->proxmeiomobilidadelista; // avança para o próximo meio de mobilidade na lista
    }
    return false; // retorna false indicando que não foi possível encontrar o meio de mobilidade com o ID especificado
}


/**
@brief Altera a localização de um meio de mobilidade existente com base no seu ID.
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser alterado.
@param localizacao Nova localização do meio de mobilidade.
@return true se o meio de mobilidade foi alterado com sucesso, false caso contrário.
*/
bool alterarLocalizacaoMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, char localizacao[]) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // apontador para o início da lista
    while (atual != NULL) { // percorre a lista de meios de mobilidade
        if (atual->meioMobilidade.id == id) { // verifica se o meio de mobilidade tem o ID especificado
            strcpy(atual->meioMobilidade.localizacao, localizacao); // altera a localização do meio de mobilidade
            return true; // retorna true indicando que o meio de mobilidade foi alterado com sucesso
        }
        atual = atual->proxmeiomobilidadelista; // avança para o próximo meio de mobilidade na lista
    }
    return false; // retorna false indicando que não foi possível encontrar o meio de mobilidade com o ID especificado
}


/**
@brief Altera o geocódigo de um meio de mobilidade existente com base no seu ID.
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser alterado.
@param geocodigo Geocódigo do meio de mobilidade.
@return true se o geocódigo do meio de mobilidade foi alterado com sucesso, false caso contrário.
*/
bool alterarGeocodigoMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, char geocodigo[]) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // apontador para o início da lista
    while (atual != NULL) { // percorre a lista de meios de mobilidade
        if (atual->meioMobilidade.id == id) { // verifica se o meio de mobilidade tem o ID especificado
            strcpy(atual->meioMobilidade.geocodigo, geocodigo); // altera o geocódigo do meio de mobilidade
            return true; // retorna true indicando que o geocódigo do meio de mobilidade foi alterado com sucesso
        }
        atual = atual->proxmeiomobilidadelista; // avança para o próximo meio de mobilidade na lista
    }
    return false; // retorna false indicando que não foi possível encontrar o meio de mobilidade com o ID especificado
}


/**
@brief Altera o estado alugado de um meio de mobilidade existente com base no seu ID.
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser alterado.
@param alugado Estado alugado do meio de mobilidade.
@return true se o estado do aluguer do meio de mobilidade foi alterado com sucesso, false caso contrário.
*/
bool alterarAlugadoMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // apontador para o início da lista
    while (atual != NULL) { // percorre a lista de meios de mobilidade
        if (atual->meioMobilidade.id == id) { // verifica se o meio de mobilidade tem o ID especificado
            atual->meioMobilidade.alugado = 1; // altera o estado para alugado (1) do meio de mobilidade
            return true; // retorna true indicando que o estado de aluguer do meio de mobilidade foi alterado com sucesso
        }
        atual = atual->proxmeiomobilidadelista; // avança para o próximo meio de mobilidade na lista
    }
    return false; // retorna false indicando que não foi possível encontrar o meio de mobilidade com o ID especificado
}


/**
@brief Pesquisa e retorna um apontador para o meio de mobilidade com o ID especificado, ou NULL caso não exista
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade
@param id ID do meio de mobilidade a ser pesquisado
@return MeioMobilidade* apontador para o meio de mobilidade com o ID especificado, ou NULL caso não exista
*/
MeioMobilidade* pesquisarMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // define um apontador para a lista de meios de mobilidade
    while (atual != NULL) { // percorre a lista até o fim
        if (atual->meioMobilidade.id == id) { // verifica se o ID do meio de mobilidade atual é o mesmo que o ID procurado
            return &atual->meioMobilidade; // retorna um apontador para o meio de mobilidade atual
        }
        atual = atual->proxmeiomobilidadelista; // avança para o próximo meio de mobilidade na lista
    }
    return NULL; // meio de mobilidade não encontrado
}


/**
@brief Liberta a memória alocada para a lista de meios de mobilidade
@param lista apontador para a lista de meios de mobilidade
@return true Operação realizada com sucesso
@return false Falha ao libertar a memória
*/
bool libertarMeiosMobilidadeLista(MeiosMobilidadeListaPtr lista) {
    MeiosMobilidadeListaPtr atual = lista; // aponta para o início da lista
    while (atual != NULL) { // percorre a lista
        MeiosMobilidadeListaPtr prox = atual->proxmeiomobilidadelista; // guarda o próximo nó a ser libertado
        free(atual); // liberta o nó atual
        atual = prox; // atualiza o apontador para o próximo nó
    }
    return true; // retorna true se a operação for realizada com sucesso
}





