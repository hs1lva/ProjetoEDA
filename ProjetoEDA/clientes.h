/*****************************************************************//**
 * \file   clientes.h
 * \brief  Header para clientes
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/
#pragma once
#include <stdbool.h>

#define TAM_NOME 50 //Definir tamanho char para nome cliente
#define TAM_END 100 //Definir tamanho char para endereço do cliente
#define TAM_LOCCLIENTE 30 //Definir tamanho char para localização do cliente
#define TAM_GEOCLIENTE 100 //Definir tamanho char para geocódigo do cliente

//Estrutura para clientes
typedef struct Cliente {
    int nif; // número de identificação fiscal
    char nome[TAM_NOME]; // nome completo
    char endereco[TAM_END]; // endereço completo
    float saldo; // saldo disponível
    char localizacao[TAM_LOCCLIENTE]; // localização do cliente
    char geocodigo[TAM_GEOCLIENTE]; // geocódigo (what3words.com)
} Cliente;

//Estrutura para a lista de clientes
typedef struct ClienteLista { 
    Cliente cliente;
    struct ClienteLista *proxclientelista; // próximo cliente na lista ligada
} ClienteLista, *ClienteListaPtr;

//Declara a função para ler os clientes do arquivo CSV e outra função para ler do arquivo BIN
ClienteListaPtr lerClientesCSV(char* nomeArquivo);
ClienteListaPtr lerClientesBin(char* nomeArquivoBin);

//Declara a função para escrever os clientes no arquivo CSV
int escreverClientesCSV(ClienteListaPtr listaClientes, char* nomeArquivo);

//Cria um novo cliente e retorna um ponteiro para a estrutura criada
Cliente* novoCliente(int nif, char nome[], char endereco[], float saldo, char localizacao[], char geocodigo[]);

//Adiciona um novo cliente à lista de clientes
ClienteListaPtr adicionarCliente(ClienteListaPtr listaClientes, Cliente* cliente);

//Remove um cliente da lista de clientes com base no seu NIF
ClienteListaPtr removerCliente(ClienteListaPtr listaClientes, int nif);

//Altera os dados de um cliente existente com base no seu NIF
bool alterarCliente(ClienteListaPtr listaClientes, int nif, char nome[], char endereco[], float saldo, char localizacao[], char geocodigo[]);
bool alterarNomeCliente(ClienteListaPtr listaClientes, int nif, char nome[]);
bool alterarEnderecoCliente(ClienteListaPtr listaClientes, int nif, char endereco[]);
bool alterarSaldoCliente(ClienteListaPtr listaClientes, int nif, float saldo);
bool alterarLocalizacaoCliente(ClienteListaPtr listaClientes, int nif, char localizacao[]);
bool alterarGeocodigoCliente(ClienteListaPtr listaClientes, int nif, char geocodigo[]);

//Retorna um ponteiro para o cliente com o NIF especificado, ou NULL caso não exista
Cliente* pesquisarCliente(ClienteListaPtr listaClientes, int nif);

//Liberta a memória da lista dos clientes
bool libertarClientesLista(ClienteListaPtr lista);

//Guardar backup dados clientes
int guardarBackupClientes(ClienteListaPtr listaClientes);

//Lista todos os clientes em memória
void listarClientes(ClienteListaPtr listaClientes);
