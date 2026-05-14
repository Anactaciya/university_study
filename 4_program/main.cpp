#include <iostream>
#include <cassert>

// 1. MixIn для операторов сравнения (CRTP)
// (Curiously Recurring Template Pattern)
template<typename T>
class less_than_comparable {
public:
    friend bool operator>(const T& lhs, const T& rhs) {
        return rhs < lhs;
    }
    
    friend bool operator<=(const T& lhs, const T& rhs) {
        return !(rhs < lhs);
    }
    
    friend bool operator>=(const T& lhs, const T& rhs) {
        return !(lhs < rhs);
    }
    
    friend bool operator==(const T& lhs, const T& rhs) {
        return !(lhs < rhs) && !(rhs < lhs);
    }
    
    friend bool operator!=(const T& lhs, const T& rhs) {
        return !(lhs == rhs);
    }
};

// 2. MixIn для подсчета экземпляров
template<typename T>
class counter {
private:
    static inline size_t instance_count = 0;
    
protected: // Позволяет вызываться из производных классов
    counter() {
        ++instance_count;
    }
    
    counter(const counter&) {
        ++instance_count;
    }
    
    counter(counter&&) {
        ++instance_count;
    }
    
    ~counter() {
        --instance_count;
    }
    
public:
    static size_t count() {
        return instance_count;
    }
};



// Пример использования
class Number: public less_than_comparable<Number>, public counter<Number> {
public:
    Number(int value): m_value{value} {}

    int value() const { return m_value; }

    bool operator<(Number const& other) const {
        return m_value < other.m_value;
    }

private:
    int m_value;
};

int main()
{
    Number one{1};
    Number two{2};
    Number three{3};
    Number four{4};
    assert(one >= one);
    assert(three <= four);
    assert(two == two);
    assert(three > two);
    assert(one < two);
    std::cout << "Count: " << counter<Number>::count() << std::endl;
    return 0;
}