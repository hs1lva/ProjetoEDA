/*****************************************************************//**
 * \file   fclientes.c
 * \brief  Fun��es para clientes
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#include "clientes.h"

#pragma warning(disable:4996) //n�o chatear com _s 

/**
@brief Cria um novo cliente e retorna um apontador para a estrutura criada
@param nif N�mero de Identifica��o Fiscal do cliente
@param nome Nome do cliente
@param endereco Endere�o do cliente
@param saldo Saldo do cliente
@param localizacao Localiza��o do cliente
@param geocodigo Geoc�digo do cliente
@return apontador para a estrutura Cliente criada
*/
Cliente* novoCliente(int nif, char nome[], char endereco[], float saldo, char localizacao[], char geocodigo[]) {
    Cliente* cliente = (Cliente*)malloc(sizeof(Cliente)); // Aloca espa�o na mem�ria para uma nova estrutura Cliente
    cliente->nif = nif; // Atribui o n�mero de identifica��o fiscal ao novo cliente
    strcpy(cliente->nome, nome); // Copia o nome do cliente para a nova estrutura
    strcpy(cliente->endereco, endereco); // Copia o endere�o do cliente para a nova estrutura
    cliente->saldo = saldo; // Atribui o saldo ao novo cliente
    strcpy(cliente->localizacao, localizacao); // Copia a localiza��o do cliente para a nova estrutura
    strcpy(cliente->geocodigo, geocodigo); // Copia o geocodigo do cliente para a nova estrutura
    return cliente; // Retorna um apontador para a nova estrutura Cliente criada
}


/**
@brief Adiciona um novo cliente � lista de clientes.
Esta fun��o recebe um apontador para a lista de clientes e um apontador para a estrutura Cliente,
e cria um novo n� na lista com a informa��o do cliente. Em seguida, retorna um apontador para o novo n�.
@param listaClientes O apontador para a lista de clientes.
@param cliente O apontador para a estrutura Cliente a ser adicionada na lista.
@return Retorna um apontador para o novo n� criado na lista.
*/
ClienteListaPtr adicionarCliente(ClienteListaPtr listaClientes, Cliente* cliente) {
    // Verifica se j� existe um cliente com o mesmo NIF
    if (pesquisarCliente(listaClientes, cliente->nif) != NULL) {
        return listaClientes;
    }
    ClienteListaPtr novoCliente = (ClienteListaPtr)malloc(sizeof(ClienteLista)); // Aloca espa�o na mem�ria para o novo n� na lista
    novoCliente->cliente = *cliente; // Copia a informa��o do cliente recebido para a estrutura dentro do novo n�
    novoCliente->proxclientelista = listaClientes; // Faz o novo n� apontar para o in�cio da lista
    return novoCliente; // Retorna o apontador para o novo n� criado na lista
}


/**
@brief Remove um cliente da lista de clientes com base no seu NIF
@param listaClientes apontador para o in�cio da lista de clientes
@param nif NIF do cliente a ser removido
@return ClienteListaPtr apontador para o in�cio da lista de clientes ap�s a remo��o
*/
ClienteListaPtr removerCliente(ClienteListaPtr listaClientes, int nif) {
    ClienteListaPtr atual = listaClientes; // inicializa o apontador atual para apontar para o in�cio da lista
    ClienteListaPtr anterior = NULL; // inicializa o apontador anterior como nulo
    while (atual != NULL) { // enquanto a lista n�o for percorrida por completo
        if (atual->cliente.nif == nif) { // se encontrar o cliente com o NIF desejado
            if (anterior == NULL) { // caso especial: primeiro elemento
                listaClientes = atual->proxclientelista; // atualiza o in�cio da lista
            }
            else {
                anterior->proxclientelista = atual->proxclientelista; // atualiza o apontador do elemento anterior
            }
            free(atual); // libera a mem�ria alocada para o elemento
            return listaClientes; // retorna a lista atualizada
        }
        anterior = atual; // atualiza o apontador anterior para apontar para o atual
        atual = atual->proxclientelista; // atualiza o apontador atual para apontar para o pr�ximo elemento da lista
    }
    return listaClientes; // retorna a lista original caso o cliente n�o tenha sido encontrado
}


