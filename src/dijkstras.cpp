#include "dijkstras.h"

struct Node {
    int idx;
    int distance_from_source;
};

struct NodeSourceDistLT
{
    bool operator() (Node n1, Node n2) {
        return n1.distance_from_source < n2.distance_from_source;
    }
};

vector<int> dijkstras_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.numVertices, INF);
    previous.assign(G.numVertices, -1);
    vector<bool> visited(G.numVertices, false);

    priority_queue<Node, vector<Node>, NodeSourceDistLT> node_queue;
    node_queue.emplace(source, 0);
    distances[source] = 0;

    while (!node_queue.empty()) {
        Node current = node_queue.top();
        node_queue.pop();

        if (visited[current.idx])
            continue;
        visited[current.idx] = true;

        for (Edge edge : G[current.idx]) {
            if (current.distance_from_source + edge.weight < distances[edge.dst]) {
                distances[edge.dst] = current.distance_from_source + edge.weight;
                previous[edge.dst] = current.idx;
                node_queue.emplace(edge.dst, distances[edge.dst]);
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int> &distances, const vector<int> &previous, int tgt) {
    vector<int> path {tgt};
    while (-1 != (tgt = previous[tgt]))
        path.push_back(tgt);

    reverse(path.begin(), path.end());
    return path;
}


int main() {
    Graph G {{
        {
            {0, 1, 1}, {0, 2, 4}
        },
        {
            {1, 2, 1}
        },
        {}
    }, 3};

    vector<int> previous(G.numVertices, -1);
    vector<int> distances = dijkstras_shortest_path(G, 0, previous);

    cout << "Previous\n";
    for (int n : previous)
        cout << n << endl;

    cout << "Distances\n";
    for (int d : distances)
        cout << d << endl;

    vector<int> path = extract_shortest_path(distances, previous, 2);
    cout << "Path\n";
    for (int n : path)
        cout << n << endl;

    return 0;
}