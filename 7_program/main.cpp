// main.cpp
#include "set.h"
#include <iostream>

int main() {
 
    Set set1;
    for (int i = 1; i <= 30; ++i) {
        set1.add(i);
    }
    std::cout << "1. Size: " << set1.size() << ", " << set1.getImplType() << "\n";
    

    for (int i = 31; i <= 50; ++i) {
        set1.add(i);
    }
    std::cout << "\n2. Size: " << set1.size() << ", " << set1.getImplType() << "\n";
    
    set1.remove(25);


    Set set2;
    for (int i = 40; i <= 60; ++i) {
        set2.add(i);
    }
    std::cout << "\nSet2 implementation: " << set2.getImplType() << "\n";
    

    Set unionSet = set1.unionWith(set2);
    std::cout << "\nUnion size: " << unionSet.size() << "\n";
    std::cout << "Union impl: " << unionSet.getImplType() << "\n";


    Set intersectionSet = set1.intersectionWith(set2);
    std::cout << "\nIntersection size: " << intersectionSet.size() << "\n";
    std::cout << "Intersection elements: ";
    intersectionSet.print();

    
    set1.clear();
    std::cout << "\n\nAfter clear, size: " << set1.size() << "\n";
    std::cout << "Implementation: " << set1.getImplType() << "\n";

    
    // Копирование
    for (int i = 1; i <= 10; ++i) {
        set1.add(i);
    }
    std::cout << "\nSet: ";
    set1.print();

    Set set3 = set1;
    set3.add(100);
    std::cout << "\nOriginal: ";
    set1.print();
    std::cout << "\nCopy: ";
    set3.print();
    std::cout << "\n";
    
    return 0;
}