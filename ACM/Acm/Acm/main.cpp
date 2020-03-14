#include <iostream>
#include <string>
#include "stdlib.h"
#include "stdio.h"

using namespace std;

class DisjointSetNode
{
public:
    DisjointSetNode() { parent = NULL; rank = 0; }
    DisjointSetNode* parent;
    int rank;

    void Union(DisjointSetNode* n2)
    {
        if (this->rank > n2->rank)
        {
            n2->parent = this;
        }
        else if (n2->rank > this->rank)
        {
            this->parent = n2;
        }
        else
        {
            n2->parent = this;
            this->rank++;
        }
    }
};

int main()
{

}