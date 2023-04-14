/*****************************************************************//**
 * \file   alugueres.h
 * \brief  Header para alugueres
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/
#pragma once

//Estrutura para aluguer
typedef struct Aluguer {
    int id; //ID da transação de aluguer
    int nifcliente; //Corresponde ao NIF do cliente (ID unico)
    int idmeio;
    float preco;
    float duracaominutos;
    time_t data;
} Aluguer;

//Estrutura para lista de aluguer
typedef struct AluguerLista {
    Aluguer aluguer;
    struct AluguerLista* proxaluguer;
} AluguerLista, *AluguerListaPtr;

//Função para criar um novo aluger
Aluguer novoAluguer(int nifcliente, int idmeiomobilidade);

//Função para inserir o aluguer na lista de alugueres
int inserirAluguerLista(AluguerListaPtr* listaAlugueres, Aluguer aluguer);

//Função para verificar se o saldo do cliente é suficiente para realizar o aluguer
int verificarSaldoCliente(Cliente* cliente, int duracaominutos);

//Função para calcular o custo do aluguer
float calcularCustoAluguer(MeioMobilidade* meiomobilidade, int duracaominutos, float custoporminuto);

//Função para verificar se o meio de mobilidade está apto para realizar aluguer e já não se encontra alugado
int verificarEstadoMeioMobilidade(MeioMobilidade* meiomobilidade);

//Função para adicionar um aluguer
int adicionarAluguer(ClienteListaPtr listaClientes, MeiosMobilidadeListaPtr listaMeiosMobilidad, AluguerListaPtr listaAlugueres, Aluguer* aluguer);

//Função para colocar os alugueres realizados num ficheiro backup binário
int guardarBackupAlugueres(Aluguer aluguer);

//Função para ler o ficheiro backup binário e introduzir na lista de alugueres
AluguerListaPtr lerAlugueresBin(char* nomeArquivo);

//Função para listar os alugueres/transações feitas
void listarAlugueres(AluguerListaPtr lista_alugueres);
