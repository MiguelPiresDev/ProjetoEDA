/*****************************************************************//**
 *  @file   --   metodos.c
*
*   @brief  --   Funções de complementação
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
#include "queue.h"
#pragma warning (disable:4996)

#define MAX 100

 /**
  * Esta funcao importa os valores do ficheiro.
  *
  * \param g Variavel que contem os valores do grafo
  * \param nomeFicheiro Variavel que contem o nome do ficheiro
  * \return
  */
int* ImportaValorFicheiro(Grafo* g, char nomeFicheiro[]) {
    FILE* fp = fopen(nomeFicheiro, "r");
    if (fp == NULL) return 0;

    //Aloca a memoria
    int* peso = (int*)malloc(sizeof(int) * (g->totalVertices * g->totalVertices));
    if (peso == NULL) return NULL;

    for (int i = 0; i < (g->totalVertices * g->totalVertices); i++)
    {
        //Guarda os valores do ficheiro
        fscanf(fp, "%d;", (peso + i));
    }
    fclose(fp);
    return peso;
}

/**
 * Esta funcao conta linhas do ficheiro.
 *
 * \param nomeFicheiro Variavel que contem o nome do ficheiro
 * \return
 */
int ContarFicheiro(char nomeFicheiro[]) {
    int c;
    FILE* fp = fopen(nomeFicheiro, "r");
    if (fp == NULL)
        return 0;

    //Conta linhas atraves de '\n'
    int linhas = 1;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n')
            linhas = linhas + 1;
    }
    fclose(fp);
    return linhas;
}

/**
 * Esta funcao e responsavel por inserir os vertices no grafo.
 *
 * \param vertice Variavel que contem os vertices
 * \param g Variavel que contem os valores do grafo
 * \param res Variavel apontada, que retorna se a execucao foi realizada com sucesso
 * \return
 */
Grafo* InserirVerticeGrafoCompleto(Vertice* vertice, Grafo* g, bool* res) {

    for (int i = 0; i < g->totalVertices; i++)
    {
        Vertice* v = CriaVertice(1 + i, 65 + i);
        g = InsereVerticeGrafo(g, v, &res);
    }
    return g;
}

/**
 * Esta funcao insere as adjacencias dos vertices, com o respetivo peso, no grafo.
 *
 * \param adj Esta variavel contem as adjacencias
 * \param g Variavel que contem os valores do grafo
 * \param peso Variavel que contém o valor pesado de cada adjacencia
 * \param res Variavel apontada, que retorna se a execucao foi realizada com sucesso
 * \return
 */
Grafo* InserirAdjGrafoCompleto(Adjacente* adj, Grafo* g, int* peso, bool* res) {

    for (int j = 1; j < g->totalVertices + 1; j++)
    {
        //Variável que altera o valor do peso
        int pesoSoma = (j * g->totalVertices) - g->totalVertices;

        for (int i = 1; i < g->totalVertices + 1; i++)
        {
            g = InsereAdjaGrafo(g, j, i, *(peso + pesoSoma), &res);
            pesoSoma++;
        }
    }
    return g;
}

/**
 * Este procedimento imprime o id do vertice.
 *
 * \param v contem os valores dos vertices
 */
void ProcessaVertice(Vertice* v) {
    printf("%d | ", v->id);
}

/**
 *  Esta funcao procura o vertice pelo seu id e retorna-o.
 *
 * \param inicio Variavel que contem a lista de vertices
 * \param id Variavel que contem o id que se procura
 * \return
 */
Vertice* ObterVertice(Vertice* inicio, int id) {
    if (inicio == NULL) return NULL;
    Vertice* aux = inicio;
    while (aux) {
        if (aux->id == id) return aux;
        aux = aux->proxVertice;
    }
    return NULL;
}

/**
 * Esta funcao percorre o grafo para encontrar a ligacao entre vertices.
 *
 * \param g Variavel que contem todos os elementos do grafo
 * \param v Variavel que contem o id do vertice que se comeca a procurar
 * \return
 */
bool BTF(Grafo* g, int v)
{
    int fila[MAX];
    int ultimo, primeiro;

    ultimo = primeiro = 0;

    bool res = false;
    int proximoV;

    Vertice* auxV = g->grafoLV;

    //marca vertice como visitado 
    Vertice* aux = ObterVertice(auxV, v);
    if (aux == NULL) return false;
    aux->percorrido = true;

    //insere vertice na fila 
    res = InsereFila(fila, &ultimo, v);
    if (!res) return false;

    while (!isFilaVazia(ultimo, primeiro)) {
        //trata nodo da frente da fila
        proximoV = RemoveFila(fila, &primeiro);
        aux = ObterVertice(auxV, proximoV);
        if (aux == NULL) return false;
        ProcessaVertice(aux);

        Adjacente* adj = aux->proxAdjacente;
        while (adj) {
            aux = ObterVertice(auxV, adj->id);
            if (aux->percorrido == false)
            {
                aux->percorrido = true;
                res = InsereFila(fila, &ultimo, adj->id);
            }
            adj = adj->prox;
        }
    }
}

