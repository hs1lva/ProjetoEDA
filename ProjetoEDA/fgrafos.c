/*****************************************************************//**
 * \file   fgrafos.c
 * \brief  Fun��es com utiliza��es de grafos
 * 
 * \author hugo2
 * \date   April 2023
 *********************************************************************/

#include "grafos.h"
#include "meios.h"

#pragma warning(disable:4996) //n�o chatear com _s 

/**
@brief Cria um novo v�rtice para o grafo.
@param idvertice Identificador num�rico do v�rtice.
@param cidade Nome da cidade correspondente ao v�rtice.
@return Apontador para o novo v�rtice criado, ou NULL se n�o for poss�vel alocar mem�ria.
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
@brief Insere um novo v�rtice em ordem crescente no grafo.
@param grafo O apontador para o grafo.
@param novo O apontador para o novo v�rtice a ser inserido.
@return O apontador para o grafo atualizado.
*/
Vertice* inserirVertice(Vertice* grafo, Vertice* novo) {
    Vertice* anterior = NULL;
    Vertice* atual = grafo;

    while (atual != NULL && atual->idvertice < novo->idvertice) { // Posi��o para inserir o novo v�rtice
        anterior = atual;
        atual = atual->proximo;
    }

    if (anterior == NULL) { // Insere o novo v�rtice na posi��o
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
@brief Cria um novo n� adjacente.
@param idvertice ID do v�rtice adjacente.
@param distancia Dist�ncia entre o v�rtice atual e o v�rtice adjacente.
@return Apontador para o novo n� adjacente criado.
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
@brief Insere um v�rtice adjacente numa lista de adjacentes de um v�rtice no grafo.
@param grafo Apontador para o grafo.
@param origem Identificador do v�rtice de origem.
@param novoadjacente Apontador para o v�rtice adjacente a ser inserido.
@return Apontador para o grafo atualizado com o novo v�rtice adjacente inserido na lista de adjacentes da origem, ou NULL se a origem n�o for encontrada no grafo.
*/
Vertice* inserirAdjacente(Vertice* grafo, int origem, Adjacente* novoadjacente) {

    Vertice* aux = grafo;
    while (aux && aux->idvertice != origem) { // Loop para encontrar origem no grafo
        aux = aux->proximo;
    }

    if (aux == NULL) {
        return NULL; // Origem n�o encontrada
    }

    novoadjacente->proximo = aux->adjacentes; // Inserir o novo v�rtice adjacente na lista de adjacentes da origem
    aux->adjacentes = novoadjacente;

    aux->numadjacentes++; // Contador de v�rtices adjacentes da origem

    return grafo;
}


/**
@brief Cria uma nova fila vazia
@return Apontador para a nova fila criada ou NULL caso n�o seja poss�vel alocar mem�ria
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
@param vertice Apontador para o v�rtice a ser inserido.
@return int Retorna 1 se a opera��o for bem-sucedida e 0 se a aloca��o de mem�ria falhar.
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
@brief Remove o primeiro elemento da fila e retorna o v�rtice correspondente.
@param fila A fila de v�rtices a ser manipulada.
@return O v�rtice removido da fila, ou NULL se a fila estiver vazia.
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
@brief Verifica se a fila est� vazia.
@param fila Apontador para a fila a ser verificada.
@return 1 se a fila estiver vazia, 0 caso contr�rio.
*/
int filaVazia(Fila* fila) {
    if (fila->proximo == NULL) {
        return 1;
    }
    return 0;
}

/**
@brief Pesquisa um v�rtice no grafo pelo ID.
@param grafo Apontador para o primeiro v�rtice do grafo.
@param idvertice ID do v�rtice a ser pesquisado.
@return Apontador para o v�rtice encontrado, ou NULL se n�o encontrado.
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
@brief Pesquisa um v�rtice no grafo pelo nome da cidade.
@param grafo Apontador para o primeiro v�rtice do grafo.
@param cidade Nome da cidade do v�rtice a ser pesquisado.
@return Apontador para o v�rtice encontrado, ou NULL se n�o encontrado.
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
@brief L� um inteiro do input do user e verifica se � v�lido.  
@return Retorna o inteiro lido e validado.
*/
int verificarInt() {
    int resultado = 0;
    // tamanho maximo do buffer inicializado a 0
    char buffer[1024] = { 0 };

    // enquanto o utilizador n�o inserir um inteiro v�lido
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
@brief Limpa os campos "visitado", "predecessor" e "dist�ncia" de todos os v�rtices do grafo
@param grafo Apontador para o primeiro v�rtice do grafo
@return int 1 se a opera��o for bem-sucedida, 0 caso contr�rio
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
@brief Realiza uma pesquisa em largura num grafo para encontrar um caminho entre dois v�rtices.
@param grafo Apontador para o primeiro v�rtice do grafo.
@param origem Identificador do v�rtice de origem.
@param destino Identificador do v�rtice de destino.
@return distancia Apontador para distancia mais curta entre a origem e o destino.
*/
int pesquisarEmLargura(Vertice* grafo, int origem, int destino) { // Grafo n�o ponderado.. bruteforce, ve qual caminho mais perto, encontra, posiciona-se nele e faz nova pesquisa etc etc...

    if (grafo == NULL) { // Grafo vazio ent�o NULL
        return NULL;
    }

    limparCamposGrafo(grafo); // limpar vertices visitados, predecessor etc..

    Vertice* verticeOrigem = pesquisarVerticePorID(grafo, origem); // Pesquisar v�rtices de origem
    Vertice* verticeDestino = pesquisarVerticePorID(grafo, destino); // Pesquisar v�rtices de destino

    if (verticeOrigem == NULL || verticeDestino == NULL) { // NULL se esses v�rtices n�o existem
        return NULL;
    }

    Fila* fila = criarFila();

    inserirElemFinalFila(fila, verticeOrigem); // Inserir v�rtice origem na fila
    verticeOrigem->visitado = 1; // V�rtice origem como visitado
    verticeOrigem->distancia = 0;
    verticeOrigem->predecessor = -1;
    int encontrouDestino = 0;
    
    while (!filaVazia(fila) && !encontrouDestino) { // Loop para v�rtices na fila
        Vertice* verticeAtual = removerElemFila(fila);
        Adjacente* adjacenteAtual = verticeAtual->adjacentes;

        while (adjacenteAtual) { // Loop para todos os v�rtices adjacentes do v�rtice atual
            Vertice* adjacente = pesquisarVerticePorID(grafo, adjacenteAtual->idvertice);

            if (!adjacente->visitado) {
                
                adjacente->visitado = 1; // V�rtice adjacente como visitado
                inserirElemFinalFila(fila, adjacente); // Inserir v�rtice adjacente na fila

                // Armazenar dados no predecessor
                adjacente->predecessor = verticeAtual->idvertice;
                adjacente->distancia = verticeAtual->distancia + adjacenteAtual->distancia;

                if (adjacente->idvertice == destino) { // Parar se v�rtice destino encontrado
                    encontrouDestino = 1;
                    break;
                }
            }
            adjacenteAtual = adjacenteAtual->proximo;
        }
    }

    if (verticeDestino->predecessor == -1) { // NULL se caminho do destino n�o encontrado
        return NULL;
    }

    float distancia = verticeDestino->distancia;
    return distancia;
}

/**
@brief Calcula a dist�ncia entre dois v�rtices no grafo
@param origem apontador para o v�rtice de origem
@param destino apontador para o v�rtice de destino
@return float dist�ncia entre os v�rtices
*/
float calcularDistanciaEntreVertices(Vertice* origem, Vertice* destino) {
    Adjacente* adjacente = origem->adjacentes;
    while (adjacente != NULL) {
        if (adjacente->idvertice == destino->idvertice) {
            return adjacente->distancia;
        }
        adjacente = adjacente->proximo;
    }
    // caso os v�rtices n�o estejam diretamente ligados
    return INFINITY;
}
