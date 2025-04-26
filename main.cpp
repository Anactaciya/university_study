#include <iostream>


// Задача на сегодня: 
// написать класс декартова дерева в котором возможны одинаковые значения. 
// Операции: добавить значение, 
//                  удалить значение, узнать количество элементов.

class DecTree
{
private:
    /* data */
    int key;
    int priority;
    int count_of_elements = 1;
    DecTree* left = nullptr;
    DecTree* right = nullptr;

public:
    DecTree(int key, int priority, DecTree* left = nullptr, DecTree* right = nullptr)
    {
        this->key = key; // x
        this->priority = priority; // y
        this->left = left;
        this->right = right;

        if (left != nullptr) {
            count_of_elements += left->count_of_elements;
        }
        if (right != nullptr) {
            count_of_elements += right->count_of_elements;
        }
    }

    DecTree* merge(DecTree* left, DecTree* right)
    {
        if (left == nullptr) return right;
        if (right == nullptr) return right;
        if (left->priority > right->priority) 
        {
            DecTree* modified_right = merge(left->right, right);
            return new DecTree(left->key, left->priority, 
                                left->left, modified_right);
        }
        else
        {
            DecTree* modified_left = merge(left, right->left);
            return new DecTree(right->key, right->priority, 
                                modified_left, right->left);
        }
    }

    void split(int key, DecTree* left, DecTree* right, bool flag_not_inclusive = false)
    {
        DecTree* modified_tree = nullptr;
        if (this->key < key || this->key == key && !flag_not_inclusive)
        {
            if (this->right == nullptr) // завершаем рекурсию
            {
                right = nullptr;
            }
            else
            {
                this->right->split(key, modified_tree, right);
            }
            left = new DecTree(this->key, priority, this->left, modified_tree);

        }

        else
        {
            if (this->left == nullptr)
            {
                left = nullptr;
            }
            else
            {
                this->left->split(key, left, modified_tree);
            }
            right = new DecTree(this->key, priority, modified_tree, this->right);
        }
    }

    DecTree* add_value(int key, int priority)
    {
        DecTree* l;
        DecTree* r;
        DecTree* single_elem_tree = new DecTree(key, priority);
        split(key, l, r);
        return merge(merge(l, single_elem_tree), r);
    }

    ~DecTree() 
    {
        delete left;
        delete right;
    }
};

