#ifndef CASCADE_H
#define CASCADE_H

#include <cstddef>
#include "Filter.h"

template <size_t N>
class Cascade : public Filter
{
  public:
    Cascade(Filter * (&&filters)[N])
    {
        for (size_t i = 0; i < N; i++)
            this->filters[i] = filters[i];
    }
    double filter(double value)
    {
        for (Filter *&filter : filters)
            value = filter->filter(value);
        return value;
    }

  private:
    Filter *filters[N];
};

#endif // CASCADE_H