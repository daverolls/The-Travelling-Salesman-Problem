By Alonzo Ortiz-Sanchez & Dubin Nam

Compile command:
g++ -g -Wall -Wextra -pedantic -Werror -std=c++17 cities.cc chromosome.cc deme.cc climb_chromosome.cc tsp.cc tournament_deme.cc alternating_edge_crossover.cc -o tsp
For "original crossover" command was: `./tsp ../challenge.tsv 4 0.0075`
For "alternating edge crossover" command was: `./tsp ../challenge.tsv 40 0.05`

Valgrind gives no memory leaks for both of the newer functions!

All of our code was tested under the teacher's code. While we might find our own written code from part 2 slightly more helpful. Considering it has other helper functions and simplified things. We wish to test it with a baseline that everyone else has.

The raw code is in "raw code". Otherwise the zip is here

----------------------------------------------------------------------------------------------------

Small changes: I left "climb_chromosome" & "tournament_deme" on for both I believe.
I also added a line in the "chromosome.hh" file to allow "alternating_edge_crossover.*" to inherit protected members

<alternating_edge_crossover.hh>

Here I start the constructor for "ClimbChromosome" which starts the constructor for "Chromosome"
Than I override the "recombine()" function for Chromosome (It's fairly similar to the one provided in "Chromosome.cc").

Finally I have a protected function called "create_alter_edge_crossover_child()" which is used in "recombine()".

<alternating_edge_crossover.cc>
"create_alter_edge_crossover_child()" is a fairly complex function.
0. It follows Alternating edges crossover (AEX) (3.5) from the paper given.

How I understood the paper:
1. First two values in parent 1 are copied regardless for child.
2. We find first value found in parent1 to parent2. Than map the current value in parent2 to parent2 +1 index. To insert to child
3. And vise versa
4. If the mapped value is already found before. We choose a random number that has not been seen.
5. Keep doing this until child is full
6. Return child.

How the function works:
1. First it refuses to work if either of the parent's size is less than 2 cities long.
2. We immediately clone child and fill it with the first 2 numbers
3. Than we use a for loop which keeps track of the current index of the child.
4. We also have a vector of bools called "whatsFound" to track both parent's their values that we obtain from "currentIndex"
5. And finally we have "switch" which dictates which parent will map to whom. Based on an if statement
6. Each if statement gives favor to one parents. Like mapping parent1[i] -> parent2[i].
7. If the index number leads to a value previously found. A while loop starts and doesn't stop until a new unique index has been found.
8. Once satisfied. We update the child with the new values & update "whatsFound"
9. Keep running until we index the entire child
10. Assert if the child is valid and end.
