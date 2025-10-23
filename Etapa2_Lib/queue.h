#pragma once
/*****************************************************************//**
 *  @file   --   queue.h
 *
 *   @brief  --   Declaracao de funcoes relativo as queues
 *
 *   @author --   Miguel Pires - 27968
 *
 *   @email  --   a27968@alunos.ipca.pt
 *
 *   @date   --    Maio 2024
 *********************************************************************/

bool InsereFila(int fila[], int* ultimo, int valor);

int RemoveFila(int fila[], int* primeiro);

bool isFilaVazia(int ultimo, int primeiro);


