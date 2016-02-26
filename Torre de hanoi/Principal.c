#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

/*
void solucao(int d, char ori, char dest, char aux) {
	if (d == 1) {
		printf("Mover disco %d de %c para %c\n", d, ori, dest);
	}
	else {
		solucao(d - 1, ori, aux, dest);
		printf("Mover disco %d de %c para %c\n", d, ori, dest);
		solucao(d - 1, aux, dest, ori);
	}

}
*/

void solucao(int qtdDiscos, Pilha * pOri, Pilha * pDest, Pilha * pAux) {
	if (qtdDiscos == 1) {
		empilhar(pDest, desempilhar(pOri));
	}
	else {
		solucao(qtdDiscos - 1, pOri, pAux, pDest);
		empilhar(pDest, desempilhar(pOri));
		solucao(qtdDiscos - 1, pAux, pDest, pOri);
	}
}

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
	printf("Pino 1: ");
	imprimir(p1);
	printf("\nPino 2: ");
	imprimir(p2);
	printf("\nPino 3: ");
	imprimir(p3);
	printf("\n");
}

void verificaMovimento(Pilha * pOri, Pilha * pDest, Pilha * p3, int numDiscos) {
	if (numDiscos != 0) {
		if (topo(pOri) == -1) {
			printf("\nMovimento invalido.\n\n");
		}
		else if ((topo(pOri) < topo(pDest)) || (topo(pDest) == -1)) {
			empilhar(pDest, desempilhar(pOri));
			/*printf("\nOrigem.\n\n");
			imprimir(pOri);
			printf("\nDestino\n\n");
			imprimir(pDest);*/
		}
		else {
			printf("\nMovimento invalido.\n\n");
		}
		if (tamanho(pDest) == numDiscos && pDest == p3) {
			printf("Parabens jogo finalizado. E sera reiniciado.\n");
			//reiniciarJogo();
		}
	}
	else {
		printf("Os discos ainda nao foram inicializados.\n");
	}
}

void listaMovimentos(Pilha * p1, Pilha * p2, Pilha * p3) {
	if (topo(p1) < topo(p2) && topo(p1) != -1 && topo(p2) != -1) {
		printf("Mover de 'p1' para 'p2'\n");
	}
	else {
		if (topo(p2) < topo(p1) && topo(p1) != -1 && topo(p2) != -1) {
			printf("Mover de 'p2' para 'p1'\n");
		}
		else if (topo(p1) == -1 && topo(p2) != -1) {
			printf("Mover de 'p2' para 'p1'\n");
		}
		else if (topo(p2) == -1 && topo(p1) != -1) {
			printf("Mover de 'p1' para 'p2'\n");
		}
	}
	if (topo(p1) < topo(p3) && topo(p1) != -1 && topo(p3) != -1) {
		printf("Mover de 'p1' para 'p3'\n");
	}
	else {
		if (topo(p3) < topo(p1) && topo(p1) != -1 && topo(p3) != -1) {
			printf("Mover de 'p3' para 'p1'\n");
		}
		else if (topo(p1) == -1 && topo(p3) != -1) {
			printf("Mover de 'p3' para 'p1'\n");
		}
		else if (topo(p3) == -1 && topo(p1) != -1) {
			printf("Mover de 'p1' para 'p3'\n");
		}
	}
	if (topo(p2) < topo(p3) && topo(p2) != -1 && topo(p3) != -1) {
		printf("Mover de 'p2' para 'p3'\n");
	}
	else {
		if (topo(p3) < topo(p2) && topo(p2) != -1 && topo(p3) != -1) {
			printf("Mover de 'p3' para 'p2'\n");
		}
		else if (topo(p2) == -1 && topo(p3) != -1) {
			printf("Mover de 'p3' para 'p2'\n");
		}
		else if (topo(p3) == -1 && topo(p2) != -1) {
			printf("Mover de 'p2' para 'p3'\n");
		}
	}
}

int main() {
	Pilha * p1 = criar();
	Pilha * p2 = criar();
	Pilha * p3 = criar();
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
					empilhar(p1, discos - i);
				}
				printf("\n");
				imprimir(p1);
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
					mostraPinos(p1, p2, p3);
				}
				else {
					verificaMovimento(p1, p3, p3, discos);
					mostraPinos(p1, p2, p3);
				}
			}
			else if (origem == 2) {
				if (destino == 1) {
					verificaMovimento(p2, p1, p3, discos);
					mostraPinos(p1, p2, p3);
				}
				else {
					verificaMovimento(p2, p3, p3, discos);
					mostraPinos(p1, p2, p3);
				}
			}
			else if (origem == 3) {
				if (destino == 2) {
					verificaMovimento(p3, p2, p3, discos);
					mostraPinos(p1, p2, p3);
				}
				else {
					verificaMovimento(p3, p1, p3, discos);
					mostraPinos(p1, p2, p3);
				}
			}
		}
		else if (opcao == 3) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|   Listar movimentos    |\n"
				"|                        |\n"
				"--------------------------\n");
			mostraPinos(p1, p2, p3);
			listaMovimentos(p1, p2, p3);
		}
		else if (opcao ==4) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|    Mostrar solucao     |\n"
				"|                        |\n"
				"--------------------------\n");
			solucao(discos, p1, p3, p2);
		}
		else if (opcao == 5) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|   Situacao dos pinos   |\n"
				"|                        |\n"
				"--------------------------\n");
			mostraPinos(p1, p2, p3);
		}
		else if (opcao == 6) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|    Jogo reiniciado     |\n"
				"|                        |\n"
				"--------------------------\n");
			reiniciarJogo(p1, p2, p3, discos);
			mostraPinos(p1, p2, p3);
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