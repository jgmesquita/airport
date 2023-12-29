/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <limits>
#include <numeric>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <utility>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
    T info;                // contents
    vector<Edge<T> > adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int indegree;          // auxiliary field
    int num;               // auxiliary field
    int low;               // auxiliary field

    void addEdge(Vertex<T> *dest, double w, unsigned airline);
    bool removeEdgeTo(Vertex<T> *d);
public:
    Vertex(T in);
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Edge<T>> &getAdj() const;
    void setAdj(const vector<Edge<T>> &adj);
    int getIndegree() const;

    void setIndegree(int indegree);

    int getNum() const;

    void setNum(int num);

    int getLow() const;

    void setLow(int low);

    friend class Graph<T>;
};

template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
    unsigned airline;
public:
    Edge(Vertex<T> *d, double w, unsigned airline);
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    double getWeight() const;
    void setWeight(double weight);
    unsigned getAirline() const;
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;      // vertex set
    int _index_;                        // auxiliary field
    stack<Vertex<T>> _stack_;           // auxiliary field
    list<list<T>> _list_sccs_;        // auxiliary field

    void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
    bool dfsIsDAG(Vertex<T> *v) const;
public:
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w, unsigned airline);
    bool removeEdge(const T &sourc, const T &dest);
    vector<Vertex<T> * > getVertexSet() const;
    vector<T> dfs() const;
    vector<T> dfs(const T & source) const;
    vector<T> bfs(const T &source) const;
    vector<T> topsort() const;
    bool isDAG() const;
    /**
    * @brief Dijkstra Algorithm to find the shortest path between two nodes.
    * @param start Start node.
    * @param end End node.
    * @return Vector that contains all nodes from the shortest path between two nodes.
    */
    vector<T> dijkstra(const T &start, const T &end) const {
        // Priority queue to store vertices with their distances
        priority_queue<pair<double, Vertex<T>*>, vector<pair<double, Vertex<T>*>>, greater<pair<double, Vertex<T>*>>> pq;

        // Map to store the distance from the start vertex to each vertex
        unordered_map<Vertex<T>*, double> distance;

        // Map to store the previous vertex in the shortest path
        unordered_map<Vertex<T>*, Vertex<T>*> previous;

        // Initialize distances and add the start vertex to the priority queue
        for (auto v : vertexSet) {
            distance[v] = numeric_limits<double>::infinity();
            previous[v] = nullptr;
        }

        Vertex<T> *startVertex = findVertex(start);
        Vertex<T> *endVertex = findVertex(end);

        if (!startVertex || !endVertex) {
            cerr << "Start or end vertex not found." << endl;
            return vector<T>();
        }

        distance[startVertex] = 0.0;
        pq.push({0.0, startVertex});

        while (!pq.empty()) {
            Vertex<T>* currentVertex = pq.top().second;
            pq.pop();

            if (currentVertex == endVertex) {
                // Reconstruct the path from end to start
                vector<T> path;
                while (currentVertex != nullptr) {
                    path.insert(path.begin(), currentVertex->getInfo());
                    currentVertex = previous[currentVertex];
                }
                return path;
            }

            for (const Edge<T>& edge : currentVertex->getAdj()) {
                Vertex<T>* neighbor = edge.getDest();
                double newDistance = distance[currentVertex] + edge.getWeight();

                if (newDistance < distance[neighbor]) {
                    distance[neighbor] = newDistance;
                    previous[neighbor] = currentVertex;
                    pq.push({newDistance, neighbor});
                }
            }
        }
        return vector<T>();
    }
};

template <class T>
Vertex<T>::Vertex(T in): info(in) {}
/**
 * @brief Constructor for the Edge of a node.
 * @param d Destination node.
 * @param w Weight of the connection.
 * @param airline Unsigned value of the position of the airline in the vector.
 */
