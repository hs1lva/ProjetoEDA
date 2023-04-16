/*****************************************************************//**
 * \file   fgrafos.c
 * \brief  Fun��es com utiliza��es de grafos
 * 
 * \author hugo2
 * \date   April 2023
 *********************************************************************/

#include "grafos.h"

#pragma warning(disable:4996) //n�o chatear com _s 

 // Calcula a dist�ncia entre dois pontos utilizando a f�rmula da dist�ncia de euclides
float calcularDistancia(float x1, float y1, float x2, float y2) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

MeiosMobilidadeListaFiltradaPtr listarMeiosPorTipoERaio(Cliente cliente, MeiosMobilidadeListaPtr listaMeios, char* tipo, float raio) {
    MeiosMobilidadeListaFiltradaPtr listaFiltrada = NULL; // lista de meios de mobilidade filtrados
    MeiosMobilidadeListaPtr atual = listaMeios; // apontador para o primeiro elemento da lista de meios de mobilidade

    // percorre todos os meios de mobilidade el�trica na lista
    while (atual != NULL) {
        MeioMobilidade meio = atual->meioMobilidade;

        // verifica se o tipo de meio de mobilidade � o desejado
        if (strcmp(meio.tipo, tipo) == 0) {

            // calcula a dist�ncia entre o cliente e o meio de mobilidade el�trica
            float distancia = calcularDistancia(
                atof(cliente.geocodigo),
                atof(cliente.localizacao + 2), // +2 para ignorar as letras do geoc�digo
                atof(meio.geocodigo),
                atof(meio.localizacao + 2) // +2 para ignorar as letras do geoc�digo
            );
            // verifica se a dist�ncia � menor ou igual ao raio especificado
            if (distancia <= raio) {
                // adiciona o meio de mobilidade el�trica � lista filtrada
                MeiosMobilidadeListaFiltradaPtr novo = (MeiosMobilidadeListaFiltradaPtr)malloc(sizeof(MeiosMobilidadeListaFiltrada));
                novo->meioMobilidade = meio;
                novo->proxmeiomobilidadelista = listaFiltrada;
                listaFiltrada = novo;
            }
        }
        // avan�a para o pr�ximo meio de mobilidade el�trica na lista
        atual = atual->proxmeiomobilidadelista;
    }

    return listaFiltrada;
}


