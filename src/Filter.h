#ifndef FILTER_H
#define FILTER_H

class Filter
{
  public:
    virtual ~Filter() {}
    virtual double filter(double) = 0;
};

#endif // FILTER_H