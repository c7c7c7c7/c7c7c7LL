#include<bits/stdc++.h>
using namespace std;


unsigned long long xor128() {
    static unsigned long long rx = 123456789, ry = 362436069, rz = 521288629, rw = 88675123;
    unsigned long long rt = (rx ^ (rx << 11));
    rx = ry;
    ry = rz;
    rz = rw;
    return (rw = (rw ^ (rw >> 19)) ^ (rt ^ (rt >> 8)));
}

int a[3];

int main(){
	int i=10000000;
	while(i--){
		a[xor128()%3]++;
	}
	for(int j=0;j<3;j++){
		cout<<a[j]<<endl;
	}
}