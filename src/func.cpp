#include "func.h"
#include <unistd.h>

/* TODO: добавить проактические вычисления для ro
почему mark_chain не изменяет значения*/
////////////////////////////////////////////////////////////////////////////////////
static std::vector<double> generate_numeric(const std::vector<double> &p_matrix_row);
/*std::vector<int> mark_chain(const int steps, const int states,
                            const DoubleVector &axis_p_matrix);
DoubleVector reformat_matrix(const DoubleVector &p_marix);
DoubleVector ro_culc(const DoubleVector &p_matrix, const int steps);*/
/////////////////////////////////////////////////////////////////////////////////////
// ? Generate vector of states by step
// ! first state chose randomly
std::vector<int>
mark_chain(const int steps, const int states,
           const DoubleVector &axis_p_matrix)
{
    double cur_prob = 0.0;
    std::vector<int> current_state(steps, 0);
    current_state[0] = 1; //int)(rand() % states);
    for (uint8_t i = 1; i < steps; i++)
    {
        cur_prob = (1.0 * rand()) / RAND_MAX;
        for (uint j = 0; j < axis_p_matrix.at(current_state.at(i - 1)).size(); j++)
        {
            if (cur_prob >= axis_p_matrix.at(current_state.at(i - 1)).at(j))
            {
                current_state[i] = j;
            }
        }
    }
    //save_to_file(current_state);
    return current_state;
}

// ? reform vector of probs [0.5 , 0.3 , 0.2] to number line [0.5, 0.8 1]
std::vector<double> generate_numeric(const std::vector<double> &p_matrix_row)
{
    std::vector<double> numeric;

    numeric.push_back(0);
    numeric.push_back(p_matrix_row.at(0));
    for (uint8_t i = 2; i < p_matrix_row.size() + 1; i++)
    {
        numeric.push_back(numeric.at(i - 1) + p_matrix_row.at(i - 1));
    }

    return numeric;
}
// ? "generate_numeric()" for all prob matri    x
DoubleVector reformat_matrix(const DoubleVector &p_matrix)
{
    DoubleVector reformat_p_matrix;

    for (uint i = 0; i < p_matrix.size(); i++)
    {
        reformat_p_matrix.push_back(generate_numeric(p_matrix.at(i)));
    }

    return reformat_p_matrix;
}
// ? calculate values of prob. for every state on every step
// ! value on first step for every state = 1 / num_states
DoubleVector ro_culc(const DoubleVector &p_matrix, const int steps)
{
    uint8_t states_num = p_matrix.size();
    DoubleVector ro(states_num);
    double prob = double(1) / (double)states_num;

    //? Вероятность первого вхождения в i-е из состояний
    for (uint8_t state = 0; state < states_num; state++)
    {
        ro.at(state).push_back(0);
    }
    ro.at(0).at(0) = 1;

    prob = 0;

    for (uint8_t step = 1; step < steps; step++)
    {
        for (uint8_t state = 0; state < states_num; state++)
        {
            for (uint8_t i = 0; i < states_num; i++)
            {
                prob += ro.at(i).at(step - 1) * p_matrix.at(i).at(state);
            }
            ro.at(state).push_back(prob);
            prob = 0;
        }
    }
    save_to_file(ro);

    return ro;
}

void save_to_file(DoubleVector &vector)
{
    for (int i = 0; i < (int)vector.size(); i++)
    {
        for (int j = 0; j < (int)vector.at(i).size() - 1; j++)
            vdata << vector.at(i).at(j) << ", ";

        vdata << vector.at(i).back() << std::endl;
    }
}

void save_to_file(std::vector<int> &vector)
{
    for (int i = 0; i < (int)vector.size() - 1; i++)
        vdata << vector.at(i) << ", ";

    vdata << vector.back() << std::endl;
}
void save_to_file(std::vector<double> &vector)
{
    for (int i = 0; i < (int)vector.size() - 1; i++)
        vdata << vector.at(i) << ", ";

    vdata << vector.back() << std::endl;
}