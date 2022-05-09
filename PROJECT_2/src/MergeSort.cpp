#include "MergeSort.hpp"

using namespace std;

void mSort(std::vector<Film>& movieList, std::vector<Film>& tmp, int low,
           int high) {
  int middle, i1, i2, i;

  middle = (low + high + 1) / 2;
  if (middle - low > 1) mSort(movieList, tmp, low, middle - 1);
  if (high - middle > 0) mSort(movieList, tmp, middle, high);
  i1 = low;
  i2 = middle;
  for (i = low; i <= high; i++)
    tmp[i] = ((i1 == middle) || ((i2 <= high) && (movieList[i1].getRating() >
                                                  movieList[i2].getRating())))
                 ? movieList[i2++]
                 : movieList[i1++];
  for (i = low; i <= high; i++) movieList[i] = tmp[i];
}

void mergeSort(std::vector<Film> movies, uint64_t number, Data* records) {
  vector<Film> tmp = movies;
  vector<vector<Film>> movieByRate(10);
  mSort(movies, tmp, 0, number - 1);
  records->setMedian(tmp, number);
  saveToFile(tmp, number);
}

void saveToFile(std::vector<Film> movies, uint64_t number) {
  std::cout << "Sorted movies will be send to \"MSorted.txt\" file"
            << std::endl;
  std::ofstream newFile;
  std::string fileName = "MSorted.txt";
  newFile.open(fileName);
  if (newFile.good()) {
    newFile << "Sorted movies: \n";
    newFile << "Ordinal no.: Title Rating: \n";
    for (uint64_t element = 0; element < number; ++element) {
      newFile << movies[element];
    }
    std::cout << "File has been created or has been overwritten!" << std::endl;
  } else
    throw std::runtime_error("The file " + fileName + " could not be created!");
}