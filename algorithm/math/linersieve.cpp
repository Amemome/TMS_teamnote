
ll pw(ll a,ll b) {ll ret=1;
    while(b){
        if(b&1) ret *= a;
        a*=a; b>>=1;
    } return ret;}

#define SZ 1000010

vector<int> prime;
int phi[SZ+1],mu[SZ+1],sigma[SZ+1],tau[SZ+1],e[SZ+1],sp[SZ+1];
void sieve() { //tau=약수의개수,sigma=약수의합,sp=최소소인수
    phi[1] = mu[1] =tau[1]=sigma[1] =1;
    for(int i=2; i<=SZ; i++) {
        if(!sp[i]){
            prime.push_back(i);
            e[i]=1;phi[i]=i-1;mu[i]=-1;tau[i]=2;sigma[i]=i+1;
        }
        for(auto j:prime){
            if(i*j >= SZ)break; sp[i*j] = j;
            if(i%j==0) {
                e[i*j] = e[i]+1; phi[i*j] = phi[i]*j; mu[i*j]=0;
                tau[i*j] = tau[i]/e[i*j]*(e[i*j]+1);
                sigma[i*j] = sigma[i]*(j-1)/
                (pw(j,e[i*j]-1))*(pw(j,e[i*j]+1)-1)/(j-1);
                break; //시그마는오버플로우주의
            }
            e[i*j]=1; phi[i*j] = phi[i] * phi[j]; mu[i*j] = mu[i] * mu[j];
            tau[i*j] = tau[i] * tau[j]; sigma[i*j]=sigma[i]*sigma[j];
        }
    }
}


