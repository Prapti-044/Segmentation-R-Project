# Segmentation-R-Project
Binary Segmentation implemented in C++ and Optimal Segmentation with Dynamic Programming implemented in R


<!-- README.md is generated from README.Rmd. Please edit that file -->

<!-- badges: start -->

[![License: GPL
v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
![GitHub repo
size](https://img.shields.io/github/repo-size/Prapti-044/Segmentation-R-Project)
![GitHub code size in
bytes](https://img.shields.io/github/languages/code-size/Prapti-044/Segmentation-R-Project)
![GitHub language
count](https://img.shields.io/github/languages/count/Prapti-044/Segmentation-R-Project)
![GitHub top
language](https://img.shields.io/github/languages/top/Prapti-044/Segmentation-R-Project)
<!-- badges: end -->


*Note*: This RMarkdown is created following the guidelines of [this
R-package example](https://github.com/mvuorre/exampleRPackage).

## Installation

You can only install the development version from [this
repository](https://github.com/Prapti-044/Segmentation-R-Project) with:

``` r
# install.packages("devtools")
devtools::install_github("Prapti-044/Segmentation-R-Project")
```

# Binary_Segmentation R_CPP Package

The goal of Segmentation-R-Project is to learn how to create an R-package by
implementing [Binary_Segmentation
algorithm](https://arxiv.org/abs/1801.00718) efficiently
using C++ for binary segmentation of the data points.

## Example

This is a basic example which shows you how to perform binary segmentation in datasets:

``` r
library(Segmentation)
library(data.table)
data <- c(0.1, 0, 1, 1.1, 0.1, 0)
K <- 3
result <- apply_binseg(data, K)
result
$loss
[1] -0.8816667  0.4600000  2.1680000

```


<!-- README.md is generated from README.Rmd. Please edit that file -->

# Optimal-Segmentation-with-Dynamic-Programming
An R package implementing Optimal Segmentation using Dynamic Programming


The goal of Optimal-Segmentation-with-Dynamic-Programming is to learn how to create an R-package by
implementing [Optimal Segmentaion with Dynamic Programming](https://arxiv.org/abs/1801.00718) for
segmentation of the data points.


## Example

This is a basic example which shows you how to perform optimal segmentation using Dynamic Programming with the iris dataset:

``` r
library(Segmentation)
K <- 3
result <- apply_dynprogseg(iris[,1], K)
result
   seg.start seg.end seg.mean
1:         1      50 5.006000
2:        51     102 5.940385
3:       103     150 6.610417
```
