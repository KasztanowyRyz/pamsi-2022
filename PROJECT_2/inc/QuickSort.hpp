#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP
#include <fstream>
#include <iostream>

#include "Data.hpp"

void qSort(std::vector<Film>& movieList, int low, int high);
void quickSort(std::vector<Film> movies, uint64_t number, Data* records);
#endif