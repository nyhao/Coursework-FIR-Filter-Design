#include <iostream>
#include <fstream>
#include "coursework.h"

using namespace std;

istream& operator>>(istream& in, float_seq& flsq)
{
    in>>flsq.num_fs_element;
    for(int i = 0; i < flsq.num_fs_element; ++i)
    {
        in>>flsq.fs_data[i];
    }
    return in;
}

ostream& operator<<(ostream& out, float_seq& flsq)
{
    out<<"Number of Data: "<<flsq.num_fs_element<<endl;
    out<<"Data: "<<endl;
    for(int i = 0; i < flsq.num_fs_element; ++i)
    {
        out<<flsq.fs_data[i]<<endl;
    }
    return out;
}

istream& operator>>(istream& FIR_in, FIR& fil_FIR)
{
    FIR_in>>fil_FIR.coefts;
    return FIR_in;
}

ostream& operator<<(ostream& FIR_out, FIR& fil_FIR)
{
    FIR_out<<fil_FIR.coefts;
    return FIR_out;
}

float_seq::float_seq(int nfs, float* fsd)
{
    num_fs_element = nfs;
    fs_data = new float[nfs];
    for (int i = 0; i < num_fs_element; ++i)
    {
        fs_data[i] = fsd[i];
    }
}

float_seq::~float_seq()
{
    delete []fs_data;
}

float_seq::float_seq(const float_seq& copy_fs):num_fs_element(copy_fs.num_fs_element)
{
    fs_data = new float[num_fs_element];
    for(int i = 0; i < num_fs_element; ++i)
    {
        fs_data[i] = copy_fs.fs_data[i];
    }
}

float_seq& float_seq::operator=(const float_seq& a)
{
    if(this == &a) return *this;
    if(num_fs_element != a.num_fs_element)
    {
        num_fs_element = a.num_fs_element;
        delete []fs_data;
        fs_data = new float[num_fs_element];
    }
    for(int i = 0; i < num_fs_element; ++i)
    {
        fs_data[i] = a.fs_data[i];
    }
    return *this;
}

float float_seq::get_fs(int n)
{
    return fs_data[n];
}

void float_seq::set_value_fs(int n, float v)
{
    fs_data[n] = v;
}

void float_seq::zero_data()
{
    for(int i = 0; i < num_fs_element; ++i)
    {
        fs_data[i] = 0;
    }
}

float_seq::float_seq(istream& fs_in)
{
    fs_in>>num_fs_element;
    fs_data = new float[num_fs_element];
    for(int i = 0; i < num_fs_element; ++i)
    {
        fs_in>>fs_data[i];
    }
}

float_seq float_seq::operator+(const float_seq& f)
{
    float_seq sum(f);
    sum.num_fs_element += num_fs_element;
    delete []sum.fs_data;
    sum.fs_data = new float[sum.num_fs_element];
    sum.zero_data();
    int j;
    for (int k = 0; k < num_fs_element; ++k)
    {
        sum.fs_data[k] = fs_data[k];
    }
    for (int i = num_fs_element; i < sum.num_fs_element; ++i)
    {
        j = i - num_fs_element;
        sum.fs_data[i] = f.fs_data[j];
    }

    return sum;
}

FIR::FIR(float_seq& fsc):coefts(fsc) {}

FIR::FIR()
{
    coefts = float_seq();
}

FIR::~FIR() {}

FIR::FIR(const FIR& copy_coefts):coefts(copy_coefts.coefts) {}

FIR& FIR::operator=(const FIR& b)
{
    coefts = b.coefts;
    return *this;
}

float FIR::get_coefts(int m)
{
    return coefts.get_fs(m);
}

void FIR::set_value_fil(int m, float o)
{
    coefts.set_value_fs(m, o);
}

float_seq FIR::return_coefts()
{
    return coefts;
}

float_seq FIR::do_filtering(float_seq fil_fs)
{
    float_seq fs_output(fil_fs);
    fs_output.num_fs_element += coefts.num_fs_element - 1;
    delete []fs_output.fs_data;
    fs_output.fs_data = new float[fs_output.num_fs_element];
    fs_output.zero_data();
    int k;
    for(int i = 0; i < coefts.num_fs_element; ++i)
    {
        for(int j = 0; j < fil_fs.num_fs_element; ++j)
        {
            k = j + i;
            fs_output.fs_data[k] += coefts.fs_data[i] * fil_fs.fs_data[j];
        }
    }
    return fs_output;
}

FIR::FIR(istream& fil_in)
{
    fil_in>>coefts.num_fs_element;
    coefts.fs_data = new float[coefts.num_fs_element];
    for(int i = 0; i < coefts.num_fs_element; ++i)
    {
        fil_in>>coefts.fs_data[i];
    }
}
