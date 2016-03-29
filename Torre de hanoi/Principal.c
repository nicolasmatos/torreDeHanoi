#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

struct pino {
	Pilha * pilha;
	int nome;
};

typedef struct pino Pino;

void reiniciarJogo(Pilha * p1, Pilha * p2, Pilha * p3, int qtdDiscos) {
	int i;
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

void mostraPinos(Pilha * p1, Pilha * p2, Pilha * p3) {
	printf("Pino '1': ");
	imprimir(p1);
	printf("\nPino '2': ");
	imprimir(p2);
	printf("\nPino '3': ");
	imprimir(p3);
	printf("\n");
}

void verificaMovimento(Pino * pOri, Pino * pDest, Pino * p1, Pino * p2, Pino * p3, int numDiscos, Pilha * jogada) {
	if (topo(pOri->pilha) == -1) {
		printf("\nMovimento invalido.\n\n");
	}
	else if ((topo(pOri->pilha) < topo(pDest->pilha)) || (topo(pDest->pilha) == -1)) {
		empilhar(jogada, pDest->nome);
		empilhar(jogada, pOri->nome);

		empilhar(pDest->pilha, desempilhar(pOri->pilha));
	}
	else {
		printf("\nMovimento invalido.\n\n");
	}

	if (tamanho(pDest->pilha) == numDiscos && pDest->pilha == p3->pilha) {
		printf("Parabens jogo finalizado. E sera reiniciado.\n");
		reiniciarJogo(p1->pilha, p2->pilha, p3->pilha, numDiscos);
	}
}

void listaMovimentos(Pilha * p1, Pilha * p2, Pilha * p3) {
	if (topo(p1) < topo(p2) && topo(p1) != -1 && topo(p2) != -1) {
		printf("Mover de '1' para '2'\n");
	}
	else {
		if (topo(p2) < topo(p1) && topo(p1) != -1 && topo(p2) != -1) {
			printf("Mover de '2' para '1'\n");
		}
		else if (topo(p1) == -1 && topo(p2) != -1) {
			printf("Mover de '2' para '1'\n");
		}
		else if (topo(p2) == -1 && topo(p1) != -1) {
			printf("Mover de '1' para '2'\n");
		}
	}
	if (topo(p1) < topo(p3) && topo(p1) != -1 && topo(p3) != -1) {
		printf("Mover de '1' para '3'\n");
	}
	else {
		if (topo(p3) < topo(p1) && topo(p1) != -1 && topo(p3) != -1) {
			printf("Mover de '3' para '1'\n");
		}
		else if (topo(p1) == -1 && topo(p3) != -1) {
			printf("Mover de '3' para '1'\n");
		}
		else if (topo(p3) == -1 && topo(p1) != -1) {
			printf("Mover de '1' para '3'\n");
		}
	}
	if (topo(p2) < topo(p3) && topo(p2) != -1 && topo(p3) != -1) {
		printf("Mover de '2' para '3'\n");
	}
	else {
		if (topo(p3) < topo(p2) && topo(p2) != -1 && topo(p3) != -1) {
			printf("Mover de '3' para '2'\n");
		}
		else if (topo(p2) == -1 && topo(p3) != -1) {
			printf("Mover de '3' para '2'\n");
		}
		else if (topo(p3) == -1 && topo(p2) != -1) {
			printf("Mover de '2' para '3'\n");
		}
	}
}

void mostraSolucao(int qtdDiscos, Pino * pOri, Pino * pDest, Pino * pAux, Pilha * jogada) {
	int i = 0;
	int tam = tamanho(jogada);
	if (topo(jogada) != -1) {
		printf("\nVoltando todos os dicos para o pino 1.\n\n");
		for (i = 0; i < tam; i+=2) {
			printf("Mover do pino %d para o pino %d\n", desempilhar(jogada), desempilhar(jogada));
		}
		printf("\n");
		if (pOri->nome == 1) {
			if (pDest->nome == 2) {
				mostraPinos(pOri->pilha, pDest->pilha, pAux->pilha);
			}
			else {
				mostraPinos(pOri->pilha, pAux->pilha, pDest->pilha);
			}
		}
		else if (pDest->nome == 1) {
			if (pOri->nome == 2) {
				mostraPinos(pDest->pilha, pOri->pilha, pAux->pilha);
			}
			else {
				mostraPinos(pDest->pilha, pAux->pilha, pOri->pilha);
			}
		}
		else {
			if (pOri->nome == 2) {
				mostraPinos(pAux->pilha, pOri->pilha, pDest->pilha);
			}
			else {
				mostraPinos(pAux->pilha, pDest->pilha, pOri->pilha);
			}
		}
		printf("\nResolvendo a torre a partir do pino 1.\n\n");
	}

	if (qtdDiscos == 1) {
		empilhar(pDest->pilha, desempilhar(pOri->pilha));
		printf("Mover do pino %d para o pino %d\n", pOri->nome, pDest->nome);
	}
	else {
		mostraSolucao(qtdDiscos - 1, pOri, pAux, pDest, jogada);

		empilhar(pDest->pilha, desempilhar(pOri->pilha));

		printf("Mover do pino %d para o pino %d\n", pOri->nome, pDest->nome);

		mostraSolucao(qtdDiscos - 1, pAux, pDest, pOri, jogada);
	}
}

int main() {
	Pino * p1 = malloc(sizeof(Pino));
	Pino * p2 = malloc(sizeof(Pino));
	Pino * p3 = malloc(sizeof(Pino));

	p1->pilha = criar();
	p2->pilha = criar();
	p3->pilha = criar();

	Pilha * jogadas = criar();

	p1->nome = 1;
	p2->nome = 2;
	p3->nome = 3;

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
		if (discos != 0) {
			if (opcao == 2) {
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
						verificaMovimento(p1, p2, p1, p2, p3, discos, jogadas);
					}
					else {
						verificaMovimento(p1, p3, p1, p2, p3, discos, jogadas);
					}
				}
				else if (origem == 2) {
					if (destino == 1) {
						verificaMovimento(p2, p1, p1, p2, p3, discos, jogadas);
					}
					else {
						verificaMovimento(p2, p3, p1, p2, p3, discos, jogadas);
					}
				}
				else if (origem == 3) {
					if (destino == 2) {
						verificaMovimento(p3, p2, p1, p2, p3, discos, jogadas);
					}
					else {
						verificaMovimento(p3, p1, p1, p2, p3, discos, jogadas);
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
				mostraSolucao(discos, p1, p3, p2, jogadas);
				printf("\n");
				mostraPinos(p1->pilha, p2->pilha, p3->pilha);
				printf("Parabens jogo finalizado. E sera reiniciado.\n");
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
		}
		else {
			system("cls");
			printf("Os discos ainda nao foram inicializados.\n");
		}
		if (opcao == 7) {
			system("cls");
			printf("\n\n============================");
			printf("A operacao foi encerrada.");
			printf("===========================\n\n\n");
			getch();
		}
		if (opcao < 1 || opcao > 7) {
			system("cls");
			printf("\n=============================");
			printf("Operacao invalida.");
			printf("================================\n");
		}
	}
}