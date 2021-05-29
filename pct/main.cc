#include <iostream>
#include <cstring>
#include "roll.hh"

using std::cout;
using std::endl;

extern int usage(const char *prog);
extern int runex(const char *prog, int argc, char const **argv);
extern int runexamples(const char *prog);
extern int pct(int argc, const char **argv);

int usage(const char *prog) {
  cout << endl
       << prog << ": compute roll success probability" << endl
       << endl
       << "usage:" << endl
       << "    " << prog << " thresh dice-or-bonus ..." << endl
       << endl
       << "    where thresh is the value you are attempting to attain," << endl
       << "    and dice-or-bonus either describes some dice (like 3d6) or" << endl
       << "    is a flat bonus to the roll (like 4); you can add many" << endl
       << "    different dice and bonus values, and bonus values may" << endl
       << "    be negative." << endl
       << endl;
  return runexamples(prog);
}

int runex(const char *prog, int argc, const char **argv) {
  argv[0] = prog;
  cout << endl
       << "    $";
  for (int argi = 0; argi < argc; ++argi)
    cout << " " << argv[argi];
  cout << endl
       << "    ";
  return pct(argc, argv);
}

int runexamples(const char *prog) {

  int rv = 0;
  {
    const char *argv[] = {
      "pct", "6", "1d12", "4", "2d4", 0
    };
    int argc = sizeof (argv) / sizeof (argv[0]) - 1;
    rv += runex(prog, argc, argv);
  }

  {
    const char *argv[] = {
      "pct", "7", "1d12", "4", "2d4", 0
    };
    int argc = sizeof (argv) / sizeof (argv[0]) - 1;
    rv += runex(prog, argc, argv);
  }

  {
    const char *argv[] = {
      "pct", "8", "1d12", "4", "2d4", 0
    };
    int argc = sizeof (argv) / sizeof (argv[0]) - 1;
    rv += runex(prog, argc, argv);
  }

  {
    const char *argv[] = {
      "pct", "12", "1d12", "4", "2d4", 0
    };
    int argc = sizeof (argv) / sizeof (argv[0]) - 1;
    rv += runex(prog, argc, argv);
  }

  {
    const char *argv[] = {
      "pct", "24", "1d12", "4", "2d4", 0
    };
    int argc = sizeof (argv) / sizeof (argv[0]) - 1;
    rv += runex(prog, argc, argv);
  }

  {
    const char *argv[] = {
      "pct", "25", "1d12", "4", "2d4", 0
    };
    int argc = sizeof (argv) / sizeof (argv[0]) - 1;
    rv += runex(prog, argc, argv);
  }
  return rv;
}

int main(int argc, const char **argv) {
  // this old C programmer is too lazy to find the C++ Way to strrchr.
  const char *prog = strrchr(argv[0], '/');
  if (prog) ++prog; else prog = argv[0];

  // if no parameters are being passed,
  // either we are doing the automated testing
  // or are being run with someone who does not
  // know what to pass.

  if (argc < 3) {
    return usage(prog);
  }

  return pct(argc, argv);
}


int pct(int argc, const char **argv) {
  // first arg is threshold
  // rest are "[digits]d[digits]" for dice,
  // or "+[digits]" for bonus,
  // or "-[digits]" for penalties

  Roll d;
  int thresh;
  {
    const char *arg = argv[1];
    if (1 != sscanf(arg, "%d", &thresh)) {
      cout << "error: could not parse roll threshold '" << arg << "'" << endl;
    }
  }

  for (int argi = 2; argi < argc; ++argi) {
    const char *arg = argv[argi];

    int lp = 0;
    int o1 = 0;
    unsigned rp = 0;
    int o2 = 0;

    // this old C programmer is too lazy to find the C++ Way to strlen.
    int w = (int)strlen(arg);
    int n = sscanf(arg, "%d%nd%u%n", &lp, &o1, &rp, &o2);

    if (n == 1) {
      if (o1 != w) {
        cout << "error: could not parse '" << arg << "' (starting at offset " << o1 << ")" << endl;
        return 1;
      }
      d.plus(lp);
      continue;
    }

    if (n == 2) {
      if (o2 != w) {
        cout << "error: could not parse '" << arg << "' (starting at offset " << o2 << ")" << endl;
        return 1;
      }
      while (lp-->0)
        d.roll(rp);
      continue;
    }

    cout << "error: could not parse '" << arg << "'" << endl;
    return 1;
  }
  d.print(thresh);

  // d.roll(12).plus(2).roll(4).roll(4).plus(2).print(14);

  return 0;
}
