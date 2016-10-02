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
*
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
#undef TABULEIRO_OWN

#define pathArquivo "PecasXadrez.txt"

#define FALSE 0
#define TRUE  1

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

	static void DestruirValorMatriz(void * pValor); 

	static void DestruirValorCasa(void * pValor);

	static tpCasa * CriarCasa(); 

	static LIS_tppLista LerArquivoPecas();

	static int ValidarCor( char cor );

	static int ValidarCoordenada( char * pCoordenada );

	static tpCasa * MoverCorrente(LIS_tppLista pLista, char * pCoordenada);

	static int ValidarNome(LIS_tppLista pLista, char * nome);

	static int validarMovimento(TAB_tppTabuleiro pTabuleiro, char * origem, char * destino);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TAB  &Criar tabuleiro
*  ****/

   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro * pTabuleiro)
   {
	   int i, j;

	   TAB_tppTabuleiro pTabuleiroTemp;
	   LIS_tpCondRet    CondRet;

	   pTabuleiroTemp = (TAB_tpTabuleiro *)malloc(sizeof(TAB_tpTabuleiro));
	   if (pTabuleiroTemp == NULL)
	   {
		   return TAB_CondRetFaltouMemoria;
	   } /* if */

	   pTabuleiroTemp->pPecas = LerArquivoPecas();
	   CondRet = LIS_CriarLista("matx", DestruirValorMatriz, &pTabuleiroTemp->pMatriz);
	   if (CondRet != TAB_CondRetOK)
	   {
		   return TAB_CondRetFaltouMemoria;
	   } /* if */

	   for (i = 0; i < 8; i++)
	   {
		   LIS_tppLista pListaColunaTemp;

		   char id = (i + '0');

		   CondRet = LIS_CriarLista( &id, DestruirValorCasa, &pListaColunaTemp );
		   if (CondRet != TAB_CondRetOK)
		   {
			   return TAB_CondRetFaltouMemoria;
		   } /* if */

		   for (j = 0; j < 8; j++)
		   {
			   CondRet = LIS_InserirElemento(pListaColunaTemp, CriarCasa());
			   if (CondRet != TAB_CondRetOK)
			   {
				   return TAB_CondRetFaltouMemoria;
			   } /* if */
		   }

		   CondRet = LIS_InserirElemento(pTabuleiroTemp->pMatriz, pListaColunaTemp);
		   if (CondRet != TAB_CondRetOK)
		   {
			   return TAB_CondRetFaltouMemoria;
		   } /* if */
	   }

	   *pTabuleiro = pTabuleiroTemp;

	   return TAB_CondRetOK;

   } /* Fim função: TAB  &Criar tabuleiro */


/***************************************************************************
*
*  Função: TAB  &Inserir peca
*  ****/

   TAB_tpCondRet TAB_InserirPeca(TAB_tppTabuleiro * pTabuleiro, char * pNome, char cor, char * pCoordenada)
   {
	   tpCasa * pCasa;

	   TAB_tppTabuleiro pTabTemp;

	   if (pTabuleiro == NULL)
	   {
		   return TAB_CondRetNaoExiste;
	   } /* if */
	   
	   pTabTemp = *pTabuleiro;

	   if ( ! ValidarCor( cor ) )
	   {
		   return TAB_CondRetCorInexistente;
	   } /* if */

	   if ( ! ValidarCoordenada( pCoordenada ) )
	   {
		   return TAB_CondRetCasaInexistente;
	   } /* if */
		
	   if (!ValidarNome(pTabTemp->pPecas, pNome))
	   {
		   return TAB_CondRetPecaInexistente;
	   } /* if */

	   pCasa = MoverCorrente(pTabTemp->pMatriz,pCoordenada);
	   pCasa->cor = cor;
	   strcpy(pCasa->nome, pNome);
	   pCasa->primeiroMov = 1;

	   return TAB_CondRetOK;

   } /* Fim função: TAB  &Inserir peca */


