
#include <vector>
#include <array>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <algorithm>

typedef unsigned int uint;

enum activation_e {
    SIGMOID,
    RELU
};


class QModel {
public:
    QModel() {
        srand( (unsigned)time(NULL) );
    }
    ~QModel() {}

    int setInput(uint nodes) {
        if (this->built) return this->in_nodes;

        this->in_nodes = nodes; 
        return nodes;
    }
    int addLayer(uint nodes, activation_e a = RELU) {
        if (this->built) return this->hidden_nodes.size();

        this->hidden_nodes.push_back({nodes, a});
        return this->hidden_nodes.size();
    }
    int setOutput(uint nodes, activation_e a = RELU) {
        if (this->built) return this->out_nodes.first;

        this->out_nodes = {nodes, a};
        return nodes;
    }

    int build() {
        uint i = 0;
        
        // Construct Input Nodes
        this->createNodes(this->in_nodes);

        // Determine next step
        if (this->hidden_nodes.size() > 0) {
            // Link input to first hidden layer
            this->createWeights(this->in_nodes, this->hidden_nodes[0].first);

            for (i = 0; i < this->hidden_nodes.size(); ++i) {
                this->createNodes(this->hidden_nodes[i].first);

                if ((i + 1) >= this->hidden_nodes.size()) {
                    // Link layer to output nodes
                    this->createWeights(this->hidden_nodes[i].first,
                                        this->out_nodes.first);
                } else {
                    // Link to next Layer
                    this->createWeights(this->hidden_nodes[i].first, 
                                        this->hidden_nodes[i+1].first);
                }
            }

        } else {
            // Link input directly to output nodes
            this->createWeights(this->in_nodes, this->out_nodes.first);
        }

        // Create Output Nodes
        this->createNodes(this->out_nodes.first);
        
        // Set model as built and ready for training
        this->built = true;
        return 0;
    }

    std::vector<double> predict(std::vector<double> input) {
        uint layer = 0, node = 0;

        // Evaluate/Set Inputs (Check size)
        if (input.size() != nodes[layer].size()) return {};
        nodes[layer++] = input;

        // Forward Propagate
        while (layer < this->nodes.size()) {
            while (node < this->nodes[layer].size()) {
                this->nodes[layer][node] = this->calcNode(layer, node);
                ++node;
            }
            node = 0;

            // Increment Layer
            ++layer;
        }

        return this->nodes[this->nodes.size() - 1];
    }

private:
    bool built = false;

    uint in_nodes;
    std::vector<std::pair<uint, activation_e>> hidden_nodes;
    std::pair<uint, activation_e> out_nodes;

    std::vector<std::vector<double>> nodes;
    std::vector<std::vector<double>> weights;

    void createNodes(uint num) {
        std::vector<double> temp;
        for (uint i = 0; i < num; ++i) {
            temp.push_back(0.0);
        }
        nodes.push_back(temp);
    }

    void createWeights(uint in, uint out) {
        std::vector<double> temp;
        for (uint i = 0; i < (in * out); ++i) {
            temp.push_back(1 - (2 * (rand() % RAND_MAX)));
        }
        weights.push_back(temp);
    }

    inline double relu (double a, double b) { return (a > b) ? a : b; }

    double calcNode(uint layer, uint node) {
        // weight = y * width + x
        // y = node (out node)
        // x = prevNode (layer - 1)
        // width = layer size

        double sum = 0.0;
        uint x = 0;
        
        // Sum Weights * Nodes
        for (x = 0; x < this->nodes[layer-1].size(); ++x) {
            sum += (this->nodes[layer-1][x]) * (this->weights[layer-1][node * this->nodes[layer].size() + x]);
        }

        // Activation function
        return this->relu(0.0, sum);
    }
};