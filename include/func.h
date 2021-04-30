#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <cstdint>

/////////////////////////////////////////////////////////////////////////////////////
extern std::ofstream vdata;
/////////////////////////////////////////////////////////////////////////////////////
typedef std::vector<std::vector<double>> DoubleVector;
/////////////////////////////////////////////////////////////////////////////////////
std::vector<int> mark_chain(const int steps, const int states,
                            const DoubleVector &p_matrix);
DoubleVector reformat_matrix(const DoubleVector &p_matrix);
DoubleVector ro_culc(const DoubleVector &p_matrix, const int steps);
void save_to_file(DoubleVector &vector);
void save_to_file(std::vector<int> &vector);
void save_to_file(std::vector<double> &vector);
/////////////////////////////////////////////////////////////////////////////////////