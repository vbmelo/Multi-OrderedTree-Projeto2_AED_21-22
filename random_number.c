//
// Tomás Oliveira e Silva, AED, January 2022
//
// DO NOT CHANGE THIS CODE
//
// Random number generator interface
//
// In order to ensure reproducible results on Windows and GNU/Linux, we use a good random number generator, available at
//   https://www-cs-faculty.stanford.edu/~knuth/programs/rng.c
// This file has to be used without any modifications (but we changed its name from rng.c to random_knuth.h) so we take
// care of the main() function that is there by applying some C preprocessor tricks
//
// void aed_srandom(int seed) --- start the pseudo-random number generator
// int aed_random(void) --------- get the next pseudo-random number [0,2^30-1]
//

#include "AED_2021_A02.h"


#define main  random_knuth_main                      // main gets replaced by random_knuth_main
#ifdef __GNUC__
int random_knuth_main() __attribute__((__unused__)); // gcc will not complain if random_knuth_main() is not used
#endif
#include "random_knuth.h"
#undef main                                          // main becomes main again

void aed_srandom(int seed)
{ // start the pseudo-random number generator
  ran_start((long)seed);
}

int aed_random(void)
{ // get the next pseudo-random number [0,2^30-1]
  return (int)ran_arr_next();
}
