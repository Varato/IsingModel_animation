/* 2D Ising Model */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <cassert>

typedef std::vector<int> vec;
typedef std::vector<float> vecf;

int mod(int a, int b);

class IsingModel
{
private:
    int N, M;
    int num_s;
    float T;
    vec s;
    float e; //current system energy
    float e_sqr;
    void find_nns(int n, int (&nns)[4]);
    void energy();
public:
    IsingModel(int N, int M);
    ~IsingModel(void);
    void Monte_Carlo(bool eval_energy);
    inline void set_T(float new_T);
    inline void get_energy(float ee[2]);
    void draw(int i, bool eval_energy);
};

int main()
{

    std::ofstream outfile;
    outfile.open("energy_data_15_100_100", std::ios::out);
    int N = 100, M = 100;
    int tmax = 50000;
    int tdis = 2000;
    int ave_n = tmax - tdis;
    int t;
    vecf e_sum;
    vecf e_sqr_sum;
    vecf c;      // heat capacity record
    float ee[2]; // array to store energy and squared energy
    float cc; 
    vecf T = {1.5};
    IsingModel ising(N, M);
    ising.draw(0, false);
    for(int i = 0; i < T.size(); i++){
        ising.set_T(T[i]);
        e_sum.push_back(0.);
        e_sqr_sum.push_back(0.);

        for(t = 0; t < tdis; ++t){
            ising.Monte_Carlo(false);
            ising.draw(t+1, false);
        }
        for(t = 0; t < tmax - tdis; ++t){
            ising.Monte_Carlo(true);
            ising.draw(t+tdis+1, true);
            ising.get_energy(ee);
            outfile << ee[0] << std::endl;
            e_sum[i] += ee[0];
            e_sqr_sum[i] += ee[1];
        }
        cc = e_sqr_sum[i]/ave_n/T[i]/T[i] \
            - e_sum[i]*e_sum[i]/ave_n/ave_n/T[i]/T[i];
        c.push_back(cc);
    }
    std::cout << "\033[" << N+1 << "B" <<std::endl;

    outfile.close();

}

// constructor
IsingModel::IsingModel(int N, int M)
{
    this->N = N;
    this->M = M;
    this->num_s = N*M;
    srand(222);
    for(int i = 0; i < N*M; ++i)
        this->s.push_back(-1) ;//(int)(2*(std::rand()%2 - 0.5)) );
}

IsingModel::~IsingModel()
{
    ;
}


void IsingModel::Monte_Carlo(bool eval_energy = false)
{
    int nns[4];
    int e = 0;
    int n;
    for(int k = 0; k < this->num_s; ++k){
        n = std::rand()%this->num_s;
        this->find_nns(n, nns);
        e = 0;
        for(int j = 0; j < 4; ++j)
            e += this->s[nns[j]];
        e *= 2 * this->s[n];
        if(e <= 0 || std::rand()/(float)RAND_MAX < std::exp(-e/this->T))
            this->s[n] *= -1;
    }
    // evaluate energy
    if (eval_energy) this->energy();
}

void IsingModel::find_nns(int n, int (&nns)[4])
{

    int i, j, u_i, d_i, l_j, r_j;

    i = n/this->M; j = n%this->M;
    u_i = mod(i-1, this->N); 
    d_i = mod(i+1, this->N);
    l_j = mod(j-1, this->M); 
    r_j = mod(j+1, this->M);
    
    nns[0] = u_i*this->N + j; 
    nns[1] = d_i*this->N + j;
    nns[2] = i*this->M + l_j; 
    nns[3] = i*this->M + r_j;
}

void IsingModel::energy()
{
    int nns[4];
    this->e = 0;
    for (int i = 0; i < this->num_s; ++i){
        this->find_nns(i, nns);
        this->e -= this->s[i] * this->s[nns[1]];
        this->e -= this->s[i] * this->s[nns[3]];
    }
    assert(abs(this->e) <= this->num_s * 2 + 1e-5);
    this->e_sqr = this->e * this->e;
}

inline void IsingModel::get_energy(float ee[2])
{
    ee[0] = this->e;
    ee[1] = this->e_sqr;
}

inline void IsingModel::set_T(float new_T)
{
    this->T = new_T;
}

void IsingModel::draw(int i, bool eval_energy = false)
{
    std::string str = "\n";
    for (int i = 0; i < this->num_s ; ++i){
        str += this->s[i] == 1 ? "\033[01;31m O\033[00m" : "\033[01;32m O\033[00m";
        if ((i+1) % this->M == 0) str += "\n";
    }
    std::cout << str;
    printf(" step = %d, T = %.3f ", i,  this->T);
    if (eval_energy)
        printf(", E = %.0f", this->e );
    std::fflush(stdout);
    std::cout << "\033[" << this->N+1 << "A";
}

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}


