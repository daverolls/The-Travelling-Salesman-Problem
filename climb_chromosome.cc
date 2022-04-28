#include "climb_chromosome.hh"
#include <algorithm>
#include <cassert>



ClimbChromosome::ClimbChromosome(const Cities* cities_ptr)
  : cities_ptr_(cities_ptr),
    order_(random_permutation(cities_ptr->size())),
    generator_(rand())
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
ClimbChromosome::~ClimbChromosome()
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Perform a two mutations on this chromosome
void
ClimbChromosome::mutate()
{
  // Obtaing the best mutating for it based on p, p+1, p-1
  order_ = local_hill_climbing();
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// swap p with p+1, p==N-1 with 0. Get fitness
// compare the original, version1, version2
// fittest=chosen
Cities::permutation_t
ClimbChromosome::local_hill_climbing()
{
    std::cout << "I was ran to climb a hill!" << std::endl;
    // Defining
    Cities::permutation_t version2 = order_;
    Cities::permutation_t version3 = order_;
    Cities::permutation_t bestFit;
    int p;

    //get fitness
    std::uniform_int_distribution<int> dist(0, version2.size() - 1); //pick a random point
    p=[dist(generator_)];    //swap p with p-1. p==0 with N-1. Get fitness
    if (p == 0) {
        std::swap(version2[0], version2[version2.size()-1]);
    }
    else {std::swap(version2[p], version2[p-1]);}


    std::uniform_int_distribution<int> dist(0, version3.size() - 1);
    p=[dist(generator_)];
    if (p == version3.size()-1) {
        std::swap(version3[version3.size()-1], version3[0]);
    }
    else {std::swap(version3[p], version3[p+1]);}

    // Check which one is fitter
    if (quick_fitness(order_) > quick_fitness(version2)) { bestFit = order_; }
    else { bestFit = version2; }

    if ( quick_fitness(version3) > quick_fitness(bestFit)) { bestFit = version3; }

    return bestFit;
}

//////////////////////////////////////////////////////////////////////////////
// A helpful helper function to calculate the overral fitness .
// Without initilizing 2 extra children for it.
double quick_fitness(Cities::permutation_t sortedIndex) { return (1/(cities_ptr_->total_path_distance(sortedIndex))); }
