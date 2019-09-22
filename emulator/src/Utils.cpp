#include <cstddef>
#include "../include/Utils.hpp"


template<typename T, size_t N>
void init_array(T (&arr)[N], T const&val){
    for (size_t i = 0; i < N; ++i)
        arr[i] = val;
}