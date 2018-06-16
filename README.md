# Filters
An Arduino finite impulse response and infinite impulse response filter library.

## Digital filters
This library implements digital [finite impulse response](https://en.wikipedia.org/wiki/Finite_impulse_response) filters (FIR) 
and [infinite impulse response](https://en.wikipedia.org/wiki/Infinite_impulse_response) filters (IIR). 
Double precision floating point arithmetic is used.

### FIR
The difference equation for FIR filters is given by  
![FIR difference equation](https://wikimedia.org/api/rest_v1/media/math/render/svg/c43ba6c329a471401e87fe17c6130d801602ffdf)  
To initialize it in code, you can use:
```cpp
const double b_coefficients[] = { b_0, b_1, b_2, ... , b_N };
FIRFilter fir(b_coefficients);
```

### IIR
The difference equation for IIR filters is given by  
![IIR difference equation](https://wikimedia.org/api/rest_v1/media/math/render/svg/bddf0360f955643eeedc46d9be4b8f2d4f4d288f)  
```cpp
const double b_coefficients[] = { b_0, b_1, b_2, ... , b_P };
const double a_coefficients[] = { a_0, a_1, a_2, ... , a_Q };
IIRFilter iir(b_coefficients, a_coefficients);
```

### BiQuad Filters
When dealing with high-order IIR filters, they can get unstable.  
To prevent this, BiQuadratic filters (second order) are used.

Both Direct Form 1 and 2 are implemented.
```cpp
const double b_coefficients[] = { b_0, b_1, b_2 };
const double a_coefficients[] = { a_0, a_1, a_2 };
BiQuadFilterDF1 biquad1(b_coefficients, a_coefficients);
BiQuadFilterDF2 biquad2(b_coefficients, a_coefficients);
```
Optionally, you can specify a gain:
```cpp
const double b_coefficients[] = { b_0, b_1, b_2 };
const double a_coefficients[] = { a_0, a_1, a_2 };
const double gain = 1;
BiQuadFilterDF1 biquad1(b_coefficients, a_coefficients, gain);
BiQuadFilterDF2 biquad2(b_coefficients, a_coefficients, gain);
```

### Second Order Sections
Instead of manually cascading BiQuad filters, you can use a Second Order Sections filter (SOS).
```cpp
const double sosmatrix[][6] = {
    {b1_0, b1_1, b1_2,  a1_0, a1_1, a1_2 },
    {b2_0, b2_1, b2_2,  a2_0, a2_1, a2_2 }
};
const double gainarray[] = {1, 1};
SOSFilter<2> filter(sosmatrix, gainarray);
```
Here, `<2>` is the number of BiQuad filters in the SOS filter.

### Cascades of filters
You can apply multiple filters together in a cascade:
```cpp
Cascade<N> cascade({&filter1, &filter2, ..., &filterN});
```

## Usage
The library provides a `Filter` interface with a `filter` method that takes the new (raw) value as an intput, and outputs the new (filtered) value.

```cpp
double raw_value = getRawValue();
double filtered_value = fir.filter(raw_value);
```
You can use multiple filters on the input.
```cpp
double filtered_value = fir.filter(iir.filter(raw_value));
```
