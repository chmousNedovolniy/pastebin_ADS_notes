#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "graph.h"
#include <queue>

using Node = Graph<std::string>::Node;
using MyGraph = Graph<std::string>;
using flowMapping = std::map<std::pair<Node*, Node*>, int>;

bool isVisited(Node* x, std::vector<Node*>& path) {
    for (int i = 0; i < path.size(); i++)
        if (path[i] == x)
            return true;
    return false;
}

std::vector<Node*> bfs(MyGraph& graph, Node* source, Node* sink) {
    std::queue<std::vector<Node*>> q; // queue which stores paths

    std::vector<Node*> path; // vector to store the current path

    path.push_back(source);

    q.push(path);

    while (q.empty() == false) {
        path = q.front();

        q.pop();

        Node* lastNode = path[path.size() - 1]; // get the last node of the current path

        if (lastNode == sink)
            break; // path found!

        for (Node* v: graph.getNeighbors(lastNode)) {
            if (isVisited(v, path) == false && graph.getEdgeWeight(lastNode, v) > 0) {
                std::vector<Node*> newPath(path);
                newPath.push_back(v);
                q.push(newPath);
            }
        }

    }

    return path;
}

void update_residual(MyGraph& residual, MyGraph& network, std::map<std::pair<Node*, Node*>, int>& f) {
    for (auto edge: network.getEdgeWeights()) {
        Node* u = edge.first.first;
        Node* v = edge.first.second;
        Node* x = residual.getNode(u->data);
        Node* y = residual.getNode(v->data);
        residual.setEdgeWeight(x, y, network.getEdgeWeight(u, v) - f[{u, v}]);
        residual.setEdgeWeight(y, x, f[{u, v}]);
    }
}

flowMapping FordFulkersonAlgo(MyGraph& graph, Node* source, Node* sink) {
    flowMapping flowMap;

    for (std::pair<Node*, Node*> edge: graph.getAdjList()) {
        std::pair<Node*, Node*> edgeBack = {edge.second, edge.first};
        flowMap.insert({edge, 0});
        flowMap.insert({edgeBack, 0});

    }

    MyGraph Gf;

    for (Node* node: graph.getNodes()) {
        Gf.addNode(node->data);
    }

    for (auto edge: graph.getEdgeWeights()) {
        Node* u = edge.first.first;
        Node* v = edge.first.second;

        Node* x = Gf.getNode(u->data);
        Node* y = Gf.getNode(v->data);

        Gf.addEdge(x, y, edge.second);
        Gf.addEdge(y, x, 0);
    }


    //!!!!!
    Node* sourceGf = Gf.getNode(source->data);
    Node* sinkGf = Gf.getNode(sink->data);

    std::vector<Node*> P = bfs(Gf, sourceGf, sinkGf);

    while (P[P.size() - 1] == sinkGf) {
        int bottleneck = INT_MAX;
        //bottleneck min( { cf( (u,v) ) | (u,v) P } );
        for (int i = 1; i < P.size(); ++i) {
            if (Gf.getEdgeWeight(P[i - 1], P[i]) < bottleneck)
                bottleneck = Gf.getEdgeWeight(P[i - 1], P[i]);
        }

        for (int i = 0; i < P.size() - 1; ++i) {
            Node* u = graph.getNode(P[i]->data);
            Node* v = graph.getNode(P[i + 1]->data);

            flowMap[{u, v}] += bottleneck;
            flowMap[{v, u}] -= bottleneck;
        }

        update_residual(Gf, graph, flowMap);

        P = bfs(Gf, sourceGf, sinkGf);

//    for(int i = 0; i < P.size();++i)
//    {
//        std::cout << P[i]->data;
//    }
//        std::cout << std::endl;

    }

    return flowMap;
}

int main() {
    std::map<std::string, int> shirts({{"XS", 0}, {"S", 1}, {"M", 2}, {"L", 3}, {"XL", 4}, {"XXL", 5}});

    int test_count;
    std::cin >> test_count;
    for (int test = 0; test < test_count; ++test) {
        int n, m;
        std::cin >> n >> m;
        MyGraph graph;

        // Setup graph
        Node* source = graph.addNode("s");
        Node* sink = graph.addNode("t");
        std::vector<Node*> people(m);
        for (int i = 0; i < m; ++i) {
            people[i] = graph.addNode(std::to_string(i));
            graph.addEdge(source, people[i], 1);
        }
        std::vector<Node*> sizes(m);
        for (int i = 0; i < 6; ++i) {
            sizes[i] = graph.addNode(std::to_string(-i - 1));
            graph.addEdge(sizes[i], sink, n);
        }

        for (int i = 0; i < m; ++i) {
            std::string size1, size2;
            std::cin >> size1 >> size2;
            graph.addEdge(people[i], sizes[shirts[size1]], 1);
            graph.addEdge(people[i], sizes[shirts[size2]], 1);
        }

        flowMapping flowMap = FordFulkersonAlgo(graph, source, sink);
        for (auto flow: flowMap) {
            std::cout << "(" << flow.first.first->data << "," << flow.first.second->data << ") flow=" << flow.second
                      << std::endl;
        }
//        int flow = 0;
//        if (flow == m) {
//            std::cout << "Case " << test << ": " << "YES\n";
//        } else {
//            std::cout << "Case " << test << ": " << "YES\n";
//        }
    }
}