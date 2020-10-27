#ifndef IZANAMI_NETWORK_ACTIVATIONS_H_
#define IZANAMI_NETWORK_ACTIVATIONS_H_

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

#define ACT_MAX		10
#define ACT_IDEN 	0
#define ACT_BISTEP	1
#define ACT_SIG		2
#define ACT_TANH	3
#define ACT_RELU	4
#define ACT_LRELU	5
#define ACT_ATAN	6
#define ACT_BIDEN	7
#define ACT_SINU	8
#define ACT_SINC	9
#define ACT_GAUS	10
double (*iza_activations[])(double) = {
	activation_identity,
	activation_binary_step,
	activation_sigmoid,
	activation_tanh,
	activation_relu,
	activation_leaky_relu,
	activation_arc_tan,
	activation_bent_identity,
	activation_sinusoid,
	activation_sinc,
	activation_gaussian
};

#endif /* IZANAMI_NETWORK_ACITVATIONS_H_ */
