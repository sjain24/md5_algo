#include<bits/stdc++.h>
using namespace std;

//function to convert binary sequence to string
string BinarytoString(string bit_stream){
	stringstream sstream(bit_stream);
	string output;
	while (sstream.good())
	{
		bitset<8> bits;
		sstream >> bits;
		char c = char(bits.to_ulong());
		output += c;
	}

	cout << output;
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
	cout<<endl;

	int len = msg.size();//calculate length of message string
	int len_bits = len*8;//length in bits (1 char = 1 byte = 8 bits)

	//calculate no of bits to be padded at the end
	int len_pad = 512 - 64 - len_bits;
	
	string pad_string_bit_seq = "1";
	for(int i = 0 ; i < len_pad; i++){
		pad_string_bit_seq += "0";
	}

	//convert string binary seqeunce to string
	string pad_string = BinarytoString(pad_string_bit_seq);
	string msg_padded = msg + pad_string;//append the padded character sequence at the end of msg

	cout<<"padded msg string is :";
	cout<<msg_padded<<endl;


	//3. add length bits////////////



	//call F-block procedure

	//call G-block procedure

	//call H-block procedure

	//call I-block procedure

	//store msg digest
	return 0;
}