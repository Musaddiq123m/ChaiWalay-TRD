// phi is no of numbers < n coprime with n 
const int N = 1000005;
int lp[N], mu[N], phi[N];
vi pr;
void sieve()
{
    mu[1] = 1;
    phi[1] = 1;
    forn(i, 2, N){
        if (lp[i] == 0){
            lp[i] = i;
            pr.push_back(i);
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for (int p : pr){
            if (p > lp[i] || i * p >= N)
                break;
            lp[i * p] = p;
            if (lp[i] == p){
                mu[i * p] = 0;
                phi[i * p] = phi[i] * p;
            }
            else{
                mu[i * p] = -mu[i];
                phi[i * p] = phi[i] * (p - 1);
            }
        }
    }
}