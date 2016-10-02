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
*  Autores: fpf - Felipe Pessoa de Freitas
*           mmq - Matheus de Mello Queiroz
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



static const char CRIAR_TABULEIRO_CMD         [ ] = "=criarTab";
static const char INSERIR_PECA_CMD            [ ] = "=inserirPeca";
static const char DESTRUIR_TABULEIRO_CMD      [ ] = "=destruirTab";





#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define NULO     0
#define NAO_NULO 1

#define DIM_VT_LISTA   10

#define DIM_VALOR     100

TAB_tppTabuleiro vtTabuleiros[ DIM_VT_LISTA ];

/***** Protótipos das funções encapuladas no módulo *****/

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
*     =criarTab    inxTabuleiro CondRetEsp
*     =destruirTab inxTabuleiro CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int inxLista   = -1 ,
		numLidos   = -1 ,
		CondRetEsp = -1  ;

	TST_tpCondRet CondRet ;
	TST_tpCondRet CondRetAux;

	char IdListaDado[DIM_VALOR];

	/* LIS  &Criar tabuleiro */

		if ( strcmp( ComandoTeste , CRIAR_TABULEIRO_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxLista, &CondRetEsp );

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxLista( inxLista , VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			CondRet = TAB_CriarTabuleiro( &vtTabuleiros[inxLista] );

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao criar lista." ) ;

		} /* fim ativa: LIS  &Criar tabuleiro */



		/* LIS  &Destruir tabuleiro */

		else if ( strcmp( ComandoTeste , DESTRUIR_TABULEIRO_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxLista, &CondRetEsp );

			if (   ( numLidos != 2 )
				|| ( ! ValidarInxLista( inxLista , NAO_VAZIO ) ) )
			{
				return TST_CondRetParm ;
			} /* if */

			CondRet = TAB_DestruirTabuleiro( vtTabuleiros[inxLista] );

			return TST_CompararInt( CondRetEsp , CondRet ,
					"Condicao de retorno errada ao criar lista." ) ;

		} /* fim ativa: LIS  &Destruir tabuleiro */

		

	return TST_CondRetNaoConhec ;
} /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
*
***********************************************************************/

int ValidarInxLista( int inxLista , int Modo )
{

	if (   ( inxLista <  0 )
		|| ( inxLista >= DIM_VT_LISTA ) )
	{
		return FALSE ;
	} /* if */

	if ( Modo == VAZIO )
	{
		if ( vtTabuleiros[ inxLista ] != NULL )
		{
			return FALSE ;
		} /* if */
	} else
	{
		if ( vtTabuleiros[ inxLista ] == NULL )
		{
			return FALSE ;
		} /* if */
	} /* if */

	return TRUE ;

} /* Fim função: TLIS -Validar indice de lista */

/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

