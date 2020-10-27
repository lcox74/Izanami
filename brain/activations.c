#include "activations.h"

/*
 * A base activation that outputs a linear output. The derivative 
 * to this activation is:
 * 	f(x)' = 1;
 */
double
activation_identity(double x) {
	return x;
}

/*
 * An activation that is either 1 or 0. The derivative is:
 * 	f(x)' = 0;
 */
double
activation_binary_step(double x) {
	return (double)(x > 0.0);
}

/*
 * A common activation for ML with outputs between 0 - 1. The 
 * derivative is:
 * 	f(x)' = f(x) * (1 - f(x));
 */
double
activation_sigmoid(double x) {
	return 1.0 / (1.0 + exp(-x));
}

/*
 * Another common activation for ML with outputs between -1 and +1.
 * The derivative is:
 * 	f(x)' = 1 - pow(f(x), 2);
 */
double
activation_tanh(double x) {
	return tanh(x);
}

/*
 * ReLU is a common activation for convolutions, outputing 0 or x if
 * depending if x is negative or not. The derivative is:
 * 	f(x)' = (x > 0);
 */
double
activation_relu(double x) {
	return (x > 0.0) ? x : 0.0;
}

/*
 * Another activation common in convolutions, outputing between -inf 
 * and +inf. The derivative is:
 * 	f(x)' = (x > 0) ? 1 : 0.01; 
 */
double
activation_leaky_relu(double x) {
	return (x > 0.0) ? x : x * 0.01;
}

/*
 * Arctan outputs between -pi/2 and +pi/2. The derivative is:
 * 	f(x)' = 1 / (pow(x, 2) + 1);
 */
double
activation_arc_tan(double x) {
	return atan(x);
}

/*
 * The bent identity outputs between -inf and +inf. The derivative is:
 * 	f(x)' = 1 + ((x) / (2 * sqrt(pow(x, 2) + 1)));
 */
double
activation_bent_identity(double x) {
	return x + ((sqrt(pow(x, 2.0) + 1.0) - 1.0) / 2.0);
}

/*
 * The sinusoid outputs between -1 and 1. The derivative is:
 * 	f(x)' = cos(x);
 */
double
activation_sinusoid(double x) {
	return sin(x);
}

/*
 * Sinc outputs between -0.217234 and 1. The derivative is:
 * 	f(x)' = (x == 0) ? 0 : (cos(x)/x - sin(x)/pow(x,2));
 */
double
activation_sinc(double x) {
	return (x == 0.0) ? 1.0 : (sin(x) / x);
}

/*
 * Gaussian outputs between 0.0001^ and 1. The derivative is:
 * 	f(x)' = -2 * x * exp(-pow(x,2));
 */
double
activation_gaussian(double x) {
	return exp(-(pow(x, 2)));
}



