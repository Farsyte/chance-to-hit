#pragma once

typedef unsigned long long combos;

class Roll {
  combos den;
  int base;
  unsigned nums;
  combos *num;  

public:
  Roll() ;
  ~Roll() ;
  Roll &plus(int bonus) ;
  Roll &minus(int penalty) ;
  Roll &roll(unsigned faces) ;
  Roll &print(int thresh) ;
};
