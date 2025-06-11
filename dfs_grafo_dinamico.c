#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX 100000

int *adj[MAX];
int grau[MAX];
int cap[MAX];
char vis[MAX];
int pai[MAX];

int destino;
int encontrado = 0;

void addEdge(int u, int v) {
    if (cap[u] == 0) {
        cap[u] = 4;
        adj[u] = malloc(cap[u] * sizeof(int));
    } else if (grau[u] >= cap[u]) {
        cap[u] <<= 1;
        adj[u] = realloc(adj[u], cap[u] * sizeof(int));
    }
    adj[u][grau[u]++] = v;
}

void dfs(int v) {
    vis[v] = 1;
    if (v == destino) {
        encontrado = 1;
        return;
    }
    for (int i = 0; i < grau[v]; ++i) {
        int u = adj[v][i];
        if (!vis[u]) {
            pai[u] = v;
            dfs(u);
            if (encontrado) return;
        }
    }
}

void limpar_memoria(int V) {
    for (int i = 0; i < V; ++i) {
        free(adj[i]);
        adj[i] = NULL;
        grau[i] = 0;
        cap[i] = 0;
    }
}

int main(int argc, char *argv[]) {
    const char *arquivo = argv[1];
    int inicio = atoi(argv[2]);
    destino = atoi(argv[3]);

    FILE *saida = fopen("resultados.csv", "a");
    if (!saida) {
        perror("Erro abrindo resultados.csv");
        return 1;
    }

    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq); 

    for (int rodada = 0; rodada < 13; rodada++) {
        FILE *f = fopen(arquivo, "r");
        if (!f) { perror("Erro abrindo arquivo do grafo"); return 1; }

        int V, A;
        fscanf(f, "%d %d", &V, &A);
        if (V > MAX) {
            fprintf(stderr, "Aumente MAX (%d > %d)\n", V, MAX);
            return 1;
        }

        for (int i = 0; i < A; ++i) {
            int u, v;
            fscanf(f, "%d %d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }
        fclose(f);

        for (int i = 0; i < V; ++i) {
            vis[i] = 0;
            pai[i] = -1;
        }
        encontrado = 0;

        LARGE_INTEGER t0, t1;
        QueryPerformanceCounter(&t0);
        dfs(inicio);
        QueryPerformanceCounter(&t1);

        double tempo = (double)(t1.QuadPart - t0.QuadPart) / freq.QuadPart;
        fprintf(saida, "%s,%.40f\n", arquivo, tempo);

        limpar_memoria(V);
    }

    fclose(saida);
    printf("Concluido\n");
    return 0;
}
