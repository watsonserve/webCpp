#include <stdio.h>

class Base {
public:
    virtual void foo() =0;
};

class Foo : virtual public Base
{
public:
    Foo();
    virtual ~Foo();
    virtual void foo() override;
};

Foo::Foo()
{}

Foo::~Foo()
{}

void Foo::foo()
{
    printf("foo\n");
}

int main()
{
    Foo foo;
    foo.foo();
    return 0;
}
