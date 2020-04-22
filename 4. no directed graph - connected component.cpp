#include <bits/stdc++.h>
#include "..\graph.h"

using namespace std;

void dfs1(Graph &g, int v) {
    g.markNode(v);
    for(int adj: g.adjacentFromNode(v)) {
        if(!g.isMarkedNode(adj)) {
            dfs1(g, adj);
        }
    }
}

void isConnected(Graph &g) {
    g.cleanNodesMark();
    int u = g.root();
    dfs1(g, u);
    bool b = true;
    for(int node: g.listOfNodes())
        b &= g.isMarkedNode(node);
    if(b) cout << "el grafo es conexo\n";
    else cout << "el grano no es conexo\n";
}

int main() {

    Graph g;
    g.insertNode(1,7);

    g.insertEdge(1,2);
    g.insertEdge(1,3);
    g.insertEdge(2,3);
    g.insertEdge(1,4);
    g.insertEdge(1,5);
    g.insertEdge(4,5);
    g.insertEdge(1,6);
    g.insertEdge(1,7);
    g.insertEdge(6,7);

    /* PREGUNTA 4 */
	// Is the graph connected
    cout << "PREGUNTA 4" << endl;
    isConnected(g);
    cout << endl;

    return 0;
}


