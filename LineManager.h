#ifndef SICT_LINE_MANAGER_H
#define SICT_LINE_MANAGER_H
#include <vector>
#include <deque>
#include <algorithm>
#include "Station.h"
#include "CustomerOrder.h"

namespace sict {
  //declaring the class LineManager
  //The definition of the member functions are in the
  //LineManager.cpp file
  class LineManager {
    std::vector<Station*> stations{};
    std::vector<size_t> assemblyLine{};
    size_t firstStation{};
    size_t lastStation{};
    std::vector<size_t> nextStations{};
    std::deque<CustomerOrder> waitingQueue{};
    std::deque<CustomerOrder> completed{};
    std::deque<CustomerOrder> incomplete{};
  public:
    LineManager(std::vector<Station*>& station, std::vector<size_t>& indexNextStation, std::vector<CustomerOrder>& order, size_t indexStartingStation, std::ostream& os);
    void display(std::ostream& os) const;
    bool run(std::ostream& os);
  };
}


#endif // !SICT_LINE_MANAGER_H
