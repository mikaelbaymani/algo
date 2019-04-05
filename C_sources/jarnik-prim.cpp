// Peer-graded Assignment: Homework 3: Compute the
// minimum spanning tree for an inputted graph

// title         :mbaymani-jarnik-prim
// description   :Compute the minimum spanning tree
// author        :Mikael Baymani
// date          :Jul 24 2018

#include <set>
#include <string>
#include <limits>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

const double INFINITY = numeric_limits<double>::infinity();

class Graph
{
  class Edge
  {
  public:
    Edge(int dest, double cost = INFINITY):
      dest(dest), cost(cost) { }
    int dest;          // destination
    double cost;       // distance
  };

  class Triplet
  {
  public:
    int first, second; // first & second node
    double cost;       // distance
    Triplet(): first(0), second(0), cost(0.0) { }
    friend istream& operator>>(istream& i, Triplet& t) { return i >> t.first >> t.second >> t.cost;}
  };

  int no_of_edges;
  int no_of_vertices;  // ...or nodes

  vector<double> node_values;
  vector<vector<Edge> > vertices; // connectivity matrix

public:
  Graph() { graphTest(); }
  Graph(string filename) {
    ifstream datafile(filename);
    if (datafile.good()) {
      string first_line;
      // Get first line of file
      getline(datafile, first_line);

      // The first line is # of vertices
      no_of_vertices = stoi(first_line);
      for (int vertex = 0; vertex < no_of_vertices; ++vertex) {
        node_values.push_back(INFINITY);
        vertices.push_back(vector<Edge>());
      }

      istream_iterator<Triplet> start(datafile), end;
      vector<Triplet> data(start, end);

      for (auto d : data) {
        add(d.first, d.second);
        setEdgeValue(d.first, d.second, d.cost);
      }
    }
    else {
      // No file found!
      graphTest();
    }
  }

  ~Graph() {
    for (int v = 0; v < no_of_vertices; ++v)
      vertices[v].clear();
    vertices.clear();

    node_values.clear();
  }

  // Ira Pohl's example from 4.3 Jarnik-Prim MST: Another look
  void graphTest() {
    no_of_vertices = 9;
    for (int vertex = 0; vertex < no_of_vertices; ++vertex) {
      node_values.push_back(INFINITY);
      vertices.push_back(vector<Edge>());
    }

    // from a..
    add(0, 1); setEdgeValue(0, 1,  4.0); // ..to b
    add(0, 7); setEdgeValue(0, 7,  8.0); // ..to h

    // from b..
    add(1, 0); setEdgeValue(1, 0,  4.0); // ..to a
    add(1, 2); setEdgeValue(1, 2,  8.0); // ..to c
    add(1, 7); setEdgeValue(1, 7, 11.0); // ..to h

    // from c..
    add(2, 1); setEdgeValue(2, 1,  8.0); // ..to b
    add(2, 3); setEdgeValue(2, 3,  7.0); // ..to d
    add(2, 5); setEdgeValue(2, 5,  4.0); // ..to f
    add(2, 8); setEdgeValue(2, 8,  2.0); // ..to i

    // from d..
    add(3, 2); setEdgeValue(3, 2,  7.0); // ..to c
    add(3, 4); setEdgeValue(3, 4,  9.0); // ..to e
    add(3, 5); setEdgeValue(3, 5, 14.0); // ..to f

    // from e..
    add(4, 3); setEdgeValue(4, 3,  9.0); // ..to d
    add(4, 5); setEdgeValue(4, 5, 10.0); // ..to f

    // from f..
    add(5, 4); setEdgeValue(5, 4, 10.0); // ..to e
    add(5, 3); setEdgeValue(5, 3, 14.0); // ..to d
    add(5, 2); setEdgeValue(5, 2,  4.0); // ..to c
    add(5, 6); setEdgeValue(5, 6,  2.0); // ..to g

    // from g..
    add(6, 5); setEdgeValue(6, 5,  2.0); // ..to f
    add(6, 8); setEdgeValue(6, 8,  6.0); // ..to i
    add(6, 7); setEdgeValue(6, 7,  1.0); // ..to h

    // from h..
    add(7, 6); setEdgeValue(7, 6,  1.0); // ..to g
    add(7, 0); setEdgeValue(7, 0,  8.0); // ..to a
    add(7, 8); setEdgeValue(7, 8,  7.0); // ..to i

    // from i..
    add(8, 7); setEdgeValue(8, 7,  7.0); // ..to h
    add(8, 2); setEdgeValue(8, 2,  2.0); // ..to c
    add(8, 6); setEdgeValue(8, 6,  6.0); // ..to g

    // MST = 37
  }

