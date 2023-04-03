/*****************************************************************//**
 * \file   vgestores.c
 * \brief  Funções para imprimir menus, listas etc dos gestores
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gestores.h"
#include "clientes.h"
#include "meios.h"

/*
@brief Exibe um menu de login para gestor e clientes, permitindo acesso aos menus correspondentes.
@return Retorna 0 caso a função seja executada com sucesso.
*/
void menuLogin() {
    Cliente* head = NULL;

    int opcao;
    int logado = 0;

    do {
        printf("Selecione uma opcao:\n");
        printf("1 - Login como gestor\n");
        printf("2 - Login como cliente\n");
        printf("0 - Sair\n");

        scanf_s("%d", &opcao, sizeof(opcao));

        switch (opcao) {
        case 1:
            logado = loginGestor();
            if (logado) {
                // Chama o menu do gestor
                //menuGestor(); ------ Não está feito!
            }
            break;

        case 2:
            // Chama o menu do cliente
            //menuCliente(); ----- Não está feito!
            break;

        case 0:
            printf("A sair...\n");
            break;

        default:
            printf("Opção inválida.\n");
            break;
        }

    } while (opcao != 0);

    return 0;
}

