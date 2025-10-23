#pragma once
/*****************************************************************//**
 *  @file   --   estrutura.h
 *
 *   @brief  --   Structs e declaração de funções básicas para funcionamento do grafo
 *
 *   @author --   Miguel Pires - 27968
 *
 *   @email  --   a27968@alunos.ipca.pt
 *
 *   @date   --    Maio 2024
 *********************************************************************/

typedef struct Adjacente {
	int id;
	int peso;
	struct Adjacente* prox;
}Adjacente;

typedef struct Vertice {
	int id;
	int valor;
	bool percorrido;
	struct Adjacente* proxAdjacente;
	struct Vertice* proxVertice;
}Vertice;

typedef struct Grafo {
	struct Vertice* grafoLV; //Lista de vertices
	int numeroVertices;
	int totalVertices;
}Grafo;

// Guardar Ficheiro
typedef struct FicheiroAdj {
	int idOF;						//id Origem Ficheiro	
	int  idDF;						//id Destino Ficheiro
	int pesoF;						//peso Ficheiro
}FicheiroAdj;

typedef struct FicheiroVertice {
	int idF;						//id Ficehiro
	int valorF;						//valor Ficheiro
} FicheiroVertice;


#pragma region Metodos Essencias
#pragma region Vertices

//Criar
Vertice* CriaVertice(int id, int dado);

//Inserir
Vertice* InsereVertice(Vertice* vertices, Vertice* novo, bool* res);

//Auxiliar
Vertice* OndeEstaVertice(Vertice* inicio, int id);
bool ExisteVertice(Vertice* inicio, int id);
Vertice* ProcuraVerticeId(v, idOrigem);

//Eliminar
Vertice* EliminaVertice(Vertice* vertices, int idVertice, bool* res);
Vertice* EliminaAdjacenciaVertices(Vertice* vertices, int idAdjacencia, bool* res);

#pragma endregion
#pragma region Adjacencias

//Criar
Adjacente* CriaAdjacencia(int id, int peso);

//Inserir
Adjacente* InsereAdjacencia(Adjacente* listaAdj, int idDestino, int peso);

//Eliminar
Adjacente* EliminaAdjacencia(Adjacente* listAdj, int idAdj, bool* res);
Adjacente* EliminaAdjacenciasTotais(Adjacente* listAdj, bool* res);
Adjacente* DestruirAdj(Adjacente* h);

#pragma endregion
#pragma region Grafo

//imprimir
void ImprimeGrafo(Vertice* g);
void ImprimeGrafoLA(Grafo* g);

//Criar
Grafo* CriaGrafo(int total);

//Inserir
Grafo* InsereVerticeGrafo(Grafo* g, Vertice* novo, int* res);
Grafo* InsereAdjaGrafo(Grafo* g, int idOrigem, int idDestino, int peso, bool* res);

//Eliminar
Grafo* EliminaAdjGrafo(Grafo* g, int origem, int destino, bool* res);
Grafo* EliminaVerticeGrafo(Grafo* g, int idVertice, bool* res);
Vertice* DestruirGrafo(Vertice* v);

//Auxiliar
bool ExisteVerticeGrafo(Grafo* g, int idVertice);
Vertice* OndeEstaVerticeGrafo(Grafo* g, int idVertice);

#pragma endregion
#pragma endregion