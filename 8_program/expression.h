#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <stdexcept>


class Expression;
class Constant;
class Variable;
class ExpressionFactory;

// Приспособленец (Flyweight) - базовый класс для констант и переменных
class FlyweightExpression {
protected:
    FlyweightExpression() = default;
public:
    virtual ~FlyweightExpression() = default;
    virtual double calculate(const std::map<std::string, double>& context) const = 0;
    virtual void print(std::ostream& os) const = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const FlyweightExpression& expr) {
        expr.print(os);
        return os;
    }
};

class Constant : public FlyweightExpression {
private:
    double value_;
    
    Constant(double value) : value_(value) {}
    
public:
    double calculate(const std::map<std::string, double>&) const override {
        return value_;
    }
    
    void print(std::ostream& os) const override {
        if (value_ == static_cast<int>(value_)) {
            os << static_cast<int>(value_);
        } else {
            os << value_;
        }
    }
    
    double getValue() const { return value_; }
    
    friend class ExpressionFactory;
};

class Variable : public FlyweightExpression {
private:
    std::string name_;
    
    Variable(const std::string& name) : name_(name) {}
    
public:
    double calculate(const std::map<std::string, double>& context) const override {
        auto it = context.find(name_);
        if (it == context.end()) {
            throw std::runtime_error("Variable '" + name_ + "' not found in context");
        }
        return it->second;
    }
    
    void print(std::ostream& os) const override {
        os << name_;
    }
    
    const std::string& getName() const { return name_; }
    
    friend class ExpressionFactory;
};

// Абстрактный класс для операторов (Компоновщик)
class Expression : public FlyweightExpression {
protected:
    FlyweightExpression* left_;
    FlyweightExpression* right_;
    
public:
    Expression(FlyweightExpression* left, FlyweightExpression* right)
        : left_(left), right_(right) {}
    
    virtual ~Expression() {
    }
    
    Expression(const Expression&) = delete;
    Expression& operator=(const Expression&) = delete;
};

class Addition : public Expression {
public:
    Addition(FlyweightExpression* left, FlyweightExpression* right)
        : Expression(left, right) {}
    
    double calculate(const std::map<std::string, double>& context) const override {
        return left_->calculate(context) + right_->calculate(context);
    }
    
    void print(std::ostream& os) const override {
        os << "(";
        left_->print(os);
        os << " + ";
        right_->print(os);
        os << ")";
    }
};

class Subtraction : public Expression {
public:
    Subtraction(FlyweightExpression* left, FlyweightExpression* right)
        : Expression(left, right) {}
    
    double calculate(const std::map<std::string, double>& context) const override {
        return left_->calculate(context) - right_->calculate(context);
    }
    
    void print(std::ostream& os) const override {
        os << "(";
        left_->print(os);
        os << " - ";
        right_->print(os);
        os << ")";
    }
};

class Multiplication : public Expression {
public:
    Multiplication(FlyweightExpression* left, FlyweightExpression* right)
        : Expression(left, right) {}
    
    double calculate(const std::map<std::string, double>& context) const override {
        return left_->calculate(context) * right_->calculate(context);
    }
    
    void print(std::ostream& os) const override {
        os << "(";
        left_->print(os);
        os << " * ";
        right_->print(os);
        os << ")";
    }
};

class Division : public Expression {
public:
    Division(FlyweightExpression* left, FlyweightExpression* right)
        : Expression(left, right) {}
    
    double calculate(const std::map<std::string, double>& context) const override {
        double denominator = right_->calculate(context);
        if (denominator == 0) {
            throw std::runtime_error("Division by zero");
        }
        return left_->calculate(context) / denominator;
    }
    
    void print(std::ostream& os) const override {
        os << "(";
        left_->print(os);
        os << " / ";
        right_->print(os);
        os << ")";
    }
};


class ExpressionFactory {
private:
    std::unordered_map<double, Constant*> constants_;
    std::unordered_map<std::string, Variable*> variables_;
    std::unordered_map<Constant*, int> constant_refs_;
    std::unordered_map<Variable*, int> variable_refs_;
    
public:
    ExpressionFactory() {
        for (int i = -5; i <= 256; ++i) {
            constants_[i] = new Constant(i);
            constant_refs_[constants_[i]] = 1;
        }
    }
    
    ~ExpressionFactory() {
        for (auto& pair : constants_) {
            delete pair.second;
        }
        for (auto& pair : variables_) {
            delete pair.second;
        }
    }
    
    Constant* createConstant(double value) {
        auto it = constants_.find(value);
        if (it != constants_.end()) {
            return it->second;
        }
        Constant* constant = new Constant(value);
        constants_[value] = constant;
        constant_refs_[constant] = 1;
        return constant;
    }
    
    Variable* createVariable(const std::string& name) {
        auto it = variables_.find(name);
        if (it != variables_.end()) {
            variable_refs_[it->second]++;
            return it->second;
        }
        Variable* variable = new Variable(name);
        variables_[name] = variable;
        variable_refs_[variable] = 1;
        return variable;
    }
    
    void releaseVariable(Variable* variable) {
        if (!variable) return;
        
        auto it = variable_refs_.find(variable);
        if (it != variable_refs_.end()) {
            it->second--;
            if (it->second == 0) {
                auto map_it = variables_.find(variable->getName());
                if (map_it != variables_.end() && map_it->second == variable) {
                    variables_.erase(map_it);
                }
                variable_refs_.erase(it);
                delete variable;
            }
        }
    }
    
    void releaseConstant(Constant* constant) {
        if (!constant) return;
        
        double val = constant->getValue();
        if (val >= -5 && val <= 256 && val == static_cast<int>(val)) {
            return;
        }
        
        auto it = constant_refs_.find(constant);
        if (it != constant_refs_.end()) {
            it->second--;
            if (it->second == 0) {
                auto map_it = constants_.find(constant->getValue());
                if (map_it != constants_.end() && map_it->second == constant) {
                    constants_.erase(map_it);
                }
                constant_refs_.erase(it);
                delete constant;
            }
        }
    }
    
};

#endif // EXPRESSION_H_