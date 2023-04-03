/*****************************************************************//**
 * \file   main.c
 * \brief  Main do projeto
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#include <stdio.h>
#include "clientes.h"
#include "gestores.h"
#include "meios.h"
#include "alugueres.h"

#pragma warning(disable:4996) //não chatear com _s 

int main() {
    
    ClienteListaPtr listaClientes = lerClientesBin("backup_clientes.bin");
    MeiosMobilidadeListaPtr listaMeios = lerMeiosMobilidadeBin("backup_meiosmobilidade.bin");
    AluguerListaPtr listaAlugueres = lerAlugueresBin("backup_alugueres.bin");

#pragma region Testar funções clientes

    // Adiciona alguns clientes
    //Cliente* cliente1 = novoCliente(89, "João Silva", "Rua das Flores, 123", 1000.0);
    //listaClientes = adicionarCliente(listaClientes, cliente1);

    //Cliente* cliente2 = novoCliente(987654321, "Maria Santos", "Avenida Central, 456", 2000.0);
    //listaClientes = adicionarCliente(listaClientes, cliente2);

    //Remove um cliente
    //listaClientes = removerCliente(listaClientes, 123456789);

    //Altera um cliente
    //alterarCliente(listaClientes, 987654321, "Maria Oliveira", "Avenida Principal, 789", 3000.0);

    //Escreve os dados atualizados dos clientes de volta para o arquivo CSV
    //escreverClientesCSV(listaClientes, "clientes.csv");

    //Pesquisar um cliente
    //pesquisarCliente(listaClientes, 232);

    //Apresentar lista de clientes em memória
    //listarClientes(listaClientes);

    //Libertar memória da lista de clientes
    //libertarClientesLista(listaClientes);

    //guardarBackupClientes(listaClientes);

#pragma endregion

#pragma region Testar funções meios de mobilidade

    // Adiciona alguns meios de mobilidade
    //Cliente* meio1 = novoMeioMobilidade(100,"Bicicleta",50.0,3.4,"Porto","ASDAH23", 1); //Inserir ID 100
    //listaMeios = adicionarMeioMobilidade(listaMeios, meio1);

    //Cliente* meio2 = novoMeioMobilidade(101,"Lambreta",32.0,0.4,"Braga","ASDA3232D3", 1); //Inserir ID 101
    //listaMeios = adicionarMeioMobilidade(listaMeios, meio2);

    // Remove um meio de mobilidade
    //listaMeios = removerMeioMobilidade(listaMeios, 1); //ID 1 a remover

    // Altera um meio de mobilidade
    //alterarMeioMobilidade(listaMeios, 2, "Triciclo", 20.0, 3.1, "Guimaraes", "UEDED2"); //Alterar ID 2

    // Escreve os dados atualizados dos meios de mobilidade de volta para o arquivo CSV
    //escreverMeios(listaMeios, "meiosmobilidade.csv");

    //Guardar ficheiro bin nos meios de mobilidade para backup dados
    //guardarBackupMeiosMobilidade(listaMeios);

    //Apresentar lista de meios de mobilidade em memória
    //listarMeiosMobilidade(listaMeios);

    //Apresentar lista de meios de mobilidade em memória ordenados pela autonomia
    //listarMeiosMobilidadeOrdenadosAutonomia(listaMeios);

    //Apresentar lista de meios de mobilidade apenas numa determinada localização com geocodigo
    //listarMeiosMobilidadePorLocalizacao(listaMeios);

    //Libertar memória da lista de meios de mobilidade
    //libertarMeiosMobilidadeLista(listaMeios);

#pragma endregion

#pragma region Testar funções alugueres

    Aluguer aluguer1 = novoAluguer(232, 1);
    
    adicionarAluguer(listaClientes, listaMeios, listaAlugueres, &aluguer1);
    

    // Lista os alugueres lidos do arquivo
    //listarAlugueres(lista_alugueres);

#pragma endregion


    //--------------IDEIAS A FAZER/CONCLUIR------------
    //Função para ler ficheiro backup_alugueres.bin (ver também se o bin de registo de alugueres está operacional como todos os outros)
    //Função para listar as transações feitas (caso seja necessario mais tarde)

    return 0;
}
