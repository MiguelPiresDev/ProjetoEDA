/*****************************************************************//**
 *  @file   --   main.c
 *
 *   @brief  --   Declara variáveis e executa funções
 *
 *   @author --   Miguel Pires - 27968
 *
 *   @email  --   a27968@alunos.ipca.pt
 *
 *   @date   --    Maio 2024
 *********************************************************************/

#include <stdio.h>
#include <stdbool.h>

#pragma comment(lib,"Libs\\Etapa2_Lib.lib")
#include "Libs\\estrutura.h"
#include "Libs\\metodos.h"
#include "Libs\\estrutura.h"

int main() {

	bool* res = false;
	int linhas;

	linhas = ContarFicheiro("Peso.txt");

	Grafo* grafo = CriaGrafo(linhas);
	Vertice* listaVertices = NULL;
	Adjacente* listaAdj = NULL;

	int* peso = ImportaValorFicheiro(grafo, "Peso.txt");

	//Inserção no Grafo
	grafo = InserirVerticeGrafoCompleto(listaVertices, grafo, &res);
	grafo = InserirAdjGrafoCompleto(listaAdj, grafo, peso, &res);
	ImprimeGrafoLA(grafo); 
	
	//Conexao entre Vertices
	BTF(grafo, 4);

	//Remoção no Grafo
	grafo = EliminaVerticeGrafo(grafo, 3, &res);
	grafo = EliminaAdjGrafo(grafo, 1, 4, &res);
	ImprimeGrafoLA(grafo);
	

	//Guarda o Grafo
	GuardarGrafoB(grafo->grafoLV, "Vertices.bin");

	//Eliminar Grafo
	grafo->grafoLV = DestruirGrafo(listaVertices);
	ImprimeGrafoLA(grafo);

	grafo->grafoLV = CarregarGrafo(listaVertices, "Vertices.bin", &res);
	//grafo->grafoLV = CarregarAdj(grafo->grafoLV, &res);
	ImprimeGrafoLA(grafo);
	BTF(grafo, 1);
}

