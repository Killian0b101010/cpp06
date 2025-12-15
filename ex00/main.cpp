/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:47:57 by kiteixei          #+#    #+#             */
/*   Updated: 2025/12/15 17:13:20 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarType.hpp"
int main(int ac, char **argv) {
  if (ac == 2) {
    const std::string convert = std::string(argv[1]);
    ScalarType::Type type = ScalarType::getType(convert);
    ScalarType::convertType(convert, type);
  }
  return (0);
}
