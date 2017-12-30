#ifndef FIRFILTER_H
#define FIRFILTER_H

class FIRFilter {
  public:
    template <size_t B>
    FIRFilter(const float (&b)[B]) : lenB(B) {
      x = new float[lenB]();
      coeff_b = new float[2*lenB-1];
      for (uint8_t i = 0; i < 2*lenB-1; i++) {
        coeff_b[i] = b[(2*lenB - 1 - i)%lenB];
      } 
    }
    ~FIRFilter() {
      delete[] x;
      delete[] coeff_b;
    }
    float filter(float value) {
      x[i_b] = value;
      float b_terms = 0;
      float *b_shift = &coeff_b[lenB - i_b - 1];
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
    float *x;
    float *coeff_b;
};

#endif