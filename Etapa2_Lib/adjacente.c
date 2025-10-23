/*****************************************************************//**
 *  @file   --   adjacencte.c
 *
 *   @brief  --   Funções para operações com Adjacências
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
  * Esta funcao aloca memoria para uma adjacencia.
  *
  * \param id Variavel que guarda o valor que identifica a adjacencia
  * \return
  */
Adjacente* CriaAdjacencia(int id, int peso) {
	Adjacente* adjacente;

	adjacente = (Adjacente*)malloc(sizeof(Adjacente));
	if (adjacente == NULL)
	{
		return NULL;
	}
	adjacente->id = id;
	adjacente->peso = peso;
	adjacente->prox = NULL;
	return adjacente;
}

/**
 * Esta funcao insere uma adjacencia na lista de adjacencias.
 *
 * \param listaAdj Variavel que contem todas as adjacencias
 * \param idDestino Variavel que tem o id do novo no
 * \param peso Variavel que contem o peso
 * \return 
 */
Adjacente* InsereAdjacencia(Adjacente* listaAdj, int idDestino, int peso) {

	Adjacente* novaAdj;
	if ((novaAdj = CriaAdjacencia(idDestino, peso)) == NULL)
	{
		return listaAdj;	//se não conseguiu criar nova adjacencia
	}

	//se lista de adjacencia estava vazia
	if (listaAdj == NULL) {
		listaAdj = novaAdj; //insere a nova adjacencia no inicio
	}
	else
	{
		//Insere no fim da LA
		Adjacente* aux = listaAdj;
		while (aux->prox != NULL)
		{
			aux = aux->prox;
		}
		aux->prox = novaAdj;
	}
	return listaAdj;
}

/**
 * Esta funcao apaga uma adjacencia/nó da lista de adjacencias.
 *
 * \param listAdj Variavel que contem as adjacencia
 * \param idAdj Variavel do ID da adjacencia que se pretende remover
 * \param res Variavel apontada, que retorna se a execucao foi realizada com sucesso
 * \return
 */
Adjacente* EliminaAdjacencia(Adjacente* listAdj, int idAdj, bool* res) {
	*res = false;
	if (listAdj == NULL) return NULL;
	Adjacente* aux = listAdj;
	Adjacente* anterior = NULL;

	//procura adjacencia
	while (aux && aux->id != idAdj) {
		anterior = aux;
		aux = aux->prox;
	}
	if (!aux) return listAdj;	//adjacencia não existe
	//apaga adjacencia no inicio
	if (anterior == NULL)
	{
		//apaga todas adjacencias do vertice a eliminar
		listAdj = aux->prox;
	}
	else {
		//apaga vertice
		anterior->prox = aux->prox;
	}
	free(aux);
	*res = true;
	return listAdj;
}

/**
 * Esta funcao remove todas as adjacencias da lista de adjacencias.
 *
 * \param listAdj Variavel que contem as adjacencias
 * \param res Variavel apontada, que retorna se a execucao foi realizada com sucesso
 * \return
 */
Adjacente* EliminaAdjacenciasTotais(Adjacente* listAdj, bool* res) {
	*res = false;
	if (listAdj == NULL) return NULL;

	Adjacente* aux = listAdj;
	//percorre lista de adjacencia
	while (aux) {
		if (aux)
			listAdj = aux->prox;
		free(aux);
		aux = listAdj;
	}
	listAdj = NULL;
	*res = true;
	return listAdj;
}

/**
 * Esta funcao remove as adjacencias.
 *
 * \param adj Variavel que contem a adjacencias
 * \return
 */
Adjacente* DestruirAdj(Adjacente* h) {
	if (h == NULL) return NULL;
	Adjacente* aux = NULL;
	while (h) {
		if (h->prox != NULL)
			aux = h->prox;
		free(h);
		h = aux;
		aux = NULL;
	}
	return h;
}

/**
 * Esta funcao verifica se existe adjacencias.
 * 
 * \param adj Variavel que contem as adjacencia
 * \param id Variavel que contem o id a verificar
 * \return 
 */
bool ExisteAdjacentes(Adjacente* adj, int id) {
	if (adj == NULL) return false;
	if (adj->id == id) return true;
	return ExisteAdjacentes(adj->prox, id);
}

/**
 * Esta funcao insere uma adjacencia entre dois vertices especificos.
 * 
 * \param v Variavel que contem a lista de vertices
 * \param idOrigem Variavel que contem o id do vertice de origem
 * \param idDestino Variavel que contem o id do vertice de chegada
 * \param peso Variavel que contem o peso da adjacencia
 * \param res Variavel apontada, que retorna se a execucao foi realizada com sucesso
 * \return 
 */
Vertice* InsereAdjacenciaVerticeId(Vertice* v, int idOrigem, int idDestino, int peso, bool* res) {
	*res = false;
	if (v == NULL) return v;

	Vertice* vOrigem, *vDestino;

	//Erro esta aqui
	vOrigem = ProcuraVerticeId(v, idOrigem);
	vDestino = ProcuraVerticeId(v, idDestino);	
	if (vOrigem == NULL || vDestino == NULL) return v;

	if (ExisteAdjacentes(vOrigem->proxAdjacente, idDestino) == true)
		return v; //Se já foi registado esta adjacencia, ignorar a operação

	//Insere nova adjacencia no vertice "Origem"
	vOrigem->proxAdjacente = InsereAdjacencia(vOrigem->proxAdjacente, idDestino, peso);
	return v;
}