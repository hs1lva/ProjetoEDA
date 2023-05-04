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

//Não é necessário nenhuma struct para os gestores, apenas dados diretos para entrar como gestor

//Função para fazer login como gestor
int loginGestor();

//Função para mostrar menu login no inicio do programa
void menuLogin();
