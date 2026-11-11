#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

const int SIZE = 10;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

        void DFS(int start) {
        vector<bool> visited(adjList.size(), false);
        stack<int> s;

        s.push(start);

        cout << "DFS starting from vertex " << start << ":" << endl;

        while (!s.empty()) {
            int vertex = s.top();
            s.pop();

            if (!visited[vertex]) {
                cout << vertex << " ";
                visited[vertex] = true;

                for (Pair neighbor : adjList[vertex]) {
                    if (!visited[neighbor.first]) {
                        s.push(neighbor.first);
                    }
                }
            }
        }

        cout << endl;
    }

        void BFS(int start) {
        vector<bool> visited(adjList.size(), false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "BFS starting from vertex " << start << ":" << endl;

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();

            cout << vertex << " ";

            for (Pair neighbor : adjList[vertex]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }

        cout << endl;
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> connection between locations with walking time in minutes
        {0,1,2},   // Building Entrance - Suite Entrance
        {1,2,3},   // Suite Entrance - Research Lab
        {1,3,2},   // Suite Entrance - Intake
        {3,4,4},   // Intake - Processing
        {4,5,2},   // Processing - Storage Room
        {1,6,3},   // Suite Entrance - Break Room
        {1,7,2},   // Suite Entrance - Office Space
        {7,8,3},   // Office Space - Conference Room
        {4,9,5},   // Processing - Shipping
        {5,9,4},   // Storage Room - Shipping
        {2,7,4},   // Research Lab - Office Space
        {3,7,5},   // Intake - Office Space
        {6,8,6}    // Break Room - Conference Room
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    graph.DFS(0);
    graph.BFS(0);

    return 0;
}
