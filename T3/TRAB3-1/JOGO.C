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
			return JOGO_CondRetMovimentoInvalido;
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
		condret = TAB_ObterListaAmeacados(&pTabuleiro, destino, &pLista);

		if (condret != TAB_CondRetOK)
		{
			return condret;
		}
		
		LIS_tpCondRet lisCondRet;

		printf("\nCasas ameacadas pela peca:\n");
		lisCondRet = LIS_IrProxElemento(pLista);
		if (lisCondRet != LIS_CondRetListaVazia)
		{
			lisCondRet = LIS_CondRetOK;
			for (LIS_AndarInicio(pLista); lisCondRet == LIS_CondRetOK; lisCondRet = LIS_IrProxElemento(pLista))
			{
				LIS_ObterElemento(pLista, (void**)&pValor);
				printf("%s\n", pValor);
			}
		}

		/* Ameaçantes */
		condret = TAB_ObterListaAmeacantes(&pTabuleiro, destino, &pLista);

		if (condret != TAB_CondRetOK)
		{
			return condret;
		}
		
		printf("\nCasas que ameacam a peca:\n");
		lisCondRet = LIS_IrProxElemento(pLista);
		if (lisCondRet != LIS_CondRetListaVazia)
		{
			lisCondRet = LIS_CondRetOK;
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

	JOGO_tpCondRet JOGO_MontaTabuleiro(TAB_tppTabuleiro pTabuleiro, char * nomeArq)
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

		pFile = fopen(nomeArq, "r");


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

/***************************************************************************
*
*  Função: JOGO  &Cheque mate
*  ****/

	JOGO_tpCondRet JOGO_ChequeMate(TAB_tppTabuleiro pTabuleiro)
	{
		TAB_tpCondRet tabCondret;
		LIS_tppLista pLista, pListaTemp;
		LIS_tpCondRet lisCondRet;
		char   pCor;
		char * pNome;
		char pCoordenada[3] = { 'A', '1', '\0' };
		char pCoorTemp[3];
		int i, j;
		int naoChequeMate = 1;

		if (!jogoRodando)
		{
			return JOGO_CondRetJogoParado;
		}

		if (pTabuleiro == NULL)
		{
			return JOGO_CondRetTabuleiroInexistente;
		}

		for (i = 0; i < 8; i++)
		{
			pCoordenada[0] = i + 65;

			for (j = 1; j <= 8; j++)
			{
				pCoordenada[1] = j + 48;

				tabCondret = TAB_ObterPeca(&pTabuleiro, pCoordenada, &pCor, &pNome);
				if (tabCondret == TAB_CondRetCasaInexistente)
				{
					return tabCondret;
				}

				if (strncmp(pNome, "k", 1) == 0)
				{
					if (pCor == jogCorr || pCor == jogCorr + 32)
					{
						i = j = 42;
					}
				}
			}
		}

		if (i != 42)
		{
			return JOGO_CondRetNaoExisteRei;
		}

		tabCondret = TAB_ObterListaAmeacantes(&pTabuleiro, pCoordenada, &pLista);
		if (tabCondret != TAB_CondRetOK)
		{
			return tabCondret;
		}


		lisCondRet = LIS_IrProxElemento(pLista);
		if (lisCondRet != LIS_CondRetListaVazia)
		{
			lisCondRet = LIS_CondRetOK;
			for (LIS_AndarInicio(pLista); lisCondRet == LIS_CondRetOK; lisCondRet = LIS_IrProxElemento(pLista))
			{
				LIS_ObterElemento(pLista, (void**)&pCoorTemp);
				tabCondret = TAB_ObterListaAmeacantes(&pTabuleiro, pCoorTemp, &pListaTemp);
				if (tabCondret != TAB_CondRetOK)
				{
					return tabCondret;
				}

				if (LIS_IrProxElemento(pListaTemp) == LIS_CondRetListaVazia)
				{
					naoChequeMate = 0;
				}
			}

			if (naoChequeMate)
			{
				printf("\n\nCHEQUE\n\n");
				return JOGO_CondRetNaoChequeMate;
			}

			for (i = 0; i < 8;i++)
			{ 
				strcpy(pCoorTemp, pCoordenada);
				switch (i)
				{
				case 0:
					pCoorTemp[0] -= 1;
					break;
				case 1:
					pCoorTemp[0] += 1;
					break;
				case 2:
					pCoorTemp[1] -= 1;
					break;
				case 3:
					pCoorTemp[1] += 1;
					break;
				case 4:
					pCoorTemp[0] -= 1;
					pCoorTemp[1] += 1;
					break;
				case 5:
					pCoorTemp[0] -= 1;
					pCoorTemp[1] -= 1;
					break;
				case 6:
					pCoorTemp[0] += 1;
					pCoorTemp[1] += 1;
					break;
				case 7:
					pCoorTemp[0] += 1;
					pCoorTemp[1] -= 1;
					break;
				}

				if (TAB_ObterPeca(&pTabuleiro, pCoorTemp, &pCor, &pNome) == TAB_CondRetCasaVazia)
				{
					tabCondret = TAB_ObterListaAmeacantes(&pTabuleiro, pCoorTemp, &pListaTemp);
					if (tabCondret != TAB_CondRetOK)
					{
						return tabCondret;
					}

					if (LIS_IrProxElemento(pLista) == LIS_CondRetListaVazia)
					{
						printf("\n\nCHEQUE\n\n");
						return JOGO_CondRetNaoChequeMate;
					}
				}
			}
			printf("\n\nCHEQUE MATE\n\n");
			jogoRodando = 0;
			return JOGO_CondRetChequeMate;
		}
		printf("\n\nCHEQUE\n\n");
		return JOGO_CondRetNaoChequeMate;
	}/* Fim função: JOGO  &Cheque mate */

/********** Fim do módulo de implementação: JOGO  Jogo de xadrez **********/

	//int main()
	//{
	//	char coordOrigem[4];
	//	char coordDestino[3];

	//	char jogBrancas[20];
	//	char jogPretas[20];

	//	TAB_tppTabuleiro pTabuleiro = NULL;

	//	TAB_CriarTabuleiro(&pTabuleiro);

	//	JOGO_MontaTabuleiro(pTabuleiro, "PecasTabuleiro.txt");

	//	printf("Nome do jogador das pecas brancas:\n");
	//	scanf("%s", jogBrancas);

	//	printf("Nome do jogador das pecas pretas:\n");
	//	scanf("%s", jogPretas);

	//	JOGO_RecebeJogadores(jogBrancas, jogPretas);

	//	jogoRodando = 1;
	//	
	//	JOGO_MostraTabuleiro(pTabuleiro);
	//	JOGO_ChequeMate(pTabuleiro);

	///*	while (jogoRodando)
	//	{
	//		JOGO_MostraTabuleiro(pTabuleiro);
	//		printf("Jogador %s, realize sua jogada (coord origem, coord destino) ou FIM para terminar:\n", (jogCorr=='B')?jogadorB:jogadorP);
	//		scanf("%s", coordOrigem);
	//		scanf("%s", coordDestino);
	//		JOGO_RecebeJogada(pTabuleiro, coordOrigem, coordDestino);
	//		JOGO_ChequeMate(pTabuleiro);
	//	}*/

	//	return 0;
	//}