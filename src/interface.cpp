#include <Rcpp.h>
#include <R.h>
#include "apply_binseg.h"

//' Applies Binary Segmentation Algorithm to the given data data_vec
//'
//' \code{apply_binseg} returns the status of a successful Binary Segmentation algorithm on the given parameters.
//' Most of the passed parameters are set for the result.
//'
//' @param data_vec The 1 dimensional input chromosome data
//' @param kmax Maximum number of segments to divide.
//' @return Status code of the algorithm.
//'
//'   For description of how Binseg algorithm works, please see the following url.
//'   \url{https://arxiv.org/abs/1801.00718}
//' @examples
//' apply_binseg(c(0.1, 0, 1, 1.1, 0.1, 0), 3)
//' @export
// [[Rcpp::export]]
Rcpp::List apply_binseg
  (const Rcpp::NumericVector data_vec,
   const int kmax) {
  if(data_vec.size() < 1){
    Rcpp::stop("need at least one data point");
  }
  if(kmax < 1){
    Rcpp::stop("kmax must be positive");
  }
  Rcpp::IntegerVector end(kmax);
  Rcpp::NumericVector loss(kmax);
  Rcpp::NumericVector before_mean(kmax);
  Rcpp::NumericVector after_mean(kmax);
  Rcpp::IntegerVector before_size(kmax);
  Rcpp::IntegerVector after_size(kmax);
  Rcpp::IntegerVector invalidates_index(kmax);
  Rcpp::IntegerVector invalidates_after(kmax);
  int status = BINSEG
    (&data_vec[0], data_vec.size(), kmax,
     //inputs above, outputs below.
     &end[0], &loss[0],
                   &before_mean[0], &after_mean[0],
                   &before_size[0], &after_size[0],
                   &invalidates_index[0], &invalidates_after[0]);

                   return Rcpp::List::create
                     (Rcpp::Named("loss", loss),
                      Rcpp::Named("end", end),
                      Rcpp::Named("before.mean", before_mean),
                      Rcpp::Named("after.mean", after_mean),
                      Rcpp::Named("before.size", before_size),
                      Rcpp::Named("after.size", after_size),
                      Rcpp::Named("invalidates.index", invalidates_index),
                      Rcpp::Named("invalidates.after", invalidates_after)
                     ) ;
}
