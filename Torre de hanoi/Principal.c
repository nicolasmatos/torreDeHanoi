#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"


struct pino {
	Pilha * pilha;
	char nome;
};

typedef struct pino Pino;

void reiniciarJogo(Pilha * p1, Pilha * p2, Pilha * p3, int qtdDiscos) {
	int i;
	if (qtdDiscos != 0) {
		while (tamanho(p1) != 0) {
			desempilhar(p1);
		}
		while (tamanho(p2) != 0) {
			desempilhar(p2);
		}
		while (tamanho(p3) != 0) {
			desempilhar(p3);
		}
		for (i = 0; i < qtdDiscos; i++) {
			empilhar(p1, qtdDiscos - i);
		}
	}
	else {
		printf("Os discos ainda nao foram inicializados.\n");
	}
}

void mostraPinos(Pilha * p1, Pilha * p2, Pilha * p3) {
	printf("Pino 'A': ");
	imprimir(p1);
	printf("\nPino 'B': ");
	imprimir(p2);
	printf("\nPino 'C': ");
	imprimir(p3);
	printf("\n");
}

void verificaMovimento(Pino * pOri, Pino * pDest, Pino * p3, int numDiscos) {
	if (numDiscos != 0) {
		if (topo(pOri->pilha) == -1) {
			printf("\nMovimento invalido.\n\n");
		}
		else if ((topo(pOri->pilha) < topo(pDest->pilha)) || (topo(pDest->pilha) == -1)) {
			empilhar(pDest->pilha, desempilhar(pOri->pilha));
		}
		else {
			printf("\nMovimento invalido.\n\n");
		}
		if (tamanho(pDest->pilha) == numDiscos && pDest->pilha == p3->pilha) {
			printf("Parabens jogo finalizado. E sera reiniciado.\n");
			if (pOri->nome == 'A') {
				if (pDest->nome == 'B') {
					reiniciarJogo(pOri->pilha, pDest->pilha, p3->pilha, numDiscos);
				}
				else {
					reiniciarJogo(pOri->pilha, p3->pilha, pDest->pilha, numDiscos);
				}
			}
			else if (pDest->nome == 'A') {
				if (pOri->nome == 'B') {
					reiniciarJogo(pDest->pilha, pOri->pilha, p3->pilha, numDiscos);
				}
				else {
					reiniciarJogo(pDest->pilha, p3->pilha, pOri->pilha, numDiscos);
				}
			}
			else {
				if (pOri->nome == 'B') {
					reiniciarJogo(p3->pilha, pOri->pilha, pDest->pilha, numDiscos);
				}
				else {
					reiniciarJogo(p3->pilha, pDest->pilha, pOri->pilha, numDiscos);
				}
			}
		}
		else {
			printf("Os discos ainda nao foram inicializados.\n");
		}
	}
}

void listaMovimentos(Pilha * p1, Pilha * p2, Pilha * p3) {
	if (topo(p1) < topo(p2) && topo(p1) != -1 && topo(p2) != -1) {
		printf("Mover de 'A' para 'B'\n");
	}
	else {
		if (topo(p2) < topo(p1) && topo(p1) != -1 && topo(p2) != -1) {
			printf("Mover de 'B' para 'A'\n");
		}
		else if (topo(p1) == -1 && topo(p2) != -1) {
			printf("Mover de 'B' para 'A'\n");
		}
		else if (topo(p2) == -1 && topo(p1) != -1) {
			printf("Mover de 'A' para 'B'\n");
		}
	}
	if (topo(p1) < topo(p3) && topo(p1) != -1 && topo(p3) != -1) {
		printf("Mover de 'A' para 'C'\n");
	}
	else {
		if (topo(p3) < topo(p1) && topo(p1) != -1 && topo(p3) != -1) {
			printf("Mover de 'C' para 'A'\n");
		}
		else if (topo(p1) == -1 && topo(p3) != -1) {
			printf("Mover de 'C' para 'A'\n");
		}
		else if (topo(p3) == -1 && topo(p1) != -1) {
			printf("Mover de 'A' para 'C'\n");
		}
	}
	if (topo(p2) < topo(p3) && topo(p2) != -1 && topo(p3) != -1) {
		printf("Mover de 'B' para 'C'\n");
	}
	else {
		if (topo(p3) < topo(p2) && topo(p2) != -1 && topo(p3) != -1) {
			printf("Mover de 'C' para 'B'\n");
		}
		else if (topo(p2) == -1 && topo(p3) != -1) {
			printf("Mover de 'C' para 'B'\n");
		}
		else if (topo(p3) == -1 && topo(p2) != -1) {
			printf("Mover de 'B' para 'C'\n");
		}
	}
}

