#' Applies Segmentation algorithm to the given data data.mat
#'
#' \code{Segmentation} returns the ...
#'
#' @param data.dt A list of doubles representing the sequence data
#' @param max.segments Maximum number of segments to calculate
#' @return A data.table of 3 columns with segments
#'
#'   For description of how Binary segmentation and Dynamic Programming algorithm works in change point detection, please refer to this paper
#'   \url{https://arxiv.org/abs/1801.00718}
#' @examples
#' library(data.table)
#' apply_dynprogseg(iris[,1], 3)
#'
#' @export
apply_dynprogseg <- function(data.dt, max.segments) {
  N.data <- length(data.dt)
  cost.mat <- matrix(NA, N.data, max.segments)
  last.mean.mat <- matrix(NA, N.data, max.segments)
  last.change.mat <- matrix(NA, N.data, max.segments)
  ## best cost = sum of squares - sum^2/N.data.
  cum.vec <- cumsum(data.dt)
  cum.N <- 1:N.data
  loss <- function(sum.vec, N.vec){
    -sum.vec^2/N.vec
  }
  cost.mat[,1] <- loss(cum.vec, cum.N)
  last.mean.mat[,1] <- cum.vec/cum.N

  loss1.dt <- data.table(
    loss=cost.mat[,1],
    N.data=cum.N)

  ## computation of best loss in N.segments up.to.t
  ## => L_{N.segments, up.to.t}
  for(N.segments in 2:max.segments){
    for(up.to.t in N.segments:N.data){
      possible.prev.end <-
        seq(N.segments-1, up.to.t-1) #t'
      prev.loss <- cost.mat[possible.prev.end,N.segments-1]
      N.last.segs <- up.to.t-possible.prev.end
      sum.last.segs <-
        cum.vec[up.to.t]-cum.vec[possible.prev.end]
      data.dt[up.to.t]
      last.loss <- loss(sum.last.segs, N.last.segs)
      total.loss <- prev.loss + last.loss
      best.index <- which.min(total.loss)
      last.mean.mat[up.to.t,N.segments] <-
        (sum.last.segs/N.last.segs)[best.index]
      last.change.mat[up.to.t, N.segments] <-
        possible.prev.end[best.index]
      cost.mat[up.to.t, N.segments] <- total.loss[best.index]
    }
  }

  seg.end <- N.data
  seg.dt.list <- list()
  for(seg.i in max.segments:1){
    prev.end <- last.change.mat[seg.end, seg.i]
    seg.start <- if(seg.i==1)1 else prev.end+1
    seg.dt.list[[seg.i]] <- data.table(
      seg.start, seg.end,
      seg.mean=last.mean.mat[seg.end, seg.i])
    seg.end <- prev.end
  }
  seg.dt <- do.call(rbind, seg.dt.list)
  return(seg.dt)
}
