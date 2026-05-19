// main.cpp
#include "expression.h"
#include <iostream>
#include <map>

int main() {
    ExpressionFactory factory;
    
    Constant* c = factory.createConstant(2);
    Variable* v = factory.createVariable("x");
    Addition* expr1 = new Addition(c, v);
    
    std::map<std::string, double> context;
    context["x"] = 3;
    
    std::cout << "Expression: " << *expr1 << std::endl;
    std::cout << "Result (x=3): " << expr1->calculate(context) << std::endl;
    delete expr1;
    factory.releaseVariable(v);
    
  
    Variable* x = factory.createVariable("x");
    Constant* five = factory.createConstant(5);
    Constant* two = factory.createConstant(2);
    Variable* y = factory.createVariable("y");
    
    Addition* sum = new Addition(x, five);
    Subtraction* diff = new Subtraction(y, two);
    Multiplication* product = new Multiplication(sum, diff);
    
    context["x"] = 10;
    context["y"] = 7;
    
    std::cout << "\nExpression: " << *product << std::endl;
    std::cout << "Result (x=10, y=7): " << product->calculate(context) << std::endl;
    delete product;
    factory.releaseVariable(x);
    factory.releaseVariable(y);
    

    std::cout << "\nFlyweight demonstration:\n";
    Constant* c1 = factory.createConstant(42);
    Constant* c2 = factory.createConstant(42);
    Constant* c3 = factory.createConstant(42);
    
    std::cout << "c1 address: " << c1 << std::endl;
    std::cout << "c2 address: " << c2 << std::endl;
    std::cout << "c3 address: " << c3 << std::endl;
    
   
    Variable* x1 = factory.createVariable("x");
    Variable* x2 = factory.createVariable("x");
    Variable* x3 = factory.createVariable("x");
    
    Constant* const2 = factory.createConstant(2);
    
    Multiplication* x_squared = new Multiplication(x1, x2);
    Multiplication* two_x = new Multiplication(const2, x3);
    Addition* quadratic = new Addition(x_squared, two_x);
    
    context["x"] = 5;
    std::cout << "\nExpression: " << *quadratic << std::endl;
    std::cout << "Result (x=5): " << quadratic->calculate(context) << std::endl;

    delete quadratic;
    factory.releaseVariable(x1);
    factory.releaseVariable(x2);
    factory.releaseVariable(x3);
    
   
    return 0;
}