void solucao(int qtdDiscos, Pino * pOri, Pino * pDest, Pino * pAux) {
	if (qtdDiscos == 1) {
		empilhar(pDest->pilha, desempilhar(pOri->pilha));
		printf("Mover do pino %c para o pino %c\n", pOri->nome, pDest->nome);
	}
	else {
		solucao(qtdDiscos - 1, pOri, pAux, pDest);
		if (pOri->nome == 'A') {
			if (pDest->nome == 'B') {
				mostraPinos(pOri->pilha, pDest->pilha, pAux->pilha);
			}
			else {
				mostraPinos(pOri->pilha, pAux->pilha, pDest->pilha);
			}
		}
		else if (pDest->nome == 'A') {
			if (pOri->nome == 'B') {
				mostraPinos(pDest->pilha, pOri->pilha, pAux->pilha);
			}
			else {
				mostraPinos(pDest->pilha, pAux->pilha, pOri->pilha);
			}
		}
		else {
			if (pOri->nome == 'B') {
				mostraPinos(pAux->pilha, pOri->pilha, pDest->pilha);
			}
			else {
				mostraPinos(pAux->pilha, pDest->pilha, pOri->pilha);
			}
		}
		empilhar(pDest->pilha, desempilhar(pOri->pilha));
		printf("Mover do pino %c para o pino %c\n", pOri->nome, pDest->nome);
		if (pOri->nome == 'A') {
			if (pDest->nome == 'B') {
				mostraPinos(pOri->pilha, pDest->pilha, pAux->pilha);
			}
			else {
				mostraPinos(pOri->pilha, pAux->pilha, pDest->pilha);
			}
		}
		else if (pDest->nome == 'A') {
			if (pOri->nome == 'B') {
				mostraPinos(pDest->pilha, pOri->pilha, pAux->pilha);
			}
			else {
				mostraPinos(pDest->pilha, pAux->pilha, pOri->pilha);
			}
		}
		else {
			if (pOri->nome == 'B') {
				mostraPinos(pAux->pilha, pOri->pilha, pDest->pilha);
			}
			else {
				mostraPinos(pAux->pilha, pDest->pilha, pOri->pilha);
			}
		}
		solucao(qtdDiscos - 1, pAux, pDest, pOri);
	}
}

int main() {

	Pino * p1 = malloc(sizeof(Pino));
	Pino * p2 = malloc(sizeof(Pino));
	Pino * p3 = malloc(sizeof(Pino));

	p1->pilha = criar();
	p2->pilha = criar();
	p3->pilha = criar();

	p1->nome = 'A';
	p2->nome = 'B';
	p3->nome = 'C';

	int discos = 0, opcao = 1, origem, destino, i;

	while (opcao != 7) {
		printf("================================Menu de opcoes================================\n");
		printf("1\. Inicializar os pinos\n"
			"2\. Realizar jogada\n"
			"3\. Listar movimentos\n"
			"4\. Mostrar solucao\n"
			"5\. Mostrar situacao dos pinos\n"
			"6\. Reiniciar o jogo\n"
			"7\. Sair do programa\n");
		printf("===============================================================================\n");
		printf("\nQual opcao do menu deseja executar?\n");
		scanf("%d", &opcao);
		if (opcao == 1) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|    Inicializar pinos   |\n"
				"|                        |\n"
				"--------------------------\n");
			if (discos == 0) {
				printf("Digite a quantidade de discos com que deseja jogar: ");
				scanf("%d", &discos);
				for (i = 0; i < discos; i++) {
					empilhar(p1->pilha, discos - i);
				}
				printf("\n");
				imprimir(p1->pilha);
			}
			else {
				printf("Discos ja inicializados.\n");
			}
		}
		else if (opcao == 2) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|    Realizar jogada     |\n"
				"|                        |\n"
				"--------------------------\n");

			printf("\nPino de origem: ");
			scanf("%d", &origem);
			printf("Pino de destino: ");
			scanf("%d", &destino);
			printf("\n");

			if (origem == 1) {
				if (destino == 2) {
					verificaMovimento(p1, p2, p3, discos);
				}
				else {
					verificaMovimento(p1, p3, p3, discos);
				}
			}
			else if (origem == 2) {
				if (destino == 1) {
					verificaMovimento(p2, p1, p3, discos);
				}
				else {
					verificaMovimento(p2, p3, p3, discos);
				}
			}
			else if (origem == 3) {
				if (destino == 2) {
					verificaMovimento(p3, p2, p3, discos);
				}
				else {
					verificaMovimento(p3, p1, p3, discos);
				}
			}
			mostraPinos(p1->pilha, p2->pilha, p3->pilha);
		}
		else if (opcao == 3) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|   Listar movimentos    |\n"
				"|                        |\n"
				"--------------------------\n");
			mostraPinos(p1->pilha, p2->pilha, p3->pilha);
			listaMovimentos(p1->pilha, p2->pilha, p3->pilha);
		}
		else if (opcao == 4) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|    Mostrar solucao     |\n"
				"|                        |\n"
				"--------------------------\n");
			reiniciarJogo(p1->pilha, p2->pilha, p3->pilha, discos);
			printf("\n");
			solucao(discos, p1, p3, p2);
			mostraPinos(p1->pilha, p2->pilha, p3->pilha);
			printf("\n\nParabens jogo finalizado. E sera reiniciado.\n");
			reiniciarJogo(p1->pilha, p2->pilha, p3->pilha, discos);

		}
		else if (opcao == 5) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|   Situacao dos pinos   |\n"
				"|                        |\n"
				"--------------------------\n");
			mostraPinos(p1->pilha, p2->pilha, p3->pilha);
		}
		else if (opcao == 6) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|    Jogo reiniciado     |\n"
				"|                        |\n"
				"--------------------------\n");
			reiniciarJogo(p1->pilha, p2->pilha, p3->pilha, discos);
			mostraPinos(p1->pilha, p2->pilha, p3->pilha);
		}
		else if (opcao == 7) {
			system("cls");
			printf("\n\n============================");
			printf("A operacao foi encerrada.");
			printf("===========================\n\n\n");
			getch();
		}
		else {
			system("cls");
			printf("\n=============================");
			printf("Operacao invalida.");
			printf("================================");
		}
	}
}