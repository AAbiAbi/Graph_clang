#include "graph.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct Vertex {
    void *data;
    Node *edges;
    int visited;
} Vertex;

struct MyGraph {
    Vertex **vertices;
    int vertexCount;
    int capacity;       // Capacity of the vertices array
} ;

Graph newGraph() {
    Graph g = malloc(sizeof(*g));
    if (g == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    int initialCapacity = 10; // Provide a value for initialCapacity
    if (g->vertices == NULL) {
        // Handle the case when vertices array is NULL
    }
    g->vertices = malloc(sizeof(Vertex *) * initialCapacity);
    if (g->vertices == NULL) {
        // Handle memory allocation failure
        free(g);
        return NULL;
    }
    g->vertexCount = 0;
    g->capacity = initialCapacity;
    return g;
}

void insertVertex(Graph g, void *v) {
    // Check if the vertex already exists in the graph
    for (int i = 0; i < g->vertexCount; i++) {
        if (g->vertices[i]->data == v) {
            // Vertex already exists
            return;
        }
    }

    // Check if resizing is needed
    if (g->vertexCount == g->capacity) {
        int newCapacity = g->capacity * 2; // Or any other resizing strategy
        Vertex **newVertices = realloc(g->vertices, sizeof(Vertex *) * newCapacity);
        if (newVertices == NULL) {
            // Handle memory allocation failure
            return;
        }
        g->vertices = newVertices;
        g->capacity = newCapacity;
    }

    // Create a new vertex as it doesn't exist
    Vertex *newVertex = malloc(sizeof(Vertex));
    if (newVertex == NULL) {
        // Handle memory allocation failure
        return;
    }

    // Initialize the new vertex
    newVertex->data = v;
    newVertex->edges = NULL;  // No edges initially
    newVertex->visited = 0;   // Not visited initially

    // Add the new vertex to the vertices array
    g->vertices[g->vertexCount++] = newVertex;
    // g->vertexCount++;
}
void insertEdge(Graph g, void *from, void *to) {
    /// Find the 'from' vertex in the graph
    Vertex *fromVertex = NULL;
    for (int i = 0; i < g->vertexCount; i++) {
        if (g->vertices[i]->data == from) {
            fromVertex = g->vertices[i];
            break;
        }
    }

    if (fromVertex == NULL) {
        // 'from' vertex not found
        return;
    }

    // Find the 'to' vertex in the graph
    Vertex *toVertex = NULL;
    for (int i = 0; i < g->vertexCount; i++) {
        if (g->vertices[i]->data == to) {
            toVertex = g->vertices[i];
            break;
        }
    }

    if (toVertex == NULL) {
        // 'to' vertex not found
        return;
    }

    // Create a new node for the 'to' vertex
    Node *newEdge = malloc(sizeof(Node));
    if (newEdge == NULL) {
        // Handle memory allocation failure
        return;
    }
    newEdge->data = toVertex;

    // Add the new node to the adjacency list of 'from' vertex
    newEdge->next = fromVertex->edges;
    fromVertex->edges = newEdge;
    // printf("Edge added from %d to %d is %d\n", *(int *)from, *(int *)to, *(int *)newEdge->data);
}

void printGraph(Graph g, void (*print)(void *)) {
    for (int i = 0; i < g->vertexCount; i++) {
        printf("Vertex %d: ", i);
        print(g->vertices[i]->data); // Print vertex data
        printf(" -> ");

        Node *current = g->vertices[i]->edges;
        
        while (current) {
            Vertex *v = (Vertex *)current->data;
            print(v->data); // Print edge data
            printf(" -> ");
            current = current->next;
        }
        printf("NULL\n");
    }
}


void *findVertex(Graph g, void *data) {
    for (int i = 0; i < g->vertexCount; i++) {
        if (g->vertices[i]->data == data) {
            return g->vertices[i];
        }
    }
    return NULL; // Vertex not found
}

void markVertexAsVisited(Graph g, void *vertex) {
    Vertex *v = (Vertex *)vertex;
    if (v != NULL) {
        v->visited = 1;
    }
}

void *getFirstNeighbor(Graph g, void *vertex) {
    Vertex *v = (Vertex *)vertex;
    if (v != NULL) {
        Node *first = v->edges;
        if (first != NULL) {
            return first->data;
        }
    }
    return NULL;
}

void *getNextNeighbor(Graph g, void *vertex, void *currentNeighbor) {
    Vertex *v = (Vertex *)vertex;
    Node *current = v->edges;
    while (current != NULL) {
        if (current->data == currentNeighbor && current->next != NULL) {
            return current->next->data;
        }
        current = current->next;
    }
    return NULL;
}



void bfs(Graph g, void *startData, void (*visit)(void *)) {
    // Initialize all vertices as not visited
    resetVertices(g);

    // Create a queue for BFS
    Queue *queue = createQueue();

    // Find the start vertex and enqueue it
    Vertex *startVertex = (Vertex *)findVertex(g, startData);
    if (startVertex) {
        enqueue(queue, startVertex);
        markVertexAsVisited(g, startVertex);
    }

    // Perform BFS
    while (!isQueueEmpty(queue)) {
        Vertex *current = (Vertex *)dequeue(queue);
        visit(current->data); // Visit the vertex

        // Enqueue all adjacent vertices that are not visited
        Vertex *neighbor = (Vertex *)getFirstNeighbor(g, current);
        while (neighbor) {
            if (!isVertexVisited(g, neighbor)) {
                markVertexAsVisited(g, neighbor);
                enqueue(queue, neighbor);
            }
            neighbor = (Vertex *)getNextNeighbor(g, current, neighbor);
        }
    }

    // Free the queue
    freeQueue(queue);
}



// Helper function for DFS
void dfsVisit(Vertex *v, void (*visit)(void *)) {
    // ... (DFS logic)
    // Mark vertex as visited
    // Call 'visit' function
    // Recursively call 'dfsVisit' for all adjacent vertices
    if (v == NULL || v->visited) {
        return; // Vertex is null or already visited
    }

    // Mark the vertex as visited
    v->visited = 1;

    // Visit the vertex
    visit(v->data);

    // Recursively visit all adjacent vertices
    Node *current = v->edges;
    while (current != NULL) {
        Vertex *adjacentVertex = (Vertex *)current->data;
        dfsVisit(adjacentVertex, visit);
        current = current->next;
    }
    
}

void dfs(Graph g, void *start, void (*visit)(void *)) {
    // ... (Depth-First Search implementation using recursion)
    // Set all vertices as not visited
    // Call the recursive helper function 'dfsVisit' for the 'start' vertex
    // Reset all vertices as not visited
    resetVertices(g);

    // Find the start vertex
    Vertex *startVertex = (Vertex *)findVertex(g, start);
    if (startVertex) {
        // Start DFS from the found vertex
        dfsVisit(startVertex, visit);
    }
}

void resetVertices(Graph g) {
    for (int i = 0; i < g->vertexCount; i++) {
        g->vertices[i]->visited = 0;
    }
}

int isVertexVisited(Graph g, void *vertexData) {
    for (int i = 0; i < g->vertexCount; i++) {
        if (g->vertices[i]->data == vertexData) {
            return g->vertices[i]->visited;
        }
    }
    return 0; // Return 0 if vertex is not found
}
