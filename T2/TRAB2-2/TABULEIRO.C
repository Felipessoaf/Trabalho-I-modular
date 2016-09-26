/***************************************************************************
*  $MCI Módulo de implementação: TAB  Tabuleiro do Xadrez
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  -------------------------------------------Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW 
*
*  -------------------------------------------Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  -------------------------------------------Gestor:  LES/DI/PUC-Rio
*  Autores: pf - Pedro Ferreira
*           mmq - Matheus de Mello Queiroz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       avs   25/set/2016 início da implementação das peças
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define TABULEIRO_OWN
#include "TABULEIRO.h"
#include "LISTA.H"
#undef TABULEIRO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: TAB Conteudo da lista de peças
*
*
***********************************************************************/

	typedef struct tagPeca{
		
		char nome[4];
			/* Nome da peça */

		char cor;
			/* Cor da peça, podendo ser b (branco) ou p (preto) */

		LIS_tppLista pAndar;
				/* Ponteiro da Lista contendo os movimentos da peça de andar */

		LIS_tppLista pComer;
				/* Ponteiro da Lista contendo os movimentos da peça de comer */

	} tpPeca;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Conteudo da lista de movimentos da pecas
*
*
***********************************************************************/

	typedef struct tagMovimentoPeca{

		int coordenadas[4];
			/* Vetor de inteiros que representa as coordenadas Oeste = 0, 
			Norte = 1, Leste =2 e Sul = 3 */

		int max;
			/* Numero maximo de vezes que esse movimento pode ser repetido em uma jogada */

		int min;
			/* Numero minimo de vezes que esse movimento pode ser repetido em uma jogada */

		int primeiroMov;
			/* Movimento que so pode ser executado na primeira jogada daquela peça */

	} tpMovimentoPeca;

/***** Protótipos das funções encapsuladas no módulo *****/

	static tpPeca LerArquivoPecas()