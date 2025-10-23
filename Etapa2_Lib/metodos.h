#pragma once
/*****************************************************************//**
 *  @file   --   metodos.h
 *
 *   @brief  --   Declaração de funções complementares para funcionamento do grafo
 *
 *   @author --   Miguel Pires - 27968
 *
 *   @email  --   a27968@alunos.ipca.pt
 *
 *   @date   --    Maio 2024
 *********************************************************************/
#include "estrutura.h"

 //Tratamento de Ficheiros
int ContarFicheiro(char filename[]);
int* ImportaValorFicheiro(Grafo* g, char fileName[]);

//Guardar e Carregar Grafo
int GuardarGrafoB(Vertice* v, char* nomeFicheiro);
Vertice* CarregarGrafo(Vertice* v, char* fileName, bool* res);
Vertice* CarregarAdj(Vertice* v, bool* res);

//Metodos Complementares
Grafo* InserirVerticeGrafoCompleto(Vertice* vertice, Grafo* g, bool* res);
Grafo* InserirAdjGrafoCompleto(Adjacente* adj, Grafo* g, int* peso, bool* res);

bool BTF(Grafo* g, int v);

