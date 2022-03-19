#include "Heap.hpp"
#include "climits"
#include "cstdio"
#include "fstream"

template <typename message>
Heap<message>::Heap(std::vector<std::pair<uint32_t, message>> _pack) {
  addPackets(_pack);
}

template <typename message>
void Heap<message>::addPackets(
    std::vector<std::pair<uint32_t, message>> _pack) {
  packetTab = new std::pair<uint32_t, message>[2];
  // sizeOfMessages = *(&packetTab + 1) - packetTab - 1;  // pointer arithmetic
  sizeOfTab = 2;
  for (auto const &packet : _pack) {
    insertKey(packet);
  }
  print();
}

template <typename message>
void Heap<message>::heapify(uint32_t node) {
  // node in that function is an element which we have added
  if (node == 1 || packetTab[node / 2] < packetTab[node]) return;
  swap(packetTab[node / 2], packetTab[node]);
  heapify(node / 2);
}

template <typename message>
std::pair<uint32_t, message> Heap<message>::minValue() {
  return packetTab[1];
}

template <typename message>
void Heap<message>::pushDown(uint32_t node) {
  if (node * 2 > size) return;
  if (node * 2 + 1 > size) {
    if (packetTab[node * 2] < packetTab[node]) {
      swap(packetTab[node], packetTab[node * 2]);
      this->pushDown(node * 2);
    }
    return;
  }
  if (packetTab[node * 2] < packetTab[node * 2 + 1]) {
    if (packetTab[node * 2] < packetTab[node]) {
      swap(packetTab[node], packetTab[node * 2]);
      this->pushDown(node * 2);
    }
    return;
  }
  if (packetTab[node * 2 + 1] < packetTab[node]) {
    swap(packetTab[node], packetTab[node * 2 + 1]);
    this->pushDown(node * 2 + 1);
  }
}

template <typename message>
void Heap<message>::pop() {
  swap(packetTab[1], packetTab[size]);
  packetTab[size--] = std::make_pair(NULL, NULL);
  this->pushDown(1);
}

template <typename message>
void Heap<message>::insertKey(std::pair<uint32_t, message> element) {
  if (size + 1 >= sizeOfTab) {
    sizeOfTab *= 2;
    resize();
  }
  packetTab[++size] = element;
  heapify(size);
}

template <typename message>
void Heap<message>::resize() {
  std::pair<uint32_t, message> *tmp =
      new std::pair<uint32_t, message>[sizeOfTab];
  for (uint32_t i = 0; i <= size; ++i) {
    tmp[i] = packetTab[i];
  }
  delete[] packetTab;
  packetTab = tmp;
}

template <typename message>
uint32_t Heap<message>::getSize() {
  return size;
}

template <typename message>
void Heap<message>::print() {
  if (size <= 100) {
    std::cout << "Sorted message: \n";
    std::cout << "Ordinal no.: Massage: \n";
    while (getSize() > 0) {
      std::pair<uint32_t, message> tmp;
      tmp = minValue();
      pop();
      std::cout << tmp.first << "\t" << tmp.second << std::endl;
    }
  } else {
    std::cout << "The input file has more than 100 lines. It will be send to "
                 "\"Sorted.txt\" file"
              << std::endl;
    std::cout << "Do you want to continue ? [y/n]: ";
    char choice;
    while (true) {
      std::cin >> choice;
      if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        std::cout << "Option selection error. Try again: " << std::endl;
        continue;
      } else
        break;
    }
    if (choice == 'n' || choice == 'N') {
      std::cerr << "The action has been stopped. Quitting the program..."
                << std::endl;
    }
    std::ofstream newFile;
    std::string fileName = "Sorted.txt";
    newFile.open(fileName);
    if (newFile.good()) {
      newFile << "Sorted message: \n";
      newFile << "Ordinal no.: Massage: \n";
      while (getSize() > 0) {
        std::pair<uint32_t, message> tmp;
        tmp = minValue();
        pop();
        newFile << tmp.first << tmp.second << std::endl;
      }
      std::cout << "File has been created" << std::endl;
    }
    else
    throw std::runtime_error("The file " + fileName +
                                " could not be created!");
  }
}
