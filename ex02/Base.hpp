/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:54:21 by kiteixei          #+#    #+#             */
/*   Updated: 2025/12/15 23:21:33 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
#define BASE_HPP
#include <exception>
#include <iostream>
#include <cstdlib>
class Base {
public:
  Base();
  virtual ~Base();
  static Base *generate(void);
  void identify(Base *p);
  void identify(Base &p);
};
class A : public Base {};
class B : public Base {};
class C : public Base {};
#endif
