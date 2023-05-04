/*****************************************************************//**
 * \file   fgrafos.c
 * \brief  Funções com utilizações de grafos
 * 
 * \author hugo2
 * \date   April 2023
 *********************************************************************/

#include "grafos.h"

#pragma warning(disable:4996) //não chatear com _s 

/**
@brief Cria um novo vértice para o grafo.
@param idVertice Identificador numérico do vértice.
@param cidade Nome da cidade correspondente ao vértice.
@return Apontador para o novo vértice criado, ou NULL se não for possível alocar memória.
*/
Vertice* criarVertice(int idVertice, char cidade[]) {
	Vertice* novo = (Vertice*)calloc(1, sizeof(Vertice));
	if (novo == NULL) {
		return NULL;
	}

	novo->idVertice = idVertice;
	strcpy(novo->cidade, cidade);
	novo->proximo = NULL;

	return novo;
}

/**
@brief Insere um novo vértice em ordem crescente no grafo.
@param grafo O apontador para o grafo.
@param novo O apontador para o novo vértice a ser inserido.
@return O apontador para o grafo atualizado.
*/
Vertice* inserirVertice(Vertice* grafo, Vertice* novo) {
    Vertice* anterior = NULL;
    Vertice* atual = grafo;

    while (atual != NULL && atual->idVertice < novo->idVertice) { // Posição para inserir o novo vértice
        anterior = atual;
        atual = atual->proximo;
    }

    if (anterior == NULL) { // Insere o novo vértice na posição
        novo->proximo = grafo;
        grafo = novo;
    }
    else {
        novo->proximo = anterior->proximo;
        anterior->proximo = novo;
    }

    return grafo;
}

/*
@brief Cria um novo nó adjacente.
@param idVertice ID do vértice adjacente.
@param distancia Distância entre o vértice atual e o vértice adjacente.
@return Apontador para o novo nó adjacente criado.
*/
Adjacente* criarAdjacente(int idVertice, float distancia) {
    Adjacente* novo = (Adjacente*)malloc(sizeof(Adjacente));

    if (novo == NULL) {
        return NULL;
    }

    novo->idVertice = idVertice;
    novo->distancia = distancia;
    novo->proximo = NULL;

    return novo;
}

/**
@brief Insere um vértice adjacente numa lista de adjacentes de um vértice no grafo.
@param grafo Apontador para o grafo.
@param origem Identificador do vértice de origem.
@param novoAdjacente Apontador para o vértice adjacente a ser inserido.
@return Apontador para o grafo atualizado com o novo vértice adjacente inserido na lista de adjacentes da origem, ou NULL se a origem não for encontrada no grafo.
*/
Vertice* inserirAdjacente(Vertice* grafo, int origem, Adjacente* novoAdjacente) {

    Vertice* aux = grafo;
    while (aux && aux->idVertice != origem) { // Loop para encontrar origem no grafo
        aux = aux->proximo;
    }

    if (aux == NULL) {
        return NULL; // Origem não encontrada
    }

    novoAdjacente->proximo = aux->adjacentes; // Inserir o novo vértice adjacente na lista de adjacentes da origem
    aux->adjacentes = novoAdjacente;

    aux->numAdjacentes++; // Contador de vértices adjacentes da origem

    return grafo;
}

/**
@brief Imprime na tela o grafo representado pela lista de adjacência.
@param grafo Apontador para o primeiro vértice do grafo.
@return void.
*/
void imprimirGrafo(Vertice* grafo) {
    Vertice* vertice = grafo;

    while (vertice) { // Loop nos vértices
        printf("ID: %d\tCidade: %s\n", vertice->idVertice, vertice->cidade);

        Adjacente* adjacent = vertice->adjacentes;

        while (adjacent) { // Loop nas adjacentes
            printf("  -> ID: %d\tDistancia: %.2f\n", adjacent->idVertice, adjacent->distancia);
            adjacent = adjacent->proximo;
        }

        printf("\n");
        vertice = vertice->proximo;
    }
}

/**
@brief Cria um novo caminho com um vértice e distância.
@param idVertice ID do vértice do caminho.
@param distancia Distância do caminho.
@return Apontador para o novo caminho criado.
*/
Caminho* criarCaminho(int idVertice, float distancia) {
    Caminho* novoCaminho = (Caminho*)malloc(sizeof(Caminho));
    novoCaminho->idVertice = idVertice;
    novoCaminho->distancia = distancia;
    novoCaminho->proximo = NULL;
    return novoCaminho;
}

/**
@brief Cria uma nova fila vazia
@return Apontador para a nova fila criada ou NULL caso não seja possível alocar memória
*/
Fila* criarFila() {
    Fila* novaFila = (Fila*)malloc(sizeof(Fila));
    if (!novaFila) {
        return NULL;
    }
    novaFila->proximo = NULL;
    novaFila->anterior = NULL;
    return novaFila;
}


/**
@brief Insere um elemento no final da fila.
@param fila Apontador para a fila.
@param vertice Apontador para o vértice a ser inserido.
@return int Retorna 1 se a operação for bem-sucedida e 0 se a alocação de memória falhar.
*/
int inserirElemFinalFila(Fila* fila, Vertice* vertice) {
    NodeFila* novoNo = (NodeFila*)malloc(sizeof(NodeFila));
    if (novoNo == NULL) {
        return 0;
    }
    novoNo->vertice = vertice;
    novoNo->proximo = NULL;

    if (fila->anterior == NULL) {
        fila->proximo = novoNo;
        fila->anterior = novoNo;
    }
    else {
        fila->anterior->proximo = novoNo;
        fila->anterior = novoNo;
    }

    return 1;
}

