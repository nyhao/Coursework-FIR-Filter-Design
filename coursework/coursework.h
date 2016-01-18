using namespace std;

class float_seq;
class FIR;
ostream& operator<<(ostream&, float_seq&);
ostream& operator<<(ostream&, FIR&);
istream& operator>>(istream&, float_seq&);
istream& operator>>(istream&, FIR&);

class float_seq
{
    public:
    float_seq(int nfs = 0, float* fsd = NULL);
    ~float_seq();
    float_seq(const float_seq& copy_fs);
    float_seq& operator=(const float_seq& a);
    float get_fs(int n);
    void set_value_fs(int n, float v);
    void zero_data();
    float_seq(istream& fs_in);
    float_seq operator+(const float_seq& f);
    friend class FIR;
    friend istream& operator>>(istream&, float_seq&);
    friend ostream& operator<<(ostream&, float_seq&);

    private:
    float* fs_data;
    int num_fs_element;
};

class FIR
{
    public:
    FIR(float_seq& fsc);
    FIR();
    ~FIR();
    FIR(const FIR& copy_coefts);
    FIR& operator=(const FIR& b);
    float get_coefts(int m);
    void set_value_fil(int m, float o);
    float_seq return_coefts();
    float_seq do_filtering(float_seq fil_fs);
    FIR(istream& fil_in);
    friend istream& operator>>(istream&, FIR&);
    friend ostream& operator<<(ostream&, FIR&);

    private:
    float_seq coefts;
};
