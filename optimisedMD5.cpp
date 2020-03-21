#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

static unsigned func0(unsigned abcd[]){
	return (abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);
}

static unsigned func1(unsigned abcd[]){
	return (abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);
}

static unsigned func2(unsigned abcd[]){
	return  abcd[1] ^ abcd[2] ^ abcd[3];
}

static unsigned func3(unsigned abcd[]){
	return abcd[2] ^ (abcd[1] | ~abcd[3]);
}

typedef unsigned(*DgstFctn)(unsigned a[]);

static unsigned *calctable(unsigned *k)
{
	double s, pwr;
	int i;

	pwr = pow(2.0, 32);
	for (i = 0; i<64; i++) {
		s = fabs(sin(1.0 + i));
		k[i] = (unsigned)(s * pwr);
	}
	return k;
}

static unsigned rol(unsigned r, short N)
{
	unsigned  mask1 = (1 << N) - 1;
	return ((r >> (32 - N)) & mask1) | ((r << N) & ~mask1);
}

static unsigned* MD5Hash(string msg)
{
	int mlen = msg.length();
	static unsigned h0[4] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };
	
	static short M[] = { 1, 5, 3, 7 };
	static short O[] = { 0, 1, 5, 0 };
	static short rot0[] = { 7, 12, 17, 22 };
	static short rot1[] = { 5, 9, 14, 20 };
	static short rot2[] = { 4, 11, 16, 23 };
	static short rot3[] = { 6, 10, 15, 21 };
	
	static unsigned kspace[64];
	static unsigned *k;

	static unsigned h[4];
	unsigned abcd[4];
	short m, o, g;
	unsigned f;
	int q, p;
	unsigned char *msg2;

    k = calctable(kspace);

	for (q = 0; q<4; q++) h[q] = h0[q];

	
		msg2 = (unsigned char*)malloc(64*1);
		memcpy(msg2, msg.c_str(), mlen);
		msg2[mlen] = (unsigned char)0x80;
		q = mlen + 1;
		while (q < 64){ msg2[q] = 0; q++; }
		{
			int numBytes=8*mlen;
			q -= 8;
			memcpy(msg2 + q, &numBytes, 4);
		}
	
        unsigned word[16];
        char message[64];
		memcpy(message, msg2, 64);
        for(q=0;q<16;q++)
        {
            word[q]=0;
            for(p=0;p<4;p++)
            {
                word[q]+=abs(message[q*4+p])*pow(2,(8*p));
            }
        }
        
    
		for (q = 0; q<4; q++) abcd[q] = h[q];
		for (p = 0; p<4; p++) {
			
			
			m = M[p]; o = O[p];
			for (q = 0; q<16; q++) {
				g = (m*q + o) % 16;
                if(p==0)
				f = abcd[1] + rol(abcd[0] + func0(abcd) + k[q + 16 * p] + word[g], rot0[q % 4]);
                else if(p==1)
				f = abcd[1] + rol(abcd[0] + func1(abcd) + k[q + 16 * p] + word[g], rot1[q % 4]);
                if(p==2)
				f = abcd[1] + rol(abcd[0] + func2(abcd) + k[q + 16 * p] + word[g], rot2[q % 4]);
                if(p==3)
				f = abcd[1] + rol(abcd[0] + func3(abcd) + k[q + 16 * p] + word[g], rot3[q % 4]);

				abcd[0] = abcd[3];
				abcd[3] = abcd[2];
				abcd[2] = abcd[1];
				abcd[1] = f;
			}
		}
		for (p = 0; p<4; p++)
			h[p] += abcd[p];
		

	return h;
}

static string GetMD5String(string msg) {
	string str;
	int j, k;
	unsigned *d = MD5Hash(msg);
	
	for (j = 0; j<4; j++){
        unsigned temp=d[j];
        unsigned b[4];
        for (k=3;k>=0;k--)
        {
            b[k]=temp/(pow(2,k*8));
            temp%=(int)(pow(2,k*8));
        }
		char s[9];
		sprintf(s, "%02x%02x%02x%02x",b[0], b[1], b[2], b[3]);
		str += s;
	}

	return str;
}
int main()
{
    cout<<GetMD5String("hello");return 0;
}
