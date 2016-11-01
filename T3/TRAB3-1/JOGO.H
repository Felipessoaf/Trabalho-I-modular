#if ! defined( JOGO_ )
#define JOGO_
/***************************************************************************
*
*  $MCD Módulo de definição: JOGO	Jogo de xadrez
*
*  Arquivo gerado:              JOGO.h
*  Letras identificadoras:      JOGO
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / Juiz de Xadrez
*  -------------------------------------------Gestor:  LES/DI/PUC-Rio
*  Autores: fpf - Felipe Pessoa de Freitas
*			mmq - Matheus de Mello Queiroz
*			pf  - Pedro Ferreira
*			
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       fpf   21/out/2016 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa jogo de xadrez
*     Caso o Rei esteja em uma casa ameaçada e não possa se movimentar para qualquer outra casa,
*	  é emitida a mensagem “Cheque Mate”. Caso ele possa se movimentar
*	  para outra casa, é emitida a mensagem “Cheque”.
*	  A partida termina com o Cheque Mate ou a qualquer momento que um dos jogadores digite “FIM”.
*
*
***************************************************************************/

#include "TABULEIRO.H"

#if defined( JOGO_OWN )
#define JOGO_EXT
#else
#define JOGO_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: JOGO Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do jogo
*
***********************************************************************/

typedef enum {

	JOGO_CondRetOK,
	/* Concluiu corretamente */
	
	JOGO_CondRetFaltouMemoria,
	/* Faltou memória ao tentar criar um elemento do jogo */

	JOGO_CondRetTabuleiroInexistente
	/* Tabuleiro não existe */

} JOGO_tpCondRet;


/***********************************************************************
*
*  $FC Função: JOGO  &Mostrar tabuleiro
*
*  $ED Descrição da função
*     Mostra um tabuleiro de xadrez
*
*  $EP Parâmetros
*	 pTabuleiro - referencia para o tabuleiro a ser criado
*
*  $FV Valor retornado
*     JOGO_CondRetOK				   - Executou corretamente
*	  JOGO_CondRetTabuleiroInexistente - Tabuleiro não existe
*
***********************************************************************/

	JOGO_tpCondRet JOGO_MostrarTabuleiro(TAB_tppTabuleiro pTabuleiro);

#undef TABULEIRO_EXT

/********** Fim do módulo de definição: JOGO  Jogo de xadrez **********/

#else
#endif
