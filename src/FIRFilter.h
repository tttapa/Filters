#ifndef FIRFILTER_H
#define FIRFILTER_H

#ifndef ARDUINO
#include <cstdint>
#endif
#include "Filter.h"

class FIRFilter : public Filter {
  public:
    template <size_t B>
    FIRFilter(const double (&b)[B]) : lenB(B) {
      x = new double[lenB]();
      coeff_b = new double[2*lenB-1];
      for (uint8_t i = 0; i < 2*lenB-1; i++) {
        coeff_b[i] = b[(2*lenB - 1 - i)%lenB];
      } 
    }
    ~FIRFilter() {
      delete[] x;
      delete[] coeff_b;
    }
    double filter(double value) {
      x[i_b] = value;
      double b_terms = 0;
      double *b_shift = &coeff_b[lenB - i_b - 1];
      for (uint8_t i = 0; i < lenB; i++) {
        b_terms += x[i] * b_shift[i];
      }
      i_b++;
      if(i_b == lenB)
        i_b = 0;
      return b_terms;
    }
  private:
    const uint8_t lenB;
    uint8_t i_b = 0;
    double *x;
    double *coeff_b;
};

#endif