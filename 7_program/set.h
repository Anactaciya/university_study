// set.h
#ifndef SET_H_
#define SET_H_

#include "set_impl.h"
#include <memory>
#include <algorithm>

// Абстракция 
class Set {
private:
    SetImplPtr impl_;
    static constexpr size_t SWITCH_THRESHOLD = 40;
    
    void switchIfNeeded() {
        if (!impl_) return;
        
        size_t current_size = impl_->size();
        
        // Если много элементов и текущая реализация - массив, переключаемся на хэш
        if (current_size > SWITCH_THRESHOLD && 
            dynamic_cast<ArraySetImpl*>(impl_.get())) {
            
            auto all_elements = impl_->getAllElements();
            impl_ = std::make_unique<HashSetImpl>(all_elements);
            std::cout << "[Bridge] Switched from Array to Hash (size=" 
                      << current_size << ")\n";
        }
        // Если мало элементов и текущая реализация - хэш, переключаемся на массив
        else if (current_size <= SWITCH_THRESHOLD && 
                 dynamic_cast<HashSetImpl*>(impl_.get())) {
            
            auto all_elements = impl_->getAllElements();
            impl_ = std::make_unique<ArraySetImpl>(all_elements);
            std::cout << "[Bridge] Switched from Hash to Array (size=" 
                      << current_size << ")\n";
        }
    }
    
public:
    Set() : impl_(std::make_unique<ArraySetImpl>()) {}
    
    Set(const Set& other) {
        if (other.impl_) {
            impl_ = other.impl_->clone();
        }
    }
    
    Set& operator=(const Set& other) {
        if (this != &other && other.impl_) {
            impl_ = other.impl_->clone();
        }
        return *this;
    }
    
    Set(Set&& other) noexcept = default;
    Set& operator=(Set&& other) noexcept = default;

    void add(int element) {
        if (!impl_) return;
        
        try {
            impl_->add(element);
        } catch (const std::runtime_error& e) {
            auto all_elements = impl_->getAllElements();
            impl_ = std::make_unique<HashSetImpl>(all_elements);
            impl_->add(element);
            std::cout << "[Bridge] Auto-switch: Array overflow, switched to Hash\n";
        }
        switchIfNeeded();
    }
    
    void remove(int element) {
        if (impl_) {
            impl_->remove(element);
            switchIfNeeded();
        }
    }
    
    bool contains(int element) const {
        return impl_ ? impl_->contains(element) : false;
    }
    
    size_t size() const {
        return impl_ ? impl_->size() : 0;
    }
    
    bool empty() const {
        return impl_ ? impl_->empty() : true;
    }
    
    void clear() {
        if (impl_) {
            impl_->clear();
            impl_ = std::make_unique<ArraySetImpl>();
        }
    }
    
    Set unionWith(const Set& other) const {
        Set result;

        if (impl_) {
            for (int elem : impl_->getAllElements()) {
                result.add(elem);
            }
        }

        if (other.impl_) {
            for (int elem : other.impl_->getAllElements()) {
                if (!result.contains(elem)) {
                    result.add(elem);
                }
            }
        }
        
        return result;
    }

    Set intersectionWith(const Set& other) const {
        Set result;
        
        if (!impl_ || !other.impl_) return result;
        
        const Set& smaller = (size() < other.size()) ? *this : other;
        const Set& larger = (size() < other.size()) ? other : *this;
        
        for (int elem : smaller.impl_->getAllElements()) {
            if (larger.contains(elem)) {
                result.add(elem);
            }
        }
        
        return result;
    }
    
    std::vector<int> getAllElements() const {
        return impl_ ? impl_->getAllElements() : std::vector<int>();
    }
    
    const char* getImplType() const {
        return impl_ ? impl_->getType() : "None";
    }
    
    void print() const {
        if (!impl_ || impl_->empty()) {
            std::cout << "{}";
            return;
        }
        
        auto elements = impl_->getAllElements();
        std::sort(elements.begin(), elements.end());
        
        std::cout << "{";
        for (size_t i = 0; i < elements.size(); ++i) {
            std::cout << elements[i];
            if (i < elements.size() - 1) std::cout << ", ";
        }
        std::cout << "}";
    }
};

#endif // SET_H_