#include <bits/stdc++.h>
#include "..\graph.h"

using namespace std;

int P[1005];
int R[1005];

int find_set(int x)
{
    if(x != P[x])
        P[x] = find_set(P[x]);
    return P[x];
}

void merge_set(int x, int y)
{
    int fx = find_set(x);
    int fy = find_set(y);

    if(R[x] > R[y]){
        P[fy] = fx;
        R[fx] += R[fy];
    }
    else {
        P[fx] = fy;
        R[fy] += R[fx];
    }
}

void mstKruskal(Graph &g){
    for(int n: g.listOfNodes())
        P[n] = n, R[n] = 1;
    int sol = 0;

    for(auto e: g.listOfEdgesWeighted())
        Q.push({e.first,{e.second.first, e.second.second}});

    while(!Q.empty()){
        int c = Q.top().first;
        int u = Q.top().second.first;
        int v = Q.top().second.second;
        Q.pop();
        if(find_set(u) != find_set(v)){
            merge_set(u, v);
            cout << "costo (" << g.getNameOfNode(u) << "," << g.getNameOfNode(v) << ") = " << c << endl;
            sol += c;
        }
    }
    cout << "MST Kruskal " << sol << endl;
}

int main() {

    Graph g(0,1);
    g.insertNode({{1,"a"},{2,"b"},{3,"c"},{4,"d"},{5,"e"},{6,"f"},{7,"g"},{8,"h"}});

    g.insertEdgeWeighted(1,2,2);
    g.insertEdgeWeighted(1,3,3);
    g.insertEdgeWeighted(2,4,2);
    g.insertEdgeWeighted(3,4,1);
    g.insertEdgeWeighted(4,5,2);
    g.insertEdgeWeighted(4,6,4);
    g.insertEdgeWeighted(5,6,1);
    g.insertEdgeWeighted(5,7,2);
    g.insertEdgeWeighted(6,7,2);
    g.insertEdgeWeighted(6,8,1);
    g.insertEdgeWeighted(7,8,3);

    mstKruskal(g);

    return 0;
}


