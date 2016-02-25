#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

#define TAM_MAX 50

struct pilha {
	int itens[TAM_MAX];
	int tp;
};

Pilha * criar() {
	Pilha * p = (Pilha *)malloc(sizeof(Pilha));
	p->tp = 0;
	return p;
}

void destruir(Pilha * p) {
	if (p != NULL) {
		free(p);
	}
}

int desempilhar(Pilha * p) {
	if (p->tp == 0) {
		printf("Pilha vazia");
		return -1;
	}
	return p->itens[--p->tp];
}

void empilhar(Pilha * p, int x) {
	if (p->tp == TAM_MAX) {
		printf("Estouro de pilha!");
		return;
	}
	p->itens[p->tp++] = x;
}

int tamanho(Pilha * p) {
	return p->tp;
}

int topo(Pilha * p) {
	if (p->tp == 0) {
		//printf("Pilha vazia");
		return -1;
	}
	return p->itens[p->tp - 1];
}

void imprimir(Pilha * p) {
	int i;
	printf("[ ");
	for (i = 0; i<p->tp; i++) {
		printf("%d ", p->itens[i]);
	}
	printf("]\n");
}

void inverter3(Pilha * p) {
	int i, f, tmp;
	for (i = 0, f = p->tp - 1; i < f; i++, f--) {
		tmp = p->itens[i];
		p->itens[i] = p->itens[f];
		p->itens[f] = tmp;
	}
}

Pilha * clonar(Pilha * p) {
	Pilha * clone = criar();
	int tamClone = p->tp;
	int i;

	for (i = 0; i < tamClone; i++) {
		clone->itens[i] = p->itens[i];
	}
	clone->tp = p->tp;

	return clone;
}

int compIgual(Pilha * p1, Pilha * p2) {
	int i;
	int retorno;
	if (p1->tp != p2->tp) {
		return 0;
	}
	else {
		for (i = 0; i < p1->tp; i++) {
			if (p1->itens[i] == p2->itens[i]) {
				retorno = 1;
			}
			else {
				retorno = 0;
				i = p1->tp;
			}
		}
		if (retorno == 1) {
			return 1;
		}
		else {
			return 0;
		}
	}
}