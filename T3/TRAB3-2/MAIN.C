/***************************************************************************
*  $MCI Módulo de implementação: MAIN	modulo para jogar jogo de xadrez
*
*  Arquivo gerado:              MAIN.c
*  Letras identificadoras:      MAIN
*
*  Projeto: INF 1301 / Juiz de Xadrez
*  -------------------------------------------Gestor:  LES/DI/PUC-Rio
*  Autores: pf - Pedro Ferreira
*           mmq - Matheus de Mello Queiroz
*			fpf - Felipe Pessoa de Freitas
*
*  $HA Histórico de evolução:
*     Versão  Autor     Data       Observações
*     1       fpf     08/nov/2016  início da implementação
*
***************************************************************************/

#include <stdio.h>

#include "JOGO.H"

int main(int argc, char *argv[])
{
	char coordOrigem[4];
	char coordDestino[4];

	char jogBrancas[20];
	char jogPretas[20];

	TAB_tppTabuleiro pTabuleiro = NULL;

	TAB_CriarTabuleiro(&pTabuleiro);

	JOGO_MontaTabuleiro(pTabuleiro, argv[1]);

	printf("Nome do jogador das pecas brancas:\n");
	scanf("%s", jogBrancas);

	printf("Nome do jogador das pecas pretas:\n");
	scanf("%s", jogPretas);

	JOGO_RecebeJogadores(jogBrancas, jogPretas);

	JOGO_IniciaJogo();
	
	while (jogoRodando)
	{
		JOGO_MostraTabuleiro(pTabuleiro);
		printf("Jogador %s, realize sua jogada (coord origem, coord destino) ou FIM para terminar:\n", (jogCorr=='B')?jogadorB:jogadorP);
		scanf("%s", coordOrigem);
		scanf("%s", coordDestino);
		JOGO_RecebeJogada(pTabuleiro, coordOrigem, coordDestino);
		JOGO_ChequeMate(pTabuleiro);
	}

	return 0;
}

/********** Fim do módulo de implementação: MAIN  modulo para jogar jogo de xadrez **********/