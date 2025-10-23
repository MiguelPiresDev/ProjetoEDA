/*****************************************************************//**
 *  @file   --   grafo.c
 *
 *   @brief  --   Funções para operações com o Grafo
 *
 *   @author --   Miguel Pires - 27968
 *
 *   @email  --   a27968@alunos.ipca.pt
 *
 *   @date   --    Maio 2024
 *********************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#include "estrutura.h"

 /**
  * Este procedimento imprime o valor de cada vertice e o valor das adjacencias.
  *
  * \param v Variavel que contem os vertices
  */
void ImprimeGrafo(Vertice* v) {

	if (v == NULL)
	{
		printf("\n\nGrafo Vazio\n");
		return NULL;
	}

	Vertice* atual = v;
	printf("\n\n----------- 'Grafo' -----------\n\n");
	while (atual != NULL) {
		printf("%d: ", atual->id);
		printf("%c\n", atual->valor);
		Adjacente* adjAtual = atual->proxAdjacente;
		while (adjAtual != NULL)
		{
			printf("\t");
			printf("adjacent: %d; Peso: %d\n", adjAtual->id, adjAtual->peso);
			adjAtual = adjAtual->prox;
		}
		atual = atual->proxVertice;
	}
	printf("\n\n");
}

/**
 * Este procedimento imprime o grafo.
 *
 * \param gr Variavel que contem os valores do grafo
 */
void ImprimeGrafoLA(Grafo* g) {
	ImprimeGrafo(g->grafoLV);
}

/**
 * Esta funcao aloca memoria para criar o grafo.
 *
 * \param total Variavel que indica numero maximo de vertices possiveis no grafo
 * \return
 */
Grafo* CriaGrafo(int total) {
	//validações
	Grafo* aux = (Grafo*)malloc(sizeof(Grafo));
	//testar
	if (aux != NULL) {
		aux->grafoLV = NULL;
		aux->numeroVertices = 0;
		aux->totalVertices = total;
	}
	return aux;
}

/**
 * Esta funcao insere um vertice novo no grafo.
 *
 * \param g Variavel que contem os valores do grafo
 * \param novo Variavel que contem o novo vertice a inserir
 * \param res Variavel apontada, que retorna se a execucao foi realizada com sucesso
 * \return
 */
Grafo* InsereVerticeGrafo(Grafo* g, Vertice* novo, int* res) {
	*res = 1;

	//validações
	if (novo == NULL) { //vertice invalido
		*res = 0;
		return g;
	}
	if (g == NULL) { // grafo vazio
		*res = -1;
		return NULL;
	}
	//verificar se V já existe no grafo...
	if (ExisteVerticeGrafo(g, novo->id)) { //vertice desconhecido
		*res = -2;
		return g;
	}

	g->grafoLV = InsereVertice(g->grafoLV, novo, res);
	if (*res == true)

		g->numeroVertices++;

	return g;
}

/**
 * Esta funcao insere uma adjacencia entre dois vertices.
 *
 * \param g Variavel que contem os valores do grafo
 * \param idOrigem Variavel que contem o id de origem do vertice
 * \param idDestino Variavel que contem o id de destino do vertice
 * \param peso Variavel que contem o valor pesado de cada adjacencia
 * \param res Variãvel apontada, que retorna se a execucao foi realizada com sucesso
 * \return
 */
Grafo* InsereAdjaGrafo(Grafo* g, int idOrigem, int idDestino, int peso, bool* res) {
	*res = false;

	//Validações
	if (g == NULL) return NULL;
	//Verificar se vertices existem
	Vertice* originNode = OndeEstaVerticeGrafo(g, idOrigem);
	if (originNode == NULL) return g;
	Vertice* destinyNode = OndeEstaVerticeGrafo(g, idDestino);
	if (!destinyNode) return g;

	originNode->proxAdjacente = InsereAdjacencia(originNode->proxAdjacente, idDestino, peso);

	*res = true;
	return g;
}

/**
 * Esta funcao elimina uma adjacencia entre vertices.
 *
 * \param g Variavel que contem os valores do grafo
 * \param origem  Variavel que contem o id de origem do vertice
 * \param destino Variavel que contem o id de destino do vertice
 * \param res Variavel apontada, que retorna se a execucao foi realizada com sucesso
 * \return
 */
Grafo* EliminaAdjGrafo(Grafo* g, int origem, int destino, bool* res) {
	*res = false;

	//validações
	if (g == NULL) return NULL;
	//Verificar se vertices existem
	Vertice* originNode = OndeEstaVerticeGrafo(g, origem);
	if (originNode == NULL) return g;
	Vertice* destinyNode = OndeEstaVerticeGrafo(g, destino);
	if (!destinyNode) return g;

	originNode->proxAdjacente = EliminaAdjacencia(originNode->proxAdjacente, destino, res);
	return g;
}

/**
 *  Esta funcao remove um determinado vertice do grafo.
 *
 * \param g Variavel que contem os valores do grafo
 * \param idVertice Variavel que contem o id do vertice a eliminar
 * \param res Variavel apontada, que retorna se a execucao foi realizada com sucesso
 * \return
 */
Grafo* EliminaVerticeGrafo(Grafo* g, int idVertice, bool* res) {
	*res = false;
	if (g == NULL) return NULL;

	g->grafoLV = EliminaVertice(g->grafoLV, idVertice, res);
	g->grafoLV = EliminaAdjacenciaVertices(g->grafoLV, idVertice, res);
	if (*res == true) {
		g->numeroVertices--;
	}
	return g;
}

/**
 * Esta funcao confirma se existe um determinado vertice no grafo.
 *
 * \param g Variavel que contem os valores do grafo
 * \param idVertice Variavel que contém o id do vertice
 * \return
 */
bool ExisteVerticeGrafo(Grafo* g, int idVertice) {
	if (g == NULL) return false;
	return (ExisteVertice(g->grafoLV, idVertice));
}

/**
 * Esta funcao localiza um vertice.
 *
 * \param g Variavel que contem os valores do grafo
 * \param idVertice Variavel que contém o id do vertice a localizar
 * \return
 */
Vertice* OndeEstaVerticeGrafo(Grafo* g, int idVertice) {
	if (g == NULL) return NULL;
	return (OndeEstaVertice(g->grafoLV, idVertice));
}

/**
 * Esta funcao elimina o grafo por completo.
 * 
 * \param v Variavel que contem os valores dos vertices
 * \return 
 */
Vertice* DestruirGrafo(Vertice* v) {
	if (v == NULL) return NULL;
	Vertice* aux = NULL;
	while (v) {
		if (v->proxVertice)
			aux = v->proxVertice;
		v->proxAdjacente = DestruirAdj(v->proxAdjacente);
		free(v);
		v = aux;
		aux = NULL;
	}
	return v;
}