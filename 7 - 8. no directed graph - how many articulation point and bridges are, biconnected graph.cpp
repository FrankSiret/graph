#include <bits/stdc++.h>
#include "..\graph.h"

using namespace std;

int dfsNumberCounter;
int prof[1001], tope[1001], articulation_vertex[1001];
set<pair<int,int>> bridges;

void dfs4(Graph &g, int u)
{
    tope[u] = prof[u] = ++dfsNumberCounter;
    g.markNode(u);
    for(int v: g.adjacentFromNode(u)) {
        if(!g.isMarkedNode(v)) {
            g.setParentNode(v,u);
            if(u == root) child ++;
            dfs4(g, v);
            if(u!=root && tope[v] >= prof[u]) articulation_vertex[u] = 1;
            if(tope[v] > prof[u]) bridges.insert({u,v});
            tope[u] = min(tope[u], tope[v]);
        }
        else if(v != g.getParentNode(u))
            tope[u] = min(tope[u], prof[v]);
    }
}

void articualtionPoints(Graph &g) {
    g.cleanNodesMark();
    dfsNumberCounter = 0;
    int connected_component = 0;
    for(int node: g.listOfNodes()) {
        if(!g.isMarkedNode(node)) {
            connected_component ++;
            child = 0;
            root = node;
            dfs4(g, root);
            if(child >= 2)
                articulation_vertex[root] = 1;
        }
    }
    int number_ap = 0;
    cout << "PREGUNTA 7" << endl;
    for(int node: g.listOfNodes()) {
        if(articulation_vertex[node]) {
            number_ap ++;
            cout << "articulation point " << node << endl;
        }
    }
    for(auto p: bridges) {
        cout << "bridges " << p.first << " " << p.second << endl;
    }
    for(int node: g.listOfNodes()) {
        cout << prof[node] << ' ';
    }
    cout << endl;
    for(int node: g.listOfNodes()) {
        cout << tope[node] << ' ';
    }
    cout << endl;

    cout << "\nPREGUNTA 8\n";
    if(number_ap == 0 && connected_component == 1)
        cout << "The graph is biconnected\n";
    else cout << "The graph is not biconnected\n";
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

    /* PREGUNTA 7 and 8 */
	// 7. How many articulation point and bridges there is in the graph
	// 8. Is the graph biconnected
    articualtionPoints(g);
    cout << endl;

    return 0;
}


