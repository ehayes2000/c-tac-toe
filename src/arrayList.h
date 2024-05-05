#include "ctype.h"

class ArrayList
{
public:
    ArrayList();
    int operator[](size_t i);
    int pop();
    void append(int i);

private:
    size_t size;
    size_t items;
    int *container;
};
