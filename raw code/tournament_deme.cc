#include "tournament_deme.hh"
#include <cmath>
#include <set>
#include <cassert>

//////////////////////////////////////////////////////////////////////////////
// We simply take "randp" parents
// Based on their fitness we keep purging them until 1 remains
Chromosome* TournamentDeme::select_parent()
{
    // Initializing
    std::set<Chromosome*> compareHouse;
    Chromosome* chromeptr;

    std::uniform_int_distribution<int> randParent(0, pop_.size()-1);
    int randp = power_of_two();

    while ( randp > 0 ){
      chromeptr = pop_[(randParent(generator_))];
      // Ensuring the randomly selected parents are already unique. Sets do not like the same item twice
      while(compareHouse.count(chromeptr)){chromeptr = pop_[(randParent(generator_))];}

      compareHouse.insert(chromeptr);
      --randp;
    }

    int houseSize = static_cast<int>(compareHouse.size());

    while ( houseSize > 1){
      auto compareIter1 = *(compareHouse.cbegin()); // Index of 0
      auto compareIter2 = *((compareHouse.cbegin())++); // Index of 1
      if(compareIter1->get_fitness() > compareIter2->get_fitness() ) { compareHouse.erase(compareIter2); }
      else { compareHouse.erase(compareIter1); }

      // Updating end condition
      houseSize = static_cast<int>(compareHouse.size());
    }
    // Returning out parent
    return *(compareHouse.cbegin());
}

//////////////////////////////////////////////////////////////////////////////
// Simply obtains at random some random power of 2.
// When its called it already assumes the minimum is 2^0
// So it picks from 2^1 - 2^(size of population)
// If it happens to be too big. We keep subtracting 1 from the exponent until correct
int TournamentDeme::power_of_two()
{
  std::uniform_int_distribution<int> exponent(1, pop_.size()-1);
  int n = exponent(generator_);

  while ( std::pow(2, n) > pop_.size() ){
    --n;    // Reducing the exponent
  }

  return std::pow(2,n);
}
