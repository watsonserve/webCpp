#include <stdio.h>

class Foo
{
public:
    Foo(int);
};

class Bar: virtual public Foo
{
public:
    Bar(int);
};

class Baz: virtual public Bar
{
public:
    Baz(int, int);
};

Foo::Foo(int i)
{
    printf("Foo: %d\n", i);
}

Bar::Bar(int i) : Foo(i)
{
    printf("Bar: %d\n", i);
}

// Class Foo 不存在默认构造函数
Baz::Baz(int i, int j) : Bar(i)
{
    printf("Baz: %d, %d\n", i, j);
}

int main()
{
    Baz Baz(1, 2);
    return 0;
}
