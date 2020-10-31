#include "neuron.h"

#include <stdlib.h>
#include <string.h>

#include "../math/activations.h"

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
#define ACT_DEFAULT 2
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

/*
 * Processing a single neuron in the network with a given input and weights.
 * The product of the inputs and weights are summed and passed through to the
 * neurons selected activation function.
 */
double
process_neuron(struct iza_neuron *neuron, double *inputs, double *weights, 
    size_t input_size) 
{

	/* Error checking if the neuron has an activation set */
	if (!(neuron->n_flags & (NEU_ACTIVATION_SET)))
		return 0.0;

	/* The bulk of the processing */
	double sum = neuron->n_bias;
	for (size_t i = 0; i < input_size; i++) {
		sum += inputs[i] * weights[i];
	}

	return (neuron->n_output = neuron->n_activation(sum));
}

/*
 * Returns the last calculated output of the neuron.
 */
double
get_neuron_value(struct iza_neuron *neuron) 
{
	return neuron->n_output;
}

/*
 * Overriding the output of the neuron, used for input nodes. Returns 0
 * on success and non-zero on failure.
 */
int
override_neuron(struct iza_neuron *neuron, double new_output) 
{
	neuron->n_output = new_output;

	return 0;
}

/*
 * Sets an individual neuron's activation function. The supplied index
 * is capped at ACT_MAX. This also sets the flag to notify the neuron that
 * it's activation has been set. Returns 0 on success and non-zero on failure.
 */
int
set_neuron_activation(struct iza_neuron *neuron, size_t index) 
{
	size_t constrained_index = (index < ACT_MAX) ? index : ACT_MAX;
	neuron->n_activation = iza_activations[constrained_index]; 
	neuron->n_flags |= NEU_ACTIVATION_SET;

	return 0;
}

/*
 * Setting the bias of the neuron. The neuron currently can have any value 
 * for a bias. Returns 0 on success and non-zero on failure.
 */
int
set_neuron_bias(struct iza_neuron *neuron, double new_bias) 
{
	neuron->n_bias = new_bias;

	return 0;
}

/*
 * Allocates memory and creates a completly clean neuron. A default activation
 * of a signmoid function gets set as its default. This also sets the flags
 * to indicate a functional neuron. Returns 0 on success.
 */
int
create_neuron(struct iza_neuron *neuron) 
{
	neuron = (struct iza_neuron *) calloc(1, sizeof(struct iza_neuron));
	neuron->n_activation = iza_activations[ACT_DEFAULT];
	neuron->n_flags = NEU_CREATED | NEU_ACTIVATION_SET;

	return 0;
}

/*
 * Allocates memory and creates multiple clean empty neuron. A default 
 * activation of a signmoid function gets set as its default for each. 
 * This also sets the flags to indicate a functional neurons. 
 * Returns 0 on success.
 */
int
create_neurons(struct iza_neuron *neurons, size_t neurons_num) 
{
	neurons = (struct iza_neuron *) calloc(neurons_num,
	    sizeof(struct iza_neuron));

	for (size_t i = 0; i < neurons_num; i++) {
		neurons[i].n_activation = iza_activations[ACT_DEFAULT];
		neurons[i].n_flags = NEU_CREATED | NEU_ACTIVATION_SET;
	}

	return 0;
}

/*
 * Creates a copy of an existing neuron, taking its activation and bias.
 * This will be extended with mutations. Returns 0 on success.
 */
int
create_copy_neuron(struct iza_neuron *dest, struct iza_neuron *src) 
{
	dest = (struct iza_neuron *) calloc(1, sizeof(struct iza_neuron));
	*dest = *src;

	return 0;
}

/*
 * Neuron garbage collection, frees allocated memory properly.
 */
int
delete_neuron(struct iza_neuron *neuron) 
{
	free(neuron);

	return 0;
}

