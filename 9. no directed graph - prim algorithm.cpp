#include <bits/stdc++.h>
#include "..\graph.h"

using namespace std;

// costo, vertice
typedef pair<int, int> par;
typedef pair<int, par> est;
vector<par> G[105];
priority_queue<est, vector<est>, greater<est> > Q;
bool mark[105];

void mstPrim(Graph &g) {
    g.cleanNodesMark();
    int sol = 0;
    // importante respetar el orden (costo,vertice) para que Q ordene por costo
    Q.push({0,{g.root(),-1}}); // iniciamente con costo 0 en el nodo inicial
    while(!Q.empty()){
        int c = Q.top().first; // tomar el costo del tope de la cola
        int u = Q.top().second.first; // tomar el vertice a visitar
        int p = Q.top().second.second; // el padre de u
        Q.pop(); // sacar vertice de la cola
        if(!g.isMarkedNode(u)){ // si no esta marcado u
            g.markNode(u); // marco u
            sol += c; // tomo el costo de llegar al vertice u

            // IMPRIMIR RECORRIDO
            if(p != -1) { // si no es el nodo inicial
                cout << "costo (" << g.getNameOfNode(p) << "," << g.getNameOfNode(u) << ") = " << c << endl;
            }

            for(auto p : g.adjacentFromNodeWeighted(u)){ // recorro los adyacentes a u, nota es un par (costo,vertice)
                int v = p.second; // el nodo de destino
                if(!g.isMarkedNode(v)) {
                    int nc = p.first; // costo de la arista (u,v)
                    Q.push({nc, {v,u}}); // lleno la cola con los adyacentes a u con sus respectivos costos
                }
            }
        }
    }

    cout << "MST Prim " << sol << endl;
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


