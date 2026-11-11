// COMSC 210 | Lab 34 | Yeji Kim
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

const int SIZE = 10;
const string locations[SIZE] = {
    "Building Entrance",
    "Suite Entrance",
    "Research Lab",
    "Intake",
    "Processing",
    "Storage Room",
    "Break Room",
    "Office Space",
    "Conference Room",
    "Shipping"
};

struct Edge {
    int src, dest, weight;
};

typedef pair < int, int > Pair; // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
    public:
        // a vector of vectors of Pairs to represent an adjacency list
        vector < vector < Pair >> adjList;

    // Graph Constructor
    Graph(vector < Edge >
        const & edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto & edge: edges) {
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
        cout << "Genomics Laboratory Navigation System" << endl;
        cout << "Adjacency List:" << endl;

        for (int i = 0; i < adjList.size(); i++) {
            cout << locations[i] << " --> ";

            for (Pair v: adjList[i]) {
                cout << "(" << locations[v.first] <<
                    ", " << v.second << " min) ";
            }

            cout << endl;
        }
    }

    void DFS(int start) {
        vector < bool > visited(adjList.size(), false);
        stack < int > s;

        s.push(start);

        cout << "DFS starting from " << locations[start] << ":" << endl;

        while (!s.empty()) {
            int vertex = s.top();
            s.pop();

            if (!visited[vertex]) {
                cout << locations[vertex] << " -> ";
                visited[vertex] = true;

                for (Pair neighbor: adjList[vertex]) {
                    if (!visited[neighbor.first]) {
                        s.push(neighbor.first);
                    }
                }
            }
        }

        cout << endl;
    }

    void BFS(int start) {
        vector < bool > visited(adjList.size(), false);
        queue < int > q;

        q.push(start);
        visited[start] = true;

        cout << "BFS starting from " << locations[start] << ":" << endl;

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();

            cout << locations[vertex] << " -> ";

            for (Pair neighbor: adjList[vertex]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }

        cout << endl;
    }

    void shortestPath(int start, int end) {
        vector < int > dist(SIZE, numeric_limits < int > ::max());
        vector < int > previous(SIZE, -1);
        vector < bool > visited(SIZE, false);

        dist[start] = 0;

        for (int i = 0; i < SIZE; i++) {
            int current = -1;
            int minDist = numeric_limits < int > ::max();

            // Find the unvisited vertex with the smallest distance
            for (int j = 0; j < SIZE; j++) {
                if (!visited[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    current = j;
                }
            }

            if (current == -1)
                break;

            visited[current] = true;

            // Update distances to neighboring vertices
            for (Pair neighbor: adjList[current]) {
                int next = neighbor.first;
                int weight = neighbor.second;

                if (!visited[next] && dist[current] + weight < dist[next]) {
                    dist[next] = dist[current] + weight;
                    previous[next] = current;
                }
            }
        }

        if (dist[end] == numeric_limits < int > ::max()) {
            cout << "No route found." << endl;
            return;
        }

        // Reconstruct the shortest path
        vector < int > path;
        for (int at = end; at != -1; at = previous[at]) {
            path.push_back(at);
        }

        cout << "Shortest path from " << locations[start] <<
            " to " << locations[end] << ":" << endl;

        for (int i = path.size() - 1; i >= 0; i--) {
            cout << locations[path[i]];

            if (i > 0)
                cout << " -> ";
        }

        cout << endl;
        cout << "Total walking time: " << dist[end] << " minutes" << endl;
    }

    void minimumSpanningTree() {
        vector < Edge > edges;

        // Collect every edge from the adjacency list
        for (int i = 0; i < adjList.size(); i++) {
            for (Pair neighbor: adjList[i]) {
                if (i < neighbor.first) {
                    edges.push_back({
                        i,
                        neighbor.first,
                        neighbor.second
                    });
                }
            }
        }

        // Sort edges by weight (smallest first)
        sort(edges.begin(), edges.end(),
            [](Edge a, Edge b) {
                return a.weight < b.weight;
            });

        vector < int > parent(SIZE);
        for (int i = 0; i < SIZE; i++) {
            parent[i] = i;
        }

        // Find the root of a set
        auto find = [ & ](int vertex) {
            while (parent[vertex] != vertex) {
                vertex = parent[vertex];
            }
            return vertex;
        };

        int totalWeight = 0;
        int edgesAdded = 0;

        cout << "Minimum Spanning Tree:" << endl;

        // Add edges that do not create a cycle
        for (Edge edge: edges) {
            int root1 = find(edge.src);
            int root2 = find(edge.dest);

            if (root1 != root2) {
                cout << locations[edge.src] << " - " <<
                    locations[edge.dest] << ": " <<
                    edge.weight << " min" << endl;

                parent[root1] = root2;
                totalWeight += edge.weight;
                edgesAdded++;

                if (edgesAdded == SIZE - 1) {
                    break;
                }
            }
        }

        cout << "Total MST walking time: " <<
            totalWeight << " minutes" << endl;
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector < Edge > edges = {
        // (x, y, w) —> connection between locations with walking time in minutes
        {
            0,
            1,
            2
        }, // Building Entrance - Suite Entrance
        {
            1,
            2,
            3
        }, // Suite Entrance - Research Lab
        {
            1,
            3,
            2
        }, // Suite Entrance - Intake
        {
            3,
            4,
            4
        }, // Intake - Processing
        {
            4,
            5,
            2
        }, // Processing - Storage Room
        {
            1,
            6,
            3
        }, // Suite Entrance - Break Room
        {
            1,
            7,
            2
        }, // Suite Entrance - Office Space
        {
            7,
            8,
            3
        }, // Office Space - Conference Room
        {
            4,
            9,
            5
        }, // Processing - Shipping
        {
            5,
            9,
            4
        }, // Storage Room - Shipping
        {
            2,
            7,
            4
        }, // Research Lab - Office Space
        {
            3,
            7,
            5
        }, // Intake - Office Space
        {
            6,
            8,
            6
        } // Break Room - Conference Room
    };

    // Creates graph
    Graph graph(edges);

    int choice;

    do {
        cout << "\n===== Genomics Laboratory Navigation System =====" << endl;
        cout << "1. Display Adjacency List" << endl;
        cout << "2. Run DFS" << endl;
        cout << "3. Run BFS" << endl;
        cout << "4. Find Shortest Path" << endl;
        cout << "5. Display Minimum Spanning Tree" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            graph.printGraph();
        } else if (choice == 2 || choice == 3 || choice == 4) {
            cout << "\nAvailable Locations:" << endl;

            for (int i = 0; i < SIZE; i++) {
                cout << i << ". " << locations[i] << endl;
            }

            int start, end;

            if (choice == 2 || choice == 3) {
                cout << "Enter starting location number: ";
                cin >> start;

                if (start < 0 || start >= SIZE) {
                    cout << "Invalid location number." << endl;
                } else if (choice == 2) {
                    graph.DFS(start);
                } else {
                    graph.BFS(start);
                }
            } else {
                cout << "Enter starting location number: ";
                cin >> start;

                cout << "Enter destination location number: ";
                cin >> end;

                if (start < 0 || start >= SIZE ||
                    end < 0 || end >= SIZE) {
                    cout << "Invalid location number." << endl;
                } else {
                    graph.shortestPath(start, end);
                }
            }
        } else if (choice == 5) {
            graph.minimumSpanningTree();
        } else if (choice == 6) {
            cout << "Exiting navigation system. Goodbye!" << endl;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 6);

    return 0;
}