template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, unsigned airline): dest(d), weight(w), airline(airline) {}
/**
* @brief Get the vector size of all nodes.
* @return Vector size of all nodes.
*/
template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}
/**
* @brief Get the vector with all nodes.
* @return Vector with all nodes.
*/
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}
/**
* @brief Get the content of the Vertex.
* @return Content of the Vertex.
*/
template<class T>
T Vertex<T>::getInfo() const {
    return info;
}
/**
* @brief Set the content of the vertex.
* @param in Content of the Vertex.
*/
template<class T>
void Vertex<T>::setInfo(T in) {
    Vertex::info = in;
}
/**
* @brief See if a Vertex is being processed.
* @return Boolean value if a Vertex is being processed.
*/
template<class T>
bool Vertex<T>::isProcessing() const {
    return processing;
}
/**
* @brief Set the boolean value if a Vertex is being processed.
* @param p Boolean value if a Vertex is being processed.
*/
template<class T>
void Vertex<T>::setProcessing(bool p) {
    Vertex::processing = p;
}
/**
* @brief Get the destination node.
* @return Destination node.
*/
template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}
/**
* @brief Set the destination node.
* @param d Destination node.
*/
template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}
/**
 * @brief Get the weight of the connection between two nodes.
 * @return Weight of the connection between two nodes.
 */
template<class T>
double Edge<T>::getWeight() const {
    return weight;
}
/**
* @brief Get the unsigned value of the position of the airline in the vector.
* @return Unsigned value of the position of the airline in the vector.
*/
template<class T>
unsigned Edge<T>::getAirline() const {
    return airline;
}
/**
* @brief Set the weight of the connection between two nodes.
* @param weight
*/
template<class T>
void Edge<T>::setWeight(double weight) {
    Edge::weight = weight;
}
/**
* @brief Auxiliary function to find a Vertex with a given content.
* @param in Type T object;
* @return Returns the Vertex.
*/
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}
/**
* @brief See if a Vertex is being visited.
* @return Boolean value if a Vertex is being visited.
*/
template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}
/**
* @brief Get the indegree of a Vertex.
* @return Indegree of a Vertex.
*/
template<class T>
int Vertex<T>::getIndegree() const {
    return indegree;
}
/**
 * @brief Set the indegree for a Vertex.
 * @param indegree Indegree of a Vertex.
 */
template<class T>
void Vertex<T>::setIndegree(int indegree) {
    Vertex::indegree = indegree;
}
/**
* @brief Get the distance that the node is visited
* @return num Distance that the node is visited.
*/
template<class T>
int Vertex<T>::getNum() const {
    return num;
}
/**
* @brief Set the distance that the node is visited.
* @param num Distance that the node is visited.
*/
template<class T>
void Vertex<T>::setNum(int num) {
    Vertex::num = num;
}
/**
* @brief Get the lowest distance that the node is visited.
* @return Lowest value.
*/
template<class T>
int Vertex<T>::getLow() const {
    return low;
}
/**
* @brief Set the lowest distance that the node is visited.
* @param low Lowest value.
*/
template<class T>
void Vertex<T>::setLow(int low) {
    Vertex::low = low;
}
/**
 * @brief Set the boolean value of a Vertex is being visited.
 * @param v Boolean value.
 */
