/*****************************************************************//**
 * \file   ficheiros.c
 * \brief  Funções para leitura/armazenamento de ficheiros externos
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#include "clientes.h"
#include "meios.h"
#include "alugueres.h"
#include "grafos.h"

#define MAX_LINHA_CLIENTES_CSV 200 //Definir tamanho char linha importar clientes em CSV
#define MAX_LINHA_MEIOS_CSV 200 //Definir tamanho char linha importar meios de mobilidade em CSV
#define MAX_LINHA_GRAFO_CSV 200

#pragma warning(disable:4996) //não chatear com _s 

#pragma region Funções para ficheiros de texto dos clientes e meios (.csv)

 //------------------------------CLIENTES------------------------------------------------

 /**
 @brief Lê um arquivo CSV com dados de clientes e cria uma lista de clientes
 @param nomeArquivo nome do arquivo CSV a ser lido
 @return ClienteListaPtr apontador para o início da lista de clientes criada a partir do arquivo
 */
ClienteListaPtr lerClientesCSV(char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo %s\n", nomeArquivo);
        return NULL;
    }
    ClienteListaPtr inicioLista = NULL;
    char linha[MAX_LINHA_CLIENTES_CSV];
    while (fgets(linha, MAX_LINHA_CLIENTES_CSV, arquivo)) {
        Cliente cliente;
        int numCampos = sscanf(linha, "%d,%[^,],%[^,],%f,%[^,],%[^,]", &cliente.nif, cliente.nome, cliente.endereco, &cliente.saldo, cliente.localizacao, cliente.geocodigo);
        if (numCampos != 6) {
            perror("Erro ao ler linha do arquivo CSV\n");
            continue;
        }
        // Utiliza a função adicionarCliente para adicionar um novo cliente na lista
        ClienteListaPtr novoNo = adicionarCliente(inicioLista, &cliente);
        if (novoNo == NULL) {
            perror("Erro ao adicionar cliente na lista\n");
            continue;
        }
        inicioLista = novoNo;
    }
    fclose(arquivo);
    return inicioLista;
}


/**
@brief Escreve a lista de clientes em um arquivo CSV
@param listaClientes Apontador para o início da lista de clientes
@param nomeArquivo Nome do arquivo a ser escrito
@return Retorna 1 em caso de sucesso e 0 em caso de falha ao abrir o arquivo
*/
int escreverClientesCSV(ClienteListaPtr listaClientes, char* nomeArquivo) { //Esta função poderá não ser necessária para escrever no ficheiro csv.
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        return 0; // falha ao abrir arquivo
    }
    ClienteListaPtr atual = listaClientes;
    while (atual != NULL) {
        fprintf(arquivo, "%d,%s,%s,%.2f,%s,%s\n", atual->cliente.nif, atual->cliente.nome, atual->cliente.endereco, atual->cliente.saldo, atual->cliente.localizacao, atual->cliente.geocodigo);
        atual = atual->proxclientelista;
    }
    fclose(arquivo);
    return 1; // sucesso
}


//------------------------------MEIOS DE MOBILIDADE------------------------------------------------

/**
@brief Lê os dados dos meios de mobilidade de um arquivo CSV e armazena em uma lista encadeada.
@param nomeArquivo O nome do arquivo CSV contendo os dados dos meios de mobilidade.
@return Um apontador para a lista encadeada contendo os meios de mobilidade lidos do arquivo. Retorna NULL em caso de falha ao abrir o arquivo.
*/
MeiosMobilidadeListaPtr lerMeiosMobilidadeCSV(char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo %s\n", nomeArquivo);
        return NULL;
    }
    MeiosMobilidadeListaPtr inicioLista = NULL;
    char linha[MAX_LINHA_MEIOS_CSV];
    while (fgets(linha, MAX_LINHA_MEIOS_CSV, arquivo)) {
        MeioMobilidade meioMobilidade;
        int numCampos = sscanf(linha, "%d,%[^,],%f,%f,%[^,],%[^,], %d", &meioMobilidade.id, meioMobilidade.tipo, &meioMobilidade.autonomia, &meioMobilidade.custo, meioMobilidade.localizacao, meioMobilidade.geocodigo, &meioMobilidade.alugado);
        if (numCampos != 7) {
            perror("Erro ao ler linha do arquivo CSV\n");
            continue;
        }
        MeiosMobilidadeListaPtr novoNo = adicionarMeioMobilidade(inicioLista, &meioMobilidade);
        if (novoNo == inicioLista) {
            perror("Erro ao adicionar novo meio de mobilidade à lista\n");
            continue;
        }
        inicioLista = novoNo;
    }
    fclose(arquivo);
    return inicioLista;
}


