#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

static unsigned k[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
	0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
	0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
	0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
	0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
	0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

static unsigned func0(unsigned abcd[])
{
	return (abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);
}

static unsigned func1(unsigned abcd[])
{
	return (abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);
}

static unsigned func2(unsigned abcd[])
{
	return abcd[1] ^ abcd[2] ^ abcd[3];
}

static unsigned func3(unsigned abcd[])
{
	return abcd[2] ^ (abcd[1] | ~abcd[3]);
}

typedef unsigned (*DgstFctn)(unsigned a[]);

static unsigned rol(unsigned r, short N)
{
	unsigned mask1 = (1 << N) - 1;
	return ((r >> (32 - N)) & mask1) | ((r << N) & ~mask1);
}

static unsigned *MD5Hash(string msg)
{
	int mlen = msg.length();
	static unsigned h[4] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
	//we dont need different h0 and h
	static short M[] = {1, 5, 3, 7};
	static short O[] = {0, 1, 5, 0};
	static short rot0[] = {7, 12, 17, 22};
	static short rot1[] = {5, 9, 14, 20};
	static short rot2[] = {4, 11, 16, 23};
	static short rot3[] = {6, 10, 15, 21};
	// static unsigned h[4];
	unsigned abcd[4];
	short m, o, g;
	unsigned f;
	int q, p;
	unsigned char *msg2;
	// for (q = 0; q < 4; q++)
	// 	h[q] = h0[q];
	msg2 = (unsigned char *)malloc(64 * 1);
	memcpy(msg2, msg.c_str(), mlen);
	msg2[mlen] = (unsigned char)0x80;
	q = mlen + 1;
	while (q < 64)
	{
		//add padding bits
		msg2[q] = 0;
		q++;
	}
	
	int numBytes = 8 * mlen;
	q -= 8;
	//add length bits
	memcpy(msg2 + q, &numBytes, 4);

	unsigned word[16];
	char message[64];
	memcpy(message, msg2, 64);
	for (q = 0; q < 16; q++)
	{
		word[q] = 0;
		for (p = 0; p < 4; p++)
		{
			word[q] += abs(message[q * 4 + p]) * pow(2, (8 * p));
		}
	}

	for (q = 0; q < 4; q++)
		abcd[q] = h[q];

	for (p = 0; p < 4; p++)
	{

		m = M[p];
		o = O[p];
		for (q = 0; q < 16; q++)
		{
			g = (m * q + o) % 16;
			if (p == 0)
				f = abcd[1] + rol(abcd[0] + func0(abcd) + k[q + 16 * p] + word[g], rot0[q % 4]);
			else if (p == 1)
				f = abcd[1] + rol(abcd[0] + func1(abcd) + k[q + 16 * p] + word[g], rot1[q % 4]);
			if (p == 2)
				f = abcd[1] + rol(abcd[0] + func2(abcd) + k[q + 16 * p] + word[g], rot2[q % 4]);
			if (p == 3)
				f = abcd[1] + rol(abcd[0] + func3(abcd) + k[q + 16 * p] + word[g], rot3[q % 4]);

			abcd[0] = abcd[3];
			abcd[3] = abcd[2];
			abcd[2] = abcd[1];
			abcd[1] = f;
		}
	}
	
	for (p = 0; p < 4; p++)
		h[p] += abcd[p];

	return h;
}

static string GetMD5String(string msg)
{
	string str;
	int j, k;
	unsigned *d = MD5Hash(msg);

	for (j = 0; j < 4; j++)
	{
		unsigned temp = d[j];
		unsigned b[4];
		for (k = 3; k >= 0; k--)
		{
			b[k] = temp / (pow(2, k * 8));
			temp %= (int)(pow(2, k * 8));
		}
		char s[9];
		sprintf(s, "%02x%02x%02x%02x", b[0], b[1], b[2], b[3]);
		str += s;
	}

	return str;
}
int main()
{
	cout << GetMD5String("hello");
	return 0;
}
