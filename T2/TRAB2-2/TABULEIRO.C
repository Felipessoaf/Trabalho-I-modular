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

#define pathArquivo "C:/Users/pedro/Documents/Trab1 Modular/trunk/T2/TRAB2-2/PecasXadrez.txt"

/***********************************************************************
*
*  $TC Tipo de dados: TAB Cabeça da Matriz
*
*
***********************************************************************/


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

	static LIS_tppLista LerArquivoPecas();

	static void DestruirValor(void * pValor);

/*****  Código das funções encapsuladas no módulo  *****/


	void DestruirValor(void * pValor)
	{

		free(pValor);

	} /* Fim função: TAB -Destruir valor */

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

		LIS_CriarLista("p", DestruirValor, &lisPecas);

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

					LIS_CriarLista("a", DestruirValor, &lisTemp);
					pecaTemp->pAndar = lisTemp;

					LIS_CriarLista("c", DestruirValor, &lisTemp);
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
		return 0;
	}

	int main()
	{
		LerArquivoPecas();
		return 0;
	}