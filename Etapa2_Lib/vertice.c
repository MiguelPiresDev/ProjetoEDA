/*****************************************************************//**
 *  @file   --   vertice.c
 *
 *   @brief  --   Funções para operações com Vértices
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
  * Função que cria os vertices do grafo.
  *
  * \param id Variavel que contem o id do vertice
  * \param dado Variavel que contem um valor para o vertice
  * \return
  */
Vertice* CriaVertice(int id, int dado) {
	Vertice* aux = (Vertice*)malloc(sizeof(Vertice));
	if (aux == NULL)
	{
		return NULL;
	}
	aux->id = id;
	aux->valor = dado;
	aux->percorrido = false;

	aux->proxVertice = NULL;
	aux->proxAdjacente = NULL;

	return aux;
}

/**
 * Esta funcao insere um vertice na lista de vertices.
 *
 * \param vertices Variavel que contem os vwrtices
 * \param novo Variavel que se pretende inserir na lista de vertices
 * \param res Variavel apontada, que retorna se a execucao foi realizada com sucesso
 * \return
 */
Vertice* InsereVertice(Vertice* vertices, Vertice* novo, bool* res) {
	*res = false;
	bool verifica = false;
	Vertice* anterior = NULL;
	Vertice* aux = vertices;

	//Insere 
	if (vertices == NULL) {
		*res = 1;
		vertices = novo;
		return vertices;
	}
	//verificar se V já existe na lista de vertices...
	if (ExisteVertice(vertices, novo->id))
	{
		return vertices;
	}
	else {
		//Procura onde inserir
		while (aux != NULL && aux->id < novo->id)
		{
			anterior = aux;
			aux = aux->proxVertice;
		}
		//Insere
		*res = true;
		if (anterior == NULL) {
			novo->proxVertice = vertices;	//insere à cabeça
			vertices = novo;
		}
		else {
			novo->proxVertice = aux;
			anterior->proxVertice = novo;
		}
	}
	return vertices;
}

/**
 * Esta funcao elimina um vertice da lista de vertices.
 *
 * \param vertices Variavel que contem os vertices
 * \param idVertice  Variavel que se pretende eliminar da lista de vertices
 * \param res Variavel apontada, que retorna se a execução foi realizada com sucesso
 * \return
 */
Vertice* EliminaVertice(Vertice* vertices, int idVertice, bool* res) {
	*res = false;
	if (vertices == NULL) return NULL;

	Vertice* aux = vertices;
	Vertice* anterior = NULL;
	//procurar vertice
	while (aux->id != idVertice) {
		anterior = aux;
		aux = aux->proxVertice;
	}
	if (!aux) return vertices;	//signifca que não existe o vertice

	//apaga vertice no inicio
	if (anterior == NULL)
	{
		//apaga todas adjacencias do vertice a eliminar
		aux->proxAdjacente = EliminaAdjacenciasTotais(aux->proxAdjacente, res);
		if (*res == false) return vertices;
		vertices = aux->proxVertice;
	}
	else {
		//apaga vertice
		anterior->proxVertice = aux->proxVertice;
	}
	free(aux);
	*res = true;
	return vertices;
}

/**
 * Esta funcao elimina todas as adjacencias de um vertice.
 *
 * \param vertices Variavel que contem os vertices
 * \param idAdjacencia Variavel que contem o id da adjacencia
 * \param res Variavel apontada, que retorna se a execução foi realizada com sucesso
 * \return
 */
Vertice* EliminaAdjacenciaVertices(Vertice* vertices, int idAdjacencia, bool* res) {
	*res = false;
	if (vertices == NULL)
		return NULL;

	Vertice* aux = vertices;
	while (aux) {
		aux->proxAdjacente = EliminaAdjacencia(aux->proxAdjacente, idAdjacencia, res);
		aux = aux->proxVertice;
	}
	*res = true;
	return vertices;
}

/**
 * Esta funcao procura onde esta um determinado vértice.
 *
 * \param v Variavel que contem os vertices
 * \param id Variavel que contem o id dos vertices
 * \return
 */
Vertice* OndeEstaVertice(Vertice* v, int id) {
	if (v == NULL) return NULL;
	Vertice* aux = v;
	while (aux) {
		if (aux->id == id) return aux;
		aux = aux->proxVertice;
	}
	return NULL;
}

/**
 * Esta funcao verifica se um determinado vertice existe.
 *
 * \param inicio Variavel que contem os vertices
 * \param id Variavel que contem o id do vertice a verificar
 * \return
 */
bool ExisteVertice(Vertice* inicio, int id) {
	if (inicio == NULL) return false;
	Vertice* aux = inicio;
	while (aux) {
		if (aux->id == id) return true;
		aux = aux->proxVertice;
	}
	return false;
}

/**
 * Esta funcao procura o vertice pelo seu id.
 * 
 * \param g Variavel que contem os vertices
 * \param id Variavel que contem o id do vertice a procurar
 * \return 
 */
Vertice* ProcuraVerticeId(Vertice* v, int id) {
	if (v == NULL) return NULL;
	if (v->id == id) return v;
	return(ProcuraVerticeId(v->proxVertice, id));
}
