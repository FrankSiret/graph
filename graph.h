#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cassert>
#include <vector>
#include <set>

#define F first
#define S second

using namespace std;

struct _attrNode {
    string name;
    int mark;
    int parent;
    int distance;
    _attrNode()
        : name(""), mark(0), parent(-1), distance(INT_MIN) { }
    void clear()
    { clean(); name = ""; }
    void clean()
    { mark = 0; parent = -1; distance = INT_MIN; }
};

/**
 * Graph class using adjacency list for Data Structure II course, Universidad de Oriente, Cuba. 2019-2020.
 * All implementations use the STL (Standard Template Library). \
 * @note The nodes start in 0 (0-index), \
 * @note maximum of nodes is 1000, if you want change it, then modify the class, \
 * @note use c++11 or above. \
 * @author Frank Rodriguez Siret. \
 * @email frank.siret@gmai.com \
 * @link http://www.github.com/FrankSiret/Graph \
 * @date feb 08, 2020. \
 * @copyright
*/
class Graph {
private:
    vector<pair<int,int>> _G[1005];
    _attrNode _attr[1005];

    int _index;
    set<int> _nodes;
    bool _isDirected;
    bool _isWeighted;

    bool _deleteIndexNode(vector<pair<int,int>> &adj, int idx);
    int _indexNode(vector<pair<int,int>> &adj, int node);
public:
    /**
    constructor
    */
    Graph(bool isDirected = false, bool isWeighted = false);

    /**
    copy constructor
    */
    Graph(const Graph &x);

    /**
    assignment operator
    */
    Graph &operator=(const Graph &x);

    ~Graph() { }

    /**
    check the graph is empty
    */
    bool empty() {
        return _nodes.empty();
    }

    /**
    get root of graph
    */
    int root() {
    	if(_nodes.empty()) cout << "In method root check that the graph does not be empty" << endl;
    	assert(!_nodes.empty());
    	return *_nodes.begin();
    }

    /**
    clean marks, distance and parent in all nodes
    */
    void cleanNodesMark();

    /**
    insert in the graph the node
    @arg node: the node to insert
    @arg name: name of node if require, default is empty
    @return true if the node was inserted satisfactorily, false in other case
    */
    bool insertNode(int node, string name="");

    /**
    insert in the graph a list of nodes
    @arg args: list of nodes to insert
    */
    void insertNode(initializer_list<int> args);

    /**
    insert in the graph a list of named nodes
    @arg args: list of nodes to insert
    */
    void insertNode(initializer_list<pair<int,string>> args);

    /**
    insert in the graph all nodes between from-to including both
    @arg from: insert nodes begin in from
    @arg to: insert nodes end in to
    */
    void insertNode(int from, int to);

    /**
    delete node from the graph, and all connected edge with it
    @arg node: to delete from graph
    */
    void deleteNode(int node);

    /**
    @return list of actives nodes in the graph
    */
    vector<int> listOfNodes() const;

    /**
    list of actives edges in the graph
    @return vector of pairs that contains all edges of the graph (u,v)
    @note if the grafo is not directed the edge (u,v) appears just once
    @note return vector<u,v>
    */
    vector<pair<int,int>> listOfEdges() const;

    /**
    list of actives edges in the graph, include the weight of the edge
    @return vector of pairs that contains all weights and edges in shape of pairs (u,v) respectivity of the graph
    @note return vector<pair<weight,pair<u,v>>>
    */
    vector<pair<int,pair<int,int>>> listOfEdgesWeighted() const;

    /**
    check if one node exist in the graph
    @arg node: node to check
    @return true if the node exist, false in other case
    */
    bool isNodeExist(int node) const;

    /**
    @return count of nodes in the graph
    */
    int nodeSize();

    /**
    @return count of edges in the graph
    */
    int edgeSize();

    /**
    edge (u,v) to insert
    @arg u: node of origin
    @arg v: node of destination
    @note only for not weighted graph
    */
    void insertEdge(int u, int v);

    /**
    edge (u,v) to insert
    @arg u: node of origin
    @arg v: node of destination
    @arg weight: weight of the edge
    */
    void insertEdgeWeighted(int u, int v, int weight);

    /**
    edge (u,v) to delete
    @arg u: node of origin
    @arg v: node of destination
    */
    void deleteEdge(int u, int v);

    /**
    edge (u,v) to check if exist
    @arg u: node of origin
    @arg v: node of destination
    */
    bool checkEdge(int u, int v);

    /**
    list of adjacent nodes from the arg node
    @arg node: the origin node
    @return list with all nodes adjacent to node
    */
    vector<int> adjacentFromNode(int node);

