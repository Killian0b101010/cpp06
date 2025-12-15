/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 19:19:39 by kiteixei          #+#    #+#             */
/*   Updated: 2025/12/06 20:13:47 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Serializer.hpp"

#include <iostream>
#include "Serializer.hpp"


int main() {
 
    Data* data = new Data();
    data->_name = "kiteixei";
    data->_age = 15;

    std::cout << "objet original " << std::endl;
    std::cout << "Adresse de data : " << data << std::endl;
    std::cout << "data->_name      : " << data->_name << std::endl;
    std::cout << "data->_age       : " << data->_age << std::endl;
    std::cout << std::endl;

    
    uintptr_t raw = Serializer::serialize(data);

    std::cout << "avant deserialize" << std::endl;
    std::cout << "valeur de raw (entier) : " << raw << std::endl;
    std::cout << "'juste l'adresse convertie en nombre " << std::endl;
    std::cout << std::endl;

    Data* ptr = Serializer::deserialize(raw);

    std::cout << "apres deserialize" << std::endl;
    std::cout << "Adresse de ptr : " << ptr << std::endl;
    std::cout << "ptr->_name      : " << ptr->_name << std::endl;
    std::cout << "ptr->_age       : " << ptr->_age << std::endl;
    std::cout << std::endl;

  
    std::cout << " verif " << std::endl;
    if (ptr == data)
        std::cout << "ptr et data pointent la mm adresse !" << std::endl;
    else
        std::cout << "ptr et data sont diff (impossible)." << std::endl;

    ptr->_age = 30;

    std::cout << "\n modif ptr" << std::endl;
    std::cout << "data->_age : " << data->_age << "  (30)" << std::endl;

    delete data;
    return 0;
}

