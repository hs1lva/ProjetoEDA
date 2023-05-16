/*****************************************************************//**
 * \file   vmeios.c
 * \brief  Funções para imprimir menus, listas etc dos meios de mobilidade
 * 
 * \author hugo2
 * \date   March 2023
 *********************************************************************/

#include "meios.h"

#pragma warning(disable:4996) //não chatear com _s 

/**
@brief Lista todos os meios de mobilidade em memória
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade
@return void lista de meios de mobilidade em memória
*/
void listarMeiosMobilidade(MeiosMobilidadeListaPtr listaMeiosMobilidade) {
	MeiosMobilidadeListaPtr atual = listaMeiosMobilidade;
	printf("------ Lista de Meios de Mobilidade ------\n");
	while (atual != NULL) {
		printf("ID: %d\nTipo: %s\nAutonomia(%): %.2f\nCustop/km(€): %.2f\nLocalização(ID local): %d\nGeocódigo: %s\nAlugado: %d\n\n",
			atual->meioMobilidade.id, atual->meioMobilidade.tipo, atual->meioMobilidade.autonomia,
			atual->meioMobilidade.custo, atual->meioMobilidade.localizacao, atual->meioMobilidade.geocodigo, atual->meioMobilidade.alugado);
		atual = atual->proxmeiomobilidadelista;
	}
	printf("------------------------------------------\n");
}

/**
@brief Lista todos os meios de mobilidade com carga de bateria abaixo de 50%
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade
@return void
*/
void listarMeiosMobilidadeComCargaBateriaAbaixo50(MeiosMobilidadeListaPtr listaMeiosMobilidade) {
    MeiosMobilidadeListaPtr atual = listaMeiosMobilidade;
    printf("------ Lista de Meios de Mobilidade com Carga de Bateria Abaixo de 50%% ------\n");
    while (atual != NULL) {
        if (atual->meioMobilidade.autonomia < 50) {
            printf("ID: %d\nTipo: %s\nAutonomia(%): %.2f\nCustop/km(€): %.2f\nLocalização(ID local): %d\nGeocódigo: %s\nAlugado: %d\n\n",
                atual->meioMobilidade.id, atual->meioMobilidade.tipo, atual->meioMobilidade.autonomia,
                atual->meioMobilidade.custo, atual->meioMobilidade.localizacao, atual->meioMobilidade.geocodigo, atual->meioMobilidade.alugado);
        }
        atual = atual->proxmeiomobilidadelista;
    }
    printf("-----------------------------------------------------------------------------\n");
}

/**
@brief Lista todos os meios de mobilidade em memória ordenados pela autonomia
@param listaMeiosMobilidade apontador para a lista de meios de mobilidade
@return void lista de meios de mobilidade em memória ordenados pela autonomia
*/
void listarMeiosMobilidadeOrdenadosAutonomia(MeiosMobilidadeListaPtr listaMeiosMobilidade) {
    MeiosMobilidadeListaPtr listaTemp = NULL; // Cria uma lista temporária para ordenar os meios de mobilidade por ordem decrescente de autonomia
    // Percorrer a lista de meios de mobilidade original, copiando cada meio de mobilidade para uma nova lista temporária, chamada listaTemp.
    for (MeiosMobilidadeListaPtr ptr = listaMeiosMobilidade; ptr != NULL; ptr = ptr->proxmeiomobilidadelista) {
        listaTemp = adicionarMeioMobilidade(listaTemp, &ptr->meioMobilidade);
    }
    // Ordena a lista temporária por ordem decrescente de autonomia
    // Se o meio de mobilidade da posição ptr1 tiver menos autonomia que o meio de mobilidade da posição ptr2, assim sucessivamente
    for (MeiosMobilidadeListaPtr ptr1 = listaTemp; ptr1 != NULL; ptr1 = ptr1->proxmeiomobilidadelista) {
        for (MeiosMobilidadeListaPtr ptr2 = ptr1->proxmeiomobilidadelista; ptr2 != NULL; ptr2 = ptr2->proxmeiomobilidadelista) {
            if (ptr1->meioMobilidade.autonomia < ptr2->meioMobilidade.autonomia) {
                MeioMobilidade temp = ptr1->meioMobilidade;
                ptr1->meioMobilidade = ptr2->meioMobilidade;
                ptr2->meioMobilidade = temp;
            }
        }
    }
    printf("------ Lista de Meios de Mobilidade ------\n");
    for (MeiosMobilidadeListaPtr ptr = listaTemp; ptr != NULL; ptr = ptr->proxmeiomobilidadelista) {
        printf("ID: %d\nTipo: %s\nAutonomia: %.2f \nCusto: %.2f euros/hora\nLocalizacao: %d\nGeocodigo: %s\nAlugado: %d\n\n",
            ptr->meioMobilidade.id, ptr->meioMobilidade.tipo, ptr->meioMobilidade.autonomia, ptr->meioMobilidade.custo,
            ptr->meioMobilidade.localizacao, ptr->meioMobilidade.geocodigo, ptr->meioMobilidade.alugado);
    }
    printf("-----------------------------------------\n");
    libertarMeiosMobilidadeLista(listaTemp); // Liberta a memória alocada para a lista temporária
}