template <class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}
/**
* @brief Get the vector of the adjacent nodes for a Vertex.
* @return Vector of the adjacent nodes for a Vertex.
*/
template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}
/**
* @brief Set the vector of the adjacent nodes for a Vertex.
* @param adj Vector of the adjacent nodes for a Vertex.
*/
template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}
/**
* @brief Adds a vertex with a given content or info (in) to a graph (this).
* @param in Type T object
* @return Returns true if successful, and false if a vertex with that content already exists.
*/
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}
/**
* @brief Adds an edge to a graph (this), given the contents of the source and
* destination vertices and the edge weight (w).
* @param sourc Source node.
* @param dest Destination node.
* @param w Weight of the connection.
* @param airline Unsigned value corresponding to the position of the airline in the vector.
* @return Returns true if successful, and false if the source or destination vertex does not exist.
*/
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, unsigned airline) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w, airline);
    return true;
}
/**
* @brief Auxiliary function to add an outgoing edge to a vertex (this),
* with a given destination vertex (d), edge weight (w) and airline (airline).
* @param d Vertex being visited.
* @param w Weight of the connection.
* @param airline Unsigned value corresponding to the position of the airline in the vector.
*/
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w, unsigned airline) {
    adj.push_back(Edge<T>(d, w, airline));
}
/**
* @brief Removes an edge from a graph (this).
* The edge is identified by the source (sourc) and destination (dest) contents.
* @param sourc Source node.
* @param dest Destination node.
* @return Returns true if successful, and false if such edge does not exist.
*/
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}
/**
* @brief Auxiliary function to remove an outgoing edge (with a given destination (d))
* from a vertex (this).
* @param d Vertex being visited.
* @return Returns true if successful, and false if such edge does not exist.
*/
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}
/**
* @brief Removes a vertex with a given content (in) from a graph (this), and
* all outgoing and incoming edges.
* @param in Type T object.
* @return Returns true if successful, and false if such vertex does not exist.
*/
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->info  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}
/**
 * @brief Performs a depth-first search (dfs) traversal in a graph (this).
 * @return Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (! v->visited)
            dfsVisit(v, res);
    return res;
}
/**
* @brief Auxiliary function that visits a vertex (v) and its adjacent, recursively.
* @param res Vetor com o resultado.
* @param v Vertex que está a ser visitado.
* @return Updates a parameter with the list of visited node contents.
*/
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto & e : v->adj) {
        auto w = e.dest;
        if ( ! w->visited)
            dfsVisit(w, res);
    }
}
/**
* @brief Performs a depth-first search (dfs) in a graph (this).
* @param source Source node.
* @return Returns a vector with the contents of the vertices by dfs order from the source node.
*/
template <class T>
vector<T> Graph<T>::dfs(const T & source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
}
/**
* @brief Performs a breadth-first search (bfs) in a graph (this), starting
* from the vertex with the given source contents (source).
* @param source Source node.
* @return Returns a vector with the contents of the vertices by bfs order.
*/
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex<T> *> q;
    for (auto v : vertexSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto & e : v->adj) {
            auto w = e.dest;
            if ( ! w->visited ) {
                q.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}
/**
* @brief Performs a depth-first search in a graph (this), to determine if the graph
* is acyclic (acyclic directed graph or DAG).
* During the search, a cycle is found if an edge connects to a vertex
* that is being processed in the stack of recursive calls (see theoretical classes).
* @return Returns true if the graph is acyclic, and false otherwise.
*/
template <class T>
bool Graph<T>::isDAG() const {
    for (auto v : vertexSet) {
        v->visited = false;
        v->processing = false;
    }
    for (auto v : vertexSet)
        if (! v->visited)
            if ( ! dfsIsDAG(v) )
                return false;
    return true;
}
/**
* @brief Auxiliary function that visits a vertex (v) and its adjacent, recursively.
* @return Returns false (not acyclic) if an edge to a vertex in the stack is found.
*/
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
    v->visited = true;
    v->processing = true;
    for (auto & e : v->adj) {
        auto w = e.dest;
        if (w->processing)
            return false;
        if (! w->visited)
            if (! dfsIsDAG(w))
                return false;
    }
    v->processing = false;
    return true;
}
/**
* @brief Performs a topological sorting of the vertices of a graph (this).
* Returns a vector with the contents of the vertices by topological order.
* If the graph has cycles, returns an empty vector.
* Follows the algorithm described in theoretical classes.
* @return vector to tipo T ordenado pelo algoritmo Topsort.
*/
template<class T>
vector<T> Graph<T>::topsort() const {
    vector<T> res;
    for (auto w: vertexSet) {
        w->indegree = 0;
    }

    for (auto v: vertexSet) {
        for (auto& e : v->adj) {
            e.dest->indegree++;
        }
    }

    queue<Vertex<T>*> q;
    for (auto v: vertexSet) {
        if (v->indegree == 0) {
            q.push(v);
        }
    }
    while(!q.empty()) {
        Vertex<T> * v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto& e : v->adj) {
            auto w = e.dest;
            w->indegree--;
            if (w->indegree == 0) {
                q.push(w);
            }
        }
    }
    if (res.size() != vertexSet.size()) {
        res.clear();
        return res;
    }
    return res;
}

#endif /* GRAPH_H_ */
