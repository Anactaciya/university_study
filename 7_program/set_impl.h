// set_impl.h
#ifndef SET_IMPL_H_
#define SET_IMPL_H_

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <iostream>

// Forward declaration
class SetImpl;

using SetImplPtr = std::unique_ptr<SetImpl>;

// Абстрактная реализация
class SetImpl {
public:
    virtual ~SetImpl() = default;
    
    virtual void add(int element) = 0;
    virtual void remove(int element) = 0;
    virtual bool contains(int element) const = 0;
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual void clear() = 0;
    
    virtual std::vector<int> getAllElements() const = 0;

    virtual SetImplPtr clone() const = 0;
    
    virtual const char* getType() const = 0;
};

// Конкретная реализация 1: массив
class ArraySetImpl : public SetImpl {
private:
    std::vector<int> elements_;
    static constexpr size_t MAX_SIZE = 50;
    
    void sortAndUnique() {
        std::sort(elements_.begin(), elements_.end());
        auto last = std::unique(elements_.begin(), elements_.end());
        elements_.erase(last, elements_.end());
    }
    
public:
    ArraySetImpl() = default;
    
    ArraySetImpl(const std::vector<int>& elements) : elements_(elements) {
        sortAndUnique();
    }
    
    void add(int element) override {
        if (size() >= MAX_SIZE) {
            throw std::runtime_error("ArraySetImpl: size limit reached. Need to switch to another implementation.");
        }
        
        if (!contains(element)) {
            elements_.push_back(element);
            sortAndUnique();
        }
    }
    
    void remove(int element) override {
        auto it = std::find(elements_.begin(), elements_.end(), element);
        if (it != elements_.end()) {
            elements_.erase(it);
        }
    }
    
    bool contains(int element) const override {
        return std::binary_search(elements_.begin(), elements_.end(), element);
    }
    
    size_t size() const override {
        return elements_.size();
    }
    
    bool empty() const override {
        return elements_.empty();
    }
    
    void clear() override {
        elements_.clear();
    }
    
    std::vector<int> getAllElements() const override {
        return elements_;
    }
    
    SetImplPtr clone() const override {
        return std::make_unique<ArraySetImpl>(elements_);
    }
    
    const char* getType() const override {
        return "ArraySetImpl";
    }
    
    static constexpr size_t getMaxSize() {
        return MAX_SIZE;
    }
};

// Конкретная реализация 2: хэш-таблица
class HashSetImpl : public SetImpl {
private:
    std::unordered_set<int> elements_;
    
public:
    HashSetImpl() = default;
    
    HashSetImpl(const std::vector<int>& elements) {
        for (int elem : elements) {
            elements_.insert(elem);
        }
    }
    
    void add(int element) override {
        elements_.insert(element);
    }
    
    void remove(int element) override {
        elements_.erase(element);
    }
    
    bool contains(int element) const override {
        return elements_.find(element) != elements_.end();
    }
    
    size_t size() const override {
        return elements_.size();
    }
    
    bool empty() const override {
        return elements_.empty();
    }
    
    void clear() override {
        elements_.clear();
    }
    
    std::vector<int> getAllElements() const override {
        return std::vector<int>(elements_.begin(), elements_.end());
    }
    
    SetImplPtr clone() const override {
        auto new_set = std::make_unique<HashSetImpl>();
        new_set->elements_ = elements_;
        return new_set;
    }
    
    const char* getType() const override {
        return "HashSetImpl";
    }
};

#endif // SET_IMPL_H_