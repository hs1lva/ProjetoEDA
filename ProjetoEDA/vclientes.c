/*****************************************************************//**
 * \file   vclientes.c
 * \brief  Fun��es para imprimir menus, listas etc dos clientes
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#include "clientes.h"

#pragma warning(disable:4996) //n�o chatear com _s 

/**
@brief Lista todos os clientes em mem�ria
@param listaClientes Apontador para a lista de clientes
@return void lista de clientes em mem�ria
*/
void listarClientes(ClienteListaPtr listaClientes) {
    ClienteListaPtr atual = listaClientes;
    printf("------ Lista de Clientes ------\n");
    while (atual != NULL) {
        printf("NIF: %d\nNome: %s\nEndere�o: %s\nSaldo: %.2f\nLocaliza��o: %d\nGeoc�digo: %s\n\n", atual->cliente.nif, atual->cliente.nome, atual->cliente.endereco, atual->cliente.saldo, atual->cliente.localizacao, atual->cliente.geocodigo);
        atual = atual->proxclientelista;
    }
    printf("-------------------------------\n");
}

