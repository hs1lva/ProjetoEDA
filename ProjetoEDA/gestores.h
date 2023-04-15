/*****************************************************************//**
 * \file   gestores.h
 * \brief  Header para gestores
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//N�o � necess�rio nenhuma struct para os gestores

#define MAX_USER 20
#define MAX_SENHA 20

// Definir o user e a senha do gestor
#define GESTOR_USER "admin"
#define GESTOR_SENHA "1234"

//Fun��o para fazer login como gestor
int loginGestor();

//Fun��o para mostrar menu login no inicio do programa
void menuLogin();
