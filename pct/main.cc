#include <iostream>
#include "roll.hh"

using std::cout;
using std::endl;

int main(int argc, char **argv) {

  // first arg is threshold
  // rest are "[digits]d[digits]" for dice,
  // or "+[digits]" for bonus,
  // or "-[digits]" for penalties

  Roll d;
  int thresh;
  {
    char *token = argv[1];
    if (1 != sscanf(token, "%d", &thresh)) {
      cout << "error: could not parse '" << token << "'" << endl;
    }
  }

  for (int argi = 2; argi < argc; ++argi) {
    char *token = argv[argi];

    int lp = 0;
    int o1 = 0;
    unsigned rp = 0;
    int o2 = 0;

    int w = (int)strlen(token);
    int n = sscanf(token, "%d%nd%u%n", &lp, &o1, &rp, &o2);

    if (n == 1) {
      if (o1 != w) {
        cout << "error: could not parse '" << token << "' at offset " << o1 << endl;
        return 1;
      }
      d.plus(lp);
      continue;
    }

    if (n == 2) {
      if (o2 != w) {
        cout << "error: could not parse '" << token << "' at offset " << o2 << endl;
        return 1;
      }
      while (lp-->0)
        d.roll(rp);
      continue;
    }

    cout << "error: could not parse '" << token << "'" << endl;
    return 1;
  }
  d.print(thresh);

  // d.roll(12).plus(2).roll(4).roll(4).plus(2).print(14);

  return 0;
}
