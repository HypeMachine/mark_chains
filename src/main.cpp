#include "func.h"
#include <string>

std::ofstream vdata;
int main()
{
    std::string ex;
    DoubleVector ro;
    const uint8_t NUM_STATES = 2;
    const uint8_t NUM_STEPS = 10;
    std::vector<double> result(NUM_STEPS, 0);
    std::vector<int> buffer(NUM_STEPS, 0);
    int NUM_TESTS = 1000;
    DoubleVector prob_matrix = {
        {0.3, 0.7},
        {0.4, 0.6}};

    vdata.open(".//scripts/vectors.txt", std::ios_base::trunc);
    if (!vdata)

        vdata << NUM_STEPS - 1 << std::endl;
    while (NUM_TESTS--)
    {
        buffer = mark_chain(NUM_STEPS, NUM_STATES, reformat_matrix(prob_matrix));
        for (uint8_t i = 0; i < buffer.size(); i++)
        {
            result.at(i) += buffer.at(i);
        }
        buffer.clear();
    }
    for (uint8_t i = 0; i < result.size(); i++)
        result.at(i) = result.at(i) / 1000.0;

    save_to_file(result);

    ro = ro_culc(prob_matrix, NUM_STEPS);

    vdata.close();

    system("python3 .//scripts//plot.py &>> /dev/null");
    system("eog -f .//graphics//state_p*.jpeg &>> /dev/null");

    return 0;
}