    /**
    list of adjacent nodes from the arg node, include the weight of edge (node,v)
    @arg node: the origin node
    @return list of pair<weight,v> contains weight of edge (node,v) and adjacent node v from the arg node
    */
    vector<pair<int,int>> adjacentFromNodeWeighted(int node);

    /**
    check if one node is marked
    @arg node: node to check
    @return true if the node is marked, false in other case
    */
    bool isMarkedNode(int node);

    /**
    check if one node is marked
    @arg node: node to check
    @return mark of the label node
    */
    int getMarkNode(int node);

    /**
    mark one node
    @arg node: node to mark
    @arg label: write a label in the node marked, default is 1
    */
    void markNode(int node, int label=1);

    /**
    dismark one node
    @arg node: node to dismark
    */
    void dismarkNode(int node);

    /* last update */
    void setParentNode(int node, int parent);
    int getParentNode(int node);
    void setDistanceNode(int node, int distance);
    int getDistanceNode(int node);
    string getNameOfNode(int node);
};

bool Graph::_deleteIndexNode(vector<pair<int, int>> &adj, int idx) {
    if(idx>=0) {
        adj.erase(adj.begin()+idx);
        return true;
    }
    return false;
}

int Graph::_indexNode(vector<pair<int, int>> &adj, int node) {
    int idx=0;
    while(idx < (int)adj.size() && adj[idx].S != node) idx++;
    if(idx < (int)adj.size()) return idx;
    return -1;
}

Graph::Graph(bool isDirected, bool isWeighted) {
    _index = 0;
    _nodes.clear();
    _isDirected = isDirected;
    _isWeighted = isWeighted;
}

Graph::Graph(const Graph &x) {
    _nodes = x._nodes;
    _index = x._index;
    _isWeighted = x._isWeighted;
    for(int i=0; i < _index; i++) {
        _G[i] = x._G[i];
        _attr[i] = x._attr[i];
    }
}

Graph &Graph::operator=(const Graph &x) {
    if(this != &x) {
        _nodes = x._nodes;
        _index = x._index;
        _isDirected = x._isDirected;
        _isWeighted = x._isWeighted;
        for(int i=0; i < _index; i++) {
            _G[i] = x._G[i];
            _attr[i] = x._attr[i];
        }
    }
    return *this;
}

void Graph::cleanNodesMark() {
    for(int i=0; i < _index; i++) {
        _attr[i].clean();
    }
}

bool Graph::insertNode(int node, string name) {
    if(!(node >= 0 && node <= 1000)) cout << "In method insertNode the node " << node << " can not be inserted" << std::endl;
    assert(node >= 0 && node <= 1000);
    if(isNodeExist(node)) return false;
    _nodes.insert(node);
    _G[node].clear();
    _attr[node].name = name;
    _attr[node].mark = 0;
    _attr[node].parent = -1;
    _attr[node].distance = INT_MIN;
    _index = max(_index, node+1);
    return true;
}

void Graph::insertNode(initializer_list<int> args) {
    for(int node: args)
        insertNode(node);
}

void Graph::insertNode(initializer_list<pair<int,string>> args) {
    for(auto node: args)
        insertNode(node.F, node.S);
}

void Graph::insertNode(int from, int to) {
    for(int i=from; i <= to; i++)
        insertNode(i);
}

void Graph::deleteNode(int node) {
    if(!isNodeExist(node)) cout << "In method deleteNode the node " << node << " does not exist" << endl;
    assert(isNodeExist(node));
    _attr[node].mark = 0;
    _nodes.erase(node);
    for(auto p: _G[node]) {
        int adj = p.S;
        int idx = _indexNode(_G[adj], node);
        _deleteIndexNode(_G[adj],idx);
    }
    _G[node].clear();
}

vector<int> Graph::listOfNodes() const {
    vector<int> res;
    for(int n: _nodes)
        res.push_back(n);
    return res;
}

vector<pair<int, int> > Graph::listOfEdges() const {
    vector<pair<int,int>> res;
    for(int u: _nodes) {
        for(auto p: _G[u]) {
            int v = p.S;
            if(_isDirected && u > v) swap(u, v);
            res.push_back({u,v});
        }
    }
    return res;
}

vector<pair<int, pair<int, int> > > Graph::listOfEdgesWeighted() const {
    if(!_isWeighted) cout << "In method listOfEdgeWeighted the graph must be weighted, use listOfEdges method instead" << endl;
    assert(_isWeighted);
    vector<pair<int,pair<int,int>>> res;
    for(int u: _nodes) {
        for(auto p: _G[u]) {
            int weight = p.F;
            int v = p.S;
            if(_isDirected && u > v) swap(u, v);
            res.push_back({weight,{u,v}});
        }
    }
    return res;
}

