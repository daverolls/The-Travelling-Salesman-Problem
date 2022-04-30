#include "climb_chromosome.hh"
#include <cassert>

class AlternatingChromosome : public virtual ClimbChromosome{
 public:
   // Calling it's constructor as needed
   AlternatingChromosome(const Cities* cities_ptr): ClimbChromosome::ClimbChromosome(cities_ptr){}

   // We overwrite this function for a slightly better one
   std::pair<Chromosome*, Chromosome*> recombine(const Chromosome* other) override;

 protected:
   Chromosome* create_alter_edge_crossover_child(const Chromosome* ptr1, const Chromosome* ptr2) const;
};
