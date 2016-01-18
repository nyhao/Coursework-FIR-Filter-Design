#include <iostream>
#include <fstream>
#include "coursework.h"

using namespace std;

int main()
{
    ifstream input("input1.txt");
    ifstream filter("filter1.txt");
    ofstream output("output.txt");
    FIR my_filter(filter1);
    float_seq ip(input1);
    float_seq op(my_filter.do_filtering(ip));
    cout<<op;
    output<<op;
    input.close();
    filter.close();
    output.close();
}