/***************************************************************************
*
*  Função: TAB  &Retirar peca
*  ****/

   TAB_tpCondRet TAB_RetirarPeca(TAB_tppTabuleiro * pTabuleiro, char * pCoordenada)
   {
	   tpCasa * pCasa;
	   TAB_tppTabuleiro pTabTemp;

	   if (pTabuleiro == NULL)
	   {
		   return TAB_CondRetNaoExiste;
	   } /* if */

	   pTabTemp = *pTabuleiro;

	   if ( ! ValidarCoordenada( pCoordenada ) )
	   {
		   return TAB_CondRetCasaInexistente;
	   } /* if */

	   pCasa = MoverCorrente(pTabTemp->pMatriz, pCoordenada);
	   pCasa->cor = 'u';
	   strcpy(pCasa->nome, "xxxx");

	   return TAB_CondRetOK;

   } /* Fim função: TAB  &Retirar peca */


/***************************************************************************
*
*  Função: TAB  &Obter peca
*  ****/

   TAB_tpCondRet TAB_ObterPeca(TAB_tppTabuleiro * pTabuleiro, char * pCoordenada, char * pCor, char ** pNome)
   {
	   tpCasa * pCasa;
	   TAB_tppTabuleiro pTabTemp;

	   if (pTabuleiro == NULL)
	   {
		   return TAB_CondRetNaoExiste;
	   } /* if */

	   pTabTemp = *pTabuleiro;

	   if ( ! ValidarCoordenada( pCoordenada ) )
	   {
		   return TAB_CondRetCasaInexistente;
	   } /* if */

	   pCasa = MoverCorrente( pTabTemp->pMatriz, pCoordenada );
	   *pCor = pCasa->cor;

	   strcpy(*pNome, pCasa->nome);

	   return TAB_CondRetOK;

   } /* Fim função: TAB  &Obter peca */


/***************************************************************************
*
*  Função: TAB  &Obter lista ameaçantes
*  ****/

   TAB_tpCondRet TAB_ObterListaAmeacantes(TAB_tppTabuleiro * pTabuleiro, char * pCoordenada, LIS_tppLista * pLista)
   {
	   tpCasa * pCasa;
	   TAB_tppTabuleiro pTabTemp;

	   if (pTabuleiro == NULL)
	   {
		   return TAB_CondRetNaoExiste;
	   } /* if */

	   pTabTemp = *pTabuleiro;

	   if (! ValidarCoordenada( pCoordenada ) )
	   {
		   return TAB_CondRetCasaInexistente;
	   } /* if */

	   pCasa   = MoverCorrente(pTabTemp->pMatriz, pCoordenada);
	   *pLista = pCasa->pAmeacantes;

	   return TAB_CondRetOK;

   } /* Fim função: TAB  &Obter lista ameacantes */


/***************************************************************************
*
*  Função: TAB  &Obter lista ameaçados
*  ****/

   TAB_tpCondRet TAB_ObterListaAmeacados(TAB_tppTabuleiro * pTabuleiro, char * pCoordenada, LIS_tppLista * pLista)
   {
	   tpCasa * pCasa;
	   TAB_tppTabuleiro pTabTemp;

	   if (pTabuleiro == NULL)
	   {
		   return TAB_CondRetNaoExiste;
	   } /* if */

	   pTabTemp = *pTabuleiro;

	   if ( ! ValidarCoordenada( pCoordenada ) )
	   {
		   return TAB_CondRetCasaInexistente;
	   } /* if */

	   pCasa   = MoverCorrente(pTabTemp->pMatriz, pCoordenada);
	   *pLista = pCasa->pAmeacados;

	   return TAB_CondRetOK;

   } /* Fim função: TAB  &Obter lista ameacados */


/***************************************************************************
*
*  Função: TAB  &Destruir tabuleiro
*  ****/

   TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tppTabuleiro pTabuleiro)
   {
	   if ( pTabuleiro == NULL)
	   {
		   return TAB_CondRetNaoExiste;
	   } /* if */

	   LIS_DestruirLista(pTabuleiro->pMatriz);
	   LIS_DestruirLista(pTabuleiro->pPecas);
	   free(pTabuleiro);

	   return TAB_CondRetOK;

   } /* Fim função: TAB  &Destruir tabuleiro */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor peca