/**
@brief Altera os dados de um cliente existente com base no seu NIF
@param listaClientes apontador para a lista de clientes
@param nif NIF do cliente a ser alterado
@param nome novo nome do cliente
@param endereco novo endere�o do cliente
@param saldo novo saldo do cliente
@param localizacao Localiza��o do cliente
@param geocodigo Geoc�digo do cliente
@return bool 1 se a altera��o for bem sucedida, 0 caso contr�rio
*/
bool alterarCliente(ClienteListaPtr listaClientes, int nif, char nome[], char endereco[], float saldo, char localizacao[], char geocodigo[]) {
    ClienteListaPtr atual = listaClientes; // Inicializa o apontador atual para o primeiro elemento da lista
    while (atual != NULL) { // enquanto a lista n�o for percorrida por completo
        if (atual->cliente.nif == nif) { // Percorre a lista at� encontrar o cliente com o NIF especificado
            strcpy(atual->cliente.nome, nome); // Altera os dados do cliente
            strcpy(atual->cliente.endereco, endereco); // Altera os dados do cliente
            atual->cliente.saldo = saldo; // Altera os dados do cliente
            strcpy(atual->cliente.localizacao, localizacao); // Altera os dados do cliente
            strcpy(atual->cliente.geocodigo, geocodigo); // Altera os dados do cliente
            return true; // sucesso
        }
        atual = atual->proxclientelista; // atualiza o apontador atual para apontar para o pr�ximo elemento da lista
    }
    return false; // cliente n�o encontrado
}


/**
@brief Altera o nome de um cliente existente com base no seu NIF
@param listaClientes apontador para a lista de clientes
@param nif NIF do cliente a ser alterado
@param nome novo nome do cliente
@return bool 1 se a altera��o for bem sucedida, 0 caso contr�rio
*/
bool alterarNomeCliente(ClienteListaPtr listaClientes, int nif, char nome[]) {
    ClienteListaPtr atual = listaClientes; // Inicializa o apontador atual para o primeiro elemento da lista
    while (atual != NULL) { // enquanto a lista n�o for percorrida por completo
        if (atual->cliente.nif == nif) { // Percorre a lista at� encontrar o cliente com o NIF especificado
            strcpy(atual->cliente.nome, nome); // Altera o nome do cliente
            return true; // sucesso
        }
        atual = atual->proxclientelista; // atualiza o apontador atual para apontar para o pr�ximo elemento da lista
    }
    return false; // cliente n�o encontrado
}


/**
@brief Altera o endere�o de um cliente existente com base no seu NIF
@param listaClientes apontador para a lista de clientes
@param nif NIF do cliente a ser alterado
@param endereco novo endere�o do cliente
@return bool 1 se a altera��o for bem sucedida, 0 caso contr�rio
*/
bool alterarEnderecoCliente(ClienteListaPtr listaClientes, int nif, char endereco[]) {
    ClienteListaPtr atual = listaClientes; // Inicializa o apontador atual para o primeiro elemento da lista
    while (atual != NULL) { // enquanto a lista n�o for percorrida por completo
        if (atual->cliente.nif == nif) { // Percorre a lista at� encontrar o cliente com o NIF especificado
            strcpy(atual->cliente.endereco, endereco); // Altera o endere�o do cliente
            return true; // sucesso
        }
        atual = atual->proxclientelista; // atualiza o apontador atual para apontar para o pr�ximo elemento da lista
    }
    return false; // cliente n�o encontrado
}


/**
@brief Altera o saldo de um cliente existente com base no seu NIF
@param listaClientes apontador para a lista de clientes
@param nif NIF do cliente a ser alterado
@param saldo novo saldo do cliente
@return bool 1 se a altera��o for bem sucedida, 0 caso contr�rio
*/
bool alterarSaldoCliente(ClienteListaPtr listaClientes, int nif, float saldo) {
    ClienteListaPtr atual = listaClientes; // Inicializa o apontador atual para o primeiro elemento da lista
    while (atual != NULL) { // enquanto a lista n�o for percorrida por completo
        if (atual->cliente.nif == nif) { // Percorre a lista at� encontrar o cliente com o NIF especificado
            atual->cliente.saldo = saldo; // Altera o saldo do cliente
            return true; // sucesso
        }
        atual = atual->proxclientelista; // atualiza o apontador atual para apontar para o pr�ximo elemento da lista
    }
    return false; // cliente n�o encontrado
}