bool Graph::isNodeExist(int node) const {
    return _nodes.find(node) != _nodes.end();
}

int Graph::nodeSize() {
    return _nodes.size();
}

int Graph::edgeSize() {
    return listOfEdges().size();
}

void Graph::insertEdge(int u, int v) {
    if(!(isNodeExist(u) && isNodeExist(v))) cout << "In method insertEdge the nodes " << u << " or " << v << " does not exist" << endl;
    assert(isNodeExist(u) && isNodeExist(v));

    if(_isWeighted) cout << "In method insertEdge can't be inserted edge because the graph is weighted, use insertEdgeWeighted method instead" << endl;
    assert(!_isWeighted);

    _G[u].push_back({1,v});
    if(!_isDirected) {
        _G[v].push_back({1,u});
    }
}

void Graph::insertEdgeWeighted(int u, int v, int weight) {
    if(!(isNodeExist(u) && isNodeExist(v))) cout << "In method insertEdge the nodes " << u << " or " << v << " does not exist" << endl;
    assert(isNodeExist(u) && isNodeExist(v));
    if(!_isWeighted) cout << "In method insertEdgeWeighted can't be inserted edge because the graph is not weighted, use insertEdge method instead" << endl;
    assert(_isWeighted);
    _G[u].push_back({weight,v});
    if(!_isDirected) {
        _G[v].push_back({weight,u});
    }
}

void Graph::deleteEdge(int u, int v) {
    if(!(isNodeExist(u) && isNodeExist(v))) cout << "In method deleteEdge the nodes " << u << " or " << v << " does not exist" << endl;
    assert(isNodeExist(u) && isNodeExist(v));
    _deleteIndexNode(_G[u], _indexNode(_G[u],v));
    if(!_isDirected) {
        _deleteIndexNode(_G[v], _indexNode(_G[v],u));
    }
}

bool Graph::checkEdge(int u, int v) {
    if(!(isNodeExist(u) && isNodeExist(v))) cout << "In method checkEdge the nodes " << u << " or " << v << " does not exist" << endl;
    assert(isNodeExist(u) && isNodeExist(v));
    return _indexNode(_G[u],v) >= 0;
}

vector<int> Graph::adjacentFromNode(int node) {
    if(!isNodeExist(node)) cout << "In method adjacentFromNode the node " << node << " does not exist" << endl;
    assert(isNodeExist(node));
    vector<int> res;
    for(auto p: _G[node])
        res.push_back(p.S);
    return res;
}

vector<pair<int, int> > Graph::adjacentFromNodeWeighted(int node) {
    if(!isNodeExist(node)) cout << "In method adjacentFromNodeWeighted the node " << node << " does not exist" << endl;
    assert(isNodeExist(node));
    if(!_isWeighted) cout << "In method adjacentFromNodeWeighted can't return adjacent nodes because the graph is not weighted, use adjacentFromNode method instead" << endl;
    assert(_isWeighted);
    vector<pair<int,int>> res;
    for(auto p: _G[node])
        res.push_back({p.F,p.S});
    return res;
}

bool Graph::isMarkedNode(int node) {
    if(!isNodeExist(node)) cout << "In method isMarkedNode the node " << node << " does not exist" << endl;
    assert(isNodeExist(node));
    return _attr[node].mark;
}

int Graph::getMarkNode(int node) {
    if(!isNodeExist(node)) cout << "In method isMarkedNode the node " << node << " does not exist" << endl;
    assert(isNodeExist(node));
    return _attr[node].mark;
}

void Graph::markNode(int node, int label) {
    if(!isNodeExist(node)) cout << "In method markNode the node " << node << " does not exist" << endl;
    assert(isNodeExist(node));
    _attr[node].mark = label;
}

void Graph::dismarkNode(int node) {
    if(!isNodeExist(node)) cout << "In method markNode the node " << node << " does not exist" << endl;
    assert(isNodeExist(node));
    _attr[node].mark = 0;
}

void Graph::setParentNode(int node, int parent) {
    _attr[node].parent = parent;
}

int Graph::getParentNode(int node) {
    return _attr[node].parent;
}

void Graph::setDistanceNode(int node, int distance) {
    _attr[node].distance = distance;
}

int Graph::getDistanceNode(int node) {
    return _attr[node].distance;
}

string Graph::getNameOfNode(int node) {
    return _attr[node].name;
}

#endif // GRAPH_H