/**
@brief Remove o primeiro elemento da fila e retorna o vértice correspondente.
@param fila A fila de vértices a ser manipulada.
@return O vértice removido da fila, ou NULL se a fila estiver vazia.
*/
Vertice* removerElemFila(Fila* fila) {
    if (fila->proximo == NULL) {
        return NULL;
    }

    NodeFila* noASerRemovido = fila->proximo;
    Vertice* verticeRemovido = noASerRemovido->vertice;

    fila->proximo = noASerRemovido->proximo;

    if (fila->proximo == NULL) {
        fila->anterior = NULL;
    }

    free(noASerRemovido);
    return verticeRemovido;
}

/**
@brief Verifica se a fila está vazia.
@param fila Apontador para a fila a ser verificada.
@return 1 se a fila estiver vazia, 0 caso contrário.
*/
int filaVazia(Fila* fila) {
    if (fila->proximo == NULL) {
        return 1;
    }
    return 0;
}

/**
@brief Pesquisa um vértice no grafo pelo ID.
@param grafo Apontador para o primeiro vértice do grafo.
@param idVertice ID do vértice a ser pesquisado.
@return Apontador para o vértice encontrado, ou NULL se não encontrado.
*/
Vertice* pesquisarVertice(Vertice* grafo, int idVertice) {
    
    Vertice* aux = grafo;

    while (aux) {
        if (aux->idVertice == idVertice) {
            return aux;
        }
        aux = aux->proximo;
    }
    return NULL;
}

/**
@brief Calcula a distância total percorrida num caminho
@param caminho Apontador para o primeiro nó de um caminho
@return float A distância total percorrida no caminho, ou INFINITY se o caminho for nulo (libraria math.h)
*/
float distanciaCaminho(Caminho* caminho) {
    if (caminho == NULL) {
        return INFINITY;
    }

    float distancia = 0;
    while (caminho != NULL) {
        distancia = caminho->distancia;
        caminho = caminho->proximo;
    }

    return distancia;
}

/**
@brief Limpa os campos "visitado", "predecessor" e "distância" de todos os vértices do grafo
@param grafo Apontador para o primeiro vértice do grafo
@return int 1 se a operação for bem-sucedida, 0 caso contrário
*/
int limparCamposGrafo(Vertice* grafo) {
    if (grafo == NULL) {
        return 0;
    }
    Vertice* verticeAux = grafo;

    while (verticeAux != NULL) {
        verticeAux->visitado = 0;
        verticeAux->predecessor = -1;
        verticeAux->distancia = 0;
        verticeAux = verticeAux->proximo;
    }

    return 1;
}

/**
@brief Realiza uma pesquisa em largura num grafo para encontrar um caminho entre dois vértices.
@param grafo Apontador para o primeiro vértice do grafo.
@param origem Identificador do vértice de origem.
@param destino Identificador do vértice de destino.
@return Apontador para a lista encadeada de vértices do caminho encontrado, ou NULL se não for encontrado.
*/
int pesquisarEmLargura(Vertice* grafo, int origem, int destino) {

    if (grafo == NULL) { // Grafo vazio então NULL
        return NULL;
    }

    limparCamposGrafo(grafo);

    Vertice* verticeOrigem = pesquisarVertice(grafo, origem); // Pesquisar vértices de origem
    Vertice* verticeDestino = pesquisarVertice(grafo, destino); // Pesquisar vértices de destino

    if (verticeOrigem == NULL || verticeDestino == NULL) { // NULL se esses vértices não existem
        return NULL;
    }

    Fila* fila = criarFila();

    inserirElemFinalFila(fila, verticeOrigem); // Inserir vértice origem na fila
    verticeOrigem->visitado = 1; // Vértice origem como visitado
    verticeOrigem->distancia = 0;
    verticeOrigem->predecessor = -1;
    int encontrouDestino = 0;
    
    while (!filaVazia(fila) && !encontrouDestino) { // Loop para vértices na fila
        Vertice* verticeAtual = removerElemFila(fila);
        Adjacente* adjacenteAtual = verticeAtual->adjacentes;

        while (adjacenteAtual) { // Loop para todos os vértices adjacentes do vértice atual
            Vertice* adjacente = pesquisarVertice(grafo, adjacenteAtual->idVertice);

            if (!adjacente->visitado) {
                
                adjacente->visitado = 1; // Vértice adjacente como visitado
                inserirElemFinalFila(fila, adjacente); // Inserir vértice adjacente na fila

                // Armazenar dados no predecessor
                adjacente->predecessor = verticeAtual->idVertice;
                adjacente->distancia = verticeAtual->distancia + adjacenteAtual->distancia;

                if (adjacente->idVertice == destino) { // Parar se vértice destino encontrado
                    encontrouDestino = 1;
                    break;
                }
            }
            adjacenteAtual = adjacenteAtual->proximo;
        }
    }

    if (verticeDestino->predecessor == -1) { // NULL se caminho do destino não encontrado
        return NULL;
    }

    Caminho* caminho = NULL;
    Vertice* atual = verticeDestino;
    while (atual != NULL) { // Loop para construir lista de vértices com predecessores e distâncias
        Caminho* novoCaminho = criarCaminho(atual->idVertice, atual->distancia);
        novoCaminho->proximo = caminho;
        caminho = novoCaminho;

        if (atual->predecessor == -1) {
            atual = NULL;
        }
        else {
            atual = pesquisarVertice(grafo, atual->predecessor);
        }
    }

    return caminho;
}