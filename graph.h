#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>
	
namespace graph {
using Vertex = size_t;
using Verticies = std::vector<Vertex>;

class Graph{
public:
    Graph() : graph_() {}
    Graph(size_t vertex_count) : graph_(vertex_count) {}
    Graph(const Graph& rhs) : graph_(rhs.graph_) {}
    Graph(Graph&& rhs) noexcept : graph_(std::move(rhs.graph_)) {}
    
    size_t size() const { return graph_.size(); }
    bool empty() const { return !size(); }

    void resize(size_t new_vertex_count) {
        graph_.clear();
        graph_.resize(new_vertex_count);
    }

    // возвращает список смежных вершин для вершины v
    const std::vector<Vertex>& GetAdjacents(Vertex v) const {
        return graph_.at(v);
    }

    // добавляет ориентированное ребро from->to
    void AddEdge(Vertex from, Vertex to) {
        if(to >= graph_.size()) {
            std::string error = "There_is no vertex with index " + std::to_string(to);
            throw std::logic_error(error);
        }
        graph_.at(from).push_back(to);
    }

    enum class Colors {
    White,  // вершина не посещена
    Gray,   // вершина в процессе обработки (рекурсия не завершена)
    Black   // вершина полностью обработана

    };

    void GoDfs(const graph::Graph& g, std::vector<Colors>& colors, Vertex v){
        switch (colors[v]) {
        case Colors::White:
            std::cout << "I'm seing " << v << std::endl;
            colors[v] = Colors::Gray;
            for (Vertex w : g.GetAdjacents(v))
                GoDfs(g, colors, w);
            colors[v] = Colors::Black;
            break;
        case Colors::Gray:
            std::cout << "I'm seeing incoming cycle at " << v << std::endl;
            break;
        case Colors::Black:
            std::cout << "I'm seeing completed point " << v << std::endl;
            break;
        }
    }


    void Dfs(const graph::Graph& g) {
    std::vector<Colors> colors(g.size());
    for (Vertex i = 0; i < colors.size(); ++i) {
        if(colors[i] == Colors::White)
            GoDfs(g, colors, i);
    }
    }


    /* Алгоритм Косарайю для поиска сильно связных компонент (SCC - Strongly Connected Components)
    Состоит из трех шагов:
    1. Выполнить поиск в глубину (DFS), пока не будут «помечены» все вершины. 
    2. Инвертировать исходный граф (развернуть все ребра)
    3. Выполнить DFS в порядке убывания пометок вершин.
    Сложность O(V+E)
    (Оценка сверху O(V^2) (для насыщенных графов, худший случай); 
    оценка снизу O(V+E) (для разреженных графов, лучший случай))
    */

    // Первый DFS
    void FirstDfsForKosaraju(Vertex v, std::vector<Colors>& colors, std::vector<Vertex>& finish_order) {
        switch (colors[v]) {
        case Colors::White:
            std::cout << "(1 Kosaraju) I'm seing " << v << std::endl;
            colors[v] = Colors::Gray;
            // Рекурсивно обходим всех соседей
            for (Vertex w : GetAdjacents(v)) {
                FirstDfsForKosaraju(w, colors, finish_order);
            }

            colors[v] = Colors::Black;
            // Добавляем вершину в порядок завершения при полной обработке
            finish_order.push_back(v);
            break;
        case Colors::Gray:
            // Вершина уже в обработке
            std::cout << "(1 Kosaraju) I'm seeing incoming cycle at " << v << std::endl;
            break;
        case Colors::Black:
            // Вершина уже полностью обработана
            std::cout << "(1 Kosaraju) I'm seeing completed point " << v << std::endl;
            break;
    }
    }

    // Построение инвертированного графа
    Graph BuildTransposedGraph() const {
        Graph transposed(size());
        
        // Для каждого ребра u->v добавляем обратное ребро v->u
        for (int u = 0; u < size(); ++u) {
            const std::vector<Vertex>& neighbors = GetAdjacents(u);
            for (int i = 0; i < neighbors.size(); ++i) {
                Vertex v = neighbors[i];
                transposed.AddEdge(v, u);
            }
        }
        
        return transposed;
    }

    // Второй DFS на транспонированном графе
    void SecondDfsForKosaraju(const Graph& transposed, Vertex v, std::vector<Colors>& colors, std::vector<Vertex>& component) {
    switch (colors[v]) {
    case Colors::White:{
        std::cout << "(2 Kosaraju, add vertex to SCC) I'm seing " << v << std::endl;
        colors[v] = Colors::Gray;
        component.push_back(v);  // Добавляем вершину в текущую компоненту
        
        // Обходим транспонированный граф
        const std::vector<Vertex>& neighbors = transposed.GetAdjacents(v);
        for (Vertex w : transposed.GetAdjacents(v)) {
            SecondDfsForKosaraju(transposed, w, colors, component);
        }
        
        colors[v] = Colors::Black;
        break;
    } // Фигурные скобки чтобы не было пересечения инициализации
        
    case Colors::Gray:
        std::cout << "(2 Kosaraju) I'm seeing incoming cycle at " << v << std::endl;
        break;
        
    case Colors::Black:
        std::cout << "(2 Kosaraju) I'm seeing completed point " << v << std::endl;
        break;
    }
    }

    // алгоритм Косарайю
    std::vector<std::vector<Vertex>> Kosaraju() {
        std::vector<Colors> colors(size(), Colors::White);
        std::vector<Vertex> finish_order;
        
        // Шаг 1
        for (Vertex v = 0; v < size(); ++v) {
            if (colors[v] == Colors::White) {
                FirstDfsForKosaraju(v, colors, finish_order);
            }
        }
        
        // Шаг 2
        Graph transposed = BuildTransposedGraph();
        
        // Шаг 3
        std::fill(colors.begin(), colors.end(), Colors::White);
        std::vector<std::vector<Vertex>> strongly_connected_components;
        
        // Обходим вершины в порядке убывания времени завершения
        for (auto it = finish_order.rbegin(); it != finish_order.rend(); ++it) {
            Vertex v = *it;
            if (colors[v] == Colors::White) {  // = нашли новую компоненту
                std::vector<Vertex> component;
                SecondDfsForKosaraju(transposed, v, colors, component);
                strongly_connected_components.push_back(component);
            }
        }
        
        return strongly_connected_components;
    }

private:
    std::vector<std::vector<Vertex>> graph_;
    
};

}
#endif // _GRAPH_H_