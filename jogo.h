#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

typedef struct _rank{
	char nomeJogador[100];
	int pontuacao;
} Ranking;

Ranking rank[10];
char nomeTemp[100];
int pontuacaoTemp;

typedef struct no {
	int valor;
	char naipe;
	struct no* prox;
} noCarta;

noCarta* monte;
noCarta* pilhaDeBaixo[7];
noCarta* pilhaDeCima[4];
noCarta* atual;

int linhaEscondida[7];
char nomeJogador[50];
time_t start;
time_t diff;

////ponteiro para struct que armazena data e hora  
//struct tm* horaInicial;
//struct tm* horaFinal;
////variável do tipo time_t para armazenar o tempo em segundos  
//time_t segundos;



void Cronometro();

void ProximaCarta();
int podeMover(noCarta* colunaOrigem, noCarta* colunaDestino);
int MoverPilhaBaixoBaixo(int linha, int colunaOrigem, int colunaDestino);
void criarMonte(void);
void CriarMenu();
noCarta* RemoveCartaMonte(int);
void CriarMonte();
void EmbaralharMonte();
void DistribuirCartas();
void imprimeCartas();
void IniciarJogo();
void Tutorial();
void AbrirRanking();
void SalvarJogo();
void ContinuarJogo();
void CriarJogador();
int MoverMontePilhaBaixo(int colunaDestino);
int MoverPilhaBaixoPilhaCima(int colunaOrigem);
int naipeCima(char c);
noCarta* RemoverElemento(noCarta* PILHA);
int EstaVazia(noCarta* PILHA);
void AdicionarElemento(noCarta* PILHA);
noCarta* MoverPilhaFim(noCarta* pilha);
int MoverMontePilhaCima(void);

void GravaRanking();
void LeArquivoInicio();

#endif // JOGO_H_INCLUDED

