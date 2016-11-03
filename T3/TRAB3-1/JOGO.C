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
#include <windows.h>

#define JOGO_OWN
#include "JOGO.h"
#undef JOGO_OWN


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: JOGO  &Mostrar tabuleiro
*  ****/

	JOGO_tpCondRet JOGO_MostraTabuleiro(TAB_tppTabuleiro pTabuleiro)
	{
		int i, j;
		char pCoordenada[3] = { 'A', '1', '\0' };
		char   pCor;
		char * pNome;

		if (pTabuleiro == NULL)
		{
			return JOGO_CondRetTabuleiroInexistente;
		}

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		WORD saved_attributes;

		/* Save current attributes */
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		saved_attributes = consoleInfo.wAttributes;

		printf("\n\n");
		printf("  A   B   C   D   E   F   G   H\n");
		printf("---------------------------------\n");
		for (i = 8; i > 0; i--)
		{
			pCoordenada[1] = i + 48;
			for (j = 0; j < 8; j++)
			{
				pCoordenada[0] = j + 65;				
				TAB_ObterPeca(&pTabuleiro, pCoordenada, &pCor, &pNome);
				if (strcmp(pNome, "xxx"))
				{
					printf("|");
					if (pCor == 'b')
					{
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					}
					else
					{
						SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
					}
					printf("%s%c ", pNome, pCor);

					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
				else
				{
					printf("|   ");
				}
			}
			printf("| %d\n---------------------------------\n",i);
		}
		printf("\n\n");

		return JOGO_CondRetOK;
	} /* Fim função: JOGO  &Mostrar tabuleiro */

/***************************************************************************
*
*  Função: JOGO  &Recebe jogada
*  ****/

	JOGO_tpCondRet JOGO_RecebeJogada(TAB_tppTabuleiro pTabuleiro, char * origem, char * destino)
	{
		

		return JOGO_CondRetOK;
	} /* Fim função: JOGO  &Recebe jogada */

/***************************************************************************
*
*  Função: JOGO  &Monta tabuleiro
*  ****/

	JOGO_tpCondRet JOGO_MontaTabuleiro(TAB_tppTabuleiro pTabuleiro)
	{
		FILE * pFile;

		int i;

		char cor = 'u';
		char nome[4];
		char pCoordenada[3];

		char line[50];

		if (pTabuleiro == NULL)
		{
			return JOGO_CondRetTabuleiroInexistente;
		}

		pFile = fopen("PecasTabuleiro.txt", "r");


		if (pFile == NULL)
		{
			printf("\nErro, nao foi possivel abrir o arquivo de pecas do tabuleiro.\n");
			return JOGO_CondRetArquivoPecasNaoExiste;
		}

		while (fgets(line, sizeof(line), pFile) != NULL)
		{
			if (strncmp(line, ">>>>>>>>>>", 10) == 0)
			{
				/* Nome */
				if (fgets(line, sizeof(line), pFile) == NULL)
				{
					return JOGO_CondRetArquivoPecasForaPadrao;
				}
				strncpy(nome, line, 4);
				for (i = 0; i < 4; i++)
				{
					if (nome[i] == '\n')
					{
						nome[i] = '\0';
					}
				}

				/* Cor */
				if (fgets(line, sizeof(line), pFile) == NULL)
				{
					return JOGO_CondRetArquivoPecasForaPadrao;
				}
				cor = line[0];

				/* Coordenada */
				if (fgets(line, sizeof(line), pFile) == NULL)
				{
					return JOGO_CondRetArquivoPecasForaPadrao;
				}
				pCoordenada[0] = line[0];
				if (fgets(line, sizeof(line), pFile) == NULL)
				{
					return JOGO_CondRetArquivoPecasForaPadrao;
				}
				pCoordenada[1] = line[0];
				pCoordenada[2] = '\0';

			}
			else if (strncmp(line, "<<<<<<<<<<", 10) == 0)
			{
				if (cor == 'b' || cor == 'p' || cor == 'B' || cor == 'P')
				{
					TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);
					cor = 'u';
				}
				else
				{
					return JOGO_CondRetArquivoPecasForaPadrao;
				}
			}
		}
		fclose(pFile);

		return JOGO_CondRetOK;
	} /* Fim função: JOGO  &Monta tabuleiro */

/********** Fim do módulo de implementação: JOGO  Jogo de xadrez **********/

	int main()
	{
		TAB_tppTabuleiro pTabuleiro = NULL;

		TAB_CriarTabuleiro(&pTabuleiro);

		JOGO_MontaTabuleiro(pTabuleiro);

		JOGO_MostraTabuleiro(pTabuleiro);
	}