#include <iostream>
#include <list>
#include <stack>
using namespace std;

class Graph {
    int num_vertices;
    list<int>* adj_list;
    void DepthFirstSearch(int vertex, bool visited[]);
    void fillStackWithVertices(int vertex, bool visited[], stack<int>& Stack);

public:
    Graph(int V);
    void addEdge(int start, int end);
    void printStronglyConnectedComponents();
    Graph getTranspose();
};

Graph::Graph(int V) {
    this->num_vertices = V;
    adj_list = new list<int>[V];
}

void Graph::DepthFirstSearch(int vertex, bool visited[]) {
    visited[vertex] = true;
    cout << vertex << " ";
    for (auto it = adj_list[vertex].begin(); it != adj_list[vertex].end(); ++it)
        if (!visited[*it])
            DepthFirstSearch(*it, visited);
}

void Graph::fillStackWithVertices(int vertex, bool visited[], stack<int>& Stack) {
    visited[vertex] = true;
    for (auto it = adj_list[vertex].begin(); it != adj_list[vertex].end(); ++it)
        if (!visited[*it])
            fillStackWithVertices(*it, visited, Stack);
    Stack.push(vertex);
}

Graph Graph::getTranspose() {
    Graph transposed_graph(num_vertices);
    for (int v = 0; v < num_vertices; v++) {
        for (auto it = adj_list[v].begin(); it != adj_list[v].end(); ++it) {
            transposed_graph.adj_list[*it].push_back(v);
        }
    }
    return transposed_graph;
}

void Graph::addEdge(int start, int end) {
    adj_list[start].push_back(end);
}

void Graph::printStronglyConnectedComponents() {
    stack<int> Stack;
    bool* visited = new bool[num_vertices];
    for (int i = 0; i < num_vertices; i++)
        visited[i] = false;
    for (int i = 0; i < num_vertices; i++)
        if (!visited[i])
            fillStackWithVertices(i, visited, Stack);
    Graph transposed_graph = getTranspose();
    for (int i = 0; i < num_vertices; i++)
        visited[i] = false;
    while (!Stack.empty()) {
        int vertex = Stack.top();
        Stack.pop();
        if (!visited[vertex]) {
            transposed_graph.DepthFirstSearch(vertex, visited);
            cout << endl;
        }
    }
}

int main() {
    Graph graph(7);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(4, 5);
    graph.addEdge(4, 3);
    graph.addEdge(3, 6);

    cout << "Strongly Connected Components:\n";
    graph.printStronglyConnectedComponents();
    return 0;
}
