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
*  Função: JOGO  &Mostra tabuleiro
*  ****/

	JOGO_tpCondRet JOGO_MostraTabuleiro(TAB_tppTabuleiro pTabuleiro)
	{
		int i, j;
		char pCoordenada[3] = { 'A', '1', '\0' };
		char   pCor;
		char * pNome;

		TAB_tpCondRet condret;

		if (!jogoRodando)
		{
			return JOGO_CondRetJogoParado;
		}

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
				condret = TAB_ObterPeca(&pTabuleiro, pCoordenada, &pCor, &pNome);
				if (condret != TAB_CondRetOK && condret != TAB_CondRetCasaVazia)
				{
					return condret;
				}
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
	} /* Fim função: JOGO  &Mostra tabuleiro */

/***************************************************************************
*
*  Função: JOGO  &Recebe jogada
*  ****/

	JOGO_tpCondRet JOGO_RecebeJogada(TAB_tppTabuleiro pTabuleiro, char * origem, char * destino)
	{
		LIS_tppLista pLista;
		TAB_tpCondRet condret;
		char   pCor;
		char * pNome;
		char * pValor;
		
		if (!jogoRodando)
		{
			return JOGO_CondRetJogoParado;
		}

		if (pTabuleiro == NULL)
		{
			return JOGO_CondRetTabuleiroInexistente;
		}

		if (!strcmp(origem, "FIM"))
		{
			jogoRodando = 0;
			return JOGO_CondRetOK;
		}

		condret = TAB_ObterPeca(&pTabuleiro, origem, &pCor, &pNome);
		if (condret != TAB_CondRetOK)
		{
			printf("\nMovimento Invalido\n");
			return condret;
		}

		if (pCor != jogCorr && pCor != (jogCorr + 32))
		{
			printf("\nMovimento Invalido\n");
			return JOGO_CondRetMovimentoInvalido;
		}

		condret = TAB_MoverPeca(&pTabuleiro, origem, destino);
		if (condret != TAB_CondRetOK)
		{
			printf("\nMovimento Invalido\n");
			return JOGO_CondRetMovimentoInvalido;
		}

		if (jogCorr == 'B')
		{
			jogCorr = 'P';
		}
		else
		{
			jogCorr = 'B';
		}

		/* Ameaçados */
		TAB_ObterListaAmeacados(&pTabuleiro, destino, &pLista);

		LIS_tpCondRet lisCondRet;

		printf("\nCasas ameacadas pela peca:\n");
		lisCondRet = LIS_IrProxElemento(pLista);
		if (lisCondRet != LIS_CondRetListaVazia)
		{
			for (LIS_AndarInicio(pLista); lisCondRet == LIS_CondRetOK; lisCondRet = LIS_IrProxElemento(pLista))
			{
				LIS_ObterElemento(pLista, (void**)&pValor);
				printf("%s\n", pValor);
			}
		}

		/* Ameaçantes */
		TAB_ObterListaAmeacantes(&pTabuleiro, destino, &pLista);
		
		printf("\nCasas que ameacam a peca:\n");
		lisCondRet = LIS_IrProxElemento(pLista);
		if (lisCondRet != LIS_CondRetListaVazia)
		{
			for (LIS_AndarInicio(pLista); lisCondRet == LIS_CondRetOK; lisCondRet = LIS_IrProxElemento(pLista))
			{
				LIS_ObterElemento(pLista, (void**)&pValor);
				printf("%s\n", pValor);
			}
		}

		return JOGO_CondRetOK;
	} /* Fim função: JOGO  &Recebe jogada */

/***************************************************************************
*
*  Função: JOGO  &Recebe jogadores
*  ****/

	JOGO_tpCondRet JOGO_RecebeJogadores(char * jogB, char * jogP)
	{
		if (jogoRodando)
		{
			return JOGO_CondRetJogoEmAndamento;
		}

		if (jogadorB != NULL)
		{
			free(jogadorB);
		}

		if (jogadorP != NULL)
		{
			free(jogadorP);
		}

		jogadorB = (char*)malloc((strlen(jogB) + 1) * sizeof(char));

		if (jogadorB == NULL)
		{
			return JOGO_CondRetFaltouMemoria;
		} /* if */

		strcpy(jogadorB, jogB);

		jogadorP = (char*)malloc((strlen(jogP) + 1) * sizeof(char));

		if (jogadorP == NULL)
		{
			return JOGO_CondRetFaltouMemoria;
		} /* if */

		strcpy(jogadorP, jogP);

		jogCorr = 'B';

		return JOGO_CondRetOK;
	} /* Fim função: JOGO  &Recebe jogadores */

/***************************************************************************
*
*  Função: JOGO  &Monta tabuleiro
*  ****/

	JOGO_tpCondRet JOGO_MontaTabuleiro(TAB_tppTabuleiro pTabuleiro)
	{
		TAB_tpCondRet condret;

		FILE * pFile;

		int i;

		char cor = 'u';
		char nome[4];
		char pCoordenada[3];

		char line[50];

		if (jogoRodando)
		{
			return JOGO_CondRetJogoEmAndamento;
		}

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
					condret = TAB_InserirPeca(&pTabuleiro, nome, cor, pCoordenada);
					if (condret != TAB_CondRetOK)
					{
						return condret;
					}
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

/***************************************************************************
*
*  Função: JOGO  &Inicia jogo
*  ****/

	JOGO_tpCondRet JOGO_IniciaJogo()
	{
		if (jogoRodando)
		{
			return JOGO_CondRetJogoEmAndamento;
		}

		if (jogadorB == NULL || jogadorP == NULL)
		{
			return JOGO_CondRetJogoNaoPodeIniciar;
		}

		jogoRodando = 1;
		return JOGO_CondRetOK;
	} /* Fim função: JOGO  &Inicia jogo */

/********** Fim do módulo de implementação: JOGO  Jogo de xadrez **********/

	//int main()
	//{
	//	char coordOrigem[4];
	//	char coordDestino[3];

	//	char jogBrancas[20];
	//	char jogPretas[20];

	//	TAB_tppTabuleiro pTabuleiro = NULL;

	//	TAB_CriarTabuleiro(&pTabuleiro);

	//	JOGO_MontaTabuleiro(pTabuleiro);

	//	printf("Nome do jogador das pecas brancas:\n");
	//	scanf("%s", jogBrancas);

	//	printf("Nome do jogador das pecas pretas:\n");
	//	scanf("%s", jogPretas);

	//	JOGO_RecebeJogadores(jogBrancas, jogPretas);

	//	jogoRodando = 1;
	//	
	//	while (jogoRodando)
	//	{
	//		JOGO_MostraTabuleiro(pTabuleiro);
	//		printf("Jogador %s, realize sua jogada (coord origem, coord destino) ou FIM para terminar:\n", (jogCorr=='B')?jogadorB:jogadorP);
	//		scanf("%s", coordOrigem);
	//		scanf("%s", coordDestino);
	//		JOGO_RecebeJogada(pTabuleiro, coordOrigem, coordDestino);
	//	}

	//	return 0;
	//}