/***************************************
Name: Md. Hussainul Islam Sajib
Email: mhisajib@myseneca.ca
Id: 137651170
Assignment: Project - Milestone 2
Date: 12 March 2019
****************************************/
#include "LineManager.h"
namespace sict {
  LineManager::LineManager(std::vector<Station*>& station, std::vector<size_t>& indexNextStation, std::vector<CustomerOrder>& order, size_t indexStartingStation, std::ostream& os) {
    
    stations.resize(station.size());
    for (size_t i = 0; i < station.size(); i++) {
      stations.at(i) = station.at(i);
    }
    for (size_t i = 0; i < order.size(); i++) {
      waitingQueue.push_back(std::move(order.at(i)));
    }
    assemblyLine.resize(stations.size());
    for (size_t i = 0; i < station.size(); i++) {
      if (i == 0) { 
        assemblyLine.at(i) = indexStartingStation; 
      }
      else { 
        assemblyLine.at(i) = indexNextStation.at(i - 1); 
      }
    }
    
    /*for (auto& i : order) { waitingQueue.push_back(std::move(i)); }
    stations.resize(station.size());
    size_t index = indexStartingStation;
    for (size_t i = 0; i < station.size() && index != station.size(); i++) {
      stations[i] = station[index];
      index = indexNextStation[index];
    }*/
  }

  void LineManager::display(std::ostream& os) const {
    os << "COMPLETED ORDERS" << std::endl;
    for (auto& i : completed) { i.display(os, true); }
    os << "INCOMPLETE ORDERS" << std::endl;
    for (auto& i : incomplete) { i.display(os, true); }
  }

  bool LineManager::run(std::ostream& os) {
    if (!waitingQueue.empty()) {
      *(stations.at(assemblyLine.at(0))) += std::move(waitingQueue.back());
    }
    for (size_t i = 0; i < stations.size(); i++) {
      stations.at(i)->fill(os);
    }
    for (size_t i = 0; i < stations.size(); i++) {
      if (stations.at(assemblyLine.at(i))->hasAnOrderToRelease()) {
        if (assemblyLine.at(i) != stations.size()) {
          stations.at(assemblyLine.at(i + 1)) = std::move(stations.at(assemblyLine.at(i)));
        }
        else {
          CustomerOrder temp{};
          stations.at(assemblyLine.at(i))->pop(temp);
          if (temp.isFilled()) {
            completed.push_back(std::move(temp));
          }
          else {
            incomplete.push_back(std::move(temp));
          }
        }
      }
    }
    return true;


    //  bool allProcessed{ false };
    //  size_t noItemInProcess{ 0 };
    //  //loop until the waitingQueue
    //  while (!waitingQueue.empty()) {
    //    //if (!waitingQueue.empty()) {
    //      *(stations.at(0)) += std::move(waitingQueue.front());
    //      waitingQueue.pop_front();
    //      ++noItemInProcess;
    //    //}
    //    for (size_t i = 0; i < noItemInProcess; i++) {
    //      stations.at(i)->fill(os);
    //    }
    //    for (size_t i = 0; i < noItemInProcess; i++) {
    //      CustomerOrder temp{};
    //      if (i == stations.size() - 1) {
    //        stations.at(i)->pop(temp);
    //        if (stations.at(i)->hasAnOrderToRelease()) {
    //          completed.push_back(std::move(temp));
    //        }
    //        else {
    //          incomplete.push_back(std::move(temp));
    //        }
    //      }
    //      else {
    //        stations.at(i)->pop(temp);
    //        *(stations.at(i + 1)) += std::move(temp);
    //      }
    //      
    //    }
    //  }
    //  
    //  size_t extraStations{ stations.size() - noItemInProcess };
    //  while (noItemInProcess) {
    //    for (size_t i = extraStations; i < (noItemInProcess + extraStations); i++) {
    //      stations.at( i )->fill(os);
    //    }
    //    for (size_t i = extraStations; i < (noItemInProcess + extraStations); i++) {
    //      CustomerOrder temp{};
    //      if (i == stations.size() - 1) {
    //        stations.at(i)->pop(temp);
    //        if (stations.at(i)->hasAnOrderToRelease()) {
    //          completed.push_front(std::move(temp));
    //        }
    //        else {
    //          incomplete.push_front(std::move(temp));
    //        }
    //      }
    //      else {
    //        stations.at(i)->pop(temp);
    //        *(stations.at(i + 1)) += std::move(temp);
    //      }
    //    }

    //    noItemInProcess--;
    //  }
    //  
    //  allProcessed = true;
    //  
    //  return allProcessed;
    //}
    }
}