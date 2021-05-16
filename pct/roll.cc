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
  // cout << "min " << base << " max " << base+(int)nums-1 << " combos " << nums << ":" << endl;
  combos s = den;
  for (unsigned i = 0; i < nums; ++i) {
    if (base+(int)i == thresh)
      cout << "chances of rolling "
           << thresh
           << " or higher: "
           << s
           << " in "
           << den
           << " or "
           << ((unsigned)(s * 100.0 / den)) << "%"
           << endl;
    s -= num[i];
    // printf("%6u: %4.0f%% %16.0f this %16.0f are higher\n",
    // cout << base + (int)i << ": "
    //      << (unsigned)(num[i] * 100.0 / den) << "% "
    //      << num[i] << " " << s << " " << den << endl;
  }
  return *this;
}
