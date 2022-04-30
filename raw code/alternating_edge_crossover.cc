#include "alternating_edge_crossover.hh"
#include <algorithm>

//////////////////////////////////////////////////////////////////////////////
// Return a pair of offsprings by recombining with another chromosome
// Note: this method allocates memory for the new offsprings
std::pair<Chromosome*, Chromosome*>
AlternatingChromosome::recombine(const Chromosome* other)
{
  assert(Chromosome::is_valid());
  assert(other->Chromosome::is_valid());

  // Make children:
  auto child1 = create_alter_edge_crossover_child(this, other);
  auto child2 = create_alter_edge_crossover_child(other, this);

  return std::make_pair(child1, child2);
}

//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using Alternating edges crossove.
// The child will first start at ptr1's number at the start of its index, and simply find where the first number of the index maps to the right.
// After its initilized, than
// Than with the second variable it maps it's current number, and tries to map it to the first index
Chromosome*
AlternatingChromosome::create_alter_edge_crossover_child(const Chromosome* ptr1, const Chromosome* ptr2) const{
  assert(ptr1->Chromosome::is_valid() && ptr2->Chromosome::is_valid());   // Ensuring their good

  // Obtaining an immutable ordering of the parent's index for readability
  const Cities::permutation_t parentOneOrdering = ptr1->get_ordering();
  const Cities::permutation_t parentTwoOrdering = ptr2->get_ordering();
  const unsigned int parOneSize = parentOneOrdering.size();
  const unsigned int parTwoSize = parentTwoOrdering.size();
  assert( parOneSize > 1 && parTwoSize > 1 && "Your doing TSP on a SINGLE city?");        // Ensuring their is atleast 2 cities were trying to index the best

  // Creating the child from ptr1. Since it's an exact copy. We can begin at the second index
  Chromosome* child = ptr1->clone();

  // Simple way to track which parent to interact with
  std::uniform_int_distribution<int> distribution(0, child->order_.size()-1);
  std::default_random_engine generator(rand());
  std::vector<bool> whatsFound(parOneSize, false);
  child->order_[0] = parentOneOrdering[0]; child->order_[1] = parentOneOrdering[1];
  whatsFound[parentOneOrdering[0]] = true;  whatsFound[parentOneOrdering[1]] = true;      // Since the child is based on the first parent. We can ignore the first two numbers
  unsigned int currentIndex = 1;
  bool switchh = true;

  for ( unsigned i = 2; i < parOneSize && i < parTwoSize; ++i){
    if (!switchh) {  // We changed child by using parent2, now parent1 time
      currentIndex = (*std::find(parentOneOrdering.cbegin(), parentOneOrdering.cbegin(), parentTwoOrdering[currentIndex]))+1;

      // In case we go over the index size, or we have already been to that index
      // Than we pick random number until it's brand new
      while(whatsFound[parentOneOrdering[currentIndex]] || currentIndex > child->order_.size()-1) {
        currentIndex = distribution(generator);
        if (!whatsFound[parentOneOrdering[currentIndex]]) { break; }
        currentIndex = child->order_.size()+1;   // Cause while loop to run again
      }

      child->order_[i] = parentOneOrdering[currentIndex];
      whatsFound[parentOneOrdering[currentIndex]] = true;          // Keeping track
    }

    else if (switchh) { // We changed child by using parent1, now parent2 time
      currentIndex = (*std::find(parentTwoOrdering.cbegin(), parentTwoOrdering.cbegin(), parentOneOrdering[currentIndex]))+1;

      // In case we go over the index size, or we have already been to that index
      // Than we pick random number until it's brand new
      while(whatsFound[parentTwoOrdering[currentIndex]] || currentIndex > child->order_.size()-1) {
        currentIndex = distribution(generator);
        if (!whatsFound[parentTwoOrdering[currentIndex]]) { break; }
        currentIndex = child->order_.size()+1;    // Cause while loop to run again
      }

      child->order_[i] = parentTwoOrdering[currentIndex];
      whatsFound[parentTwoOrdering[currentIndex]] = true;          // Keeping track
    }

    // False -> True, True -> False, and iterate
    switchh = !switchh;
  }
  assert(child->Chromosome::is_valid());    // Checking if I did math right
  return child;
}
