#ifndef BiQuadFilter_H
#define BiQuadFilter_H

#ifndef ARDUINO
#include <cstdint>
#endif
#include "Filter.h"

/* ------------ Direct Form I ------------ */

class BiQuadFilterDF1 : public Filter
{
public:
  BiQuadFilterDF1(const double (&b)[3], const double (&a)[3])
      : b_0(b[0] / a[0]),
        b_1(b[1] / a[0]),
        b_2(b[2] / a[0]),
        a_1(a[1] / a[0]),
        a_2(a[2] / a[0])
  {
  }
  BiQuadFilterDF1(const double (&b)[3], const double (&a)[2])
      : b_0(b[0]),
        b_1(b[1]),
        b_2(b[2]),
        a_1(a[0]),
        a_2(a[1])
  {
  }
  BiQuadFilterDF1(const double (&b)[3], const double (&a)[2], double gain)
      : b_0(gain *b[0]),
        b_1(gain *b[1]),
        b_2(gain *b[2]),
        a_1(a[0]),
        a_2(a[1])
  {
  }
  BiQuadFilterDF1(const double (&b)[3], const double (&a)[3], double gain)
      : b_0(gain * b[0] / a[0]),
        b_1(gain * b[1] / a[0]),
        b_2(gain * b[2] / a[0]),
        a_1(a[1] / a[0]),
        a_2(a[2] / a[0])
  {
  }
  double filter(double value)
  {
    double x_2 = x_1;
    x_1 = x_0;
    x_0 = value;
    double b_terms = x_0 * b_0 + x_1 * b_1 + x_2 * b_2;
    double a_terms = y_1 * a_1 + y_2 * a_2;
    y_2 = y_1;
    y_1 = b_terms - a_terms;
    return y_1;
  }

private:
  const double b_0;
  const double b_1;
  const double b_2;
  const double a_1;
  const double a_2;

  double x_0 = 0;
  double x_1 = 0;
  double y_1 = 0;
  double y_2 = 0;
};

/* ------------ Direct Form II ------------ */

class BiQuadFilterDF2 : public Filter
{
public:
  BiQuadFilterDF2(const double (&b)[3], const double (&a)[3])
      : b_0(b[0] / a[0]),
        b_1(b[1] / a[0]),
        b_2(b[2] / a[0]),
        a_1(a[1] / a[0]),
        a_2(a[2] / a[0])
  {
  }
  BiQuadFilterDF2(const double (&b)[3], const double (&a)[2])
      : b_0(b[0]),
        b_1(b[1]),
        b_2(b[2]),
        a_1(a[0]),
        a_2(a[1])
  {
  }
  BiQuadFilterDF2(const double (&b)[3], const double (&a)[2], double gain)
      : b_0(gain *b[0]),
        b_1(gain *b[1]),
        b_2(gain *b[2]),
        a_1(a[0]),
        a_2(a[1])
  {
  }
  BiQuadFilterDF2(const double (&b)[3], const double (&a)[3], double gain)
      : b_0(gain * b[0] / a[0]),
        b_1(gain * b[1] / a[0]),
        b_2(gain * b[2] / a[0]),
        a_1(a[1] / a[0]),
        a_2(a[2] / a[0])
  {
  }
  double filter(double value)
  {
    double w_2 = w_1;
    w_1 = w_0;
    w_0 = value - a_1 * w_1 - a_2 * w_2;
    double y = b_0 * w_0 + b_1 * w_1 + b_2 * w_2;
    return y;
  }

private:
  const double b_0;
  const double b_1;
  const double b_2;
  const double a_1;
  const double a_2;

  double w_0 = 0;
  double w_1 = 0;
};

#endif