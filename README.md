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

## Implementation
This library uses the straightforward [Direct Form I](https://en.wikipedia.org/wiki/Digital_filter#Direct_form_I) implementation.  
This is basically just calculating the difference equation in the form expressed above.  
In this documentation, we'll only look at the implementation of the FIR filter, but the IIR filter implementation is very similar.  
![FIR difference equation](https://wikimedia.org/api/rest_v1/media/math/render/svg/c43ba6c329a471401e87fe17c6130d801602ffdf)  
All we have to do is multiplying the previous input samples with their respective coefficients. 

  $$\vec{x}[n] = \{x[n-3], x[n-2], x[n-1], x[n]\}$$
  $$\vec{b} = \{b_3, b_2, b_1, b_0\}$$
  $$y[n]=\sum\limits_{i=0}^{3}b_i x[n-i] = \vec{b}\cdot\vec{x}[n] &emsp;(1)$$ 
The dot product can be very easily implemented using a for-loop.
Having to shift the buffer every time a new sample comes in is rather inefficient ($O(n)$). It would be better to use a ring buffer ($O(1)$). However, then we lose the simplicity of the dot product. Unless we shift the coefficient vector as well. If $\vec{x}[n]$ is a ring buffer, it could look like this (for $n=4k+2, k\in\mathbb{N}$):
$$\vec{x}[n] = \{x[n-2], x[n-1], x[n], x[n-3]\}$$
To ensure that $(1)$ is still valid, $\vec{b}$ should be as follows:
$$\vec{b} = \{b_2, b_1, b_0, b_3\}$$

The principle of a ring buffer is rather simple. Every time a sample is added, it is inserted into the array at index $j$, then $j$ is incremented. If $j$ is equal to the length of the array, it is reset to zero.
For example:
$$n = 0, j = 0:&emsp;x = [x[0], 0, 0, 0]$$
$$n = 1, j = 1:&emsp;x = [x[0], x[1], 0, 0]$$
$$n = 2, j = 2:&emsp;x = [x[0], x[1], x[2], 0]$$
$$n = 3, j = 3:&emsp;x = [x[0], x[1], x[2], x[3]]$$
$$n = 4, j = 0:&emsp;x = [x[4], x[1], x[2], x[3]]$$
$$n = 5, j = 1:&emsp;x = [x[4], x[5], x[2], x[3]]$$
$$n = 6, j = 2:&emsp;x = [x[4], x[5], x[6], x[3]]$$
$$n = 7, j = 3:&emsp;x = [x[4], x[5], x[6], x[7]]$$
$$etc.$$ 
Let's use the notation $x[n-i] = x_i$ to show the parallels between $x_i$ and $b_i$. $x_0$ represents the most recent sample, $x_1$ the previous sample, etc.
$$$$
There are four different situations that require a different coefficient vector $\vec{b_j}$:
$$j = 0:&emsp; \vec{x_0} = \{x_0, x_3, x_2, x_1\}, \vec{b_0} = \{b_0, b_3, b_2, b_1\}$$
$$j = 1:&emsp; \vec{x_1} = \{x_1, x_0, x_3, x_2\}, \vec{b_1} = \{b_1, b_0, b_3, b_2\}$$
$$j = 2:&emsp; \vec{x_2} = \{x_2, x_1, x_0, x_3\}, \vec{b_2} = \{b_2, b_1, b_0, b_3\}$$
$$j = 3:&emsp; \vec{x_3} = \{x_3, x_2, x_1, x_0\}, \vec{b_3} = \{b_3, b_2, b_1, b_0\}$$
We could use four different coefficient vectors, but that would be pretty wasteful. Instead, we can use a single, larger array:
$$\vec{b}=\{b_3, b_2, b_1, b_0, b_3, b_2, b_1\}$$
By changing the offset in this array, we can select any of the coefficient vectors used above:
$$\vec{b_j} = \vec{b}[4-1-j], j\in[0,3]$$
(Some vectors will be longer than others, but we only care about the first four elements.)
Now that we have the input vector $\vec{x}$ (the ring buffer) and the right coefficient vector $\vec{b_j}$ (depending on the index $j$ of the ring buffer), we can just multiply these two vectors to calculate the filter's output $y$.

### Code
Let's start with the easiest part: calculating the dot product of x and b_j.
```cpp
float sum = 0;
for (uint8_t i = 0; i < 4; i++) {
  sum += x[i] * b_j[i];
}
```
`sum` now contains the filter's output value.  

To calculate the extended b vector `coeff_b = { b_N, ..., b_2, b_1, b_0, b_N, ..., b_2, b_1 }` from a given vector `b = { b_0, b_1, b_2, ..., b_N }`, the following loop is used:
```cpp
coeff_b = new float[2*N-1];
for (uint8_t i = 0; i < 2*N-1; i++) {
  coeff_b[i] = b[(2*N - 1 - i)%N];
} 
```
To find the correct b_j vector, we can use the following:
```cpp
float *b_j = &coeff_b[N - 1 - j];
```
To update the x ring buffer with a new sample, we have to insert it at position j:
```cpp
x[j] = newSample;
```
Finally, we'll need some logic to increment and wrap around index j:
```cpp
j++;
if(j == N)
  j = 0;
```
