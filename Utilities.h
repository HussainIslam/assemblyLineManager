/***************************************
Name: Md. Hussainul Islam Sajib
Email: mhisajib@myseneca.ca
Id: 137651170
Assignment: Project - Milestone 2
Date: 12 March 2019
****************************************/

#ifndef SICT_UTILITIES_H_
#define SICT_UTILITIES_H_
#include <string>

namespace sict {
  class Utilities {
    static size_t fieldWidth;
    static char delimiter;
  public:
    Utilities();
    const std::string extractToken(const std::string& str, size_t& next_pos);
    const char getDelimiter() const;
    size_t getFieldWidth() const;
    static void setDelimiter(const char d);
    static void setFieldWidth(size_t);
  };
}


#endif