#include <bits/stdc++.h>
#include <vector>
#include <string>
using namespace std;

unsigned long long int K[64] = {
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

// int md5_shift[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20,
// 					 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
// 					 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

// int md5_indexes[64] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1, 6, 11, 0, 5, 10, 15, 4,
// 					   9, 14, 3, 8, 13, 2, 7, 12, 5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
// 					   0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9};


unsigned long long int F(unsigned long long int x, unsigned long long int y, unsigned long long int z){
	return (z ^ (x & (y ^ z)) );
}

unsigned long long int G(unsigned long long int x, unsigned long long int y, unsigned long long int z)
{
	return y ^ (z & (x ^ y));
}

unsigned long long int H(unsigned long long int x, unsigned long long int y, unsigned long long int z)
{
	return x ^ y ^ z;
}

unsigned long long int I(unsigned long long int x, unsigned long long int y, unsigned long long int z)
{
	return y ^ (x | ~z);
}

void funct(unsigned long long int *Aptr, unsigned long long int *Bptr, unsigned long long int *Cptr, unsigned long long int *Dptr, int k , int s , int i ,unsigned long long int m[16] , int flag ){
	
	if(flag == 0){
		*Aptr = *Bptr + ((*Aptr + F(*Bptr, *Cptr, *Dptr) + m[k] + K[i])<<s);
		*Aptr = (*Aptr) & (0xffffffff);
		*Bptr = (*Bptr) & (0xffffffff);
		*Cptr = (*Cptr) & (0xffffffff);
		*Dptr = (*Dptr) & (0xffffffff);
	} 
	else if(flag == 1){
		*Aptr = *Bptr + ((*Aptr + G(*Bptr, *Cptr, *Dptr) + m[k] + K[i]) << s);
		*Aptr = (*Aptr) & (0xffffffff);
		*Bptr = (*Bptr) & (0xffffffff);
		*Cptr = (*Cptr) & (0xffffffff);
		*Dptr = (*Dptr) & (0xffffffff);
	}
	else if(flag == 2){
		*Aptr = *Bptr + ((*Aptr + H(*Bptr, *Cptr, *Dptr) + m[k] + K[i]) << s);
		*Aptr = (*Aptr) & (0xffffffff);
		*Bptr = (*Bptr) & (0xffffffff);
		*Cptr = (*Cptr) & (0xffffffff);
		*Dptr = (*Dptr) & (0xffffffff);
	}else{
		*Aptr = *Bptr + ((*Aptr + I(*Bptr, *Cptr, *Dptr) + m[k] + K[i]) << s);
		*Aptr = (*Aptr) & (0xffffffff);
		*Bptr = (*Bptr) & (0xffffffff);
		*Cptr = (*Cptr) & (0xffffffff);
		*Dptr = (*Dptr) & (0xffffffff);
	}
}

void F_block(string msg){
	unsigned long long int m[16];
	memset(m , sizeof(m) , 0);

	for(int i = 0; i < 16; i++){
		for(int j = i*4; j < i*4 + 4; j++){
			m[i] += (msg[j])*(int)(pow(2, (3-j%4)*8) + 0.5);
		}
	}

	unsigned long long int A = 0x01234567;
	unsigned long long int B = 0x89abcdef;
	unsigned long long int C = 0xfedcba98;
	unsigned long long int D = 0x76543210;

	///F block
	funct(&A, &B, &C, &D, 0, 7, 0, m ,0);
	funct(&D, &A, &B, &C, 1, 12, 1, m, 0);
	funct(&C, &D, &A, &B, 2, 17, 2, m, 0);
	funct(&B, &C, &D, &A, 3, 22, 3, m, 0);

	funct(&A, &B, &C, &D, 4, 7, 4, m, 0);
	funct(&D, &A, &B, &C, 5, 12, 5, m, 0);
	funct(&C, &D, &A, &B, 6, 17, 6, m, 0);
	funct(&B, &C, &D, &A, 7, 22, 7, m, 0);

	funct(&A, &B, &C, &D, 8, 7, 8, m, 0);
	funct(&D, &A, &B, &C, 9, 12, 9, m, 0);
	funct(&C, &D, &A, &B, 10, 17, 10, m, 0);
	funct(&B, &C, &D, &A, 11, 22, 11, m, 0);

	funct(&A, &B, &C, &D, 12, 7, 12, m, 0);
	funct(&D, &A, &B, &C, 13, 12, 13, m, 0);
	funct(&C, &D, &A, &B, 14, 17, 14, m, 0);
	funct(&B, &C, &D, &A, 15, 22, 15, m, 0);

	//G block
	funct(&A, &B, &C, &D, 1, 5, 16, m, 1);
	funct(&D, &A, &B, &C, 6, 9, 17, m, 1);
	funct(&C, &D, &A, &B, 11, 14, 18, m, 1);
	funct(&B, &C, &D, &A, 0, 20, 19, m, 1);

	funct(&A, &B, &C, &D, 5, 5, 20, m, 1);
	funct(&D, &A, &B, &C, 10, 9, 21, m, 1);
	funct(&C, &D, &A, &B, 3, 14, 22, m, 1);
	funct(&B, &C, &D, &A, 4, 20, 23, m, 1);

	funct(&A, &B, &C, &D, 9, 5, 24, m, 1);
	funct(&D, &A, &B, &C, 14, 9, 25, m, 1);
	funct(&C, &D, &A, &B, 3, 14, 26, m, 1);
	funct(&B, &C, &D, &A, 8, 20, 27, m, 1);

	funct(&A, &B, &C, &D, 13, 5, 28, m, 1);
	funct(&D, &A, &B, &C, 2, 9, 29, m, 1);
	funct(&C, &D, &A, &B, 7, 14, 30, m, 1);
	funct(&B, &C, &D, &A, 12, 20, 31, m, 1);

	///H block
	funct(&A, &B, &C, &D, 5, 4, 32, m, 2);
	funct(&D, &A, &B, &C, 8, 11, 33, m, 2);
	funct(&C, &D, &A, &B, 11, 16, 34, m, 2);
	funct(&B, &C, &D, &A, 14, 23, 35, m, 2);

	funct(&A, &B, &C, &D, 1, 4, 36, m, 2);
	funct(&D, &A, &B, &C, 4, 11, 37, m, 2);
	funct(&C, &D, &A, &B, 7, 16, 38, m, 2);
	funct(&B, &C, &D, &A, 10, 23, 39, m, 2);

	funct(&A, &B, &C, &D, 13, 4, 40, m, 2);
	funct(&D, &A, &B, &C, 0, 11, 41, m, 2);
	funct(&C, &D, &A, &B, 3, 16, 42, m, 2);
	funct(&B, &C, &D, &A, 6, 23, 43, m, 2);

	funct(&A, &B, &C, &D, 9, 4, 44, m, 2);
	funct(&D, &A, &B, &C, 12, 11, 45, m, 2);
	funct(&C, &D, &A, &B, 15, 16, 46, m, 2);
	funct(&B, &C, &D, &A, 2, 23, 47, m, 2);

	///I block
	funct(&A, &B, &C, &D, 0, 6, 48, m, 3);
	funct(&D, &A, &B, &C, 7, 10, 49, m, 3);
	funct(&C, &D, &A, &B, 14, 15, 50, m, 3);
	funct(&B, &C, &D, &A, 5, 21, 51, m, 3);

	funct(&A, &B, &C, &D, 12, 6, 52, m, 3);
	funct(&D, &A, &B, &C, 3, 10, 53, m, 3);
	funct(&C, &D, &A, &B, 10, 15, 54, m, 3);
	funct(&B, &C, &D, &A, 1, 21, 55, m, 3);

	funct(&A, &B, &C, &D, 8, 6, 56, m, 3);
	funct(&D, &A, &B, &C, 15, 10, 57, m, 3);
	funct(&C, &D, &A, &B, 6, 15, 58, m, 3);
	funct(&B, &C, &D, &A, 13, 21, 59, m, 3);

	funct(&A, &B, &C, &D, 4, 6, 60, m, 3);
	funct(&D, &A, &B, &C, 11, 10, 61, m, 3);
	funct(&C, &D, &A, &B, 2, 15, 62, m, 3);
	funct(&B, &C, &D, &A, 9, 21, 63, m, 3);
	// A = (*Aptr) & (0xffffffff);
	// B = (*Bptr) & (0xffffffff);
	// C = (*Cptr) & (0xffffffff);
	// D = (*Dptr) & (0xffffffff);
	cout << A << " ";
	cout << B << " ";
	cout << C << " ";
	cout << D << endl;

	cout <<hex<< A <<" ";
	cout << hex << B << " ";
	cout << hex << C << " ";
	cout << hex<<D << endl;
	funct(&A, &B, &C, &D, 0, 7, 0, m, 0);
	funct(&D, &A, &B, &C, 1, 12, 1, m, 0);
	funct(&C, &D, &A, &B, 2, 17, 2, m, 0);
	funct(&B, &C, &D, &A, 3, 22, 3, m, 0);

	funct(&A, &B, &C, &D, 4, 7, 4, m, 0);
	funct(&D, &A, &B, &C, 5, 12, 5, m, 0);
	funct(&C, &D, &A, &B, 6, 17, 6, m, 0);
	funct(&B, &C, &D, &A, 7, 22, 7, m, 0);

	funct(&A, &B, &C, &D, 8, 7, 8, m, 0);
	funct(&D, &A, &B, &C, 9, 12, 9, m, 0);
	funct(&C, &D, &A, &B, 10, 17, 10, m, 0);
	funct(&B, &C, &D, &A, 11, 22, 11, m, 0);

	funct(&A, &B, &C, &D, 12, 7, 12, m, 0);
	funct(&D, &A, &B, &C, 13, 12, 13, m, 0);
	funct(&C, &D, &A, &B, 14, 17, 14, m, 0);

	cout<<hex<<11<<endl;
}

//function to convert binary sequence to string
string BinarytoString(string bit_stream)
{
	stringstream sstream(bit_stream);
	string output;
	while (sstream.good())
	{
		bitset<8> bits;
		sstream >> bits;
		char c = char(bits.to_ulong());
		output += c;
	}
	//correction
	//
	output.pop_back();
	// cout << output;
	return output;
}
int main()
{
	//1. take input///////////
	//we assume that msg string is not greater than 512 bits in size
	string msg;
	getline(cin, msg);

	//2. padding//////////////
	//convert to bits
	cout << "binary sequence of msg string is: ";
	for (size_t i = 0; i < msg.size(); ++i)
	{
		//print out the bit sequence of msg string
		cout << bitset<8>(msg.c_str()[i]);
	}
	cout << endl;

	int len = msg.size();   //calculate length of message string
	int len_bits = len * 8; //length in bits (1 char = 1 byte = 8 bits)

	//calculate no of bits to be padded at the end
	int len_pad = 512 - 64 - len_bits;

	string pad_string_bit_seq = "1";
	for (int i = 0; i < len_pad-1; i++)
	{
		pad_string_bit_seq += "0";
	}

	//convert string binary seqeunce to string
	string pad_string = BinarytoString(pad_string_bit_seq);
	string msg_padded = msg + pad_string; //append the padded character sequence at the end of msg

	cout << "padded msg string is :";
	cout << msg_padded << endl;
	cout << "binary sequence of padded msg string is: ";
	// check if the string is correct by printing the bit sequence
	for (size_t i = 0; i < msg_padded.size(); ++i)
	{
		//print out the bit sequence of msg string
		cout << bitset<8>(msg_padded.c_str()[i]);
	}
	cout << endl;

	//3. add length bits////////////
	string len_pad_string = "";
	int len_temp = len * 8;
	cout << len_temp << endl;
	while (len_temp != 0)
	{
		int r = len_temp % 2;
		if (r == 1)
		{
			len_pad_string += "1";
		}
		else
			len_pad_string += "0";
		len_temp /= 2;
	}
	reverse(len_pad_string.begin(), len_pad_string.end());
	// cout<<len_pad_string<<endl;
	len_temp = 64 - len_pad_string.size();
	// cout<<len_temp<<endl;
	for (int i = 0; i < len_temp; i++)
	{
		len_pad_string = "0" + len_pad_string;
	}
	cout << "length bit" << endl;
	// cout<<len_bits<<endl;
	cout << len_pad_string << endl;

	pad_string = BinarytoString(len_pad_string);
	msg_padded += pad_string;
	cout << "final padded string: ";
	cout << msg_padded << endl;
	// cout << msg_padded.size();
	// for (size_t i = 0; i < msg_padded.size(); ++i)
	// {
	// 	//print out the bit sequence of msg string
	// 	cout << bitset<8>(msg_padded.c_str()[i])<<endl;
	// 	cout<<i+1<<endl;
	// }
	cout << endl;

	F_block(msg_padded);

	//call F-block procedure

	//call G-block procedure

	//call H-block procedure

	//call I-block procedure
	//store msg digest
	cout<<"bfgkl";
	return 0;
}
