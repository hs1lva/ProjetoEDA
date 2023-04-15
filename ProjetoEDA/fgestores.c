/*****************************************************************//**
 * \file   fgestores.c
 * \brief  Funções para gestores
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#include "gestores.h"

 /**
 @brief Função para fazer login como gestor
 @return 1 Se o login foi bem sucedido
 @return 0 Se ocorreu um erro no login
 */
int loginGestor() {
    char user[MAX_USER];
    char senha[MAX_SENHA];

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