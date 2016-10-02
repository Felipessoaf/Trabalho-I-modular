/***************************************************************************
*  $MCI Módulo de implementação: TAB  Tabuleiro do Xadrez
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / Juiz de Xadrez
*  -------------------------------------------Gestor:  LES/DI/PUC-Rio
*  Autores: pf - Pedro Ferreira
*           mmq - Matheus de Mello Queiroz
*			fpf - Felipe Pessoa de Freitas			
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       pf   25/set/2016 início da implementação das peças
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

#define pathArquivo "E:/Lipe/PUC/6º Período/INF1301/T2/Repo/trunk/T2/TRAB2-2/PecasXadrez.txt"

/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da cabeça do Tabuleiro
*
*
***********************************************************************/

typedef struct TAB_tagTabuleiro
{
	LIS_tppLista pPecas;
		   /* Cabeça da lista com as peças disponiveis */
	LIS_tppLista pMatriz;
		   /* Cabeça da matriz */
} TAB_tpTabuleiro;

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

/***********************************************************************
*
*  $TC Tipo de dados: TAB Conteudo da lista de casas
*
*
***********************************************************************/

	typedef struct tagCasa{
		
		char nome[4];
			/* Nome da peça na casa */

		char cor;
			/* Cor da peça na casa */

		int primeiroMov;
			/* Movimento que so pode ser executado na primeira jogada daquela peça */

		LIS_tppLista pAmeacantes;
				/* Ponteiro da Lista contendo as casas que contém peças que legalmente ameaçam a presente casa */

		LIS_tppLista pAmeacados;
				/* Ponteiro da Lista contendo as casas legalmente ameaçadas pela peça na presente casa */

	} tpCasa;

/***** Protótipos das funções encapsuladas no módulo *****/

	static void DestruirValorPeca(void * pValor);

	static void DestruirValorGenerico(void * pValor);

	static void DestruirValorMatriz(void * pValor); //TODO

	static void DestruirValorCasa(void * pValor); 

	static tpCasa * CriarCasa(); 

	static LIS_tppLista LerArquivoPecas();

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TAB  &Criar tabuleiro
*  ****/

   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro * pTabuleiro)
   {
	   int i, j;
	   TAB_tppTabuleiro pTabuleiroTemp;
	   TAB_tpCondRet temp;

	   pTabuleiroTemp = (TAB_tpTabuleiro *)malloc(sizeof(TAB_tpTabuleiro));
	   if (pTabuleiroTemp == NULL)
	   {
		   return TAB_CondRetFaltouMemoria;
	   } /* if */

	   pTabuleiroTemp->pPecas = LerArquivoPecas();
	   temp = LIS_CriarLista("matx", DestruirValorMatriz, &pTabuleiroTemp->pMatriz);
	   if (temp != TAB_CondRetOK)
	   {
		   return TAB_CondRetFaltouMemoria;
	   }
	   for (i = 0; i < 8; i++)
	   {
		   LIS_tppLista tempCol;
		   temp = LIS_CriarLista((char*)(i + 49), DestruirValorCasa, &tempCol);
		   if (temp != TAB_CondRetOK)
		   {
			   return TAB_CondRetFaltouMemoria;
		   }
		   for (j = 0; j < 8; j++)
		   {
			   temp = LIS_InserirElemento(tempCol, CriarCasa());
			   if (temp != TAB_CondRetOK)
			   {
				   return TAB_CondRetFaltouMemoria;
			   }
		   }
		   temp = LIS_InserirElemento(pTabuleiroTemp->pMatriz, tempCol);
		   if (temp != TAB_CondRetOK)
		   {
			   return TAB_CondRetFaltouMemoria;
		   }
	   }

	   *pTabuleiro = pTabuleiroTemp;

	   return TAB_CondRetOK;

   } /* Fim função: LIS  &Criar lista */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor peca
*
***********************************************************************/

	void DestruirValorPeca(void * pValor)
	{
		tpPeca * tempPeca = (tpPeca*)pValor;
		LIS_DestruirLista(tempPeca->pAndar);
		LIS_DestruirLista(tempPeca->pComer);
		free(pValor);
	} /* Fim função: TAB -Destruir valor peca*/

/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor generico
*
***********************************************************************/

	void DestruirValorGenerico(void * pValor)
	{
		free(pValor);
	} /* Fim função: TAB -Destruir valor generico*/

/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor matriz
*
***********************************************************************/

	void DestruirValorMatriz(void * pValor)
	{
		LIS_DestruirLista((LIS_tppLista)pValor);
	} /* Fim função: TAB -Destruir valor matriz*/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor casa
