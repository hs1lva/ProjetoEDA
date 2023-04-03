/*****************************************************************//**
 * \file   vclientes.c
 * \brief  Funções para imprimir menus, listas etc dos clientes
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clientes.h"

#pragma warning(disable:4996) //não chatear com _s 


/**
@brief Lista todos os clientes em memória
@param listaClientes Apontador para a lista de clientes
@return void lista de clientes em memória
*/
void listarClientes(ClienteListaPtr listaClientes) {
    ClienteListaPtr atual = listaClientes;
    printf("------ Lista de Clientes ------\n");
    while (atual != NULL) {
        printf("NIF: %d\nNome: %s\nEndereço: %s\nSaldo: %.2f\n\n", atual->cliente.nif, atual->cliente.nome, atual->cliente.endereco, atual->cliente.saldo);
        atual = atual->proxclientelista;
    }
    printf("-------------------------------\n");
}

