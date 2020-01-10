#include <stdio.h>

class Foo
{
public:
    Foo();
};

class Bar : virtual public Foo
{
public:
    Bar(int);
};

class Baz : virtual public Bar
{
public:
    Baz(int);
};

Foo::Foo()
{
    printf("Foo\n");
}

Bar::Bar(int i)
{
    printf("Bar: %d\n", i);
}

Baz::Baz(int i) : Bar(i)
{
    printf("Baz\n");
}

int main()
{
    Baz Baz(1);
    return 0;
}