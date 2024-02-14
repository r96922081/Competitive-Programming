#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
#include <streambuf>

using namespace std;

extern int main103();

int main()
{
    ifstream in("D:\\Github\\Competitive-Programming\\ACM\\_IO\\uva103_input.txt");
    streambuf* cinbuf = std::cin.rdbuf();
    cin.rdbuf(in.rdbuf());

    ofstream out("uva103_my_output.txt");
    streambuf* coutbuf = std::cout.rdbuf(); // Save old cout buffer
    cout.rdbuf(out.rdbuf());

    main103();
    return 0;
}