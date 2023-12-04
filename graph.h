#ifndef GRAPH_H
#define GRAPH_H

// Forward declaration of the struct with a unique name to avoid conflicts.
struct MyGraph;

// Define Graph as a pointer to the newly named struct MyGraph.
typedef struct MyGraph *Graph;

Graph newGraph();
void insertVertex(Graph g, void *v);
void insertEdge(Graph g, void *from, void *to);
void bfs(Graph g, void *start, void (*visit)(void *));
void dfs(Graph g, void *start, void (*visit)(void *));

// Add this declaration if you want to use resetVertices outside graph.c
void resetVertices(Graph g);
void *findVertex(Graph g, void *data);
void markVertexAsVisited(Graph g, void *vertex);
void printGraph(Graph g, void (*print)(void *));
void *getFirstNeighbor(Graph g, void *vertex);
void *getNextNeighbor(Graph g, void *vertex, void *currentNeighbor);
// Check if a vertex has been visited
int isVertexVisited(Graph g, void *vertexData);

#endif