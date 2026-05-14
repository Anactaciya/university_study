#include <type_traits>
#include <cstddef>


// Скрытие деталей в отдельном пространстве имен
namespace TypeListImpl { 

template <typename... Types>
struct TypeList {}; // использование variadic template

template <typename List>
struct Size;

template <typename... Types>
struct Size<TypeList<Types...>> {
    static constexpr size_t value = sizeof...(Types);
};

template <size_t Index, typename List>
struct Get;

template <typename First, typename... Rest>
struct Get<0, TypeList<First, Rest...>> {
    using type = First;
};

template <size_t Index, typename First, typename... Rest>
struct Get<Index, TypeList<First, Rest...>> {
    using type = typename Get<Index - 1, TypeList<Rest...>>::type;
};

template <typename T, typename List>
struct Contains;

template <typename T>
struct Contains<T, TypeList<>> {
    static constexpr bool value = false;
};

template <typename T, typename First, typename... Rest>
struct Contains<T, TypeList<First, Rest...>> {
    static constexpr bool value = std::is_same_v<T, First> || Contains<T, TypeList<Rest...>>::value;
};

template <typename T, typename List>
struct IndexOf;

template <typename T>
struct IndexOf<T, TypeList<>> {
};

template <typename T, typename... Rest>
struct IndexOf<T, TypeList<T, Rest...>> {
    static constexpr size_t value = 0;
};

template <typename T, typename First, typename... Rest>
struct IndexOf<T, TypeList<First, Rest...>> {
    static constexpr size_t value = 1 + IndexOf<T, TypeList<Rest...>>::value;
};

template <typename List, typename T>
struct PushBack;

template <typename... Types, typename T>
struct PushBack<TypeList<Types...>, T> {
    using type = TypeList<Types..., T>;
};

template <typename List, typename T>
struct PushFront;

template <typename... Types, typename T>
struct PushFront<TypeList<Types...>, T> {
    using type = TypeList<T, Types...>;
};

} // namespace TypeListImpl



template <typename... Types>
using TypeList = TypeListImpl::TypeList<Types...>;

template <typename List>
using Size = TypeListImpl::Size<List>;

template <size_t Index, typename List>
using Get = typename TypeListImpl::Get<Index, List>::type;

template <typename T, typename List>
constexpr bool Contains = TypeListImpl::Contains<T, List>::value;

template <typename T, typename List>
constexpr size_t IndexOf = TypeListImpl::IndexOf<T, List>::value;

template <typename List, typename T>
using PushBack = typename TypeListImpl::PushBack<List, T>::type;

template <typename List, typename T>
using PushFront = typename TypeListImpl::PushFront<List, T>::type;



int main() {
    using MyTypes = TypeList<int, double, char, float>;
    
    static_assert(Size<MyTypes>::value == 4);
    

    static_assert(std::is_same_v<Get<0, MyTypes>, int>);
    static_assert(std::is_same_v<Get<1, MyTypes>, double>);
    static_assert(std::is_same_v<Get<2, MyTypes>, char>);
    static_assert(std::is_same_v<Get<3, MyTypes>, float>);


    static_assert(Contains<int, MyTypes>);
    static_assert(Contains<double, MyTypes>);
    static_assert(!Contains<long, MyTypes>);
    

    static_assert(IndexOf<int, MyTypes> == 0);
    static_assert(IndexOf<double, MyTypes> == 1);
    static_assert(IndexOf<char, MyTypes> == 2);
    static_assert(IndexOf<float, MyTypes> == 3);
    

    using WithLong = PushBack<MyTypes, long>;
    static_assert(Size<WithLong>::value == 5);
    static_assert(std::is_same_v<Get<4, WithLong>, long>);
    static_assert(Contains<long, WithLong>);


    using WithShort = PushFront<MyTypes, short>;
    static_assert(Size<WithShort>::value == 5);
    static_assert(std::is_same_v<Get<0, WithShort>, short>);
    static_assert(std::is_same_v<Get<1, WithShort>, int>);
    


    using EmptyList = TypeList<>;
    static_assert(Size<EmptyList>::value == 0);
    static_assert(!Contains<int, EmptyList>);

    using SingleElement = PushBack<EmptyList, int>;
    static_assert(Size<SingleElement>::value == 1);
    static_assert(std::is_same_v<Get<0, SingleElement>, int>);
    
    return 0;
}