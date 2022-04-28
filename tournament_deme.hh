#include "deme.hh"

//////////////////////////////////////////////////////////////////////////////
class TournamentDeme : public deme{
 public:
  Chromosome* select_parent() override;
 private:
  int TournamentDeme::power_of_two();
}
