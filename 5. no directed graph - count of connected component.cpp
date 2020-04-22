#include <bits/stdc++.h>
#include "..\graph.h"

using namespace std;

set<vector<int>> list_connected_component;
vector<int> CC;

void dfs2(Graph &g, int u, int l) {
    g.markNode(u, l);
    CC.push_back(u);
    for(int v: g.adjacentFromNode(u)) {
        if(!g.isMarkedNode(v)) {
            dfs2(g, v, l);
        }
    }
}

void connectedComponent(Graph &g) {
    g.cleanNodesMark();
    int cc = 0;
    for(int node: g.listOfNodes())
        if(!g.isMarkedNode(node)) {
            CC.clear();
            dfs2(g, node, ++cc);
            list_connected_component.insert(CC);
        }
    cout << "el grafo tiene " << cc << " componentes conexas\n";

    int nc = 1;
    for(vector<int> c: list_connected_component) {
        cout << "componente conexa " << nc++ << ": ";
        for(int n: c)
            cout << n << " ";
        cout << endl;
    }
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

    /* PREGUNTA 5 */
	// how many connected components does the graph have
    cout << "PREGUNTA 5" << endl;
    connectedComponent(g);
    cout << endl;

    return 0;
}


