/*****************************************************************//**
 * \file   fmeios.c
 * \brief  Fun��es para meios de mobilidade
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

#pragma warning(disable:4996) //n�o chatear com _s 

/**
@brief Cria um novo meio de mobilidade
@param id o identificador do meio de mobilidade
@param tipo o tipo do meio de mobilidade
@param autonomia a autonomia do meio de mobilidade
@param custo o custo do meio de mobilidade
@param localizacao a localiza��o atual do meio de mobilidade
@param geocodigo o geoc�digo da localiza��o atual do meio de mobilidade
@return um apontador para a estrutura do meio de mobilidade criado
*/
MeioMobilidade* novoMeioMobilidade(int id, char tipo[], float autonomia, float custo, char localizacao[], char geocodigo[], int alugado) {
    MeioMobilidade* meioMobilidade = (MeioMobilidade*)malloc(sizeof(MeioMobilidade)); // aloca mem�ria para a estrutura do meio de mobilidade
    meioMobilidade->id = id; // atribui o identificador ao meio de mobilidade
    strcpy(meioMobilidade->tipo, tipo); // copia o tipo para o meio de mobilidade
    meioMobilidade->autonomia = autonomia; // atribui a autonomia ao meio de mobilidade
    meioMobilidade->custo = custo; // atribui o custo ao meio de mobilidade
    strcpy(meioMobilidade->localizacao, localizacao); // copia a localiza��o para o meio de mobilidade
    strcpy(meioMobilidade->geocodigo, geocodigo); // copia o geocodigo(site para usar fase 2) para o meio de mobilidade
    meioMobilidade->alugado = alugado; // escreve se o meio de mobilidade est� alugado
    return meioMobilidade; // retorna um apontador para a estrutura do meio de mobilidade criado
}


/**
@brief Adiciona um novo meio de mobilidade � lista de meios de mobilidade
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade existente
@param meioMobilidade apontador para o meio de mobilidade a ser adicionado
@return MeiosMobilidadeListaPtr apontador para a nova lista de meios de mobilidade
*/
MeiosMobilidadeListaPtr adicionarMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, MeioMobilidade* meioMobilidade) {
    // Verifica se j� existe um meio de mobilidade com o mesmo id na lista
    MeiosMobilidadeListaPtr auxiliar = listaMeiosMobilidade;
    while (auxiliar != NULL) {
        if (auxiliar->meioMobilidade.id == meioMobilidade->id) {
            return listaMeiosMobilidade; //Erro! Ja existe um meio de mobilidade com esse ID
        }
        auxiliar = auxiliar->proxmeiomobilidadelista;
    }

    MeiosMobilidadeListaPtr novoMeioMobilidade = (MeiosMobilidadeListaPtr)malloc(sizeof(MeiosMobilidadeLista)); // Cria um novo n� na lista de meios de mobilidade, alocando dinamicamente espa�o para o mesmo
    novoMeioMobilidade->meioMobilidade = *meioMobilidade; // Atribui o meio de mobilidade passado como par�metro ao novo n�
    novoMeioMobilidade->proxmeiomobilidadelista = listaMeiosMobilidade; // Define o pr�ximo n� como sendo a lista de meios de mobilidade atual
    return novoMeioMobilidade; // Retorna um apontador para o novo n�, que passa a ser o in�cio da lista de meios de mobilidade com o novo meio de mobilidade adicionado
}


/**
@brief Remove um meio de mobilidade da lista de meios de mobilidade com base no seu ID.
@param listaMeiosMobilidade Apontador para o primeiro elemento da lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser removido.
@return MeiosMobilidadeListaPtr Apontador para o primeiro elemento da lista de meios de mobilidade, ap�s a remo��o do meio de mobilidade. Caso o meio de mobilidade n�o tenha sido encontrado, retorna-se a lista original.
*/
MeiosMobilidadeListaPtr removerMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // Ponteiro para o primeiro elemento da lista
    MeiosMobilidadeListaPtr anterior = NULL; // Ponteiro para o elemento anterior na lista
    while (atual != NULL) { // Loop que percorre a lista at� encontrar o elemento a ser removido ou o final da lista
        if (atual->meioMobilidade.id == id) { // Se o ID do meio de mobilidade atual � igual ao ID a ser removido
            if (anterior == NULL) { // caso especial: primeiro elemento
                listaMeiosMobilidade = atual->proxmeiomobilidadelista; // Define a nova cabe�a da lista
            }
            else {
                anterior->proxmeiomobilidadelista = atual->proxmeiomobilidadelista; // Conecta o elemento anterior com o pr�ximo elemento ap�s o atual
            }
            free(atual); // Libera a mem�ria do elemento a ser removido
            return listaMeiosMobilidade; // Retorna a lista atualizada
        }
        anterior = atual; // Atualiza o ponteiro para o elemento anterior
        atual = atual->proxmeiomobilidadelista; // Atualiza o ponteiro para o pr�ximo elemento na lista
    }
    return listaMeiosMobilidade; // Retorna a lista original se o elemento a ser removido n�o foi encontrado
}


