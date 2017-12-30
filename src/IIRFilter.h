#ifndef IIRFILTER_H
#define IIRFILTER_H

class IIRFilter {
  public:
    template <size_t B, size_t A>
    IIRFilter(const float (&b)[B], const float (&_a)[A]) : a0(_a[0]), lenB(B), lenA(A-1) {
      x = new float[lenB]();
      y = new float[lenA]();
      coeff_b = new float[2*lenB-1];
      coeff_a = new float[2*lenA-1];
      for (uint8_t i = 0; i < 2*lenB-1; i++) {
        coeff_b[i] = b[(2*lenB - 1 - i) % lenB];
      }
      float *a = &_a[1];
      for (uint8_t i = 0; i < 2*lenA-1; i++) {
        coeff_a[i] = a[(2*lenA - 2 - i) % lenA];
      }
    }
    ~IIRFilter() {
      delete[] x;
      delete[] y;
      delete[] coeff_a;
      delete[] coeff_b;
    }
    float filter(float value) {
      x[i_b] = value;
      float b_terms = 0;
      float *b_shift = &coeff_b[lenB - i_b - 1];
      for (uint8_t i = 0; i < lenB; i++) {
        b_terms += x[i] * b_shift[i];
      }
      float a_terms = 0;
      float *a_shift = &coeff_a[lenA - i_a - 1];
      for (uint8_t i = 0; i < lenA; i++) {
        a_terms += y[i] * a_shift[i];
      }
      float filtered = (b_terms - a_terms) / a0;
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
    const float a0;
    uint8_t i_b = 0, i_a = 0;
    float *x;
    float *y;
    float *coeff_b;
    float *coeff_a;
};

#endif