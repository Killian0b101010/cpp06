/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarType.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:02:30 by kiteixei          #+#    #+#             */
/*   Updated: 2025/12/04 14:18:29 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cerrno>
#include <cfloat>
#include <cstdlib>
#include <iostream>
#include <string>

class ScalarType {
private:
  const std::string _type;
  char _charValue;
  int _intValue;
  float _floatValue;
  double _doubleValue;
  bool _charImpossible;
  bool _intImpossible;

public:
  ScalarType();
  ~ScalarType();
  ScalarType(const ScalarType &copy);
  ScalarType &operator=(const ScalarType &other);
  enum Type {
    IS_FLOAT,
    IS_INT,
    IS_CHAR,
    IS_DOUBLE,
    UNKNOW,
  };
  static Type getType(const std::string &type);
  static void convertType(const std::string &type, Type t);
};
std::ostream &operator>>(std::ostream &s, const ScalarType &other);
