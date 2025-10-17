#include <iostream>
#include "graph.h"

using graph::Vertex;


void PrintComponents(const std::vector<std::vector<Vertex>>& components) {
    std::cout << "\n=== Strongly Connected Components ===" << std::endl;
    std::cout << "Found " << components.size() << " components:" << std::endl;
    
    for (size_t i = 0; i < components.size(); ++i) {
        std::cout << "Component " << i + 1 << ": { ";
        for (Vertex v : components[i]) {
            std::cout << v << " ";
        }
        std::cout << "}" << std::endl;
    }
}

int main() {
	graph::Graph gr(4);
	// graph::Verticies& adj =  gr.GetAdjacents(1);
	// adj.push_back(0);
	// adj.push_back(2);
	// adj.push_back(3);
	gr.AddEdge(0, 1);
	gr.AddEdge(0, 2);
	gr.AddEdge(1, 3);
	gr.AddEdge(2, 3);
	// gr - граф "квадрат"
	std::cout << "Graph gr";
	for (Vertex i = 0; i < 4; ++i) {
		std::cout << "\nadjacent for vertex " << i << ": ";
		for (Vertex v : gr.GetAdjacents(i))
			std::cout << v << " ";
	}
	graph::Graph g = std::move(gr);
	std::cout << "\ngraph gr is " << (gr.empty() ? "empty" : "not empty") << std::endl;
	std::cout << "Graph g";
	for (Vertex i = 0; i < 4; ++i) {
		std::cout << "\nadjacent for vertex " << i << ": ";
		for (Vertex v : g.GetAdjacents(i))
			std::cout << v << " ";
	}
	
	// Пример работы ДФС
	graph::Graph g2(5);
    g2.AddEdge(0, 1);
    g2.AddEdge(1, 2);
    g2.AddEdge(2, 3);
    g2.AddEdge(3, 4);
    g2.AddEdge(4, 0); 
    
    std::cout << "\n\nStart DFS for g2:\n";
    g2.Dfs(g2);

	// Пример работы алгоритма Косарайю
    std::cout << "=== Kosaraju Example 1 ===" << std::endl;
    graph::Graph g3(3);
    g3.AddEdge(0, 1);
    g3.AddEdge(1, 2);
    g3.AddEdge(2, 0);
    
    auto components = g3.Kosaraju();
    PrintComponents(components);


	// Второй пример работы алгоритма Косарайю
 	std::cout << "=== Kosaraju Example 2 ===" << std::endl;
    graph::Graph g4(6);
	g4.AddEdge(1, 2);
    g4.AddEdge(2, 1);
    g4.AddEdge(3, 4);
	g4.AddEdge(4, 5);
	g4.AddEdge(5, 3);

	auto components2 = g4.Kosaraju();
    PrintComponents(components2);


	return 0;
}