/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarType.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:02:46 by kiteixei          #+#    #+#             */
/*   Updated: 2025/12/15 22:32:06 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarType.hpp"
#include <cctype>
#include <string>
#include <limits.h>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <iomanip>
ScalarType::ScalarType() {
  std::cout << "ScalarType Constructor called" << std::endl;
}

ScalarType::~ScalarType() {
  std::cout << "ScalarType destructtor called" << std::endl;
}

ScalarType::Type ScalarType::getType(const std::string &str) 
{
  if (std::isprint(str[0]) && str.length() == 1 && !std::isdigit(str[0]))
    return IS_CHAR;
    
  if (str == "nanf" || str == "+inff" || str == "-inff")
    return IS_FLOAT;

  if (str == "nan" || str == "+inf" || str == "-inf")
    return IS_DOUBLE;

  if (std::isdigit(str[0]) || str[0] == '+' || str[0] == '-') {
    bool isInt = true;
    for (size_t i = 1; i < str.size(); i++) {
      if (!std::isdigit(str[i])) {
        isInt = false;
        break;
      }
    }
    if (isInt)
      return IS_INT;
  }
   
  size_t last_f = str.length() - 1;
  if (str[last_f] == 'f') {
    size_t dot = str.find('.');
    if (dot != std::string::npos) {
      bool ok = true;
      for (size_t i = 0; i < str.size() - 1; i++) {
        if (i == dot)
          continue;

        if (i == 0 && (str[0] == '+' || str[0] == '-'))
          continue;
        if (!std::isdigit(str[i])) {
          ok = false;
          break;
        }
      }
      if (ok)
        return IS_FLOAT;
    }
  }

  {
    size_t dot = str.find('.');
    size_t last = str.length();
    if (dot != std::string::npos && str[last] != 'f') {
      bool ok = true;
      for (size_t i = 0; i < str.size(); i++) {
        if (i == dot)
          continue;
        if (i == 0 && (str[0] == '+' || str[0] == '-'))
          continue;
        if (!std::isdigit(str[i])) {
          ok = false;
          break;
        }
      }
      if (ok)
        return IS_DOUBLE;
    }
  }
  return UNKNOW;
}

void ScalarType::convertType(const std::string &str, Type t) {
  char c = 0;
  int i = 0;
  bool isZero = false;
  float f = 0;
  double d = 0;
  int _inff_moin = 0;
  int _inff_plus = 0;
  bool charImpossible = false;
  bool charDisplay = true;
  bool intImpossible = false;
  errno = 0;

  if (t == IS_CHAR) {
    c = str[0];
    i = static_cast<int>(c);
    f = static_cast<float>(c);
    d = static_cast<double>(c);
  }

  else if (t == IS_INT) {
    char *end;
    long tmp = std::strtol(str.c_str(), &end, 10);

    if (tmp < 0 && errno == ERANGE)
      _inff_moin = true;
    if (tmp > 0 && errno == ERANGE)
      _inff_plus = true;
    if (tmp > INT_MAX || tmp < INT_MIN)
      intImpossible = true;
    if (*end != '\0' || errno == ERANGE)
      intImpossible = true;
    else
      i = static_cast<int>(tmp);

    c = static_cast<char>(tmp);
    f = static_cast<float>(tmp);
    d = static_cast<double>(tmp);
    if (!std::isprint(c))
      charDisplay = false;
  }

  else if (t == IS_FLOAT) {
    if (str == "nanf" || str == "+inff" || str == "-inff") {
      f = std::strtof(str.c_str(), NULL);
      d = static_cast<double>(f);
      intImpossible = true;
      charImpossible = true;
    } else {
      char *end;
      f = std::strtof(str.c_str(), &end);
      if (*end != 'f' || errno == ERANGE) {
        intImpossible = true;
        charImpossible = true;
      }
      size_t last_f = str.length() - 1;
      if(str[last_f - 1 ] ==  '0')
        isZero = true;
      if (str[last_f - 1] != '0')
        charImpossible = true;
      d = static_cast<double>(f);
      i = static_cast<int>(f);
      c = static_cast<char>(i);

      if (!std::isprint(c))
        charDisplay = false;
    }
  }

  else if (t == IS_DOUBLE) 
  {
    size_t last_f = str.length();
    if(str[last_f - 1 ] > '0')
      charImpossible = true;
    if (str == "nan" || str == "+inf" || str == "-inf") {
      d = std::strtod(str.c_str(), NULL);
      f = static_cast<float>(d);
      intImpossible = true;
      charImpossible = true;
    } else {
      char *end;
      d = std::strtod(str.c_str(), &end);

      if (*end != '\0' || errno == ERANGE) {
        intImpossible = true;
        charImpossible = true;
      }
      f = static_cast<float>(d);
      i = static_cast<int>(d);
      c = static_cast<char>(i);
      if (!std::isprint(c))
        charDisplay = false;
    }
  }

  else {
    std::cout << "char: impossible\n";
    std::cout << "int: impossible\n";
    std::cout << "float: impossible\n";
    std::cout << "double: impossible\n";
    return;
  }

  std::cout << "char: ";
  if (charImpossible == true)
    std::cout << "impossible\n";
  else if (!charDisplay)
    std::cout << "Non displayable\n";
  else if(intImpossible)
    std::cout << "Non displayable\n";
  else
    std::cout << "'" << c << "'\n";

  std::cout << "int: ";
  if (intImpossible)
    std::cout << "impossible\n";
  else
    std::cout << i << "\n";

  std::cout << "float: ";
  if (std::isnan(f))
    std::cout << "nanf\n";
  else if(_inff_moin)
    std::cout << "-inff" << std::endl;
  else if(_inff_plus)
    std::cout << "+inff" << std::endl;
  else if (std::isinf(f))
    std::cout << (f > 0 ? "+inff\n" : "-inff\n");
  else if(isZero)
    std::cout << f << ".0f\n";
  else
    std::cout << f << "f\n";

  std::cout << "double: ";
  if (std::isnan(d))
    std::cout << "nan\n";
  else if(_inff_moin)
    std::cout << "-inf" << std::endl;
  else if(_inff_plus)
    std::cout << "+inf" << std::endl;
  else if (std::isinf(d))
    std::cout << (d > 0 ? "+inf\n" : "-inf\n");
   else if(isZero)
    std::cout << d << ".0\n";
  else
    std::cout << d << "\n";
}
