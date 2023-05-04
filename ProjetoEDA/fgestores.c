/*****************************************************************//**
 * \file   fgestores.c
 * \brief  Funções para gestores
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#include "gestores.h"

#define TAM_NOME_USER 50
#define TAM_NOME_SENHA 50

 // Definir o user e a senha do gestor
#define GESTOR_USER "admin"
#define GESTOR_SENHA "1234"

/**
@brief Função para fazer login como gestor
@return 1 Se o login foi bem sucedido
@return 0 Se ocorreu um erro no login
*/
int loginGestor() {
    char user[TAM_NOME_USER];
    char senha[TAM_NOME_SENHA];

    // Solicita o user e a senha do gestor
    printf("User: ");
    scanf_s("%s", &user, sizeof(user));

    printf("Senha: ");
    scanf_s("%s", &senha, sizeof(senha));

    // Verifica se o user e a senha estão corretos
    if (strcmp(user, GESTOR_USER) == 0 && strcmp(senha, GESTOR_SENHA) == 0) {
        return 1; //sucesso
    }
    else {
        return 0; //erro
    }
}