  // Returns the number of vertices in the graph
  inline int V() { return no_of_vertices; }
  // Returns the number of edges in the graph
  inline int E() { return no_of_edges; }

  /// \brief  Tests whether there is an edge from node x to node y
  /// \param  first - first node x
  /// \param  second - second node y
  /// \return true if edge exists, otherwise false
  bool adjacent(int first, int second) {
    for (auto& vertex : vertices[first]) {
      if (vertex.dest == second)
        return true;
    }
    return false;
  }

  /// \brief  Lists all nodes y such that there is an edge from x to y
  /// \param  node
  /// \param  vneighbors - is pased by reference
  /// \return void
  void neighbors(int node, vector<int>& vneighbors) {
    for (auto& vertex : vertices[node]) {
      if (vertex.cost != INFINITY) {
        vneighbors.push_back(vertex.dest);
      }
    }
  }

  /// \brief  Adds to G the edge from x to y, if it is not there
  /// \param  first - first node x
  /// \param  second - second node y
  /// \return void
  void add(int first, int second) {
    if ( !adjacent(first, second) ) {
      vertices[first].push_back( Edge(second) );
    }
  }

  /// \brief  Removes the edge from x to y, if it is there
  /// \param  first - first node x
  /// \param  seond - second node y
  /// \return void
  inline void _delete(int first, int second) { /*not implemented*/ }
  // Returns the value associated with the node x
  inline double getNodeValue(int x) { return node_values[x]; }
  // Sets the value associated with the node x to a
  inline void setNodeValue(int x, double a) { node_values[x] = a; }

  /// \brief  Returns the value associated to the edge (x,y)
  /// \param  first - first node x
  /// \param  second - second node y
  /// \return the cost associated to edge, otherwise INFINITY
  double getEdgeValue(int first, int second) {
    for (auto& vertex : vertices[first]) {
      if (vertex.dest == second)
        return vertex.cost;
    }
    return INFINITY;
  }

  /// \brief  Sets the value associated to the edge (x,y) to v
  /// \param  first - first node x
  /// \param  second - second node
  /// \param  cost - the distance between x and y
  /// \return void
  void setEdgeValue(int first, int second, double cost) {
    for (auto& vertex : vertices[first]) {
      if (vertex.dest == second) {
        vertex.cost = cost;
        if (cost != INFINITY)
          ++no_of_edges;
        else
          --no_of_edges;
        return ;
      }
    }
  }

  // --debug
  friend ostream& operator<<(ostream& os, const Graph& graph) {
    for (int vertex = 0; vertex < graph.no_of_vertices; ++vertex) {
      os << vertex;
      for (unsigned neighbor = 0; neighbor < graph.vertices[vertex].size(); ++neighbor)
        os << " ->  " << "(" << graph.vertices[vertex][neighbor].cost << ")"
           << graph.vertices[vertex][neighbor].dest;
    }
    return os;
  }

}; // Graph