*
***********************************************************************/

	void DestruirValorCasa(void * pValor)
	{
		tpCasa * tempCasa = (tpCasa*)pValor;
		LIS_DestruirLista(tempCasa->pAmeacados);
		LIS_DestruirLista(tempCasa->pAmeacantes);
		free(pValor);
	} /* Fim função: TAB -Destruir valor casa*/


/***********************************************************************
*
*  $FC Função: TLIS -Criar casa
*
***********************************************************************/

	tpCasa* CriarCasa()
	{
		tpCasa * pCasa;
		pCasa = (tpCasa*)malloc(sizeof(tpCasa));
		pCasa->primeiroMov = 0;
		pCasa->cor = 'u';
		strcpy(pCasa->nome,"xxxx");

		LIS_CriarLista("amdo",DestruirValorGenerico,&pCasa->pAmeacados);
		LIS_CriarLista("amte", DestruirValorGenerico, &pCasa->pAmeacantes);
		

		return pCasa;
	} /* Fim função: TAB -Criar casa*/

/***********************************************************************
*
*  $FC Função: TAB  -Ler Arquivo de peças
*
***********************************************************************/

	LIS_tppLista LerArquivoPecas()
	{
		LIS_tppLista lisPecas;
		LIS_tppLista lisTemp;

		tpPeca* pecaTemp;
		tpMovimentoPeca* movPeca;

		LIS_CriarLista("p", DestruirValorPeca, &lisPecas);

		FILE * pFile = fopen(pathArquivo, "r");
		char line[50];

		if (pFile == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
		else
			while (fgets(line, sizeof(line), pFile) != NULL)
			{
				if (strncmp(line, ">>>>>>>>>>", 10) == 0)
				{
					pecaTemp = (tpPeca*)malloc(sizeof(tpPeca));
				
					pecaTemp->cor = 'u';

					LIS_CriarLista("a", DestruirValorGenerico, &lisTemp);
					pecaTemp->pAndar = lisTemp;

					LIS_CriarLista("c", DestruirValorGenerico, &lisTemp);
					pecaTemp->pComer = lisTemp;
				}
				else if (strncmp(line, "Nome", 4) == 0)
				{
					strncpy(pecaTemp->nome, &line[5], 4);
					printf("%s", pecaTemp->nome);
				}
				else if ((strncmp(line, "--Andar", 7) == 0) || (strncmp(line, "--Comer", 7) == 0))
				{
					movPeca = (tpMovimentoPeca*)malloc(sizeof(tpMovimentoPeca));
				}
				else if (strncmp(line, "--FimAndar", 10) == 0)
				{	
					printf("---------\nAndar\ncoord = %d %d %d %d\nmax = %d\nmin = %d\nprim = %d\n", movPeca->coordenadas[0], movPeca->coordenadas[1], movPeca->coordenadas[2], movPeca->coordenadas[3], movPeca->max, movPeca->min, movPeca->primeiroMov);
					LIS_InserirElemento(pecaTemp->pAndar, pecaTemp);
				}
				else if (strncmp(line, "--FimComer", 10) == 0)
				{
					printf("---------\nComer\ncoord = %d %d %d %d\nmax = %d\nmin = %d\nprim = %d\n", movPeca->coordenadas[0], movPeca->coordenadas[1], movPeca->coordenadas[2], movPeca->coordenadas[3], movPeca->max, movPeca->min, movPeca->primeiroMov);
					LIS_InserirElemento(pecaTemp->pComer, pecaTemp);
				}
				else if (strncmp(line, "Oeste", 5) == 0)
				{
					movPeca->coordenadas[0] = (int)line[6] - 48;
				}
				else if (strncmp(line, "Norte", 5) == 0)
				{
					movPeca->coordenadas[1] = (int)line[6] - 48;
				}
				else if (strncmp(line, "Leste", 5) == 0)
				{
					movPeca->coordenadas[2] = (int)line[6] - 48;
				}
				else if (strncmp(line, "Sul", 3) == 0)
				{
					movPeca->coordenadas[3] = (int)line[4] - 48;
				}
				else if (strncmp(line, "Max", 3) == 0)
				{
					movPeca->max = (int)line[4] - 48;
				}
				else if (strncmp(line, "Min", 3) == 0)
				{
					movPeca->min = (int)line[4] - 48;
				}
				else if (strncmp(line, "Primeiro", 8) == 0)
				{
					movPeca->primeiroMov = (int)line[9] - 48;
				}
				else if (strncmp(line, "<<<<<<<<<<", 10) == 0)
				{
					printf("----------\n");
					printf("Nome = %s\nCor = %c\n>>>>>>>>>>>>>>>\n", pecaTemp->nome, pecaTemp->cor);
					LIS_InserirElemento(lisPecas, pecaTemp);
				}
			}

		fclose(pFile);
		return lisPecas;
	}

	int main()
	{
		LerArquivoPecas();
		return 0;
	}