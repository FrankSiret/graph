/**
 * Graph class for Data Structure II, Universidad de Oriente, Cuba. Course 2019-2020
 * lots of implementation about graph theory
 * all implementations use the STL (Standard Template Library)
 * @note the nodes start in 0 (0-index)
 * @note maximum of nodes is 1000, if you want change it, then modify the class
 * @note use c++11 or above
 * @author Frank Rodriguez Siret
 * @link http://www.github.com/FrankSiret/Graph
 * @date feb 08, 2020
*/

#include <cassert>
#include <vector>
#include <set>
#define assertMsg(e,msg) ((e) ? (void)0 : _assert(msg, __FILE__, __LINE__))

using namespace std;

class Graph {
private:
	vector<int> _G[1001];
	bool _mark[1001];
	set<int> _nodes;
	int _index;

	bool _deleteIndexNode(vector<int> &adj, int idx);
	int _indexNode(vector<int> &adj, int node);
    bool _isNodeExist(int node) const;
public:
    /**
        default constructor
        @note linked list graph 1-index
    */
	Graph();
	/**
        copy constructor
        @note linked list graph 0-index
	*/
	Graph(const Graph &x);
	~Graph();
	/**
        insert in the graph a new node
        @return node inserted, in increment mode
	*/
	int insertNode();
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
        @return size of the graph
	*/
    int size();
    /**
        @arg edge (u,v) to insert, use isDirected=1 if the graph is directed
    */
    void insertEdge(int u, int v, bool isDirected=0);
    /**
        @arg edge (u,v) to delete, use isDirected=1 if the graph is directed
    */
    void deleteEdge(int u, int v, bool isDirected=0);
    bool checkEdge(int u, int v);
    vector<int> adjacencyList(int node) const;
    bool isMarkedNode(int node);
    void markNode(int node, int label=1);
    void dismarkNode(int node);
};

Graph::Graph() {
    _index = 0;
    _nodes.clear();
    for(int i=0; i<1001; i++){
        _G[i].clear();
        _mark[i] = 0;
    }
}
Graph::Graph(const Graph &x) {
    _nodes = x._nodes;
    _index = x._index;
    for(int i=0; i < _index; i++) {
        _mark[i] = x._mark[i];
        _G[i] = x._G[i];
    }
}
Graph::~Graph() { }
int Graph::insertNode() {
    _nodes.insert(_index);
    return _index++;
}
void Graph::deleteNode(int node) {
    assertMsg(_isNodeExist(node), "deleteNode: node does not exist");
    _mark[node] = 0;
    _nodes.erase(node);
    for(int i: _G[node])
        _deleteIndexNode(_G[i],_indexNode(_G[i], node));
    _G[node].clear();
}
vector<int> Graph::listOfNodes() const {
    vector<int> res;
    for(int n: _nodes)
        res.push_back(n);
    return res;
}
bool Graph::_deleteIndexNode(vector<int> &adj, int idx) {
    if(idx>=0) {
        adj.erase(adj.begin()+idx);
        return true;
    }
    return false;
}
int Graph::_indexNode(vector<int> &adj, int node) {
    int idx=0;
    while(idx<adj.size() && adj[idx++] != node);
    if(idx < adj.size())
        return idx;
    return -1;
}
int Graph::size() {
    return _nodes.size();
}
bool Graph::_isNodeExist(int node) const {
    return _nodes.find(node) != _nodes.end();
}
void Graph::insertEdge(int u, int v, bool isDirected) {
    assertMsg(_isNodeExist(u) && _isNodeExist(v), "insertEdge: the nodes u or v does not exist");
    _G[u].push_back(v);
    if(!isDirected)
        _G[v].push_back(u);
}
void Graph::deleteEdge(int u, int v, bool isDirected) {
    assertMsg(_isNodeExist(u) && _isNodeExist(v), "deleteEdge: the nodes u or v does not exist");
    _deleteIndexNode(_G[u], _indexNode(_G[u],v));
    if(!isDirected)
        _deleteIndexNode(_G[v], _indexNode(_G[v],u));
}
bool Graph::checkEdge(int u, int v) {
    assertMsg(_isNodeExist(u) && _isNodeExist(v), "checkEdge: the nodes u or v does not exist");
    return _indexNode(_G[u],v) >= 0;
}
vector<int> Graph::adjacencyList(int node) const {
    assertMsg(_isNodeExist(node), "adjacencyList: node does not exist");
    return _G[node];
}
bool Graph::isMarkedNode(int node) {
    assertMsg(_isNodeExist(node), "isMarkedNode: node does not exist");
    return _mark[node];
}
void Graph::markNode(int node, int label) {
    assertMsg(_isNodeExist(node), "markNode: node does not exist");
    _mark[node] = label;
}
void Graph::dismarkNode(int node) {
    assertMsg(_isNodeExist(node), "markNode: node does not exist");
    _mark[node] = 0;
}
