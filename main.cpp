#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <iostream>
#include <fstream>

typedef boost::adjacency_list<> Graph;
typedef boost::erdos_renyi_iterator<boost::minstd_rand, Graph> ERGen;

int main(int argc, char *argv[]) {

  std::string file = "er2.gr";
  int scale = 10;
  double p = (double)0.25;
  for (int i=0; i < argc; ++i) {
    if (strcmp(argv[i], "--file") == 0) {
      file = argv[i+1];
    }

    if (strcmp(argv[i], "--scale") == 0) {
      scale = std::stoi(argv[i+1]);
    }

    if (strcmp(argv[i], "--p") == 0) {
      p = std::stod(argv[i+1]);
    }
  }

  uint64_t n = static_cast<uint64_t>(std::pow(2, scale));
  std::cout << "Scale = " << scale << std::endl;
  std::cout << "n = " << n << std::endl;
  std::cout << "p = " << p << std::endl;
  std::cout << "file = " << file << std::endl;

  std::ofstream myfile;
  myfile.open (file.c_str());
  myfile << "Vertex" << "\t" << "Degree\n";
  boost::minstd_rand gen;
  // Create graph with 100 nodes and edges with probability 0.05
  Graph g(ERGen(gen, n, p), ERGen(), n);
  BGL_FORALL_VERTICES_T(v, g, Graph) {
    myfile << v << "\t" << boost::out_degree(v, g) << "\n";
  }

  myfile.close();
  return 0;
}
