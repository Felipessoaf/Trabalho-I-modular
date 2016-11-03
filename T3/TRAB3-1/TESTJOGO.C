/***************************************************************************
*  $MCI Módulo de implementação: TJOGO Teste jogo de xadrez
*
*  Arquivo gerado:              TestJOGO.c
*  Letras identificadoras:      TJOGO
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
*     1        fpf   21/out/2016  início do desenvolvimento
*
***************************************************************************/

#include    <stdio.h>

#include <string.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "JOGO.H"

static const char MOSTRAR_TABULEIRO_CMD            [ ] = "=mostraTab"	;


TAB_tppTabuleiro pTabuleiro;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TJOGO &Testar jogo
*
*  $ED Descrição da função
*     Testa a execução de um jogo de xadrez
*
*     Comandos disponíveis:
*
*     =mostraTab	inxTabuleiro	CondRetEsp
*
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int numLidos   = -1 ,
		CondRetEsp = -1  ;

	TST_tpCondRet CondRet = TST_CondRetOK;

	TAB_tppTabuleiro pTabuleiro = NULL;

	TAB_CriarTabuleiro(&pTabuleiro); 

	JOGO_MontaTabuleiro(pTabuleiro);
	
	/* JOGO  &Mostrar tabuleiro */

		if (strcmp(ComandoTeste, MOSTRAR_TABULEIRO_CMD) == 0)
		{
			numLidos = LER_LerParametros("i", &CondRetEsp);

			if (numLidos != 1)
			{
				return TST_CondRetParm;
			} /* if */

			CondRet = JOGO_MostrarTabuleiro(pTabuleiro);

			return TST_CompararInt(CondRetEsp, CondRet,
				"Condicao de retorno errada ao mostrar tabuleiro.");

		} /* fim ativa: TAB  &Criar tabuleiro */

	return TST_CondRetNaoConhec ;
} /* Fim função: TLIS &Testar lista */



/********** Fim do módulo de implementação: TTAB Teste tabuleiro de xadrez **********/