/**
@brief Escreve os dados dos meios de mobilidade em um arquivo CSV.
@param listaMobilidade apontador para o inicio da lista de meios de mobilidade
@param nomeArquivo nome do arquivo CSV onde os dados serão escritos
@return 1 se os dados foram escritos com sucesso, 0 caso contrário
*/
int escreverMeios(MeiosMobilidadeListaPtr listaMobilidade, char* nomeArquivo) { //Esta função poderá não ser necessária para escrever no ficheiro csv.
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        return 0; // falha ao abrir arquivo
    }
    MeiosMobilidadeListaPtr atual = listaMobilidade;
    while (atual != NULL) {
        fprintf(arquivo, "%d,%s,%.2f,%.2f,%s,%s,%d\n", atual->meioMobilidade.id, atual->meioMobilidade.tipo, atual->meioMobilidade.autonomia, atual->meioMobilidade.custo, atual->meioMobilidade.localizacao, atual->meioMobilidade.geocodigo, atual->meioMobilidade.alugado);
        atual = atual->proxmeiomobilidadelista;
    }
    fclose(arquivo);
    return 1; // sucesso
}
#pragma endregion

#pragma region Funções para ficheiros binários clientes, meios e alugueres (.bin)

//------------------------------CLIENTES------------------------------------------------

/**
 @brief Lê um arquivo bin com dados de clientes e cria uma lista de clientes. Se o arquivo binário estiver vazio, lê a partir do CSV. Caso contrário, lê a partir do arquivo binário.
 @param nomeArquivoBin nome do arquivo binário a ser lido ou criado
 @return ClienteListaPtr apontador para o início da lista de clientes criada a partir do arquivo
 */
ClienteListaPtr lerClientesBin(char* nomeArquivoBin) {
    FILE* arquivoBin = fopen(nomeArquivoBin, "rb");
    if (arquivoBin == NULL) {
        perror("Erro ao abrir arquivo backup_clientes.bin\n");
        return NULL;
    }

    ClienteListaPtr inicioLista = NULL;
    Cliente cliente;

    // Verifica se o arquivo binário está vazio
    if (fread(&cliente, sizeof(Cliente), 1, arquivoBin) == 0) {
        fclose(arquivoBin);
        return lerClientesCSV("clientes.csv");
    }
    else {
        // Aloca espaço para o primeiro nó da lista
        inicioLista = (ClienteListaPtr)malloc(sizeof(ClienteLista));
        if (inicioLista == NULL) {
            perror("Erro ao alocar memória\n");
            fclose(arquivoBin);
            return NULL;
        }
        inicioLista->proxclientelista = NULL;
        inicioLista->cliente = cliente;
        // Arquivo binário não está vazio, lê a partir dele
        while (fread(&cliente, sizeof(Cliente), 1, arquivoBin) == 1) {
            // Utiliza a função adicionarCliente para adicionar um novo cliente na lista
            ClienteListaPtr novoNo = adicionarCliente(inicioLista, &cliente);
            if (novoNo == NULL) {
                perror("Erro ao adicionar cliente na lista\n");
                continue;
            }
            inicioLista = novoNo;
        }
        fclose(arquivoBin);
    }
    return inicioLista;
}


/**
@brief Função para guardar o backup dos dados dos clientes em um arquivo binário
@param listaClientes Apontador para a lista encadeada de clientes a serem salvos
@return int retorna 1 se a operação for bem-sucedida, 0 caso contrário
*/
int guardarBackupClientes(ClienteListaPtr listaClientes) {
    FILE* arquivo = fopen("backup_clientes.bin", "wb+"); // diferente do "wb" o "wb+" permite limpar o ficheiro antes de começar a escrever!!
    if (arquivo == NULL) {
        perror("ERRO: Nao foi possivel criar o arquivo de backup dos clientes\n");
        return 0;
    }

    ClienteListaPtr atual = listaClientes;
    while (atual != NULL) {
        Cliente* cliente = &(atual->cliente);
        fwrite(cliente, sizeof(Cliente), 1, arquivo);
        atual = atual->proxclientelista;
    }

    fclose(arquivo);
    return 1;
}


//------------------------------MEIOS DE MOBILIDADE------------------------------------------------

/**
 @brief Lê um arquivo bin com dados dos meios de mobilidade e cria uma lista de meios. Se o arquivo binário estiver vazio, lê a partir do CSV. Caso contrário, lê a partir do arquivo binário.
 @param nomeArquivoBin nome do arquivo binário a ser lido ou criado
 @return MeiosMobilidadeListaPtr apontador para o início da lista de meios criada a partir do arquivo
 */
