/***************************************
Name: Md. Hussainul Islam Sajib
Email: mhisajib@myseneca.ca
Id: 137651170
Assignment: Project - Milestone 3
Date: 31 March 2019
****************************************/

#include <string>
#include "Utilities.h"

namespace sict {
  //Initializes the values of the class variables
  size_t Utilities::fieldWidth = 0;
  char Utilities::delimiter = '|';

  //Default constructor for the Utilities class
  Utilities::Utilities() {}

  //Member function that extracts tokens from a string and updates 
  //the next position in the string for another token
  const std::string Utilities::extractToken(const std::string& str, size_t& next_pos) {
    std::string temp{};
    if (str.size() > next_pos) {
      temp = str.substr(next_pos, str.find(delimiter, next_pos) - next_pos);
    }
    else { 
      temp = "";
    }
    
    if (str.find(delimiter,next_pos) != std::string::npos) {
      next_pos = str.find(delimiter,next_pos) + 1;
    } 
    else {
      next_pos = std::string::npos;
    }
    if (temp.size() == 0) { throw "The token is empty"; }
    return temp;
  }

  //returns the delimiter (class variable)
  const char Utilities::getDelimiter() const { return delimiter; }
  
  //returns the fieldwidth (class variable)
  size_t Utilities::getFieldWidth() const { return fieldWidth; }
  
  //sets the delimiter to the argument
  void Utilities::setDelimiter(const char d) { delimiter = d; }
  
  //sets the fieldwidth to the argument
  void Utilities::setFieldWidth(size_t newWidth) { fieldWidth = newWidth; }

}