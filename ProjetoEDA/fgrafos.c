/*****************************************************************//**
 * \file   fgrafos.c
 * \brief  Funções com utilizações de grafos
 * 
 * \author hugo2
 * \date   April 2023
 *********************************************************************/

#include "grafos.h"

#pragma warning(disable:4996) //não chatear com _s 

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

Caminho* criarCaminho(int idVertice, float distancia) {
    Caminho* novoCaminho = (Caminho*)malloc(sizeof(Caminho));
    novoCaminho->idVertice = idVertice;
    novoCaminho->distancia = distancia;
    novoCaminho->proximo = NULL;
    return novoCaminho;
}

// Cria uma nova fila vazia
Fila* criarFila() {
    Fila* novaFila = (Fila*)malloc(sizeof(Fila));
    if (!novaFila) {
        return NULL;
    }
    novaFila->proximo = NULL;
    novaFila->anterior = NULL;
    return novaFila;
}

// Adiciona um elemento ao final da fila
int inserirElemFinalFila(Fila* fila, Vertice* vertice) {
    NodeFila* novoNo = (NodeFila*)malloc(sizeof(NodeFila));
    if (novoNo == NULL) {
        return 0; // Retornar 0 se a alocação de memória falhar
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

    return 1; // Retornar 1 se a operação for bem-sucedida
}

// Remove o primeiro elemento da fila e retorna o vértice associado
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

// Verifica se a fila está vazia
int filaVazia(Fila* fila) {
    if (fila->proximo == NULL) {
        return 1;
    }
    return 0;
}

// Procura um vértice no grafo com base no ID.
Vertice* pesquisarVertice(Vertice* grafo, int idVertice) {
    // Cria um ponteiro auxiliar para percorrer a lista de vértices
    Vertice* aux = grafo;

    // Enquanto houver vértices na lista
    while (aux) {
        // Verifica se o ID do vértice atual corresponde ao ID procurado
        if (aux->idVertice == idVertice) {
            // Se encontrado, retorna o ponteiro para o vértice
            return aux;
        }
        // Avança para o próximo vértice na lista encadeada
        aux = aux->proximo;
    }

    // Se o vértice não for encontrado, retorna NULL
    return NULL;
}

// Vê o valor de distância do último node.
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

// Limpa os campos visitado, predecessor e distância de todos os vértices do grafo
void limparCamposGrafo(Vertice* grafo) {
    Vertice* verticeAux = grafo;

    while (verticeAux != NULL) {
        verticeAux->visitado = 0;
        verticeAux->predecessor = -1;
        verticeAux->distancia = 0;
        verticeAux = verticeAux->proximo;
    }
}

// Realiza uma pesquisa em largura no grafo para encontrar o caminho mais curto entre dois vértices
int pesquisarEmLargura(Vertice* grafo, int origem, int destino) {
    // Retorna NULL se o grafo estiver vazio
    if (grafo == NULL) {
        return NULL;
    }

    // Limpar o campo visitado de todos os vértices
    limparCamposGrafo(grafo);

    // Encontrar os vértices de origem e destino usando ProcuraVertice
    Vertice* verticeOrigem = pesquisarVertice(grafo, origem);
    Vertice* verticeDestino = pesquisarVertice(grafo, destino);

    // Retorna NULL se não encontrar os vértices de origem ou destino
    if (verticeOrigem == NULL || verticeDestino == NULL) {
        return NULL;
    }

    // Inicializar a fila vazia
    Fila* fila = criarFila();

    // Adicionar o vértice de origem à fila e marcá-lo como visitado
    inserirElemFinalFila(fila, verticeOrigem);
    verticeOrigem->visitado = 1;
    verticeOrigem->distancia = 0;
    verticeOrigem->predecessor = -1;
    int encontrouDestino = 0;
    // Processar vértices na fila até que esteja vazia
    while (!filaVazia(fila) && !encontrouDestino) {
        Vertice* verticeAtual = removerElemFila(fila);
        Adjacente* adjacenteAtual = verticeAtual->adjacentes;

        // Verificar todos os vértices adjacentes ao vértice atual
        while (adjacenteAtual) {
            Vertice* adjacente = pesquisarVertice(grafo, adjacenteAtual->idVertice);

            if (!adjacente->visitado) {
                // Marcar vértice adjacente como visitado e adicioná-lo à fila
                adjacente->visitado = 1;
                inserirElemFinalFila(fila, adjacente);

                // Armazene o predecessor e a distância para o vértice adjacente
                adjacente->predecessor = verticeAtual->idVertice;
                adjacente->distancia = verticeAtual->distancia + adjacenteAtual->distancia;
                // Se encontrarmos o vértice de destino, podemos parar de procurar
                if (adjacente->idVertice == destino) {
                    encontrouDestino = 1;
                    break;
                }
            }
            adjacenteAtual = adjacenteAtual->proximo;
        }
    }

    // Se não encontrarmos um caminho para o destino, retorna NULL
    if (verticeDestino->predecessor == -1) {
        return NULL;
    }

    // construir a lista de vértices do caminho usando predecessores e distâncias
    Caminho* caminho = NULL;
    Vertice* atual = verticeDestino;
    while (atual != NULL) {
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