#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARESTAS_EXTRA_POR_VERTICE 2  // Arestas extras além da árvore

int rand_int(int n) {
    return rand() % n;
}

void shuffle(int *array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand_int(i + 1);
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

void gerar_grafo_conectado(int V, const char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "w");
    if (!f) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    int arestasExtras = V * ARESTAS_EXTRA_POR_VERTICE;
    int A = (V - 1) + arestasExtras;
    fprintf(f, "%d %d\n", V, A);

    int *vertices = malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) vertices[i] = i;
    shuffle(vertices, V);

    // Parte 1: cria árvore geradora aleatória (garante conectividade)
    for (int i = 1; i < V; i++) {
        int u = vertices[i];
        int v = vertices[rand_int(i)];
        fprintf(f, "%d %d\n", u, v);
    }

    // Parte 2: adiciona arestas extras aleatórias
    for (int i = 0; i < arestasExtras; i++) {
        int u = rand_int(V);
        int v = rand_int(V);
        if (u != v)
            fprintf(f, "%d %d\n", u, v);
    }

    fclose(f);
    free(vertices);
    printf("Grafo salvo: %s (%d vértices, %d arestas)\n", nome_arquivo, V, A);
}

int main() {
    srand(time(NULL));

    int tamanhos[] = {10000,25000,50000,75000,100000};
    int total = sizeof(tamanhos) / sizeof(tamanhos[0]);

    for (int i = 0; i < total; i++) {
        char nome[100];
        sprintf(nome, "grafo_random_%d.txt", tamanhos[i]);
        gerar_grafo_conectado(tamanhos[i], nome);
    }

    return 0;
}
