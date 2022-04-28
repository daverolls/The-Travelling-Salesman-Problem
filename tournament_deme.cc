#include "tournament_deme.hh"
#include <cmath>
#include <cassert>

//////////////////////////////////////////////////////////////////////////////
//
Chromosome* select_parent()
{
    // Initializing
    std::set<Chromosome*> compareHouse;
    Chromosome* chromeptr;
    std::set<int>::iterator it;

    std::uniform_int_distribution<int> distribution(0, power_of_two());
    std::uniform_int_distribution<int> randParent(0, pop_size_()-1);
    const int randp = (distribution(generator_));

    while ( randp > 0 ){
      chromeptr = pop_[(randParent(generator_))];
      compareHouse.insert(it, chromeptr);
      --randp;
    }

    while (compareHouse.size() > 1){
      if(compareHouse[0].get_fitness() > compareHouse.get_fitness(1) ) { compareHouse.erase(compareHouse[1]); }
      else { compareHouse.erase(compareHouse[0]); }
    }
}

//////////////////////////////////////////////////////////////////////////////
//
int TournamentDeme::power_of_two()
{
  std::uniform_int_distribution<int> exponent(1, pop_size_-1);
  int n = exponent(generator_);
  assert(std::pow(2, n) > 0 && std::pow(2, n) < MAX_INT);     // Prevent overflow
  while ( std::pow(2, n) > pop_size_ ){
    n = std::floor(std::sqrt(n));
  }
  return n;
}