/**
@brief Esta função pede ao utilizador para inserir um geocódigo de localização e lista todos os meios de mobilidade naquela localização.
A função percorre a lista de meios de mobilidade e compara o geocódigo da localização de cada meio de mobilidade com o geocódigo inserido pelo utilizador
@param listaMeiosMobilidade Apontador para a lista de meios de mobilidade.
@return void lista de meios de mobilidade em memória com uma determinada localização.
*/
void listarMeiosMobilidadePorLocalizacao(MeiosMobilidadeListaPtr listaMeiosMobilidade) {
    char geocodigo[10];
    printf("Insira o geocodigo da localizacao desejada: ");
    scanf("%s", geocodigo);
    printf("\n------ Lista de Meios de Mobilidade na Localizacao %s ------\n", geocodigo);
    int count = 0; // contador para verificar se nenhum meio de mobilidade foi encontrado
    for (MeiosMobilidadeListaPtr ptr = listaMeiosMobilidade; ptr != NULL; ptr = ptr->proxmeiomobilidadelista) {
        if (strcmp(ptr->meioMobilidade.geocodigo, geocodigo) == 0) { // se o geocodigo da localização do meio de mobilidade for igual ao geocodigo especificado pelo scanf
            printf("ID: %d\nTipo: %s\nAutonomia: %.2f \nCusto: %.2f euros/hora\nLocalizacao: %d\nGeocodigo: %s\nAlugado: %d\n\n",
                ptr->meioMobilidade.id, ptr->meioMobilidade.tipo, ptr->meioMobilidade.autonomia, ptr->meioMobilidade.custo,
                ptr->meioMobilidade.localizacao, ptr->meioMobilidade.geocodigo, ptr->meioMobilidade.alugado);
            count++;
        }
    }
    if (count == 0) { // se nenhum meio de mobilidade foi encontrado
        printf("Nao foram encontrados meios de mobilidade na localizacao %s.\n", geocodigo);
    }
    printf("-----------------------------------------\n");
}

/**
 * @brief Mostra as informações de um meio de mobilidade.
 * @param meioMobilidade O meio de mobilidade a ser mostrado.
 */
void mostrarMeioMobilidade(MeioMobilidade meioMobilidade, float distancia) {
    printf("ID do meio: %d\n", meioMobilidade.id);
    printf("Tipo: %s\n", meioMobilidade.tipo);
    printf("Autonomia: %.2f\n", meioMobilidade.autonomia);
    printf("Preco por km: %.2f\n", meioMobilidade.custo);
    printf("ID Localizacao: %d\n", meioMobilidade.localizacao);
    printf("Alugado: %d\n", meioMobilidade.alugado);
    printf("Distância(m) entre cliente e meio: %.2f\n", distancia);
    printf("\n");
}

/**
@brief Lista os meios de mobilidade mais próximos do local do cliente.
@param listaMeiosMobilidade A lista de meios de mobilidade disponíveis.
@param grafo O grafo de localizações da cidade.
@param localCliente O local do cliente a partir do qual será feita a pesquisa.
@param raio O raio de pesquisa em metros.
*/
void listarMeiosMobilidadeProximosCliente(MeiosMobilidadeListaPtr listaMeiosMobilidade, Vertice* grafo, int localCliente, float raio) {
    printf("------ Meios de mobilidade disponíveis a menos de %.0f metros: ------ \n", raio);

    MeiosMobilidadeListaPtr meioMobilidadeMaisProximo = pesquisarMeioMobilidadeMaisProximo(listaMeiosMobilidade, grafo, localCliente);
    while (meioMobilidadeMaisProximo != NULL) {
        float distancia = pesquisarEmLargura(grafo, localCliente, meioMobilidadeMaisProximo->meioMobilidade.localizacao);
        if (distancia <= raio) {
            mostrarMeioMobilidade(meioMobilidadeMaisProximo->meioMobilidade, distancia);
        }
        meioMobilidadeMaisProximo = pesquisarMeioMobilidadeMaisProximo(meioMobilidadeMaisProximo->proxmeiomobilidadelista, grafo, localCliente);
    }
}