MeiosMobilidadeListaPtr lerMeiosMobilidadeBin(char* nomeArquivoBin) {
    FILE* arquivoBin = fopen(nomeArquivoBin, "rb");
    if (arquivoBin == NULL) {
        perror("Erro ao abrir arquivo backup_meiosmobilidade.bin\n");
        return NULL;
    }

    MeiosMobilidadeListaPtr inicioLista = NULL;
    MeioMobilidade meio;

    // Verifica se o arquivo binário está vazio
    if (fread(&meio, sizeof(MeioMobilidade), 1, arquivoBin) == 0) {
        fclose(arquivoBin);
        return lerMeiosMobilidadeCSV("meiosmobilidade.csv");
    }
    else {
        // Aloca espaço para o primeiro nó da lista
        inicioLista = (MeiosMobilidadeListaPtr)malloc(sizeof(MeiosMobilidadeLista));
        if (inicioLista == NULL) {
            perror("Erro ao alocar memória\n");
            fclose(arquivoBin);
            return NULL;
        }
        inicioLista->proxmeiomobilidadelista = NULL;
        inicioLista->meioMobilidade = meio;
        // Arquivo binário não está vazio, lê a partir dele
        while (fread(&meio, sizeof(MeioMobilidade), 1, arquivoBin) == 1) {
            // Utiliza a função adicionarMeioMobilidade para adicionar um novo meio de mobilidade na lista
            MeiosMobilidadeListaPtr novoNo = adicionarMeioMobilidade(inicioLista, &meio);
            if (novoNo == NULL) {
                perror("Erro ao adicionar meio de mobilidade na lista\n");
                continue;
            }
            inicioLista = novoNo;
        }
        fclose(arquivoBin);
    }
    return inicioLista;
}


/**
@brief Função para criar um backup em formato binário dos meios de mobilidade
@param listaMeiosMobilidade Apontador para a lista encadeada dos meios de mobilidade
@return int Retorna 1 em caso de sucesso e 0 em caso de falha ao criar o arquivo de backup
*/
int guardarBackupMeiosMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade) {
    FILE* arquivo = fopen("backup_meiosmobilidade.bin", "wb+"); // diferente do "wb" o "wb+" permite limpar o ficheiro antes de começar a escrever!!
    if (arquivo == NULL) {
        perror("ERRO: Nao foi possivel criar o arquivo de backup dos meios de mobilidade\n");
        return 0;
    }

    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade;
    while (atual != NULL) {
        MeioMobilidade* meioMobilidade = &(atual->meioMobilidade);
        fwrite(meioMobilidade, sizeof(MeioMobilidade), 1, arquivo);
        atual = atual->proxmeiomobilidadelista;
    }

    fclose(arquivo);
    return 1;
}


//------------------------------ALUGUERES------------------------------------------------

/**
@brief Lê um arquivo binário com dados de alugueres e cria uma lista de alugueres
@param nomeArquivo nome do arquivo binário a ser lido
@return AluguerListaPtr apontador para o início da lista de alugueres criada a partir do arquivo
*/
AluguerListaPtr lerAlugueresBin(char* nomeArquivo) {
    int aux;

    FILE* arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo %s\n", nomeArquivo);
        return NULL;
    }
    AluguerListaPtr inicioLista = NULL;
    Aluguer aluguer;
    while (fread(&aluguer, sizeof(Aluguer), 1, arquivo)) {
        // Utiliza a função inserirAluguerLista para inserir o aluguer na lista
        aux = inserirAluguerLista(&inicioLista, aluguer);
        if (aux == 0) {
            perror("Erro ao inserir aluguer na lista\n");
            continue;
        }
        //inicioLista = novoNo;
    }
    fclose(arquivo);
    return inicioLista;
}


/**
Faz o backup de um aluguer no arquivo "backup_alugueres.bin".
@param aluguer um apontador para a estrutura Aluguer contendo as informações do aluguer para fazer backup
@return 1 se a operação de backup foi bem sucedida, 0 caso contrário
*/
int guardarBackupAlugueres(Aluguer aluguer) {
    FILE* ficheiro;
    ficheiro = fopen("backup_alugueres.bin", "ab"); // abre o arquivo em modo de escrita binária
    if (ficheiro == NULL) {
        perror("ERRO: Nao foi possivel abrir o arquivo de backup\n");
        return 0; // retorna 0 para indicar que a operação falhou
    }
    fwrite(&aluguer, sizeof(Aluguer), 1, ficheiro); // escreve as informações do aluguer no arquivo
    fclose(ficheiro); // fecha o arquivo
    return 1; // retorna 1 para indicar que a operação foi bem sucedida
}
#pragma endregion

#pragma region Funções para ficheiros grafos (.csv) e (.bin)

