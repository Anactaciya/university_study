#include <vector>
#include <math.h>
#include <stdio.h>

class SegmentTree {
public:
    SegmentTree(const std::vector<int>& vec) {
        size_t element_count = vec.size(); // то же, что n' с разбора

        size_t depth = ceil(std::log2(element_count));
        n = std::pow(2, depth); // число листьев в дереве с дополнениями (эквивалентно размеру дополненного массива)

        // далее заполняем массив, как кучу
        segment_tree.resize(2 * n - 1, 0);
        
        // заполняем начальные значения, вписывая нули на недостающие позиции
        for (int i = 0; i < element_count; i++) {
            segment_tree[(n - 1) + i] = vec[i];
        }
        for(int i = element_count; i < n; i++) {
            segment_tree[(n - 1) + i] = 0;
        }

        // расчитываем значения остальных вершин на основе листьев
        for (int level = depth - 1; level >= 0; level--) {
            int elem_count_on_level = std::pow(2, level);

            for (int i = 0; i < elem_count_on_level; i++) {
                int cur = (elem_count_on_level - 1) + i;
                int child_start = (elem_count_on_level * 2 - 1) + 2 * i;

                segment_tree[cur] = segment_tree[child_start] + segment_tree[child_start + 1];
            }
        }

        printf("segment_tree is:\n  ");
        for (int i = 0; i < segment_tree.size(); i++) {
            printf("%d ", segment_tree[i]);
        }
        printf("\n");

    }
    int Request(size_t left, size_t right) { // запрос: получить сумму среза [left, right] исходного массива
        size_t Left = GetNewInd(left);
        size_t Right = GetNewInd(right);
        int ans = 0;
        while (Left < Right) {
            // % 2 == 0 будут соответствовать корень и правые дети
            // % 2 == 1 будут соответствовать левые дети
            if (Left % 2 == 0){
                ans += segment_tree[Left];
                Left++;
            }
            if (Right % 2 == 1){
                ans += segment_tree[Right];
                Right--;
            }
            Left = Parent(Left);
            Right = Parent(Right);
        }

        if (Left == Right) ans += segment_tree[Left];
        return ans;
    }
private:
    std::vector<int> segment_tree; // размер 2 ^(n-1)
    size_t n; // n - размер дополненного массива

    int Parent(size_t i){
        // принимает индекс i вершины в массиве segment_tree
        // возвращает индекс его родителя в этом массиве
        return (i - 1) / 2;
    }

    int GetNewInd(size_t i) { 
        // принимает индекс i в исходном массиве
        // возвращает индекс этого элемента в segment_tree
        return n - 1 + i;
    }

};


int main() {
    std::vector<int> arr = {1, 3, 5, 7, 9};
    SegmentTree tree(arr);
    

    for (int i = 0; i < arr.size(); i++) {
        for (int j = i; j < arr.size(); j++) {
            printf("Sum [%d, %d] is %d\n", i, j, tree.Request(i, j));
        }
        printf("\n");
    }

    return 0;
}