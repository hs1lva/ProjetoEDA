/*****************************************************************//**
 * \file   fgrafos.c
 * \brief  Fun��es com utiliza��es de grafos
 * 
 * \author hugo2
 * \date   April 2023
 *********************************************************************/

#include "grafos.h"

#pragma warning(disable:4996) //n�o chatear com _s 

/**
@brief Cria um novo v�rtice para o grafo.
@param idVertice Identificador num�rico do v�rtice.
@param cidade Nome da cidade correspondente ao v�rtice.
@return Apontador para o novo v�rtice criado, ou NULL se n�o for poss�vel alocar mem�ria.
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
@brief Insere um novo v�rtice em ordem crescente no grafo.
@param grafo O apontador para o grafo.
@param novo O apontador para o novo v�rtice a ser inserido.
@return O apontador para o grafo atualizado.
*/
Vertice* inserirVertice(Vertice* grafo, Vertice* novo) {
    Vertice* anterior = NULL;
    Vertice* atual = grafo;

    while (atual != NULL && atual->idVertice < novo->idVertice) { // Posi��o para inserir o novo v�rtice
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
@param idVertice ID do v�rtice adjacente.
@param distancia Dist�ncia entre o v�rtice atual e o v�rtice adjacente.
@return Apontador para o novo n� adjacente criado.
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
@brief Insere um v�rtice adjacente numa lista de adjacentes de um v�rtice no grafo.
@param grafo Apontador para o grafo.
@param origem Identificador do v�rtice de origem.
@param novoAdjacente Apontador para o v�rtice adjacente a ser inserido.
@return Apontador para o grafo atualizado com o novo v�rtice adjacente inserido na lista de adjacentes da origem, ou NULL se a origem n�o for encontrada no grafo.
*/
Vertice* inserirAdjacente(Vertice* grafo, int origem, Adjacente* novoAdjacente) {

    Vertice* aux = grafo;
    while (aux && aux->idVertice != origem) { // Loop para encontrar origem no grafo
        aux = aux->proximo;
    }

    if (aux == NULL) {
        return NULL; // Origem n�o encontrada
    }

    novoAdjacente->proximo = aux->adjacentes; // Inserir o novo v�rtice adjacente na lista de adjacentes da origem
    aux->adjacentes = novoAdjacente;

    aux->numAdjacentes++; // Contador de v�rtices adjacentes da origem

    return grafo;
}

/**
@brief Imprime na tela o grafo representado pela lista de adjac�ncia.
@param grafo Apontador para o primeiro v�rtice do grafo.
@return void.
*/
void imprimirGrafo(Vertice* grafo) {
    Vertice* vertice = grafo;

    while (vertice) { // Loop nos v�rtices
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
@brief Cria um novo caminho com um v�rtice e dist�ncia.
@param idVertice ID do v�rtice do caminho.
@param distancia Dist�ncia do caminho.
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
@return Apontador para a nova fila criada ou NULL caso n�o seja poss�vel alocar mem�ria
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
@param idVertice ID do v�rtice a ser pesquisado.
@return Apontador para o v�rtice encontrado, ou NULL se n�o encontrado.
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
@brief Calcula a dist�ncia total percorrida num caminho
@param caminho Apontador para o primeiro n� de um caminho
@return float A dist�ncia total percorrida no caminho, ou INFINITY se o caminho for nulo (libraria math.h)
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
@return Apontador para a lista encadeada de v�rtices do caminho encontrado, ou NULL se n�o for encontrado.
*/
int pesquisarEmLargura(Vertice* grafo, int origem, int destino) {

    if (grafo == NULL) { // Grafo vazio ent�o NULL
        return NULL;
    }

    limparCamposGrafo(grafo);

    Vertice* verticeOrigem = pesquisarVertice(grafo, origem); // Pesquisar v�rtices de origem
    Vertice* verticeDestino = pesquisarVertice(grafo, destino); // Pesquisar v�rtices de destino

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
            Vertice* adjacente = pesquisarVertice(grafo, adjacenteAtual->idVertice);

            if (!adjacente->visitado) {
                
                adjacente->visitado = 1; // V�rtice adjacente como visitado
                inserirElemFinalFila(fila, adjacente); // Inserir v�rtice adjacente na fila

                // Armazenar dados no predecessor
                adjacente->predecessor = verticeAtual->idVertice;
                adjacente->distancia = verticeAtual->distancia + adjacenteAtual->distancia;

                if (adjacente->idVertice == destino) { // Parar se v�rtice destino encontrado
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

    Caminho* caminho = NULL;
    Vertice* atual = verticeDestino;
    while (atual != NULL) { // Loop para construir lista de v�rtices com predecessores e dist�ncias
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