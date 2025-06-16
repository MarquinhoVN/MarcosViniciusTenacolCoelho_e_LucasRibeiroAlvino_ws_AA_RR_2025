# Análise de Algoritmos - UFRR

**Disciplina:** Análise de Algoritmos  
**Instituição:** Universidade Federal de Roraima (UFRR)  
**Aluno:** Marcos Vinícius Tenacol Coêlho

# Descrição do Projeto #
Este projeto apresenta uma análise empírica e teórica do algoritmo DFS (Depth-First Search) aplicado a grafos não direcionados. O objetivo é entender o comportamento assintótico da DFS por meio da função de recorrência, medição do tempo de execução e comparação com algoritmos alternativos.
# Estrutura do Projeto #
```bash
├── dfs_grafo_dinamico.c          # Código principal da DFS em C
├── gerador_grafos.c              # Gera arquivos de grafos com diferentes tamanhos 
├── grafo_random_10000.txt        # Listas encadeadas dos vértices
├── grafo_random_100000.txt
├── grafo_random_75000.txt
├── grafo_random_50000.txt
├── grafo_random_25000.txt
├── grafico.png                   # Resultado final dos testes em gráfico
├── resultados.csv                # Resultado final do tempos
├── gerar_graficos.py             # Script para gerar os gráficos a partir dos CSVs
└── README.md                     # Descrição do projeto
```

# Algoritmo Analisado: DFS #

```c
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
```

# Complexidade Assintótica #
A DFS visita cada vértice e aresta no máximo uma vez, resultando em:

Complexidade de tempo: O(V + E)

Complexidade de espaço: O(V) (devido à pilha de recursão e vetor de visitados)

# Experimentos Realizados #
Tamanhos de Entrada Testados
10.000 vértices

50.000 vértices

75.000 vértices

100.000 vértices

# Metodologia #
Geração automática: Grafos gerados via script em C

Medição de tempo: Utilização da função QueryPerformanceCounter() no código C

Execuções controladas: Mesmo algoritmo, diferentes tamanhos de entrada

Gráficos: Gerados em Python com matplotlib

# Resultados #
Gráfico 1: Tempo de Execução vs Tamanho do Grafo

Demonstra o crescimento linear da DFS em relação ao número total de vértices e arestas.
Confirma a tendência teórica prevista pela complexidade O(V + E), com crescimento proporcional à entrada.

# Como Executar #
## Compilar e Executar a DFS ##
```bash
gcc dfs_grafo_dinamico.c -o  dfs
./dfs {arquivo} {inicio} {destino}
```
## Gerar os Arquivos de Grafos ##
```bash
gcc -o gerar_grafo gerar_grafo.c
./gerar_grafo
```
## Gerar os Gráficos ##
```bash
python gerar_graficos.py
```
