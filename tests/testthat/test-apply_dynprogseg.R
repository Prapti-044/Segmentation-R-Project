library(data.table)


test_that("For Iris data First column", {
  max.segments <- 3
  my.seg <- apply_dynprogseg(iris[,1], max.segments)
  expect_equal(nrow(my.seg), 3)
  expect_equal(length(my.seg), 3)
})


