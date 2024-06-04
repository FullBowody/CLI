#pragma once
#include <iostream>
#include <vector>

template <typename T>
void listVector(std::string name, const std::vector<T>& vector)
{
    size_t size = vector.size();
    std::cout << name << " (" << size << ") :" << std::endl;
    for (size_t i = 0; i < size; i++)
        std::cout << "  [" << (i+1) << "] - " << vector[i] << std::endl;
}

template <typename T>
void listVector(std::string name, const std::vector<T*>& vector)
{
    size_t size = vector.size();
    std::cout << name << " (" << size << ") :" << std::endl;
    for (size_t i = 0; i < size; i++)
        std::cout << "  [" << (i+1) << "] - " << *vector[i] << std::endl;
}
