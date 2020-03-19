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
    cout << "PREGUNTA 4" << endl;
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

    cout << "\nPREGUNTA 5\n";
    if(number_ap == 0 && connected_component == 1)
        cout << "The graph is biconnected\n";
    else cout << "The graph is not biconnected\n";

    /*map<int,set<int>> componentes_biconexas;
    for(int i: g.listOfNodes()) {
        if(prof[i] == tope[i])
            componentes_biconexas[tope[i]].insert(i);
        else {
            int t = tope[i];
            if(t == tope[t])
                componentes_biconexas[t].insert(i);
        }
    }*/
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

    /* PREGUNTA 1 */
	// Is the graph connected
    cout << "PREGUNTA 1" << endl;
    isConnected(g);
    cout << endl;

    /* PREGUNTA 2 */
	// how many connected components does the graph have
    cout << "PREGUNTA 2" << endl;
    connectedComponent(g);
    cout << endl;

    /* PREGUNTA 3 */
	// Is a node in the graph articualtion point
    cout << "PREGUNTA 3" << endl;
    vector<int> V = g.listOfNodes();
    for(int v: V) {
        isArticulationPoint(g, v);
    }
    cout << endl;

    /* PREGUNTA 4, 5 y 6 */
	// 4. How many articulation point and bridges there is in the graph
	// 5. Is the graph biconnected
    articualtionPoints(g);
    cout << endl;

    return 0;
}


