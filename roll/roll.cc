#include "roll.hh"

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

Roll::Roll() {
  den = 1;
  base = 0;
  nums = 1;
  num = new combos[nums];
  num[0] = 1;
}

Roll::~Roll() {
  delete[] num;
}

Roll &Roll::plus(int bonus) {
  base += bonus;
  return *this;
}

Roll &Roll::minus(int penalty) {
  base -= penalty;
  return *this;
}

Roll &Roll::roll(unsigned faces) {
  unsigned olds = nums;
  combos *old = num;

  // compute new "number of possible combinations to roll"
  den *= faces;

  // compute new "minimum possible total"
  base ++;

  // compute new "number of possible totals"
  nums += faces - 1;

  // create a new array and initialize it to zero
  num = new combos[nums];
  for (unsigned i = 0; i < nums; ++i)
    num[i] = 0;

  // consider each possible old total
  // and each new roll, and accumulate the
  // number of ways to generate a new total.
  for (unsigned i = 0; i < olds; ++i)
    for (unsigned j = 0; j < faces; ++j)
      num[i+j] += old[i];

  // finally, free the memory holding the
  // old array.
  delete[] old;

  // return the original object, to allow us
  // to write "foo.roll(6).roll(6).roll(12)..." etc
  return *this;
}

double Roll::probability(int thresh) {

  int maxtotal = base + (int)nums;

  if (thresh <= base) {
    return 1.0;
  }

  if (thresh >= maxtotal) {
    return 0.0;
  }

  combos s = den;
  for (unsigned i = 0; i < nums; ++i) {
    if (base+(int)i == thresh) {
      return (double)s / (double)den;
    }
    s -= num[i];
  }

  // if we get here, there is an error in the logic,
  // as we should be either less than the base,
  // or greater than the max, or equal to one of the
  // values from base to max.
  //
  // the most likely bug would be an off-by-one error
  // in the computation if max, so blather about it
  // and presume the result is impossible.

  cerr << "looks like an off-by-one error in the probability code." << endl
       << "will presume the case is impossible, PLEASE FIX." << endl
       << "base = " << base << ", nums = " << nums << ", "
       << "maxtotal = " << maxtotal << ", thresh = " << thresh << endl;

  return 0.0;
}

Roll &Roll::print(int thresh) {

  double p = probability(thresh);
  if (p >= 1.0) {
    cout << "chances of rolling "
         << thresh
         << " or higher: "
         << " CERTAIN!"
         << " You can't roll less than " << base << endl;
    return *this; // remove this if printing the whole table
  }

  if (p <= 0.0) {
    cout << "chances of rolling "
         << thresh
         << " or higher: "
         << " IMPOSSIBLE!"
         << " You can't roll more than " << (base+(int)nums-1) << endl;
    return *this; // remove this if printing the whole table
  }

  // cout << "min " << base << " max " << base+(int)nums-1 << " combos " << nums << ":" << endl;
  cout << "chances of rolling "
       << thresh
       << " or higher: "
    // extra casts, because GCC warns us (correctly) that
    // conversion to ‘double’ from ‘unsigned long long’ may alter its value.
       << ((unsigned)(100.0 * p)) << "%"
       << endl;
  return *this;
}
