
/*
 * Working on a API design on how to use/process a DQN (Deep Q-Learning 
 * Network).
 *
 * TODO: USE MATRIX MULTIPLICATION
 */

#include "QModel.h"

int main(int argc, char** argv) {
    QModel model = QModel();
    model.setInput(3);
    model.addLayer(5);
    model.addLayer(16);
    model.setOutput(2);
    model.build();

    std::vector<double> input = { 4.0, 5.0, 2.3 };
    auto output = model.predict(input);

    printf("%F %F\n", output[0], output[1]);

    return 0;
}