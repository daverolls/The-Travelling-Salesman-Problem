#include "chromosome.hh"
#include <cassert>


class ClimbChromosome : public Chromosome{
 public:
  // Calling it's constructor as needed
  ClimbChromosome(const Cities* cities_ptr): Chromosome::Chromosome(cities_ptr){}

  Chromosome* clone() const override
  {
      return new ClimbChromosome(*this);
  }

  void mutate() override;

 private:
   // The function which will mutate in a smart way
  Cities::permutation_t local_hill_climbing();

  // A helper function to computer fitness. As thats locked away
  double quick_fitness(Cities::permutation_t);
};
