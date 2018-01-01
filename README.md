# Filters
An Arduino finite impulse response and infinite impulse response filter library.

## Digital filters
This library implements digital [finite impulse response](https://en.wikipedia.org/wiki/Finite_impulse_response) filters (FIR) 
and [infinite impulse response](https://en.wikipedia.org/wiki/Infinite_impulse_response) filters (IIR). 
32-bit floating point arithmetic is used.

The difference equation for FIR filters is given by  
![FIR difference equation](https://wikimedia.org/api/rest_v1/media/math/render/svg/c43ba6c329a471401e87fe17c6130d801602ffdf)  
To initialize it in code, you can use:
```cpp
const float b_coefficients[] = { b_0, b_1, b_2, ... , b_N };
FIRFilter fir(b_coefficients);
```
The difference equation for FIR filters is given by  
![IIR difference equation](https://wikimedia.org/api/rest_v1/media/math/render/svg/bddf0360f955643eeedc46d9be4b8f2d4f4d288f)  
```cpp
const float b_coefficients[] = { b_0, b_1, b_2, ... , b_P };
const float a_coefficients[] = { a_0, a_1, a_2, ... , a_Q };
IIRFilter iir(b_coefficients, a_coefficients);
```

## Usage
The `filter` method takes the new (raw) value as an intput, and outputs the new (filtered) value.

```cpp
float raw_value = getRawValue();
float filtered_value = fir.filter(raw_value);
```
You can use multiple filters on the input.
```cpp
float filtered_value = fir.filter(iir.filter(raw_value));
```
