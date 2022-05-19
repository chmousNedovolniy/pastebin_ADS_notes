#include <algorithm>
#include <iostream>
#include <vector>

// Usually I prefer to make Graph class to access vital fields easily.
// For instance, in class you don't need to pass all vectors, multimaps etc to functions.
class Graph {
public:
    size_t vertex_count_;
    // You can also save graph as multimap<Node, Node> or sth, choose according to given task.
    std::vector<std::vector<int>> graph_;
    // Visited can also be a field of Node class, way to implement it actually doesn't matter most time.
    std::vector<bool> visited_;

    Graph(int vertex_count) : vertex_count_(vertex_count), graph_(vertex_count), visited_(vertex_count) {}

    // Basic recursive implementation of Dfs - take a vertex, call Dfs on unvisited neighbours - profit.
    void BasicDfs(int current_vertex) {
        visited_[current_vertex] = true;
        for (auto neighbour_vertex: graph_[current_vertex]) {
            if (!visited_[neighbour_vertex]) {
                BasicDfs(neighbour_vertex);
            }
        }
    }
};

int main() {
    // Usually in graph tasks input would be sth like this:
    // 5 4
    // 1 2
    // 2 3
    // 1 5
    // 3 4
    // first line for number of vertexes and number of edges
    // then, edges in form (a, b), a, b - indexes of connected vertexes
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    Graph g(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int vertex_1, vertex_2;
        std::cin >> vertex_1 >> vertex_2;
        // Usually, numeration starts with 1.
        // We can make it to start from zero (to help ourselves with indexing later).
        --vertex_1;
        --vertex_2;
        // This is for undirected graph, if it is directed - you should use only one of lines beyond.
        g.graph_[vertex_1].push_back(vertex_2);
        g.graph_[vertex_2].push_back(vertex_1);
    }
}
