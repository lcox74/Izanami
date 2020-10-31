#ifndef IZANAMI_MATH_ACTIVATIONS_H_
#define IZANAMI_MATH_ACTIVATIONS_H_

#include <math.h>

/* Useful functions for neurons */
double activation_identity(double);
double activation_binary_step(double);
double activation_sigmoid(double);
double activation_tanh(double);
double activation_relu(double);
double activation_leaky_relu(double);
double activation_arc_tan(double);
double activation_bent_identity(double);
double activation_sinusoid(double);
double activation_sinc(double);
double activation_gaussian(double);

#endif /* IZANAMI_MATH_ACTIVATIONS_H_ */
