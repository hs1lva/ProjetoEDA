/*****************************************************************//**
 * \file   fgrafos.c
 * \brief  Funções com utilizações de grafos
 * 
 * \author hugo2
 * \date   April 2023
 *********************************************************************/

#include "grafos.h"
#include "meios.h"

#pragma warning(disable:4996) //não chatear com _s 

/**
@brief Cria um novo vértice para o grafo.
@param idvertice Identificador numérico do vértice.
@param cidade Nome da cidade correspondente ao vértice.
@return Apontador para o novo vértice criado, ou NULL se não for possível alocar memória.
*/
Vertice* criarVertice(int idvertice, char cidade[]) {
	Vertice* vertice = (Vertice*)calloc(1, sizeof(Vertice));
	if (vertice == NULL) {
		return NULL;
	}

    vertice->idvertice = idvertice;
	strcpy(vertice->cidade, cidade);
    vertice->proximo = NULL;

	return vertice;
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

    while (atual != NULL && atual->idvertice < novo->idvertice) { // Posição para inserir o novo vértice
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
@param idvertice ID do vértice adjacente.
@param distancia Distância entre o vértice atual e o vértice adjacente.
@return Apontador para o novo nó adjacente criado.
*/
Adjacente* criarAdjacente(int idvertice, float distancia) {
    Adjacente* adjacente = (Adjacente*)malloc(sizeof(Adjacente));

    if (adjacente == NULL) {
        return NULL;
    }

    adjacente->idvertice = idvertice;
    adjacente->distancia = distancia;
    adjacente->proximo = NULL;

    return adjacente;
}

/**
@brief Insere um vértice adjacente numa lista de adjacentes de um vértice no grafo.
@param grafo Apontador para o grafo.
@param origem Identificador do vértice de origem.
@param novoadjacente Apontador para o vértice adjacente a ser inserido.
@return Apontador para o grafo atualizado com o novo vértice adjacente inserido na lista de adjacentes da origem, ou NULL se a origem não for encontrada no grafo.
*/
Vertice* inserirAdjacente(Vertice* grafo, int origem, Adjacente* novoadjacente) {

    Vertice* aux = grafo;
    while (aux && aux->idvertice != origem) { // Loop para encontrar origem no grafo
        aux = aux->proximo;
    }

    if (aux == NULL) {
        return NULL; // Origem não encontrada
    }

    novoadjacente->proximo = aux->adjacentes; // Inserir o novo vértice adjacente na lista de adjacentes da origem
    aux->adjacentes = novoadjacente;

    aux->numadjacentes++; // Contador de vértices adjacentes da origem

    return grafo;
}


/**
@brief Cria uma nova fila vazia
@return Apontador para a nova fila criada ou NULL caso não seja possível alocar memória
*/
Fila* criarFila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    if (!fila) {
        return NULL;
    }
    fila->proximo = NULL;
    fila->anterior = NULL;
    return fila;
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
@param idvertice ID do vértice a ser pesquisado.
@return Apontador para o vértice encontrado, ou NULL se não encontrado.
*/
Vertice* pesquisarVerticePorID(Vertice* grafo, int idvertice) {
    
    Vertice* aux = grafo;

    while (aux) {
        if (aux->idvertice == idvertice) {
            return aux;
        }
        aux = aux->proximo;
    }
    return NULL;
}

/**
@brief Pesquisa um vértice no grafo pelo nome da cidade.
@param grafo Apontador para o primeiro vértice do grafo.
@param cidade Nome da cidade do vértice a ser pesquisado.
@return Apontador para o vértice encontrado, ou NULL se não encontrado.
*/
Vertice* pesquisarVerticePorNomeCidade(Vertice* grafo, const char* cidade) {

    Vertice* aux = grafo;

    while (aux) {
        if (strcmp(aux->cidade, cidade) == 0) {
            return aux;
        }
        aux = aux->proximo;
    }
    return NULL;
}

/*
@brief Lê um inteiro do input do user e verifica se é válido.  
@return Retorna o inteiro lido e validado.
*/
int verificarInt() {
    int resultado = 0;
    // tamanho maximo do buffer inicializado a 0
    char buffer[1024] = { 0 };

    // enquanto o utilizador não inserir um inteiro válido
    while (1) {
        fgets(buffer, 1024, stdin);
        if (sscanf(buffer, "%d", &resultado) == 1) {
            return resultado;
        }
        else if (buffer[0] != '\n') {
            printf("Insere um numero inteiro: ");
        }
    }
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
@return distancia Apontador para distancia mais curta entre a origem e o destino.
*/
int pesquisarEmLargura(Vertice* grafo, int origem, int destino) { // Grafo não ponderado.. bruteforce, ve qual caminho mais perto, encontra, posiciona-se nele e faz nova pesquisa etc etc...

    if (grafo == NULL) { // Grafo vazio então NULL
        return NULL;
    }

    limparCamposGrafo(grafo); // limpar vertices visitados, predecessor etc..

    Vertice* verticeOrigem = pesquisarVerticePorID(grafo, origem); // Pesquisar vértices de origem
    Vertice* verticeDestino = pesquisarVerticePorID(grafo, destino); // Pesquisar vértices de destino

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
            Vertice* adjacente = pesquisarVerticePorID(grafo, adjacenteAtual->idvertice);

            if (!adjacente->visitado) {
                
                adjacente->visitado = 1; // Vértice adjacente como visitado
                inserirElemFinalFila(fila, adjacente); // Inserir vértice adjacente na fila

                // Armazenar dados no predecessor
                adjacente->predecessor = verticeAtual->idvertice;
                adjacente->distancia = verticeAtual->distancia + adjacenteAtual->distancia;

                if (adjacente->idvertice == destino) { // Parar se vértice destino encontrado
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

    float distancia = verticeDestino->distancia;
    return distancia;
}

/**
@brief Calcula a distância entre dois vértices no grafo
@param origem apontador para o vértice de origem
@param destino apontador para o vértice de destino
@return float distância entre os vértices
*/
float calcularDistanciaEntreVertices(Vertice* origem, Vertice* destino) {
    Adjacente* adjacente = origem->adjacentes;
    while (adjacente != NULL) {
        if (adjacente->idvertice == destino->idvertice) {
            return adjacente->distancia;
        }
        adjacente = adjacente->proximo;
    }
    // caso os vértices não estejam diretamente ligados
    return INFINITY;
}
