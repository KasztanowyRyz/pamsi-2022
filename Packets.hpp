#ifndef PACKETS_HPP
#define PACKETS_HPP

#include <iostream>
class Packets {
 private:
  uint32_t packetNo;
  uint32_t *packetTab;

 public:
  Packets(uint32_t _packetNo);
  uint32_t draw(uint32_t packetNo, int itr);
  bool check (uint32_t value, int itr);
};
#endif