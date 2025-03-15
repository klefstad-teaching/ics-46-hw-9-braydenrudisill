#include "dijkstras.h"

struct Node {
    int idx;
    int distance_from_source;
};

struct NodeSourceDistGT
{
    bool operator() (Node n1, Node n2) {
        return n1.distance_from_source > n2.distance_from_source;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.numVertices, INF);
    previous.assign(G.numVertices, -1);
    vector<bool> visited(G.numVertices, false);

    priority_queue<Node, vector<Node>, NodeSourceDistGT> node_queue;
    node_queue.emplace(source, 0);
    distances[source] = 0;

    while (!node_queue.empty()) {
        Node current = node_queue.top();
        node_queue.pop();

        if (visited[current.idx])
            continue;
        visited[current.idx] = true;

        for (Edge edge : G[current.idx]) {
            if (!visited[edge.dst] && current.distance_from_source + edge.weight < distances[edge.dst]) {
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

void print_path(const vector<int> &v, int total) {
    for (int i : v)
        cout << i << ' ';
    cout << endl;

    cout << "Total cost is " << total << endl;
}