/**
@brief Lê um grafo no formato CSV e adiciona os vértices e arestas a uma lista de adjacência.
@param grafo Duplo apontador do primeiro vértice da lista de adjacência.
@param nomeFicheiro Nome do ficheiro que contém o grafo no formato CSV.
@return Número total de vértices do grafo.
*/
int lerGrafoCSV(Vertice** grafo, char* nomeFicheiro) {
    FILE* ficheiro;
    ficheiro = fopen(nomeFicheiro, "r");
    int totalVertices = 0;
    if (ficheiro == NULL) {
        perror("Erro ao abrir ficheiro grafos");
        return 0;
    }
    char linha[MAX_LINHA_GRAFO_CSV];
    fgets(linha, MAX_LINHA_GRAFO_CSV, ficheiro); // Passar cabeçalho
    while (fgets(linha, MAX_LINHA_GRAFO_CSV, ficheiro) != NULL) {
        int id, adj1, dist1, adj2, dist2, adj3, dist3;
        char title[256];
        sscanf(linha, "%d,%[^,],%d,%d,%d,%d,%d,%d", &id, title, &adj1, &dist1, &adj2, &dist2, &adj3, &dist3);

        Vertice* novoVertice = criarVertice(id, title);
        *grafo = inserirVertice(*grafo, novoVertice);

        Adjacente* novoAdjacente;

        if (adj1) {
            novoAdjacente = criarAdjacente(adj1, dist1);
            *grafo = inserirAdjacente(*grafo, id, novoAdjacente);
        }
        if (adj2) {
            novoAdjacente = criarAdjacente(adj2, dist2);
            *grafo = inserirAdjacente(*grafo, id, novoAdjacente);
        }
        if (adj3) {
            novoAdjacente = criarAdjacente(adj3, dist3);
            *grafo = inserirAdjacente(*grafo, id, novoAdjacente);
        }

        totalVertices++;
    }
    fclose(ficheiro);
    return totalVertices;
}

/**
@brief Função que lê os vértices de um backup binário e insere num grafo.
@param grafo Apontador para o grafo onde os vértices serão inseridos.
@return int Retorna 1 em caso de sucesso na leitura do backup ou 0 em caso contrário.
*/
int lerVerticesBin(Vertice** grafo) {
    FILE* file = fopen("backup_vertices.bin", "rb");
    if (file == NULL) {
        return 0;
    }

    int id;
    char cidade[TAM_CIDADE];
    while (fread(&id, sizeof(int), 1, file) == 1 && fread(cidade, sizeof(char), TAM_CIDADE, file) == TAM_CIDADE) {
        Vertice* novoVertice = criarVertice(id, cidade);
        *grafo = inserirVertice(*grafo, novoVertice);
    }

    fclose(file);
    return 1;
}

/**
@brief Função que lê os adjacentes de um backup binário e insere num grafo.
@param grafo Apontador para o grafo onde os adjacentes serão inseridos.
@return int Retorna 1 em caso de sucesso na leitura do backup ou 0 em caso contrário.
*/
int lerAdjacentesBin(Vertice* grafo) {
    FILE* file = fopen("backup_adjacentes.bin", "rb");
    if (file == NULL) {
        return 0;
    }

    int origem, destino;
    float distancia;
    while (fread(&origem, sizeof(int), 1, file) == 1 &&
        fread(&destino, sizeof(int), 1, file) == 1 &&
        fread(&distancia, sizeof(float), 1, file) == 1) {
        Adjacente* novoAdjacente = criarAdjacente(destino, distancia);
        grafo = inserirAdjacente(grafo, origem, novoAdjacente);
    }

    fclose(file);
    return 1;
}

/**
@brief Função que guarda os vértices de um grafo num backup binário.
@param grafo Apontador para o grafo que será salvo.
@return int Retorna 1 em caso de sucesso na escrita do backup ou 0 em caso contrário.
*/
int guardarBackupVertices(Vertice* grafo) {
    FILE* file = fopen("backup_vertices.bin", "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    Vertice* aux = grafo;
    while (aux != NULL) {
        fwrite(&aux->idVertice, sizeof(int), 1, file);
        fwrite(aux->cidade, sizeof(char), TAM_CIDADE, file);
        aux = aux->proximo;
    }

    fclose(file);
    return 1;
}

/**
@brief Função que guarda os adjacentes de um grafo num backup binário.
@param grafo Apontador para o grafo que será salvo.
@return int Retorna 1 em caso de sucesso na escrita do backup ou 0 em caso contrário.
*/
int guardarBackupAdjacentes(Vertice* grafo) {
    FILE* file = fopen("backup_adjacentes.bin", "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    Vertice* aux = grafo;
    while (aux != NULL) {
        Adjacente* adj = aux->adjacentes;
        while (adj != NULL) {
            fwrite(&aux->idVertice, sizeof(int), 1, file);
            fwrite(&adj->idVertice, sizeof(int), 1, file);
            fwrite(&adj->distancia, sizeof(float), 1, file);
            adj = adj->proximo;
        }
        aux = aux->proximo;
    }

    fclose(file);
    return 1;
}

#pragma endregion