/**
@brief Altera a localiza��o de um cliente existente com base no seu NIF
@param listaClientes apontador para a lista de clientes
@param nif NIF do cliente a ser alterado
@param localizacao nova localiza��o do cliente
@return bool 1 se a altera��o for bem sucedida, 0 caso contr�rio
*/
bool alterarLocalizacaoCliente(ClienteListaPtr listaClientes, int nif, char localizacao[]) {
    ClienteListaPtr atual = listaClientes; // Inicializa o apontador atual para o primeiro elemento da lista
    while (atual != NULL) { // enquanto a lista n�o for percorrida por completo
        if (atual->cliente.nif == nif) { // Percorre a lista at� encontrar o cliente com o NIF especificado
            strcpy(atual->cliente.localizacao, localizacao); // Altera a localiza��o do cliente
            return true; // sucesso
        }
        atual = atual->proxclientelista; // atualiza o apontador atual para apontar para o pr�ximo elemento da lista
    }
    return false; // cliente n�o encontrado
}


/**
@brief Altera o geoc�digo de um cliente existente com base no seu NIF
@param listaClientes apontador para a lista de clientes
@param nif NIF do cliente a ser alterado
@param geocodigo novo geoc�digo do cliente
@return bool 1 se a altera��o for bem sucedida, 0 caso contr�rio
*/
bool alterarGeocodigoCliente(ClienteListaPtr listaClientes, int nif, char geocodigo[]) {
    ClienteListaPtr atual = listaClientes; // Inicializa o apontador atual para o primeiro elemento da lista
    while (atual != NULL) { // enquanto a lista n�o for percorrida por completo
        if (atual->cliente.nif == nif) { // Percorre a lista at� encontrar o cliente com o NIF especificado
            strcpy(atual->cliente.geocodigo, geocodigo); // Altera o geocodigo do cliente
            return true; // sucesso
        }
        atual = atual->proxclientelista; // atualiza o apontador atual para apontar para o pr�ximo elemento da lista
    }
    return false; // cliente n�o encontrado
}


/**
@brief Retorna um apontador para o cliente com o NIF especificado, ou NULL caso n�o exista
@param listaClientes apontador para a lista de clientes
@param nif NIF do cliente a ser pesquisado
@return Cliente* apontador para o cliente encontrado, ou NULL caso n�o exista
*/
Cliente* pesquisarCliente(ClienteListaPtr listaClientes, int nif) {
    ClienteListaPtr atual = listaClientes; // Inicializa o apontador atual para o primeiro elemento da lista
    while (atual != NULL) { // enquanto a lista n�o for percorrida por completo
        if (atual->cliente.nif == nif) { // Percorre a lista at� encontrar o cliente com o NIF especificado
            return &atual->cliente; // Retorna um apontador para o cliente com o NIF especificado
        }
        atual = atual->proxclientelista; // atualiza o apontador atual para apontar para o pr�ximo elemento da lista
    }
    return NULL; // cliente n�o encontrado
}


/**
@brief Liberta a mem�ria alocada para a lista de clientes.
@param lista A lista de clientes a ser libertada.
@return bool Retorna 1 se a liberta��o foi bem sucedida, 0 caso contr�rio.
*/
bool libertarClientesLista(ClienteListaPtr listaClientes) {
    ClienteListaPtr atual = listaClientes; // Inicializa o apontador atual para o primeiro elemento da lista
    while (atual != NULL) { // enquanto a lista n�o for percorrida por completo
        ClienteListaPtr prox = atual->proxclientelista; // guarda o apontador para o pr�ximo elemento
        free(atual); // liberta a mem�ria do elemento atual
        atual = prox; // avan�a para o pr�ximo elemento
    }
    return true; // true - bem sucedido
}


