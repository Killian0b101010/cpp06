/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:32:39 by kiteixei          #+#    #+#             */
/*   Updated: 2025/12/06 20:13:43 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer() {
  std::cout << "Constructor called" << std::endl;
}

Serializer::Serializer(const Serializer &cpy) {
 *this = cpy;
}

Serializer &Serializer::operator=(const Serializer &other) {
  if (this == &other) {
    return(*this);
  }
  return (*this);
}


uintptr_t Serializer::serialize(Data *ptr) {
  return (reinterpret_cast<uintptr_t>(ptr));
}
Data *Serializer::deserialize(uintptr_t raw) {
  return (reinterpret_cast<Data *>(raw));
}

Serializer::~Serializer() { std::cout << "Destructor Called" << std::endl; }