/**
@brief Altera os dados de um meio de mobilidade existente com base no seu ID.
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser alterado.
@param tipo Tipo de meio de mobilidade.
@param autonomia Autonomia do meio de mobilidade.
@param custo Custo do meio de mobilidade.
@param localizacao Localiza��o do meio de mobilidade.
@param geocodigo Geoc�digo do meio de mobilidade.
@return true se o meio de mobilidade foi alterado com sucesso, false caso contr�rio.
*/
bool alterarMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, char tipo[], float autonomia, float custo, char localizacao[], char geocodigo[], int alugado) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // apontador para o in�cio da lista
    while (atual != NULL) { // percorre a lista de meios de mobilidade
        if (atual->meioMobilidade.id == id) { // verifica se o meio de mobilidade tem o ID especificado
            strcpy(atual->meioMobilidade.tipo, tipo); // altera o tipo do meio de mobilidade
            atual->meioMobilidade.autonomia = autonomia; // altera a autonomia do meio de mobilidade
            atual->meioMobilidade.custo = custo; // altera o custo do meio de mobilidade
            strcpy(atual->meioMobilidade.localizacao, localizacao); // altera a localiza��o do meio de mobilidade
            strcpy(atual->meioMobilidade.geocodigo, geocodigo); // altera o geoc�digo do meio de mobilidade
            atual->meioMobilidade.alugado = alugado; // altera se o meio de mobilidade est� ou n�o alugado
            return true; // retorna true indicando que o meio de mobilidade foi alterado com sucesso
        }
        atual = atual->proxmeiomobilidadelista; // avan�a para o pr�ximo meio de mobilidade na lista
    }
    return false; // retorna false indicando que n�o foi poss�vel encontrar o meio de mobilidade com o ID especificado
}


/**
@brief Altera o tipo de um meio de mobilidade existente com base no seu ID.
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser alterado.
@param tipo novo tipo do meio de mobilidade.
@return true se o meio de mobilidade foi alterado com sucesso, false caso contr�rio.
*/
bool alterarTipoMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, char tipo[]) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // apontador para o in�cio da lista
    while (atual != NULL) { // percorre a lista de meios de mobilidade
        if (atual->meioMobilidade.id == id) { // verifica se o meio de mobilidade tem o ID especificado
            strcpy(atual->meioMobilidade.tipo, tipo); // altera o tipo do meio de mobilidade
            return true; // retorna true indicando que o meio de mobilidade foi alterado com sucesso
        }
        atual = atual->proxmeiomobilidadelista; // avan�a para o pr�ximo meio de mobilidade na lista
    }
    return false; // retorna false indicando que n�o foi poss�vel encontrar o meio de mobilidade com o ID especificado
}


/**
@brief Altera a autonomia de um meio de mobilidade existente com base no seu ID.
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser alterado.
@param autonomia Autonomia do meio de mobilidade.
@return true se a autonomia do meio de mobilidade foi alterada com sucesso, false caso contr�rio.
*/
bool alterarAutonomiaMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, float autonomia) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // apontador para o in�cio da lista
    while (atual != NULL) { // percorre a lista de meios de mobilidade
        if (atual->meioMobilidade.id == id) { // verifica se o meio de mobilidade tem o ID especificado
            atual->meioMobilidade.autonomia = autonomia; // altera a autonomia do meio de mobilidade
            return true; // retorna true indicando que a autonomia do meio de mobilidade foi alterada com sucesso
        }
        atual = atual->proxmeiomobilidadelista; // avan�a para o pr�ximo meio de mobilidade na lista
    }
    return false; // retorna false indicando que n�o foi poss�vel encontrar o meio de mobilidade com o ID especificado
}


/**
@brief Altera o custo de um meio de mobilidade existente com base no seu ID.
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser alterado.
@param custo Custo do meio de mobilidade.
@return true se o meio de mobilidade foi alterado com sucesso, false caso contr�rio.
*/
bool alterarCustoMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, float custo) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // apontador para o in�cio da lista
    while (atual != NULL) { // percorre a lista de meios de mobilidade
        if (atual->meioMobilidade.id == id) { // verifica se o meio de mobilidade tem o ID especificado
            atual->meioMobilidade.custo = custo; // altera o custo do meio de mobilidade
            return true; // retorna true indicando que o meio de mobilidade foi alterado com sucesso
        }
        atual = atual->proxmeiomobilidadelista; // avan�a para o pr�ximo meio de mobilidade na lista
    }
    return false; // retorna false indicando que n�o foi poss�vel encontrar o meio de mobilidade com o ID especificado
}


