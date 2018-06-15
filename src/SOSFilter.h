#ifndef SOSFILTER_H
#define SOSFILTER_H

#ifndef ARDUINO
#include <cstddef>
#endif
#include "BiQuadFilter.h"

template <size_t N>
class SOSFilter : public Filter
{
  public:
    SOSFilter(const double (&b)[N][3], const double (&a)[N][3], const double (&gain)[N])
    {
        for (size_t i = 0; i < N; i++)
            filters[i] = new BiQuadFilterDF2(b[i], a[i], gain[i]);
    }
    SOSFilter(const double (&sos)[N][6], const double (&gain)[N])
    {
        for (size_t i = 0; i < N; i++) {
            double b[3];
            double a[3];
            copy(b, &sos[i][0]);
            copy(a, &sos[i][3]);
            filters[i] = new BiQuadFilterDF2(b, a, gain[i]);
        }
    }
    SOSFilter(const double (&b)[N][3], const double (&a)[N][2], const double (&gain)[N])
    {
        for (size_t i = 0; i < N; i++)
            filters[i] = new BiQuadFilterDF2(b[i], a[i], gain[i]);
    }
    SOSFilter(const double (&b)[N][3], const double (&a)[N][2])
    {
        for (size_t i = 0; i < N; i++)
            filters[i] = new BiQuadFilterDF2(b[i], a[i]);
    }
    SOSFilter(const double (&b)[N][3], const double (&a)[N][3])
    {
        for (size_t i = 0; i < N; i++)
            filters[i] = new BiQuadFilterDF2(b[i], a[i]);
    }
    ~SOSFilter()
    {
        for (size_t i = 0; i < N; i++)
            delete filters[i];
    }
    double filter(double value)
    {
        for (Filter *&filter : filters)
            value = filter->filter(value);
        return value;
    }

  private:
    Filter *filters[N];
    template <size_t M>
    void copy(double (&dest)[M], const double *src) {
        for (size_t i = 0; i < M; i++)
            dest[i] = src[i];
    }
};

#endif // SOSFILTER_H