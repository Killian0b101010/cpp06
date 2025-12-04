/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarType.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:02:46 by kiteixei          #+#    #+#             */
/*   Updated: 2025/12/04 14:18:35 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarType.hpp"
#include <cctype>

ScalarType::ScalarType() {
  std::cout << "ScalarType Constructor called" << std::endl;
}

ScalarType::~ScalarType() {
  std::cout << "ScalarType destructtor called" << std::endl;
}

ScalarType::Type ScalarType::getType(const std::string &str) {
  if (str.size() == 3 && str[0] == '\'' && str[2] == '\'' &&
      std::isprint(str[1]))
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

  if (str.back() == 'f') {
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
    if (dot != std::string::npos && str.back() != 'f') {
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
  float f = 0;
  double d = 0;

  bool charImpossible = false;
  bool charDisplay = true;
  bool intImpossible = false;

  errno = 0;

  if (t == IS_CHAR) {
    c = str[1];
    i = static_cast<int>(c);
    f = static_cast<float>(c);
    d = static_cast<double>(c);
  }

  else if (t == IS_INT) {
    char *end;
    long tmp = std::strtol(str.c_str(), &end, 10);
    if (tmp > INT_MAX || tmp < INT_MIN)
      intImpossible = true;
    if (*end != '\0' || errno == ERANGE)
      intImpossible = true;
    else
      i = static_cast<int>(tmp);

    c = static_cast<char>(i);
    f = static_cast<float>(i);
    d = static_cast<double>(i);

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

      d = static_cast<double>(f);
      i = static_cast<int>(f);
      c = static_cast<char>(i);

      if (!std::isprint(c))
        charDisplay = false;
    }
  }

  else if (t == IS_DOUBLE) {
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
  if (charImpossible)
    std::cout << "impossible\n";
  else if (!charDisplay)
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
  else if (std::isinf(f))
    std::cout << (f > 0 ? "+inff\n" : "-inff\n");
  else
    std::cout << f << "f\n";

  std::cout << "double: ";
  if (std::isnan(d))
    std::cout << "nan\n";
  else if (std::isinf(d))
    std::cout << (d > 0 ? "+inf\n" : "-inf\n");
  else
    std::cout << d << "\n";
}
