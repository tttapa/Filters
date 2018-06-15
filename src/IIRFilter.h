#ifndef IIRFILTER_H
#define IIRFILTER_H

#ifndef ARDUINO
#include <cstdint>
#endif
#include "Filter.h"

class IIRFilter : public Filter {
  public:
    template <size_t B, size_t A>
    IIRFilter(const double (&b)[B], const double (&_a)[A]) : lenB(B), lenA(A-1) {
      x = new double[lenB]();
      y = new double[lenA]();
      coeff_b = new double[2*lenB-1];
      coeff_a = new double[2*lenA-1];
      double a0 = _a[0];
      const double *a = &_a[1];
      for (uint8_t i = 0; i < 2*lenB-1; i++) {
        coeff_b[i] = b[(2*lenB - 1 - i) % lenB] / a0;
      }
      for (uint8_t i = 0; i < 2*lenA-1; i++) {
        coeff_a[i] = a[(2*lenA - 2 - i) % lenA] / a0;
      }
    }
    ~IIRFilter() {
      delete[] x;
      delete[] y;
      delete[] coeff_a;
      delete[] coeff_b;
    }
    double filter(double value) {
      x[i_b] = value;
      double b_terms = 0;
      double *b_shift = &coeff_b[lenB - i_b - 1];
      for (uint8_t i = 0; i < lenB; i++) {
        b_terms += x[i] * b_shift[i];
      }
      double a_terms = 0;
      double *a_shift = &coeff_a[lenA - i_a - 1];
      for (uint8_t i = 0; i < lenA; i++) {
        a_terms += y[i] * a_shift[i];
      }
      double filtered = b_terms - a_terms;
      y[i_a] = filtered;
      i_b++;
      if(i_b == lenB)
        i_b = 0;
      i_a++;
      if(i_a == lenA)
        i_a = 0;
      return filtered;
    }
  private:
    const uint8_t lenB, lenA;
    uint8_t i_b = 0, i_a = 0;
    double *x;
    double *y;
    double *coeff_b;
    double *coeff_a;
};

#endif
