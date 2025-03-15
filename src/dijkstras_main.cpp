#include "dijkstras.h"


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
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    cout << "Previous\n";
    for (int n : previous)
        cout << n << endl;

    cout << "Distances\n";
    for (int d : distances)
        cout << d << endl;

    vector<int> path = extract_shortest_path(distances, previous, 2);
    print_path(path, distances[2]);

    return 0;
}