/**
@brief Altera a localiza��o de um meio de mobilidade existente com base no seu ID.
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser alterado.
@param localizacao Nova localiza��o do meio de mobilidade.
@return true se o meio de mobilidade foi alterado com sucesso, false caso contr�rio.
*/
bool alterarLocalizacaoMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, char localizacao[]) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // apontador para o in�cio da lista
    while (atual != NULL) { // percorre a lista de meios de mobilidade
        if (atual->meioMobilidade.id == id) { // verifica se o meio de mobilidade tem o ID especificado
            strcpy(atual->meioMobilidade.localizacao, localizacao); // altera a localiza��o do meio de mobilidade
            return true; // retorna true indicando que o meio de mobilidade foi alterado com sucesso
        }
        atual = atual->proxmeiomobilidadelista; // avan�a para o pr�ximo meio de mobilidade na lista
    }
    return false; // retorna false indicando que n�o foi poss�vel encontrar o meio de mobilidade com o ID especificado
}


/**
@brief Altera o geoc�digo de um meio de mobilidade existente com base no seu ID.
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser alterado.
@param geocodigo Geoc�digo do meio de mobilidade.
@return true se o geoc�digo do meio de mobilidade foi alterado com sucesso, false caso contr�rio.
*/
bool alterarGeocodigoMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id, char geocodigo[]) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // apontador para o in�cio da lista
    while (atual != NULL) { // percorre a lista de meios de mobilidade
        if (atual->meioMobilidade.id == id) { // verifica se o meio de mobilidade tem o ID especificado
            strcpy(atual->meioMobilidade.geocodigo, geocodigo); // altera o geoc�digo do meio de mobilidade
            return true; // retorna true indicando que o geoc�digo do meio de mobilidade foi alterado com sucesso
        }
        atual = atual->proxmeiomobilidadelista; // avan�a para o pr�ximo meio de mobilidade na lista
    }
    return false; // retorna false indicando que n�o foi poss�vel encontrar o meio de mobilidade com o ID especificado
}


/**
@brief Altera o estado alugado de um meio de mobilidade existente com base no seu ID.
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade.
@param id ID do meio de mobilidade a ser alterado.
@param alugado Estado alugado do meio de mobilidade.
@return true se o estado do aluguer do meio de mobilidade foi alterado com sucesso, false caso contr�rio.
*/
bool alterarAlugadoMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // apontador para o in�cio da lista
    while (atual != NULL) { // percorre a lista de meios de mobilidade
        if (atual->meioMobilidade.id == id) { // verifica se o meio de mobilidade tem o ID especificado
            atual->meioMobilidade.alugado = 1; // altera o estado para alugado (1) do meio de mobilidade
            return true; // retorna true indicando que o estado de aluguer do meio de mobilidade foi alterado com sucesso
        }
        atual = atual->proxmeiomobilidadelista; // avan�a para o pr�ximo meio de mobilidade na lista
    }
    return false; // retorna false indicando que n�o foi poss�vel encontrar o meio de mobilidade com o ID especificado
}


/**
@brief Pesquisa e retorna um apontador para o meio de mobilidade com o ID especificado, ou NULL caso n�o exista
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade
@param id ID do meio de mobilidade a ser pesquisado
@return MeioMobilidade* apontador para o meio de mobilidade com o ID especificado, ou NULL caso n�o exista
*/
MeioMobilidade* pesquisarMeioMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade, int id) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade; // define um apontador para a lista de meios de mobilidade
    while (atual != NULL) { // percorre a lista at� o fim
        if (atual->meioMobilidade.id == id) { // verifica se o ID do meio de mobilidade atual � o mesmo que o ID procurado
            return &atual->meioMobilidade; // retorna um apontador para o meio de mobilidade atual
        }
        atual = atual->proxmeiomobilidadelista; // avan�a para o pr�ximo meio de mobilidade na lista
    }
    return NULL; // meio de mobilidade n�o encontrado
}


/**
@brief Liberta a mem�ria alocada para a lista de meios de mobilidade
@param lista apontador para a lista de meios de mobilidade
@return true Opera��o realizada com sucesso
@return false Falha ao libertar a mem�ria
*/
bool libertarMeiosMobilidadeLista(MeiosMobilidadeListaPtr lista) {
    MeiosMobilidadeListaPtr atual = lista; // aponta para o in�cio da lista
    while (atual != NULL) { // percorre a lista
        MeiosMobilidadeListaPtr prox = atual->proxmeiomobilidadelista; // guarda o pr�ximo n� a ser libertado
        free(atual); // liberta o n� atual
        atual = prox; // atualiza o apontador para o pr�ximo n�
    }
    return true; // retorna true se a opera��o for realizada com sucesso
}





