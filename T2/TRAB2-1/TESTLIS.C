/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs - Arndt Von Staa
*           mmq - Matheus de Mello Queiroz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  X		  fpf	24/set/2016	Incluido teste da LIS_AlterarElemento
*     5       mmq   11/set/2016 alterar a função LIS_ProcuraValor
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"


static const char CRIAR_LISTA_CMD         [ ] = "=criarLista"        ;
static const char OBTER_ID_LISTA_CMD      [ ] = "=obterIdLista"      ;
static const char INSERIR_NO_CMD          [ ] = "=inserirNo"         ;
static const char OBTER_NO_CMD            [ ] = "=obterNo"           ;
static const char EXCLUIR_NO_CMD          [ ] = "=excluirNoCorrente" ;
static const char IR_PROX_CMD             [ ] = "=irProx"            ;
static const char IR_ANT_CMD              [ ] = "=irAnt"             ;
static const char ALTERAR_NO_CMD		  [ ] = "=alterarNoCorrente" ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destroiLista"      ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define NULO     0
#define NAO_NULO 1

#define DIM_VT_LISTA   10
#define DIM_ID_LISTA   5

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

static void DestruirValor( void * pValor ) ;

static int  ValidarInxLista( int inxLista , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarLista                   inxLista  string   CondRetEsp
*     =obterIdLista                 inxLista  string  
*     =inserirNo                    inxLista  char     CondRetEsp  
*     =obterNo                      inxLista  char     CondRetPonteiro
*     =excluirNoCorrente            inxLista
*     =irProx                       inxLista           CondRetEsp
*     =irAnt                        inxLista           CondRetEsp
*	  =alterarNoCorrente			inxLista  char	   CondRetEsp
*     =destroiLista                 inxLista           CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{

	int inxLista   = -1 ,
		numLidos   = -1 ,
		CondRetEsp = -1  ;

	TST_tpCondRet CondRet ;

	char StringIdLista[ DIM_ID_LISTA ] ;
	char * pIdLista;

	char   CharDado ;
	char * pDado ;

	int ValEsp = -1 ;
	
	int numElem = -1 ;
	

	/* LIS  &Criar lista */

		if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "isi" ,
					&inxLista, StringIdLista, &CondRetEsp ) ;

			if (   ( numLidos != 3 )
				|| ( ! ValidarInxLista( inxLista , VAZIO ) ) 
				|| ( strlen( StringIdLista ) > DIM_ID_LISTA-1 ) )
			{
				return TST_CondRetParm ;
			} /* if */

			vtListas[ inxLista ] =
					LIS_CriarLista( StringIdLista, DestruirValor ) ;

			if( vtListas[ inxLista ] == NULL )
			{
				CondRet = TST_CondRetMemoria;
			}
			else
			{
				CondRet = TST_CondRetOK;
			}

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao criar lista." ) ;

		} /* fim ativa: LIS  &Criar lista */

	/* LIS  &Destruir lista */

		else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" ,
					&inxLista, &CondRetEsp ) ;

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxLista( inxLista , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			if ( vtListas[ inxLista ] == NULL )
			{
				return TST_CompararInt(CondRetEsp, LIS_CondRetNaoExiste,
					"Lista deveria existir.");
			} /* if */
			else
			{
				if (CondRetEsp != LIS_CondRetOK)
				{
					return TST_CompararInt(CondRetEsp, LIS_CondRetOK,
						"Lista nao deveria existir.");
				} /* if */
			} /* if */

			LIS_DestruirLista( vtListas[ inxLista ] ) ;

			vtListas[ inxLista ] = NULL ;

			return TST_CondRetOK ;

		} /* fim ativa: LIS  &Destruir lista */

	/* LIS  &Obter referência para o identificador da lista */

		else if ( strcmp( ComandoTeste , OBTER_ID_LISTA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "is" ,
					&inxLista, StringIdLista ) ;

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxLista( inxLista , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			pIdLista = ( char * ) LIS_ObterId( vtListas[ inxLista ] );
			if ( pIdLista == NULL )
			{
				return TST_CompararPonteiroNulo( NAO_NULO , pIdLista ,
						"Indice da lista deveria existir." ) ;
			} /* if */

			return TST_CompararString( StringIdLista , pIdLista ,
					"Valor do indice da lista errado." ) ;

		} /* fim ativa: LIS  &Obter referência para o identificador da lista */

	/* Testar inserir elemento */

		else if ( strcmp( ComandoTeste , INSERIR_NO_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ici" ,
					&inxLista , &CharDado , &CondRetEsp ) ;

			if (   ( numLidos != 3 )
				|| ( ! ValidarInxLista( inxLista , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			pDado = ( char * ) malloc( sizeof( char ) ) ;
			if ( pDado == NULL )
			{
				return TST_CondRetMemoria ;
			} /* if */

			*pDado = CharDado;

			CondRet = LIS_InserirElemento( vtListas[ inxLista ] , pDado ) ;

			if ( CondRet != LIS_CondRetOK )
			{
				free( pDado ) ;
			} /* if */

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao inserir no." ) ;

		} /* fim ativa: Testar inserir elemento */

	/* LIS  &Excluir elemento */

		else if ( strcmp( ComandoTeste , EXCLUIR_NO_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "i" ,
					&inxLista ) ;

			if (   ( numLidos != 1 )
				|| ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
			{
				return TST_CondRetParm ;
			} /* if */

			CondRet = LIS_ExcluirElemento( vtListas[ inxLista ] );

			return TST_CompararInt( LIS_CondRetOK, CondRet,
					"A lista está vazia." );

		} /* fim ativa: LIS  &Excluir elemento */

	/* LIS  &Obter referência para o valor contido no elemento */

		else if ( strcmp( ComandoTeste , OBTER_NO_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ici" ,
					&inxLista , &CharDado , &CondRetEsp ) ;

			if (   ( numLidos != 3 )
				|| ( ! ValidarInxLista( inxLista , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			pDado = ( char * ) LIS_ObterElemento( vtListas[ inxLista ] ) ;

			if ( pDado == NULL )
			{
				return TST_CompararInt( CondRetEsp , LIS_CondRetListaVazia ,
						"Nó deveria existir." ) ;
			} /* if */
			else
			{
				if( CondRetEsp != LIS_CondRetOK )
				{
					return TST_CompararInt( CondRetEsp , LIS_CondRetOK ,
							"Nó nao deveria existir." ) ;
				} /* if */
			} /* if */

			return TST_CompararChar( CharDado , *pDado ,
					"Valor no Nó errado." ) ;

		} /* fim ativa: LIS  &Obter referência para o valor contido no elemento */

	/* LIS  &Ir para o proximo elemento */

		else if ( strcmp( ComandoTeste , IR_PROX_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , 
					&inxLista , &CondRetEsp ) ;

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxLista( inxLista , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			return TST_CompararInt( CondRetEsp , LIS_IrProxElemento( vtListas[ inxLista ] ) ,
					"Condicao de retorno errada ao ir para o proximo nó." ) ;

		} /* fim ativa: LIS  &Ir para o proximo elemento */

	/* LIS  &Ir para o proximo elemento */

		else if ( strcmp( ComandoTeste , IR_ANT_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , 
				&inxLista , &CondRetEsp ) ;

			if (    ( numLidos != 2 )
				|| ( ! ValidarInxLista( inxLista , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			return TST_CompararInt( CondRetEsp , LIS_IrAntElemento( vtListas[ inxLista ] ) ,
				"Condicao de retorno errada ao ir para o proximo nó." ) ;

		} /* fim ativa: LIS  &Ir para o proximo elemento */

	/* LIS  &Alterar o valor contido no elemento */

		else if (strcmp(ComandoTeste, ALTERAR_NO_CMD) == 0)
		{

			numLidos = LER_LerParametros("ici",
				&inxLista, &CharDado, &CondRetEsp);

			if ((numLidos != 3)
				|| (!ValidarInxLista(inxLista, NAO_VAZIO)))
			{
				return TST_CondRetParm;
			} /* if */

			if (vtListas[inxLista] == NULL)
			{
				return TST_CompararInt(CondRetEsp, LIS_CondRetNaoExiste,
					"Lista deveria existir.");
			} /* if */

			pDado = (char *)malloc(sizeof(char));

			if (pDado == NULL)
			{
				return TST_CondRetMemoria;
			} /* if */

			*pDado = CharDado;

			CondRet = LIS_AlterarElemento(vtListas[inxLista],pDado);

			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao alterar nó corrente.");

		} /* fim ativa: LIS  &Alterar o valor contido no elemento */


	return TST_CondRetNaoConhec ;

} /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

void DestruirValor( void * pValor )
{

	free( pValor ) ;

} /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
*
***********************************************************************/

int ValidarInxLista( int inxLista , int Modo )
{

	if ( ( inxLista <  0 )
		|| ( inxLista >= DIM_VT_LISTA ))
	{
		return FALSE ;
	} /* if */

	if ( Modo == VAZIO )
	{
		if ( vtListas[ inxLista ] != NULL )
		{
			return FALSE ;
		} /* if */
	} else
	{
		if ( vtListas[ inxLista ] == NULL )
		{
			return FALSE ;
		} /* if */
	} /* if */

	return TRUE ;

} /* Fim função: TLIS -Validar indice de lista */

/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

