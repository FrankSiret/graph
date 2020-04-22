#include "..\graph.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

bool isC = false;

void dfs2(Graph &g, int u) {
    g.markNode(u); // p[u] = 1

    for(int v: g.adjacentFromNode(u)) {
        if(!g.isMarkedNode(v)) { // !m[v]
            g.setParentNode(v,u); // p[v] = u
            dfs2(g, v);
        }
        else if(v != g.getParentNode(u)) { // v != p[u]
            isC = true;
        }
    }
}
void isCyclic(Graph &g) {
    isC = false;
    g.cleanNodesMark(); // clear m, p

    for(int v0: g.listOfNodes()) {
        if(!g.isMarkedNode(v0)) { // !m[u]
            g.setParentNode(v0,-1); // p[v0] = -1
            dfs2(g,v0);
        }
    }

    if(isC)
        cout << "the graph is cyclic" << endl;
    else cout << "the graph is not cyclic" << endl;
}

int main () {
    Graph g;
    g.insertNode({1,2,3,4,5,6});
    g.insertEdge(1,2);
    g.insertEdge(2,5);
    g.insertEdge(2,6);
    g.insertEdge(4,6);
    g.insertEdge(5,6);

    /* EJERCICIO 2 */
	// Is the Graph cyclic?
    cout << "EJERCICIO 2\n";

    isCyclic(g);

    cout << endl;

    return 0;
}
