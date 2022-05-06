#include <stdio.h>
#include <functional>

template <typename T>
struct Callback;

template <typename ReturnType, typename... ParameterList>
struct Callback<ReturnType(ParameterList...)>
{
    template <typename... Args>
    static ReturnType callback(Args... args)
    {
        return func(args...);
    }
    static std::function<ReturnType(ParameterList...)> func;
};

template <typename ReturnType, typename... ParameterList>
std::function<ReturnType(ParameterList...)> Callback<ReturnType(ParameterList...)>::func;

void register_with_library(int (*func)(int* k, int* e))
{
    int x = 0, y = 1;
    int o = func(&x, &y);
    printf("Value: %i\n", o);
}

class A
{
    public:
    A();
    int e(int* k, int* j);
};

typedef int (*callback_t)(int*, int*);

A::A()
{
    Callback<int(int*, int*)>::func = std::bind(&A::e, this, std::placeholders::_1, std::placeholders::_2);
    callback_t func = static_cast<callback_t>(Callback<int(int*, int*)>::callback);
    register_with_library(func);
}

int A::e(int* k, int* j)
{
    return *k - *j;
}

int main()
{
    A a;

    return 0;
}