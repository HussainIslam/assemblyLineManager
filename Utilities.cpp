/***************************************
Name: Md. Hussainul Islam Sajib
Email: mhisajib@myseneca.ca
Id: 137651170
Assignment: Project - Milestone 2
Date: 12 March 2019
****************************************/

#include <string>
#include "Utilities.h"

namespace sict {
  size_t Utilities::fieldWidth = 0;
  char Utilities::delimiter = '|';

  Utilities::Utilities() {}

  const std::string Utilities::extractToken(const std::string& str, size_t& next_pos) {
    std::string temp{};
    if (str.size() > next_pos) {
      temp = str.substr(next_pos, str.find(delimiter, next_pos) - next_pos);
    }
    else { 
      temp = "";
      //next_pos = std::string::npos;
    }
    //else { temp = ""; }
    //if (temp.size() > fieldWidth) { setFieldWidth(temp.size()); }
    if (str.find(delimiter,next_pos) != std::string::npos) {
      next_pos = str.find(delimiter,next_pos) + 1;
    } 
    else {
      next_pos = std::string::npos;
    }
    if (temp.size() == 0) { throw "The token is empty"; }
    return temp;
  }

  const char Utilities::getDelimiter() const { return delimiter; }
  
  size_t Utilities::getFieldWidth() const { return fieldWidth; }
  
  void Utilities::setDelimiter(const char d) { delimiter = d; }
  
  void Utilities::setFieldWidth(size_t newWidth) { fieldWidth = newWidth; }

}