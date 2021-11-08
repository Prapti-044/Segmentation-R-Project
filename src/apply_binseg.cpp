#include "apply_binseg.h"

std::vector<double> get_cumsum(const std::vector<double> &data) {
  std::vector<double> cumsum;
  auto sum = 0.0;
  for(auto &i : data) {
    sum += i;
    cumsum.push_back(sum);
  }
  return cumsum;
}

void calculate_mean_cost(const std::vector<double> &cumsum_vec, int f, int l, double* mean, double* cost) {
  double total = cumsum_vec[l];
  if(0 < f){
    total -= cumsum_vec[f-1];
  }

  int N = l-f+1;
  *cost = -total*total/N;
  *mean = total/N;
}

class Split {
public:
  int this_end;
  std::pair<double, double> *before = new std::pair<double, double>(); // (mean, cost)
  std::pair<double, double> *after = new std::pair<double, double>(); // (mean, cost)

  double set_mean_cost(const std::vector<double> &cumsums, int first, int end_i, int last){
    this_end = end_i;
    calculate_mean_cost(cumsums, first, end_i, &(before->first), &(before->second));
    calculate_mean_cost(cumsums, end_i+1, last, &(after->first), &(after->second));
    return before->first + after->first;
  }
};

class Segment {
public:
  int first, last;
  int invalidates_index, invalidates_after;
  double best_decrease;
  Split best_split;

  friend bool operator<(const Segment& l, const Segment& r) {
    return l.best_decrease < r.best_decrease;
  }

  Segment(
    std::vector<double> &cumsums,
    int first,
    int last,
    int invalidates_after,
    int invalidates_index,
    double cost_no_split
  ):
    first(first),
    last(last),
    invalidates_after(invalidates_after),
    invalidates_index(invalidates_index)
  {
    Split candidate_split;
    int n_candidates = last-first;
    double best_cost_split = INFINITY, cost_split;
    for(int ci=0; ci<n_candidates; ci++){
      cost_split = candidate_split.set_mean_cost
      (cumsums, first, first+ci, last);
      if(cost_split < best_cost_split){
        best_cost_split = cost_split;
        best_split = candidate_split;
      }
    }
    best_decrease = best_cost_split - cost_no_split;
  }
};

class Candidates {
public:
  std::multiset<Segment> candidates;
  std::vector<double> cumsums;
  void maybe_add
    (int first, int last,
     int invalidates_after, int invalidates_index,
     double cost_no_split)
  {
    if(first < last){
      candidates.emplace
      (cumsums, first, last,
       invalidates_after, invalidates_index, cost_no_split);
    }
  }
};


int BINSEG(
  const double *data_vec,
  const int n_data,
  const int max_segments,
  int *seg_end,
  double *cost,
  double *before_mean,
  double *after_mean,
  int *before_size,
  int *after_size,
  int *invalidates_index,
  int *invalidates_after
) {
  Candidates V;
  const auto data = std::vector<double>(data_vec, data_vec + n_data);
  V.cumsums = get_cumsum(data);
  calculate_mean_cost(V.cumsums, 0, n_data-1, before_mean, cost);
  before_size[0] = n_data;
  seg_end[0] = n_data-1;
  after_mean[0] = INFINITY;
  after_size[0] = -2;
  invalidates_index[0]=-2;
  invalidates_after[0]=-2;
  V.maybe_add(0, n_data-1, 0, 0, cost[0]);
  for(int seg_i=1; seg_i < max_segments; seg_i++){
    std::multiset<Segment>::iterator it = V.candidates.begin();
    const Segment* s = &(*it);
    cost[seg_i] = cost[seg_i-1] + s->best_decrease;
    seg_end[seg_i] = s->best_split.this_end;
    before_mean[seg_i] = s->best_split.before->first;
    after_mean[seg_i] = s->best_split.after->first;
    invalidates_index[seg_i] = s->invalidates_index;
    invalidates_after[seg_i] = s->invalidates_after;
    before_size[seg_i] = s->best_split.this_end - s->first + 1;
    after_size[seg_i]  = s->last - s->best_split.this_end;
    V.maybe_add
      (s->first, s->best_split.this_end,
       0,
       seg_i, s->best_split.before->second);
    V.maybe_add
      (s->best_split.this_end+1, s->last,
       1,
       seg_i, s->best_split.after->second);
    V.candidates.erase(it);
  }
  return 0;
}


