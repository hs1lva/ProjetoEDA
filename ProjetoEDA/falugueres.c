/*****************************************************************//**
 * \file   falugueres.c
 * \brief  Funções para alugueres
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#include "meios.h"
#include "clientes.h"
#include "alugueres.h"

#pragma warning(disable:4996) //não chatear com _s 

/**
@brief Cria um novo aluguer com os dados fornecidos.
@param nifcliente O NIF do cliente que está a fazer o aluguer.
@param idmeiomobilidade O identificador do meio de mobilidade que está a ser alugado.
@return Uma estrutura do tipo Aluguer preenchida com os dados fornecidos.
*/
Aluguer novoAluguer(int nifcliente, int idmeiomobilidade) {
    static int totAluguer = 0; //Atribuição de ID's ao aluguer, estático para o primeiro ser sempre 0 e ir encrementando
    Aluguer aluguer;
    aluguer.nifcliente = nifcliente;
    aluguer.idmeio = idmeiomobilidade;
    aluguer.preco = 0; // inicialmente, o preço é zero
    aluguer.distancia = 0; // inicialmente, a distancia é zero
    time_t now = time(NULL);
    aluguer.data = now; // data atual
    aluguer.id=totAluguer;
    totAluguer++;
    return aluguer;
}


/**
@brief Insere um novo aluguer na lista de alugueres
@param listaClientes apontador para lista de clientes
@param listaMeiosMobilidad apontador para lista de meios de mobilidade
@param listaAlugueres apontador para a lista de alugueres
@param aluguer apontador para o aluguer a ser adicionado
@return int retorna 1 se o aluguer foi adicionado com sucesso, 0 caso contrário
*/
int adicionarAluguer(ClienteListaPtr listaClientes, MeiosMobilidadeListaPtr listaMeiosMobilidad, AluguerListaPtr listaAlugueres, Aluguer* aluguer, Vertice* grafo) {
    // Pesquisar cliente
    Cliente* cliente = pesquisarCliente(listaClientes, aluguer->nifcliente);
    // Verificar se o meio de mobilidade está disponível
    MeioMobilidade* meiomobilidade = pesquisarMeioMobilidade(listaMeiosMobilidad, aluguer->idmeio);
    if (!verificarEstadoMeioMobilidade(meiomobilidade)) {
        perror("Meio de mobilidade nao disponivel para aluguer.\n");
        return 0;
    }
    // Perguntar ao utilizador onde é que terminou a viagem para efetuar o custo da mesma
    int idlocaltermino;
    printf("Onde estás a terminar o aluguer? (ID local cidade) ");
    idlocaltermino = verificarInt();
    // Verificar distancia entre a localização do cliente (origem) e o destino
    float distanciatotal = pesquisarEmLargura(&grafo, cliente->localizacao, idlocaltermino);
    // Calcular o custo do aluguer
    float custofinal = calcularCustoAluguer(meiomobilidade, meiomobilidade->custo, distanciatotal);
    // Verificar se o cliente tem saldo suficiente para realizar o aluguer
    if (!verificarSaldoCliente(cliente, custofinal)) {
        perror("Cliente nao tem saldo suficiente para realizar este aluguer.\n");
        return 0;
    }
    aluguer->preco = custofinal;
    aluguer->distancia = distanciatotal;
    // Inserir o custo do aluguer no saldo do cliente
    cliente->saldo -= custofinal;
    // Adicionar o aluguer à lista de alug(ueres
    inserirAluguerLista(listaAlugueres, *aluguer);
    // Marcar o meio de mobilidade como indisponível
    alterarAlugadoMeioMobilidade(listaMeiosMobilidad, meiomobilidade);
    // Atualizar localização do cliente para destino da viagem
    alterarLocalizacaoCliente(listaClientes, aluguer->nifcliente, idlocaltermino);
    return 1;
}


