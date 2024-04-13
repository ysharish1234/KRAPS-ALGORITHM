#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 4

// Struct to represent edges
struct Edge {
    int from, weight;
};

// Function prototypes
void addEdge(int u, int v, int w, struct Edge edges[V][V]);
void floydWarshall(int graph[V][V]);
double minAvgWeight(struct Edge edges[V][V], int graph[V][V]);

int main() {
    // Define edges and graph
    int i,j,k;
    struct Edge edges[V][V] = {0};
    int graph[V][V];
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            graph[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }

    // Read edges from input file
    FILE *inputFile;
    inputFile = fopen("input.c", "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening input file.\n");
        return 1;
    }

    int u, v, w;
    while (fscanf(inputFile, "%d %d %d", &u, &v, &w) != EOF) {
        addEdge(u, v, w, edges);
        graph[u][v] = w;
    }

    fclose(inputFile);

    // Calculate and print the minimum average weight
    printf("Minimum average weight of a cycle: %.5lf\n", minAvgWeight(edges, graph));

    return 0;
}

// Function to add an edge to the graph
void addEdge(int u, int v, int w, struct Edge edges[V][V]) {
    edges[u][v].from = u;
    edges[u][v].weight = w;
}

// Function to calculate the minimum average weight
int i,j,k;
double minAvgWeight(struct Edge edges[V][V], int graph[V][V]) {
    double minAvg = INT_MAX;
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (graph[i][k] != INT_MAX && graph[k][j] != INT_MAX &&
                    graph[i][j] > graph[i][k] + graph[k][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }

    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (graph[i][j] != INT_MAX && i != j) {
                for (k = 0; k < V; k++) {
                    if (edges[j][k].weight != 0) {
                        double avg = (double)(graph[i][j] + edges[j][k].weight + graph[k][i]) / 3;
                        if (avg < minAvg) {
                            minAvg = avg;
                        }
                    }
                }
            }
        }
    }

    return minAvg;
}