template<typename E, typename V> class PriorityQueue
{
  vector<pair<E,V> > elements;

public:
  ~PriorityQueue() { elements.clear(); }

  /// \bried  Changes the priority (node value) of a queue element
  /// \param  elm - the element to change
  /// \param  val - new value that's associated with elm
  /// \return void
  void chgPriority(E elm, V val) {
    for (auto& item : elements) {
      if (item.first == elm) {
        item.second = val;
        sort(elements.begin(), elements.end(), [](pair<E,V> p1, pair<E,V> p2)
        {
          return p1.second < p2.second;
        });
        return ;
      }
    }
  }

  // Removes the top element of the queue
  inline void minPriority() { elements.erase(elements.begin()); }

  /// \brief  Does the queue contain queue_element
  /// \param  elm - element to look for
  /// \returns true if element exists, otherwise false
  bool contains(E elm) {
    for(auto item : elements) {
      if (item.first == elm)
        return true;
    }
    return false;
  }

  /// \brief  Insert queue_element into queue
  /// \param  elm - add element to queue
  /// \param  val - value associated with elm
  /// \return void
  void insert(E elm, V val) {
    elements.push_back( pair<E,V>(elm,val) );
    sort(elements.begin(), elements.end(), [](pair<E,V> p1, pair<E,V> p2)
    {
      return p1.second < p2.second;
    });
  }

  // Returns the top element of the queue
  inline pair<E,V> top() { return elements.front(); }
  // Returns the number of queue_elements
  inline int size() { return elements.size(); }
  inline void clear() { elements.clear(); }

  // --debug
  friend ostream& operator<<(ostream& os, PriorityQueue queue) {
    for (auto item : queue.elements)
      os << "(" << item.first << "," << item.second << ") ";
    return os;
  }

}; // PriorityQueue


class MinimumSpanningTree
{
  typedef pair<int, int> ipair;

public:
  MinimumSpanningTree(): saved_mst(INFINITY), graph() { }
  MinimumSpanningTree(string filename): saved_mst(INFINITY), graph(filename) { }
  ~MinimumSpanningTree() {
    this->reset();
  }

  /// \brief  Prim's algorithm - finds a minimum spanning tree
  /// \param  source - starting node
  /// \return *this object
  MinimumSpanningTree& jarnikPrim(int source = 0) {
    reset();

    int cursor;
    set<int> unvisited;         // Unvisited vertices (set data structure)

    double distance = 0.0;      // Distance from source to source
    queue.insert(ipair(source, source), 0.0);

    for (int vertex = 0; vertex < graph.V(); ++vertex) {
      unvisited.insert(vertex);  // All vertices are initially unvisited
    }

    while(queue.size() && !unvisited.empty()) {
      auto p = queue.top();      // Vertex with the least distance
                                 // will be selected first
      cursor = p.first.first;
      queue.minPriority();       // Remove cursor from queue

      auto it = unvisited.find(cursor);
      if (it != unvisited.end() ) {
        unvisited.erase( it );   // Mark as visited
        distance += p.second;    // Accum. distance
        if (p.first.first != p.first.second)
          saved_tree.push_back(p); // Save ref. for printing
      }

      vector<int> neighbors;
      graph.neighbors(cursor, neighbors);
      for (auto neighbor : neighbors) { // Go through list of neighbors
        if (unvisited.find(neighbor) != unvisited.end()) {
          // Add unvisited neighbors w/ distance to priority queue
          queue.insert(ipair(neighbor, cursor), graph.getEdgeValue(cursor, neighbor) );
        }
      }
    }

    // save distance
    saved_mst = unvisited.empty() ? distance : INFINITY;
    return *this;
  }

  void reset() {
    saved_mst = INFINITY;
    saved_tree.clear();
    queue.clear();
  }

  friend ostream& operator<<(ostream& os, MinimumSpanningTree& m) {
    os << "MST = " << m.saved_mst;
    for (auto p : m.saved_tree)
      os << ", " << p.first.second << "--" << p.second << "->" << p.first.first;
    return os;
  }

private:
  double saved_mst; // minimum spanning tree
  vector<pair<ipair, double>> saved_tree;

  Graph graph;
  PriorityQueue<ipair, double> queue;

}; // MinimumSpanningTree


int main(int argc, char* argv[])
{
  MinimumSpanningTree MST;

  cout << MST.jarnikPrim() << endl;

  return 0;
}

// EOF
