/*****************************************************************//**
 * \file   main.c
 * \brief  Main do projeto
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#include "clientes.h"
#include "gestores.h"
#include "meios.h"
#include "alugueres.h"
#include "grafos.h"

#pragma warning(disable:4996) //não chatear com _s 

int main() {
    
    ClienteListaPtr listaClientes = lerClientesBin("backup_clientes.bin");
    MeiosMobilidadeListaPtr listaMeios = lerMeiosMobilidadeBin("backup_meiosmobilidade.bin");
    AluguerListaPtr listaAlugueres = lerAlugueresBin("backup_alugueres.bin");

#pragma region Testar funções clientes

    // Adiciona alguns clientes
    //Cliente* cliente1 = novoCliente(89, "João Silva", "Rua das Flores, 123", 1000.0, 4, "DASDA");
    //listaClientes = adicionarCliente(listaClientes, cliente1);

    //Cliente* cliente2 = novoCliente(987654321, "Maria Santos", "Avenida Central, 456", 2000.0, 5, "DSDADDD");
    //listaClientes = adicionarCliente(listaClientes, cliente2);

    //Remove um cliente
    //listaClientes = removerCliente(listaClientes, 123456789);

    //Altera um cliente
    //alterarCliente(listaClientes, 987654321, "Maria Oliveira", "Avenida Principal, 789", 3000.0, 5, "DSADSSS");

    //Escreve os dados atualizados dos clientes de volta para o arquivo CSV
    //escreverClientesCSV(listaClientes, "clientes.csv");

    //Pesquisar um cliente
    //pesquisarCliente(listaClientes, 232);

    //Apresentar lista de clientes em memória
    listarClientes(listaClientes);

    //Libertar memória da lista de clientes
    //libertarClientesLista(listaClientes);

    guardarBackupClientes(listaClientes);

#pragma endregion

#pragma region Testar funções meios de mobilidade

    // Adiciona alguns meios de mobilidade
    //Cliente* meio1 = novoMeioMobilidade(100,"Bicicleta",50.0,3.4,"6","ASDAH23", 0); //Inserir ID 100
    //listaMeios = adicionarMeioMobilidade(listaMeios, meio1);

    //Cliente* meio2 = novoMeioMobilidade(101,"Lambreta",32.0,0.4,"7","ASDA3232D3", 0); //Inserir ID 101
    //listaMeios = adicionarMeioMobilidade(listaMeios, meio2);

    // Remove um meio de mobilidade
    //listaMeios = removerMeioMobilidade(listaMeios, 1); //ID 1 a remover

    // Altera um meio de mobilidade
    //alterarMeioMobilidade(listaMeios, 1, "Triciclo", 20.0, 3.1, "3", "UEDED2", 0); //Alterar ID 1

    // Escreve os dados atualizados dos meios de mobilidade de volta para o arquivo CSV
    //escreverMeios(listaMeios, "meiosmobilidade.csv");

    //Guardar ficheiro bin nos meios de mobilidade para backup dados
    //guardarBackupMeiosMobilidade(listaMeios);

    //Apresentar lista de meios de mobilidade em memória
    listarMeiosMobilidade(listaMeios);

    //Apresentar lista de meios de mobilidade em memória ordenados pela autonomia
    //listarMeiosMobilidadeOrdenadosAutonomia(listaMeios);

    //Apresentar lista de meios de mobilidade apenas numa determinada localização com geocodigo
    //listarMeiosMobilidadePorLocalizacao(listaMeios);

    //Libertar memória da lista de meios de mobilidade
    //libertarMeiosMobilidadeLista(listaMeios);

#pragma endregion

#pragma region Testar funções alugueres

    // Adicionar alguns alugueres manualmente
    //Aluguer aluguer1 = novoAluguer(232, 1, 34); // idCliente=232, idMeioMobilidade=1, NºMinutos=34min
    //adicionarAluguer(listaClientes, listaMeios, &listaAlugueres, &aluguer1);

    //Aluguer aluguer2 = novoAluguer(232, 100, 35.5); // idCliente=232, idMeioMobilidade=100, NºMinutos=35.5min
    //adicionarAluguer(listaClientes, listaMeios, &listaAlugueres, &aluguer2);

    // Listar alugueres
    //listarAlugueres(listaAlugueres);

    //Reescrever os ficheiros .bin para o seguinte:
    //---Atualizar o meio de mobilidade usado no aluguer acima para ficar a 1(alugado) e guardar no backup_binario o novo estado alugado.
    //---Atualizar o cliente usado no aluguer para depois de ser feito o calculo do custo de aluguer, descontar no saldo e guardar no backup_binario novo saldo.
    //guardarBackupMeiosMobilidade(listaMeios);
    //guardarBackupClientes(listaClientes);

#pragma endregion

#pragma region Testar funções grafos (localizações)

    Vertice* grafo = NULL;
    int totalVertices = lerGrafoCSV(&grafo, "grafos.csv");

    //guardarBackupVertices(grafo, "backup_vertices.bin");
    //guardarBackupAdjacentes(grafo, "backup_adjacentes.bin");

    //int totalVertices = lerVerticesBin(&grafo, "backup_vertices.bin");
    //lerAdjacentesBin(&grafo, "backup_adjacentes.bin");

    imprimirGrafo(grafo);

#pragma endregion

    // Atualizar os alugueres com o preço com os caminhos dos grafos

    return 0;
}