/**
 * Esta funcao guarda os vertices num ficheiro binario.
 *
 * \param v Variavel que contem a lista de vertices
 * \param nomeFicheiro Variavel que contem o nome do ficheiro
 * \return
 */
int GuardarGrafoB(Vertice* v, char* nomeFicheiro) {

    if (v == NULL) return -1;
    FILE* fp;
    int r;
    fp = fopen(nomeFicheiro, "wb");
    if (fp == NULL) return -2;

    Vertice* aux = v;
    FicheiroVertice auxFicheiro;	//estrutura de vertice para gravar em ficheiro
    while (aux != NULL) {
        auxFicheiro.idF = aux->id;
        auxFicheiro.valorF = aux->valor;
        fwrite(&auxFicheiro, 1, sizeof(FicheiroVertice), fp);

        //Coloca o valor tipo char
        char caracter = aux->valor;
        //Pode gravar de imediato as adjacencias!
        if (aux->proxAdjacente) 
        {
            char ficheiroAdj[10]; // Tamanho suficiente para 1 caractere + ".bin" 
            snprintf(ficheiroAdj, sizeof(ficheiroAdj), "%c.bin", caracter);

           r = GuardarAdjB(aux->proxAdjacente, ficheiroAdj , aux->id);
           if (r < 0) break;
        }
        aux = aux->proxVertice;
    }
    fclose(fp);
    return 1;
}

/**
 * Esta funcao guarda as adjacencias de cada cada vertice e o seu peso num ficheiro binario.
 * 
 * \param adj Variavel que contem a lista de adjacencias
 * \param nomeFicheiro Variavel que contem o nome do ficheiro
 * \param idVerticeOrigem Variavel que contem o id do Vertice 
 * \return 
 */
int GuardarAdjB(Adjacente* adj, char* nomeFicheiro, int idVerticeOrigem) {
    FILE* fp;
    if (adj == NULL) return -2;
    fp = fopen(nomeFicheiro, "wb");
    if (fp == NULL) return -1;

    Adjacente* aux = adj;
    FicheiroAdj ficheiroAux;
    while (aux) {

        ficheiroAux.idOF = idVerticeOrigem;
        ficheiroAux.idDF = aux->id;
        ficheiroAux.pesoF = aux->peso;
        fwrite(&ficheiroAux, 1, sizeof(FicheiroAdj), fp);
        aux = aux->prox;
    }
    fclose(fp);
    return 1;
}

/**
 * Esta funcao carrega os vertices do grafo de um ficheiro binario.
 * 
 * \param v Variavel que contem a lista dos vertices
 * \param nomeFicheiro Variavel que contem o nome do ficheiro
 * \param res Variavel apontada, que retorna se a execucao foi realizada com sucesso
 * \return 
 */
Vertice* CarregarGrafo(Vertice* v, char* nomeFicheiro, bool* res) {
    *res = false;
    FILE* fp = fopen(nomeFicheiro, "rb");
    if (fp == NULL) return NULL;

    FicheiroVertice aux;
    Vertice* novo;
    while (fread(&aux, 1, sizeof(FicheiroVertice), fp)) {
        novo = CriaVertice(aux.idF, aux.valorF);
        v = InsereVertice(v, novo, res);
    }
    fclose(fp);
    return v;
}

/**
 * Esta funcao carrega as adjacencias do grafo de um ficheiro binario.
 * 
 * \param v Variavel que contem a lista dos vertices
 * \param res Variavel apontada, que retorna se a execucao foi realizada com sucesso
 * \return 
 */
Vertice* CarregarAdj(Vertice* v, bool* res) {
    *res = false;
    FILE* fp;
    if (v == NULL) return -1;
    FicheiroAdj aux;
    Vertice* auxGrafo = v;

    while (auxGrafo) {

        char nomeFicheiroAdj[10]; // Tamanho suficiente para 1 caractere + ".bin"
        snprintf(nomeFicheiroAdj, sizeof(nomeFicheiroAdj), "%c.bin", auxGrafo->valor);

        fp = fopen(nomeFicheiroAdj, "rb");
        if (fp != NULL) {
            while (fread(&aux, 1, sizeof(FicheiroAdj), fp)) {
                v =  InsereAdjacenciaVerticeId(v, aux.idOF, aux.idDF, aux.pesoF, res);
            }
            fclose(fp);
        }
        auxGrafo= auxGrafo->proxVertice;
    }
    return v;
}

#pragma endregion