*
***********************************************************************/

	void DestruirValorPeca(void * pValor)
	{
		tpPeca * tempPeca = (tpPeca*)pValor;
		LIS_DestruirLista( tempPeca->pAndar );
		LIS_DestruirLista( tempPeca->pComer );
		free(pValor);
	} /* Fim função: TAB -Destruir valor peca*/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor generico
*
***********************************************************************/

	void DestruirValorGenerico(void * pValor)
	{
		free( pValor );
	} /* Fim função: TAB -Destruir valor generico*/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor matriz
*
***********************************************************************/

	void DestruirValorMatriz(void * pValor)
	{
		LIS_DestruirLista( (LIS_tppLista) pValor );
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

	tpCasa * CriarCasa()
	{
		tpCasa * pCasa;
		pCasa = (tpCasa*)malloc(sizeof(tpCasa));
		pCasa->primeiroMov = 0;
		pCasa->cor = 'u';
		strcpy(pCasa->nome,"xxxx");

		LIS_CriarLista( "amdo", DestruirValorGenerico, &pCasa->pAmeacados  );
		LIS_CriarLista( "amte", DestruirValorGenerico, &pCasa->pAmeacantes );

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
		//LIS_tppLista lisTemp;

		tpPeca* pecaTemp;
		tpMovimentoPeca* movPeca;

		FILE * pFile = fopen(pathArquivo, "r");
		char line[50];

		LIS_CriarLista("p", DestruirValorPeca, &lisPecas);

		if (pFile == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
		else
			while (fgets(line, sizeof(line), pFile) != NULL)
			{
				if (strncmp(line, ">>>>>>>>>>", 10) == 0)
				{

					pecaTemp = ( tpPeca * ) malloc( sizeof( tpPeca ) );
				
					pecaTemp->cor = 'u';

					LIS_CriarLista( "a", DestruirValorGenerico, &pecaTemp->pAndar );

					LIS_CriarLista( "c", DestruirValorGenerico, &pecaTemp->pComer );

				}
				else if (strncmp(line, "Nome", 4) == 0)
				{
					int i;
					strncpy(pecaTemp->nome, &line[5], 4);

					for (i = 0; i < 4; i++)
					{
						if (pecaTemp->nome[i] == '\n')
						{
							pecaTemp->nome[i] = '\0';
						}
					}

					printf("%s\n", pecaTemp->nome);
				}
				else if ((strncmp(line, "--Andar", 7) == 0) || (strncmp(line, "--Comer", 7) == 0))
				{
					movPeca = ( tpMovimentoPeca * ) malloc( sizeof( tpMovimentoPeca ) );
				}
				else if (strncmp(line, "Oeste", 5) == 0)
				{
					movPeca->coordenadas[0] = (int)line[6] - '0';
				}
				else if (strncmp(line, "Norte", 5) == 0)
				{
					movPeca->coordenadas[1] = (int)line[6] - '0';
				}
				else if (strncmp(line, "Leste", 5) == 0)
				{
					movPeca->coordenadas[2] = (int)line[6] - '0';
				}
				else if (strncmp(line, "Sul", 3) == 0)
				{
					movPeca->coordenadas[3] = (int)line[4] - '0';
				}
				else if (strncmp(line, "Max", 3) == 0)
				{
					movPeca->max = (int)line[4] - '0';
				}
				else if (strncmp(line, "Min", 3) == 0)
				{
					movPeca->min = (int)line[4] - '0';
				}
				else if (strncmp(line, "Primeiro", 8) == 0)
				{
					movPeca->primeiroMov = (int)line[9] - '0';
				}
				else if (strncmp(line, "--FimAndar", 10) == 0)
				{	
					printf("---------\nAndar\ncoord = %d %d %d %d\nmax = %d\nmin = %d\nprim = %d\n", movPeca->coordenadas[0], movPeca->coordenadas[1], movPeca->coordenadas[2], movPeca->coordenadas[3], movPeca->max, movPeca->min, movPeca->primeiroMov);
					LIS_InserirElemento(pecaTemp->pAndar, movPeca);
				}
				else if (strncmp(line, "--FimComer", 10) == 0)
				{
					printf("---------\nComer\ncoord = %d %d %d %d\nmax = %d\nmin = %d\nprim = %d\n", movPeca->coordenadas[0], movPeca->coordenadas[1], movPeca->coordenadas[2], movPeca->coordenadas[3], movPeca->max, movPeca->min, movPeca->primeiroMov);
					LIS_InserirElemento(pecaTemp->pComer, movPeca);
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

/***********************************************************************
*
*  $FC Função: TAB  -Validar Cor
*
***********************************************************************/

	int ValidarCor( char cor )
	{
		if (cor != 'p' && cor != 'b' && cor != 'P' && cor != 'B')
		{
			return FALSE;
		} /* if */

		return TRUE;
	}

/***********************************************************************
*
*  $FC Função: TAB  -Validar Coordenada
*
***********************************************************************/

	int ValidarCoordenada( char * pCoordenada )
	{
		if ( ! ( pCoordenada[0] >= 'A' && pCoordenada[0] <= 'H' ) ||
		     ! ( pCoordenada[0] <= 'a' && pCoordenada[0] >= 'h' ) )
		{
			return FALSE;
		} /* if */

		if ( ! ( pCoordenada[1] >= '1' && pCoordenada[1] <= '8' ) )
		{
			return FALSE;
		} /* if */

		return TRUE;
	}

/***********************************************************************
*
*  $FC Função: TAB  -Mover corrente
*
***********************************************************************/

	tpCasa * MoverCorrente(LIS_tppLista pLista, char * pCoordenada)
	{
		int linha, coluna, i;
		tpCasa * pCasa;
		LIS_tppLista pListaCasa;

		coluna = ( pCoordenada[0] < 97) ? pCoordenada[0] - 65 : pCoordenada[0] - 97;
		linha  = pCoordenada[1] - 48;

		LIS_AndarInicio(pLista);
		for (i = 0; i < coluna; i ++ )
		{
			LIS_IrProxElemento(pLista);
		}

		LIS_ObterElemento(pLista, (void**) &pListaCasa);
		for (i = 0; i < linha; i++)
		{
			LIS_IrProxElemento(pListaCasa);
		}

		LIS_ObterElemento( pListaCasa, (void**) &pCasa);

		return pCasa;

	}

/***********************************************************************
*
*  $FC Função: TAB  -Validar nome
*
***********************************************************************/

	int ValidarNome(LIS_tppLista pLista, char * nome)
	{
		LIS_tpCondRet CondRet = LIS_CondRetOK;
		tpPeca * pPeca;
		for (LIS_AndarInicio(pLista); CondRet != LIS_CondRetFimLista; CondRet = LIS_IrProxElemento(pLista))
		{
			LIS_ObterElemento(pLista, &pPeca);
			if (strcmp(nome, pPeca->nome) == 0)
			{
				return TRUE;
			}
		}
		return FALSE;
	}

/***********************************************************************
*
*  $FC Função: TAB  -Validar movimento
*
***********************************************************************/

	int validarMovimento(TAB_tppTabuleiro pTabuleiro, char * origem, char * destino)
	{
		char nomePeca[4];
		char cor;
		char pAlcance[2];

		int comer, i, colidiu, foraTab, branco;

		LIS_tppLista pMovimento;
		LIS_tpCondRet CondRet;

		tpPeca * pPeca;
		tpMovimentoPeca * pMov;

		tpCasa * pCasaOrigem;
		tpCasa * pCasaDestino;
		tpCasa * pCasaTemp;

		pCasaOrigem = MoverCorrente(pTabuleiro->pMatriz, origem);
		pCasaDestino = MoverCorrente(pTabuleiro->pMatriz, destino);

		comer = strcmp(pCasaDestino->nome, "xxxx") ? 1 : 0;
		branco = (pCasaDestino->cor != 'b' || pCasaDestino->cor != 'B') ? -1 : 1;

		strcpy(nomePeca, pCasaOrigem->nome);

		cor = pCasaOrigem->cor;
		pMovimento = pPeca->pComer;

		for (LIS_AndarInicio(pTabuleiro->pPecas); CondRet != LIS_CondRetFimLista; CondRet = LIS_IrProxElemento(pTabuleiro->pPecas))
		{
			LIS_ObterElemento(pTabuleiro->pPecas, &pPeca);
			if (strcmp(nomePeca, pPeca->nome) == 0)
			{
				pMovimento = comer ? pPeca->pComer : pPeca->pAndar;
				break;
			}
		}

		for (LIS_AndarInicio(pMovimento); CondRet != LIS_CondRetFimLista; CondRet = LIS_IrProxElemento(pMovimento))
		{
			LIS_ObterElemento(pMovimento, &pMov);

			// confere primeiro movimento
			if (pMov->primeiroMov && !MoverCorrente(pTabuleiro->pMatriz, pAlcance)->primeiroMov)
			{
				continue;
			}

			pAlcance[0] = origem[0] + branco*(pMov->coordenadas[1] - 48) - branco*(pMov->coordenadas[3] - 48);
			pAlcance[1] = origem[0] + branco*(pMov->coordenadas[0] - 48) - branco*(pMov->coordenadas[2] - 48);

			foraTab = 0;
			colidiu = 0;

			// primeiro passo
			if (!ValidarCoordenada(pAlcance))
			{
				continue;
			}
			pCasaTemp = MoverCorrente(pTabuleiro->pMatriz, pAlcance);
			if (strcmp(pCasaTemp->nome, "xxxx") && !comer)
			{
				continue;
			}

			// min
			for (i = 1; i < pMov->min; i++)
			{
				pAlcance[0] = pAlcance[0] + branco*(pMov->coordenadas[1] - 48) - branco*(pMov->coordenadas[3] - 48);
				pAlcance[1] = pAlcance[0] + branco*(pMov->coordenadas[0] - 48) - branco*(pMov->coordenadas[2] - 48);
				if (!ValidarCoordenada(pAlcance))
				{
					foraTab = 1;
					continue;
				}
				pCasaTemp = MoverCorrente(pTabuleiro->pMatriz, pAlcance);
				if (strcmp(pCasaTemp->nome, "xxxx"))
				{
					if (strcmp(pAlcance, destino))
					{
						colidiu = 1;
					}
				}
			}

			if (foraTab || colidiu)
			{
				continue;
			}
			if (!strcmp(pAlcance, destino))
			{
				return TRUE;
			}

			//max
			for (i = pMov->min; i < pMov->max; i++)
			{
				pAlcance[0] = pAlcance[0] + branco*(pMov->coordenadas[1] - 48) - branco*(pMov->coordenadas[3] - 48);
				pAlcance[1] = pAlcance[0] + branco*(pMov->coordenadas[0] - 48) - branco*(pMov->coordenadas[2] - 48);
				if (!strcmp(pAlcance, destino) && !colidiu)
				{
					return TRUE;
				}
				if (!ValidarCoordenada(pAlcance))
				{
					foraTab = 1;
					continue;
				}
				pCasaTemp = MoverCorrente(pTabuleiro->pMatriz, pAlcance);
				if (strcmp(pCasaTemp->nome, "xxxx"))
				{
					colidiu = 1;
				}
			}
		}

		return FALSE;
	}

	/*int main()
	{
		TAB_tppTabuleiro oi;

		TAB_CriarTabuleiro(&oi);

		printf("%d\n",TAB_InserirPeca(&oi, "a", 'B',"K9"));

		return 0;
	}*/