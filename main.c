#include "graph.h"
#include "queue.h"
#include <stdio.h>

// A simple visit function that prints the data of a vertex
void printVertex(void *data) {
    printf("%d ", *(int *)data); // Assuming data is of type int
}

int main() {
    // Create a new graph
    Graph g = newGraph();

    // Create some vertex data
    int data[] = {1, 2, 3, 4, 5};
    int numVertices = sizeof(data) / sizeof(data[0]);

    // Add vertices to the graph
    for (int i = 0; i < numVertices; i++) {
        insertVertex(g, &data[i]);
    }

    // Add edges to the graph
    insertEdge(g, &data[0], &data[1]);
    insertEdge(g, &data[0], &data[2]);
    insertEdge(g, &data[1], &data[3]);
    insertEdge(g, &data[2], &data[4]);

    // // Print the graph
    // printf("Graph structure:\n");
    // printGraph(g, printVertex);
    printf("Graph structure:\n");
    printGraph(g, printVertex);

    // Perform BFS starting from vertex '1'
    printf("\nBFS Traversal starting from vertex 1:\n");
    bfs(g, &data[0], printVertex);

    // Perform DFS starting from vertex '1'
    printf("\nDFS Traversal starting from vertex 1:\n");
    dfs(g, &data[0], printVertex); // Assuming you've implemented dfs()

    // Clean up (if you have a function to free the graph)
    // freeGraph(g);

    return 0;
}
