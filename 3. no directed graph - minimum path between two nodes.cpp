#include "..\graph.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void bfs(Graph &g, int u) {
    queue<int> q;
    q.push(u);
    g.markNode(u); // m[u] = 1
    g.setParentNode(u, -1); // p[u] = -1
    g.setDistanceNode(u, 0); // d[u] = 0
    while(!q.empty()) {
        u = q.front();
        q.pop();
        for(int v: g.adjacentFromNode(u)) {
            if(!g.isMarkedNode(v)) { // !m[v]
                q.push(v);
                g.markNode(v); // m[v] = 1
                g.setParentNode(v,u); // p[v] = u
                g.setDistanceNode(v,g.getDistanceNode(u)+1); // d[v] = d[u]+1
            }
        }
    }
}

void minPath(Graph &g, int u, int v) {
    g.cleanNodesMark(); // clear m, p, d
    bfs(g, u);
    if(g.isMarkedNode(v)) {
        cout << u << " " << v << " existe un camino (distance: " << g.getDistanceNode(v) << "): ";

        vector<int> path;
        for(int t = v; t != -1; t = g.getParentNode(t)) // ; ; t = p[t]
            path.push_back(t);

        for(int i=path.size()-1; i > 0; i--)
            cout << path[i] << " -> ";
        cout << path[0] << endl;
    }
    else cout << u << " " << v << " no existe un camino" << endl;
}

int main () {
    Graph g;
    g.insertNode({1,2,3,4,5,6});
    g.insertEdge(1,2);
    g.insertEdge(2,5);
    g.insertEdge(2,6);
    g.insertEdge(4,6);
    g.insertEdge(5,6);

    /* EJERCICIO 3 */
	// The minimum path between two nodes
    cout << "EJERCICIO 3\n";

    V = g.listOfNodes();
    for(int i=0; i < V.size()-1; i++)
        for(int j=i+1; j < V.size(); j++)
            minPath(g,V[i],V[j]);

    cout << endl;

    return 0;
}
