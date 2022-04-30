By Alonzo Ortiz-Sanchez & Dubin Nam

Compile command:
g++ -g -Wall -Wextra -pedantic -Werror -std=c++17 cities.cc chromosome.cc deme.cc climb_chromosome.cc tsp.cc tournament_deme.cc -o tsp
For "climb_chromosome", "tournament_deme", and baseline ga. Command was `./tsp challenge.tsv 40 0.5`
These were run seperately to avoid "tournament_deme" using the results from "climb_chromosome".

Valgrind gives no memory leaks for both of the newer functions!

All of our code was tested under the teacher's code. While we might find our own written code from part 2 slightly more helpful. Considering it has other helper functions and simplified things. We wish to test it with a baseline that everyone else has.

The raw code itself is compressed in a zip. Despite github doing that for you. It's how it is because that was the submission requirement.
However if you still wish to see the source_code without a zip. Simply go to "raw_source" folder.
For the extra credit one go to "raw_extra"

----------------------------------------------------------------------------------------------------


<climb_chromosome.hh>
First we made sure it initialized the base class by calling its constructor

We overwrote clone() and mutate().

Clone() here was simply defined to make a new ClimbChromosome with current class pointer used to "duplicate" it.
Mutate() simply called on our helper function local_hill_climbing(), and asserts if the current chromosome's "order_" is valid.


<climb_chromosome.cc>
local_hill_climbing() it's a helper function that does most of the work for mutate().
1. We keep track of 3 vectors of "permutation_t", and "p" which acts as our random index.
2. We first obtain the fitness of our current "order_"
3. We check where p lands in the index. If p-1 < 0. Than we will swap value p and the last index. And save the result in "version2"
4. We check where p lands in the index. If p+1 > index size, than we will swap value p and 0. And save result in "version3"
5. Everytime fitness is checked, we use our helper function ClimbChromosome(). Thus we check "version2" and "version3"'s fitness
6. Between the 3 new orderings. We now determine which one is fitter, and return that ordering as the new "order_"

ClimbChromosome() it's a helper helper function
1. It simple returns a "fitness". It simply takes the inverse (+1 on donominator) to see which one is the fittest.
2. This is to avoid having to create a chromosome or cities object.

<tournament_deme.hh>
We make sure to initialize the constructor of the base class.

We overwrite "select_parent()", and finally we have a private helper function called "power_of_two"


<tournament_deme.cc>
select_parent() The main function. It's quite bulky, but it simply grabs "randp" parents until only one is alive and alone
1. We have a "uniform_int_distribution" variable. To pick a random parents from the index's size.
2. We run and add parents to compare to "compareHouse" based on the result "randp".
3. We ensure each parent is unique. As "compareHouse" is a set and thus requires unique elements
4. We transform the unsigned size of our set "compareHouse" into an integer.
5. Than we simply check the first and second indexs at the front of the set.
6. After all no point into making it random since it requires to have only one lonely parents. Not n amount.
7. Return the *best parent (* = from what we randomly picked).

power_of_two() It's a nice helper function. It simply produces a random power of 2.
1. The exponent is selected from "pop_.size()" to give a chance for all or barely anything to be checked in the "pop_"
2. If it happens to be greater than, we simply keep reducing the exponent. This is slightly better than just randomizing it again. Considering that this runs at guaranteed linear timer, as oppose to some other time which is based on the size of "pop_".
(What if pop_.size() gives 10000? We would have a very slim chance to pick 1-13 as oppose to 14-10000.)
Returns 2^n or 2^(exponent chosen).
