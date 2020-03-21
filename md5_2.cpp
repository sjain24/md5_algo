/*****Please include following header files*****/
// string
/***********************************************/

/*****Please use following namespaces*****/
// std
/*****************************************/

#include <bits/stdc++.h>
using namespace std;

typedef union uwb {//only the first member of a union can be initialized
    unsigned w;//32 bits
    unsigned char b[4];//memory is shared between all members
    //b is the character representation of w
} MD5union;

typedef unsigned DigestArray[4];//DigestArray is another name for the array unsigned[4]

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

static unsigned *calctable(unsigned *k)
{
    double s, pwr;
    int i;

    pwr = pow(2.0, 32);
    for (i = 0; i < 64; i++)
    {
        s = fabs(sin(1.0 + i));
        k[i] = (unsigned)(s * pwr);
    }
    return k;
}

static unsigned rol(unsigned r, short N)
{
    unsigned mask1 = (1 << N) - 1;
    return ((r >> (32 - N)) & mask1) | ((r << N) & ~mask1);
}

static unsigned *MD5Hash(string msg)
{
    int mlen = msg.length();
    static DigestArray h0 = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};//intial values
    static DgstFctn ff[] = {&func0, &func1, &func2, &func3};
    static short M[] = {1, 5, 3, 7};
    static short O[] = {0, 1, 5, 0};
    static short rot0[] = {7, 12, 17, 22};
    static short rot1[] = {5, 9, 14, 20};
    static short rot2[] = {4, 11, 16, 23};
    static short rot3[] = {6, 10, 15, 21};
    static short *rots[] = {rot0, rot1, rot2, rot3};
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
        char b[64];
    } mm;
    int os = 0;
    int grp, grps, q, p;
    unsigned char *msg2;

    if (k == NULL)
    //if k is not already calculated then call function
        k = calctable(kspace);//return k which is array of all 64 k values

    for (q = 0; q < 4; q++){
        //intialize h values
        h[q] = h0[q];
    }
        grps = 1 + (mlen + 8) / 64;//for our case it is 1
        msg2 = (unsigned char *)malloc(64 * grps);//allocate 64bytes or 512bits of memory to msg2
        memcpy(msg2, msg.c_str(), mlen);//copy msg to msg2
        //c_str() returns a pointer to an array that contains a null-terminated sequence of characters- 
        //representing the current value of the msg object
        //each msg2[i] each of size of 8bits/1byte
        //msg2 = "hello"
        msg2[mlen] = (unsigned char)0x80;
        //append 10000000 bits at the end as a character
        q = mlen + 1;//6
        while (q < 64 * grps)
        {
            msg2[q] = 0;//add  00000000 bits
            q++;
        }    
        //padding done
        //now add length bits
        MD5union u;
        u.w = 8 * mlen;//40 in decimal for "hello"
        //u.w is of size 4 bytes/ 32 bits
        // 40 == 00101000
        q -= 8;//q = 56
        memcpy(msg2 + q, &u.w, 4);

    for (grp = 0; grp < grps; grp++)
    {
        memcpy(mm.b, msg2 + os, 64);

        //copy complete msg2 to mm.b
        //mm.b is the 512bit memory block that will be working with
        for (q = 0; q < 4; q++)
            //set abcd for this turn
            abcd[q] = h[q];
        for (p = 0; p < 4; p++)
        {
            fctn = ff[p];
            rotn = rots[p];
            m = M[p];
            o = O[p];
            for (q = 0; q < 16; q++)
            {
                //perform 16 turns of operations
                g = (m * q + o) % 16;
                f = abcd[1] + rol(abcd[0] + fctn(abcd) + k[q + 16 * p] + mm.w[g], rotn[q % 4]);

                abcd[0] = abcd[3];
                abcd[3] = abcd[2];
                abcd[2] = abcd[1];
                abcd[1] = f;
            }
        }
        for (p = 0; p < 4; p++)
            h[p] += abcd[p];
        os += 64;
    }

    return h;
}

static string GetMD5String(string msg)
{
    string str;
    int j, k;
    unsigned *d = MD5Hash(msg);
    MD5union u;
    for (j = 0; j < 4; j++)
    {
        u.w = d[j];
        char s[9];
        sprintf(s, "%02x%02x%02x%02x", u.b[0], u.b[1], u.b[2], u.b[3]);
        str += s;
    }

    return str;
}

int main(){
    string md5;
    string msg = "hello";
    md5 = GetMD5String(msg);
    cout<<md5<<endl;
    return 0;
}
