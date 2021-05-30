#pragma once

typedef unsigned long long combos;

class Roll {

  // the number of total ways we can roll.
  // Note: rolling a 6 and a 4, for example, is counted as
  // distinct from rolling a 4 and a 6.
  combos den;

  // the minimum total that can be rolled.
  // for example, if you are rolling "2d6 +2" this is 4.
  int base;

  // the number of distinct totals that can be obtained.
  // for example, if you are rolling "2d6 +2" this is 11.
  unsigned nums;

  // num points to an array, with one element for each possible
  // total, which contains the number of ways we can roll it.
  combos *num;  

public:

  // Create a new Roll object which is initialized to reflect
  // that you have one possible result (a zero) before you do anything.
  Roll() ;

  // Update the possible results, based on rolling one more die with the
  // specified number of faces.
  Roll &roll(unsigned faces) ;


  // Apply a bonus. For example, if you had rolled 2d6 (with results
  // ranging from 2 to 12), a bonus of +2 gives you results from 4 to 14.
  Roll &plus(int bonus) ;

  // Apply a penalty. For example, if you had rolled 2d6, and are at a -2
  // penalty, using "roll.minus(2)" gives results from 0 to 10.
  Roll &minus(int penalty) ;

  // Compute the probability that an actual roll made with the distribution
  // accumualted so far will have a total that meets or exceeds the given
  // threshold. Returns a value from 0.0 (impossible) to 1.0 (certain).
  double probability(int thresh);

  // ugly and temporary method that prints the probability of achieving
  // or exceeding the threshold with this roll.
  Roll &print(int thresh) ;

  // Destroy the object. Because this is C++ and we clean up after ourselves.
  ~Roll() ;
  
};
