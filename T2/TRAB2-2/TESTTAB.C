/***************************************************************************
*  $MCI Módulo de implementação: TTAB Teste tabuleiro de xadrez
*
*  Arquivo gerado:              TestTAB.c
*  Letras identificadoras:      TTAB
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
*     Versão  Autor      Data     Observações
*     1        mmq   02/out/2016  início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Tabuleiro.h"


static const char CRIAR_TABULEIRO_CMD         [ ] = "=criarTab"		;
static const char INSERIR_PECA_CMD            [ ] = "=inserirPeca"	;
static const char MOVER_PECA_CMD			  [ ] = "=moverPeca"	;
static const char RETIRAR_PECA_CMD			  [	] = "=retirarPeca"	;
static const char OBTER_PECA_CMD			  [ ] = "=obterPeca"	;
static const char OBTER_LIS_AMDO_CMD		  [ ] = "=obterLisAmdo"	;
static const char OBTER_LIS_AMTE_CMD		  [ ] = "=obterLisAmte"	;
static const char DESTRUIR_TABULEIRO_CMD      [ ] = "=destruirTab"	;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define NULO     0
#define NAO_NULO 1

#define DIM_VT_TABULEIRO   10

#define DIM_VALOR     100

TAB_tppTabuleiro vtTabuleiros[DIM_VT_TABULEIRO];

/***** Protótipos das funções encapuladas no módulo *****/

static int  ValidarInxTab( int inxTab , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TTAB &Testar tabuleiro
*
*  $ED Descrição da função
*     Podem ser criadas até 10 tabuleiros, identificados pelos índices 0 a 9
*
*     Comandos disponíveis:
*
*     =criarTab			inxTabuleiro		CondRetEsp
*     =inserirPeca		inxTabuleiro		CondRetEsp 
*     =moverPeca		inxTabuleiro		CondRetEsp
*     =retirarPeca		inxTabuleiro		CondRetEsp
*     =obterPeca		inxTabuleiro		CondRetEsp
*     =obterLisAmdo		inxTabuleiro		CondRetEsp
*     =obterLisAmte		inxTabuleiro		CondRetEsp
*     =destruirTab		inxTabuleiro		CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int inxTab   = -1 ,
		numLidos   = -1 ,
		CondRetEsp = -1  ;

	TST_tpCondRet CondRet = TST_CondRetOK;
	TST_tpCondRet CondRetAux;

	char IdListaDado[DIM_VALOR];

	/* TAB  &Criar tabuleiro */

		if ( strcmp( ComandoTeste , CRIAR_TABULEIRO_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxTab, &CondRetEsp );

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxTab( inxTab , VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			CondRet = TAB_CriarTabuleiro( &vtTabuleiros[inxTab] );

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao criar tabuleiro." ) ;

		} /* fim ativa: TAB  &Criar tabuleiro */


	/* TAB  &Inserir peca */

		if ( strcmp( ComandoTeste , INSERIR_PECA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxTab, &CondRetEsp );

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxTab( inxTab , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			//CondRet = TAB_InserirPeca( &vtTabuleiros[inxTab] );

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao inserir peca." ) ;

		} /* fim ativa: TAB  &Inserir peca */


	/* TAB  &Mover peca */

		if ( strcmp( ComandoTeste , MOVER_PECA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxTab, &CondRetEsp );

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxTab( inxTab , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			//CondRet = TAB_MoverPeca(&vtTabuleiros[inxTab]);

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao mover peca." ) ;

		} /* fim ativa: TAB  &Mover peca */


	/* TAB  &Retirar peca */

		if ( strcmp( ComandoTeste , RETIRAR_PECA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxTab, &CondRetEsp );

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxTab( inxTab , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			//CondRet = TAB_RetirarPeca( &vtTabuleiros[inxTab] );

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao retirar peca." ) ;

		} /* fim ativa: TAB  &Retirar peca */


	/* TAB  &Obter peca */

		if ( strcmp( ComandoTeste , OBTER_PECA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxTab, &CondRetEsp );

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxTab( inxTab , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			//CondRet = TAB_ObterPeca( &vtTabuleiros[inxTab] );

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao obter peca." ) ;

		} /* fim ativa: TAB  &Obter peca */


	/* TAB  &Obter lista ameaçantes */

		if ( strcmp( ComandoTeste , OBTER_LIS_AMTE_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxTab, &CondRetEsp );

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxTab( inxTab , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			//CondRet = TAB_ObterListaAmeacantes(&vtTabuleiros[inxTab]);

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao obter lista ameacantes." ) ;

		} /* fim ativa: TAB  &Obter lista ameaçantes */


	/* TAB  &Obter lista ameaçados */

		if ( strcmp( ComandoTeste , OBTER_LIS_AMDO_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxTab, &CondRetEsp );

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxTab( inxTab , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			//CondRet = TAB_ObterListaAmeacados(&vtTabuleiros[inxTab]);

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao obter lista ameacados." ) ;

		} /* fim ativa: TAB  &Obter lista ameaçados */



	/* TAB  &Destruir tabuleiro */

		else if ( strcmp( ComandoTeste , DESTRUIR_TABULEIRO_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxTab, &CondRetEsp );

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxTab( inxTab , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			CondRet = TAB_DestruirTabuleiro( &vtTabuleiros[inxTab] );

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao destruir tabuleiro." ) ;

		} /* fim ativa: TAB  &Destruir tabuleiro */

		

	return TST_CondRetNaoConhec ;
} /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS -Validar indice do tabuleiro
*
***********************************************************************/

int ValidarInxTab( int inxTab , int Modo )
{

	if (   ( inxTab <  0 )
		|| ( inxTab >= DIM_VT_TABULEIRO ) )
	{
		return FALSE ;
	} /* if */

	if ( Modo == VAZIO )
	{
		if ( vtTabuleiros[ inxTab ] != NULL )
		{
			return FALSE ;
		} /* if */
	} else
	{
		if ( vtTabuleiros[ inxTab ] == NULL )
		{
			return FALSE ;
		} /* if */
	} /* if */

	return TRUE ;

} /* Fim função: TLIS -Validar indice do tabuleiro */

/********** Fim do módulo de implementação: TTAB Teste tabuleiro de xadrez **********/

