#include <stdio.h>
#include <stdlib.h>

#define MAX_ARESTAS 200
#define MAX_ROTEADORES 60


typedef struct {
    int origem, destino, peso;
} Aresta;

Aresta arestas[MAX_ARESTAS];
int pai[MAX_ROTEADORES + 1];  

// Função de comparação usada para ordenar arestas pelo peso (para Kruskal)
int compararArestas(const void *a, const void *b) {
    return ((Aresta *)a)->peso - ((Aresta *)b)->peso;
}

// Encontra o representante do conjunto (com path compression)
int encontrar(int x) {
    if (pai[x] != x)
        pai[x] = encontrar(pai[x]);
    return pai[x];
}

// Une dois conjuntos (union)
void unir(int a, int b) {
    int raizA = encontrar(a);
    int raizB = encontrar(b);
    if (raizA != raizB) {
        pai[raizA] = raizB;
    }
}

int main() {
    int R, C;
    scanf("%d %d", &R, &C);  

    // Leitura das arestas
    for (int i = 0; i < C; i++) {
        scanf("%d %d %d", &arestas[i].origem, &arestas[i].destino, &arestas[i].peso);
    }

    // Inicializa o Union-Find: cada roteador é seu próprio pai
    for (int i = 1; i <= R; i++) {
        pai[i] = i;
    }

    // Ordena as arestas por peso (menor para maior) - passo essencial do Kruskal
    qsort(arestas, C, sizeof(Aresta), compararArestas);

    int custo_total = 0;
    int arestas_incluidas = 0;

    // Kruskal
    for (int i = 0; i < C && arestas_incluidas < R - 1; i++) {
        int u = arestas[i].origem;
        int v = arestas[i].destino;
        int peso = arestas[i].peso;

        // Verifica se u e v estão em componentes diferentes
        if (encontrar(u) != encontrar(v)) {
            unir(u, v);                 
            custo_total += peso;       
            arestas_incluidas++;       
        }
    }


    printf("%d\n", custo_total);

    return 0;
}
