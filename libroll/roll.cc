#include "roll.hh"

#include <iostream>

using std::cout;
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

  den *= faces;
  base ++;
  nums += faces;
  nums --;
  num = new combos[nums];
  for (unsigned i = 0; i < nums; ++i)
    num[i] = 0;

  for (unsigned i = 0; i < olds; ++i)
    for (unsigned j = 0; j < faces; ++j)
      num[i+j] += old[i];

  delete[] old;

  return *this;
}

Roll &Roll::print(int thresh) {

  if (thresh <= base) {
      cout << "chances of rolling "
           << thresh
           << " or higher: "
           << " CERTAIN!"
           << " You can't roll less than " << base << endl;
      return *this; // remove this if printing the whole table
  }

  if (thresh >= (base + (int)nums)) {
      cout << "chances of rolling "
           << thresh
           << " or higher: "
           << " IMPOSSIBLE!"
           << " You can't roll more than " << base+nums-1 << endl;
      return *this; // remove this if printing the whole table
  }

  // cout << "min " << base << " max " << base+(int)nums-1 << " combos " << nums << ":" << endl;
  combos s = den;
  for (unsigned i = 0; i < nums; ++i) {
    if (base+(int)i == thresh) {
      cout << "chances of rolling "
           << thresh
           << " or higher: "
           << s
           << " in "
           << den
           << " or "
        // extra casts, because GCC warns us (correctly) that
        // conversion to ‘double’ from ‘unsigned long long’ may alter its value.
           << ((unsigned)((double)s * 100.0 / (double)den)) << "%"
           << endl;
      return *this; // remove this if printing the whole table
    }
    s -= num[i];
    // uncomment one of these to print the whole table
    // printf("%6u: %4.0f%% %16.0f this %16.0f are higher\n",
    // cout << base + (int)i << ": "
    //      << (unsigned)(num[i] * 100.0 / den) << "% "
    //      << num[i] << " " << s << " " << den << endl;
  }
  return *this;
}
