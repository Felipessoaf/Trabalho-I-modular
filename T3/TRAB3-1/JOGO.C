/***************************************************************************
*  $MCI Módulo de implementação: JOGO	Jogo de xadrez
*
*  Arquivo gerado:              JOGO.c
*  Letras identificadoras:      JOGO
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / Juiz de Xadrez
*  -------------------------------------------Gestor:  LES/DI/PUC-Rio
*  Autores: pf - Pedro Ferreira
*           mmq - Matheus de Mello Queiroz
*			fpf - Felipe Pessoa de Freitas	
*
*  $HA Histórico de evolução:
*     Versão  Autor     Data       Observações
*     2       fpf     31/out/2016  Implementação da interface gráfica do jogo
*     1       fpf     21/out/2016  início da implementação
*
***************************************************************************/

#include <stdio.h>
#include <string.h>

#define JOGO_OWN
#include "JOGO.h"
#undef JOGO_OWN

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: JOGO  &Mostrar tabuleiro
*  ****/

	JOGO_tpCondRet JOGO_MostrarTabuleiro(TAB_tppTabuleiro pTabuleiro)
	{
		int i, j;
		char pCoordenada[3] = { 'A', '1', '\0' };
		char   pCor;
		char * pNome;

		if (pTabuleiro == NULL)
		{
			return JOGO_CondRetTabuleiroInexistente;
		}
		
		printf("\n\n");
		printf("---------------------------------\n");
		for (i = 0; i < 8; i++)
		{
			pCoordenada[0] = i + 65;
			for (j = 1; j <= 8; j++)
			{
				pCoordenada[1] = j + 48;
				TAB_ObterPeca(&pTabuleiro, pCoordenada, &pCor, &pNome);
				if (strcmp(pNome, "xxx"))
				{
					printf("|%s%c ", pNome, pCor);
				}
				else
				{
					printf("|   ");
				}
			}
			printf("|\n---------------------------------\n");
		}
		printf("\n\n");

		return JOGO_CondRetOK;
	} /* Fim função: JOGO  &Mostrar tabuleiro */

/********** Fim do módulo de implementação: JOGO  Jogo de xadrez **********/

	int main()
	{
		int i;
		char cor = 'b';
		char nome[4] = {'p','\0',' ','\0'};
		char pCoordenada[3] = {'B','1','\0'};
		TAB_tppTabuleiro pTabuleiro = NULL;

		TAB_CriarTabuleiro(&pTabuleiro);

		for (i = 1; i <= 8; i++)
		{
			pCoordenada[1] = i + 48;
			TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);
		}

		cor = 'p';
		pCoordenada[0] = 'G';

		for (i = 1; i <= 8; i++)
		{
			pCoordenada[1] = i + 48;
			TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);
		}

		cor = 'b';
		nome[0] = 't';
		pCoordenada[0] = 'A';
		pCoordenada[1] = 1 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);
		pCoordenada[1] = 8 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);

		cor = 'p';
		pCoordenada[0] = 'H';
		pCoordenada[1] = 1 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);
		pCoordenada[1] = 8 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);

		cor = 'b';
		nome[0] = 'c';
		pCoordenada[0] = 'A';
		pCoordenada[1] = 2 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);
		pCoordenada[1] = 7 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);
		
		cor = 'p';
		pCoordenada[0] = 'H';
		pCoordenada[1] = 2 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);
		pCoordenada[1] = 7 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);
				
		cor = 'b';
		nome[0] = 'b';
		pCoordenada[0] = 'A';
		pCoordenada[1] = 3 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);
		pCoordenada[1] = 6 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);

		cor = 'p';
		pCoordenada[0] = 'H';
		pCoordenada[1] = 3 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);
		pCoordenada[1] = 6 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);

		cor = 'b';
		nome[0] = 'q';
		pCoordenada[0] = 'A';
		pCoordenada[1] = 4 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);

		cor = 'p';
		pCoordenada[0] = 'H';
		pCoordenada[1] = 5 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);

		cor = 'b';
		nome[0] = 'k';
		pCoordenada[0] = 'A';
		pCoordenada[1] = 5 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);

		cor = 'p';
		pCoordenada[0] = 'H';
		pCoordenada[1] = 4 + 48;
		TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);

		JOGO_MostrarTabuleiro(pTabuleiro);
	}