/**
@brief Insere um novo aluguer na lista de alugueres.
@param listaAlugueres Apontador para o ponteiro da lista de alugueres.
@param aluguer O aluguer a ser inserido na lista.
@return Retorna 1 se a operação foi bem sucedida e 0 caso contrário.
*/
int inserirAluguerLista(AluguerListaPtr* listaAlugueres, Aluguer aluguer) {
    // Cria um novo nó da lista de alugueres
    AluguerListaPtr novo_aluguer = (AluguerListaPtr)malloc(sizeof(AluguerLista));
    novo_aluguer->aluguer = aluguer;
    novo_aluguer->proxaluguer = NULL;
    // Se a lista estiver vazia, insere o novo aluguer como primeiro elemento
    if (*listaAlugueres == NULL) {
        *listaAlugueres = novo_aluguer;
    }
    // Caso contrário, insere o novo aluguer no final da lista
    else {
        AluguerListaPtr ultimo_aluguer = *listaAlugueres;
        while (ultimo_aluguer->proxaluguer != NULL) {
            ultimo_aluguer = ultimo_aluguer->proxaluguer;
        }
        ultimo_aluguer->proxaluguer = novo_aluguer;
    }
    return 1;
}


/**
@brief Verifica se o cliente tem saldo suficiente para realizar um aluguer
@param cliente apontador para o cliente
@param custofinal custo total do aluguer
@return int retorna 1 se o cliente tem saldo suficiente, 0 caso contrário
*/
int verificarSaldoCliente(Cliente* cliente, float custofinal) {
    float saldocliente = cliente->saldo;
    float clientetemsaldo = saldocliente - custofinal;
    if (clientetemsaldo >= 1.0) {
        return 1;
    }
    else {
        return 0;
    }
}


/**
@brief Realiza o cálculo do custo do aluguer com base na distância percorrida e na duração do aluguer
@param meiomobilidade apontador para o meio de mobilidade
@param custoporkm custo do aluguer por km
@param distancia distancia percorrida em metros
@return custo do aluguer
*/
float calcularCustoAluguer(MeioMobilidade* meiomobilidade, float custoporkm, float distancia) {
    custoporkm = meiomobilidade->custo;
    // Converter a distancia de metros para km
    float distanciakm = distancia / 1000.0;
    // Calcular o custo total do aluguer
    float custo_total = custoporkm * distanciakm;
    return custo_total;
}


/**
@brief Verifica se o meio de mobilidade está disponível para alugar e chama a função alterar o valor para 1 (alugado)
@param meiomobilidade apontador para o meio de mobilidade a verificar
@return int retorna 1 se o meio de mobilidade estiver disponível para alugar, 0 caso contrário
*/
int verificarEstadoMeioMobilidade(MeioMobilidade* meiomobilidade) {
    if (meiomobilidade->alugado == 0) {
        alterarAlugadoMeioMobilidade(meiomobilidade);
        return 1;
    }
    return 0;
}


/**
@brief Converte uma data em formato time_t para uma string formatada.
@param t A data a ser convertida.
@return A data formatada como uma string.
*/
char* timeToString(time_t t) {
    static char str[20];
    strftime(str, sizeof(str), "%Y-%m-%d %H:%M:%S", localtime(&t));
    return str;
}


/**
@brief Lista os alugueres da lista de alugueres
@param lista_alugueres apontador para a lista de alugueres
*/
void listarAlugueres(AluguerListaPtr lista_alugueres) {
    if (lista_alugueres == NULL) {
        printf("A lista de alugueres está vazia.\n");
        return;
    }
    printf("Lista de alugueres:\n");
    AluguerListaPtr p = lista_alugueres;
    while (p != NULL) {
        printf("ID do aluguer: %d\n", p->aluguer.id);
        printf("NIF do cliente: %d\n", p->aluguer.nifcliente);
        printf("ID do meio de mobilidade: %d\n", p->aluguer.idmeio);
        printf("Preço do aluguer: %.2f\n", p->aluguer.preco);
        printf("Distancia percorrida (metros): %f\n", p->aluguer.distancia);
        printf("Data do aluguer: %s\n", timeToString(p->aluguer.data));
        printf("\n");
        p = p->proxaluguer;
    }
}