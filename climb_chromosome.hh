#include "chromosome.hh"


class ClimbChromosome : public Chromosome{
 public:
  Chromosome* clone() const override
  {
      return new Chromosome(*this);
  }

  void mutate() override;

 private:
  virtual Chromosome* local_hill_climbing();
}
