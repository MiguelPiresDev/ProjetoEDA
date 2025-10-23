/*****************************************************************//**
 *  @file   --   queue.c
*
*   @brief  --   Funções de complementação das queues
*
*   @author --   Miguel Pires - 27968
*
*   @email  --   a27968@alunos.ipca.pt
*
*   @date   --    Maio 2024
 *********************************************************************/

#include <stdio.h>
#include <stdbool.h>

bool InsereFila(int fila[], int* ultimo, int valor) {
	//testes
	fila[(*ultimo)++] = valor;
	return true;
}

int RemoveFila(int fila[], int* primeiro) {
	return fila[(*primeiro)++];
}

bool isFilaVazia(int ultimo, int primeiro) {
	return ultimo == primeiro;
}