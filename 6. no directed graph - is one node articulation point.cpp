#include <bits/stdc++.h>
#include "..\graph.h"

using namespace std;

int child, root;

void dfs3(Graph &g, int u) {
    g.markNode(u);
    for(int v: g.adjacentFromNode(u)) {
        if(!g.isMarkedNode(v)) {
            if(u == root) child++;
            dfs3(g, v);
        }
    }
}

void isArticulationPoint(Graph &g, int u) {
    child = 0;
    g.cleanNodesMark();
    root = u;
    dfs3(g, root);
    if(child >= 2)
        cout << u << " is an articulation point\n";
    else cout << u << " is not an articulation point\n";
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

    /* PREGUNTA 6 */
	// Is a node in the graph articualtion point
    cout << "PREGUNTA 3" << endl;
    vector<int> V = g.listOfNodes();
    for(int v: V) {
        isArticulationPoint(g, v);
    }
    cout << endl;

    return 0;
}


