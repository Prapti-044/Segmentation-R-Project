#ifndef BINSEG_H
#define BINSEG_H

#include <math.h>
#include <set>
#include <vector>
#include <utility> //pair

int BINSEG(const double *data_vec, int n_data, int max_segments, int *seg_end, double *cost, double *before_mean, double *after_mean, int *, int *, int *invalidates_index, int *invalidates_before);


#endif // BINSEG_H
