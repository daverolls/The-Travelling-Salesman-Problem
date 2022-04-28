//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using Alternating edges crossove.
// The child will first start at ptr1's number at the start of its index, and simply find where the first number of the index maps to the right.
// After its initilized, than
// Than with the second variable it maps it's current number, and tries to map it to the first index
Chromosome*
Chromosome::create_alter_edge_crossover_child(const Chromosome* ptr1, const Chromosome* ptr2) const{
  assert(ptr1->is_valid() && ptr2->is_valid());   // Ensuring their good

  // Obtaining an immutable ordering of the parent's index for readability
  const Cities::permutation_t parentOneOrdering = ptr1->get_ordering();
  const Cities::permutation_t parentTwoOrdering = ptr2->get_ordering();
  const unsigned int parOneSize = parentOneOrdering.size();
  const unsigned int parTwoSize = parentTwoOrdering.size();
  assert( parOneSize > 1 && parTwoSize > 1 && "Your doing TSP on a SINGLE city?");        // Ensuring their is atleast 2 cities were trying to index the best

  // Creating the child from ptr1. Since it's an exact copy. We can begin at the second index
  Chromosome* child = ptr1->clone();

  // Simple way to track which parent to interact with
  std::std::vector<bool> whatsFound(parOneSize, false);
  whatsFound[0] = true;  whatsFound[1] = true;      // Since the child is based on the first parent. We can ignore the first two numbers
  unsigned int currentIndex = 1;
  bool switch = true;

  std::cout << child->order_[0] << "->" child->order_[1] << std::endl;

  for ( unsigned i = 2; i <= parOneSize && i <= parTwoSize; ++i){
    if (~switch) {  // We changed child by using parent2, now parent1 time
      currentIndex = std::find(parentOneOrdering.cbegin(), parentOneOrdering.cbegin(), parentTwoOrdering[currentIndex])+1;

      // In case we go over the index size, or we have already been to that index
      // Than we pick random number until it's brand new
      while(whatsFound[currentIndex] || currentIndex > child->order_.size()-1) {
        currentIndex = std::uniform_int_distribution<int> distribution(0, child->order_.size()-1);
      }

      child->order_[i] = parentOneOrdering[currentIndex];
      whatsFound[currentIndex] = true;          // Keeping track
    }

    else if (switch) { // We changed child by using parent1, now parent2 time
      currentIndex = std::find(parentTwoOrdering.cbegin(), parentTwoOrdering.cbegin(), parentOneOrdering[currentIndex])+1;

      // In case we go over the index size, or we have already been to that index
      // Than we pick random number until it's brand new
      while(whatsFound[currentIndex] || currentIndex > child->order_.size()-1) {
        currentIndex = std::uniform_int_distribution<int> distribution(0, child->order_.size()-1);
      }

      child->order_[i] = parentTwoOrdering[currentIndex];
      whatsFound[currentIndex] = true;          // Keeping track
    }
    std::cout << child->order_[i-1] << "->" << child->order_[i] << std::endl;

    // False -> True, True -> False, and iterate
    switch = ~switch;
  }
  assert(child->is_valid());    // Checking if I did math right
  return child;
}
