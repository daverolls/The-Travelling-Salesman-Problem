#include "deme.hh"

//////////////////////////////////////////////////////////////////////////////
class TournamentDeme : public Deme{
 public:
  // Calling "Deme" constructor for insurance
  TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate): Deme(cities_ptr, pop_size, mut_rate){}

  Chromosome* select_parent() override;

 private:
  // A helper function to calculate 2^n that is below the "pop_" size
  int power_of_two();
};
