#include <iostream>
using namespace std;

template <typename TP>
 time_t to_time_t(TP tp) {
  using namespace chrono;
 auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
  return system_clock::to_time_t(sctp);
}