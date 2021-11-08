test_that("Binseg works for 3 segmentation", {
  x <- c(0.1, 0, 1, 1.1, 0.1, 0)
  result <- apply_binseg(x, 3)
  expect_equal(length(result$loss), 3)
})
