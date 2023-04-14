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
    int id; //ID da transa��o de aluguer
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

//Fun��o para criar um novo aluger
Aluguer novoAluguer(int nifcliente, int idmeiomobilidade);

//Fun��o para inserir o aluguer na lista de alugueres
int inserirAluguerLista(AluguerListaPtr* listaAlugueres, Aluguer aluguer);

//Fun��o para verificar se o saldo do cliente � suficiente para realizar o aluguer
int verificarSaldoCliente(Cliente* cliente, int duracaominutos);

//Fun��o para calcular o custo do aluguer
float calcularCustoAluguer(MeioMobilidade* meiomobilidade, int duracaominutos, float custoporminuto);

//Fun��o para verificar se o meio de mobilidade est� apto para realizar aluguer e j� n�o se encontra alugado
int verificarEstadoMeioMobilidade(MeioMobilidade* meiomobilidade);

//Fun��o para adicionar um aluguer
int adicionarAluguer(ClienteListaPtr listaClientes, MeiosMobilidadeListaPtr listaMeiosMobilidad, AluguerListaPtr listaAlugueres, Aluguer* aluguer);

//Fun��o para colocar os alugueres realizados num ficheiro backup bin�rio
int guardarBackupAlugueres(Aluguer aluguer);

//Fun��o para ler o ficheiro backup bin�rio e introduzir na lista de alugueres
AluguerListaPtr lerAlugueresBin(char* nomeArquivo);

//Fun��o para listar os alugueres/transa��es feitas
void listarAlugueres(AluguerListaPtr lista_alugueres);
