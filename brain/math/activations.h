#ifndef IZANAMI_MATH_ACTIVATIONS_H_
#define IZANAMI_MATH_ACTIVATIONS_H_

#include <math.h>

/* Useful activation functions */
double activation_identity(double x)    { return x; }
double activation_binary_step(double x) { return (double)(x > 0.0); }
double activation_sigmoid(double x)     { return 1.0 / (1.0 + exp(-x)); }
double activation_tanh(double x)        { return tanh(x); }
double activation_relu(double x)        { return (x > 0.0) ? x : 0.0; }
double activation_leaky_relu(double x)  { return (x > 0.0) ? x : x * 0.01; }
double activation_arc_tan(double x)     { return atan(x); }
double activation_bent_identity(double x) {
    return x + ((sqrt(pow(x, 2.0) + 1.0) - 1.0) / 2.0);
}
double activation_sinusoid(double x)    { return sin(x); }
double activation_sinc(double x)        { 
    return (x == 0.0) ? 1.0 : (sin(x) / x); 
}
double activation_gaussian(double x)    { return exp(-(pow(x, 2))); }

#endif /* IZANAMI_MATH_ACTIVATIONS_H_ */
