/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;
/*****Please include following header files*****/
// string
/***********************************************/

/*****Please use following namespaces*****/
// std
/*****************************************/

typedef union uwb {
	unsigned w;
	unsigned char b[4];
} MD5union;

typedef unsigned DigestArray[4];

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

	static DigestArray h;
	DigestArray abcd;
	DgstFctn fctn;
	short m, o, g;
	unsigned f;
	short *rotn;
	union {
		unsigned w[16];
		char     b[64];
	}mm;
	int os = 0;
	int grp, grps, q, p;
	unsigned char *msg2;

	//if (k == NULL) 
    k = calctable(kspace);

	for (q = 0; q<4; q++) h[q] = h0[q];

	
		//grps = 1;
        //cout<<"NO "<<grps<<endl;
		msg2 = (unsigned char*)malloc(64*1);
		memcpy(msg2, msg.c_str(), mlen);
		msg2[mlen] = (unsigned char)0x80;
		q = mlen + 1;
		while (q < 64){ msg2[q] = 0; q++; }
		{
			//MD5union u;
			//u.w = 8 * mlen;
			int numBytes=8*mlen;
			q -= 8;
			memcpy(msg2 + q, &numBytes, 4);
		}
	

	//for (grp = 0; grp<grps; grp++)
	//{
		memcpy(mm.b, msg2, 64);
		for (q = 0; q<4; q++) abcd[q] = h[q];
		for (p = 0; p<4; p++) {
			
			
			m = M[p]; o = O[p];
			for (q = 0; q<16; q++) {
				g = (m*q + o) % 16;
                if(p==0)
				f = abcd[1] + rol(abcd[0] + func0(abcd) + k[q + 16 * p] + mm.w[g], rot0[q % 4]);
                else if(p==1)
				f = abcd[1] + rol(abcd[0] + func1(abcd) + k[q + 16 * p] + mm.w[g], rot1[q % 4]);
                if(p==2)
				f = abcd[1] + rol(abcd[0] + func2(abcd) + k[q + 16 * p] + mm.w[g], rot2[q % 4]);
                if(p==3)
				f = abcd[1] + rol(abcd[0] + func3(abcd) + k[q + 16 * p] + mm.w[g], rot3[q % 4]);

				abcd[0] = abcd[3];
				abcd[3] = abcd[2];
				abcd[2] = abcd[1];
				abcd[1] = f;
			}
		}
		for (p = 0; p<4; p++)
			h[p] += abcd[p];
		//os += 64;
	//}

	return h;
}

static string GetMD5String(string msg) {
	string str;
	int j, k;
	unsigned *d = MD5Hash(msg);
	//MD5union u;
	
	for (j = 0; j<4; j++){
		//u.w = d[j];
        //cout<<d[j]<<endl;
        unsigned temp=d[j];
        unsigned b[4];
        for (k=3;k>=0;k--)
        {
            b[k]=temp/(pow(2,k*8));
            cout<<b[k]<<endl;
            temp%=(int)(pow(2,k*8));
        }
		char s[9];
		sprintf(s, "%02x%02x%02x%02x",b[0], b[1], b[2], b[3]);
		//cout<<u.b[0]<<u.b[1]<<u.b[2]<<u.b[3]<<endl;
		str += s;
	}

	return str;
}
int main()
{
    cout<<GetMD5String("hello");

    return 0;
}
