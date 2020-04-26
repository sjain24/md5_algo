/*  
    X19: Contains the base address of the message, later contains the padded message 
    X20: Contains the base address of abcd[4]
    X21: Contains the base address of K[64]
    X22: Contains the base address of h[4]
    X23: Contains the base address of M[4]
    X24: Contains the base address of O[4]
    X25: Contains the base address of rot[4][4] or rot[16]
    X26: Contains the length of the message in bytes
*/
@ X19 points to message array which is of length 64 i.e X19 = &msg[0]
@ each msg[i] is of length 1 byte 

MD5Hash             :   ADDI X9, XZR, #128
                        STRB X9, [X19,X26]
                        ADD X9, XZR, X26
                        ADDI X9, X9, #1
 
LoopForPadding      :   STRB XZR, [X19, X9]
                        ADDI X9, X9, #1
                        SUBIS XZR, X9, #64
                        B.EQ AddLengthBits
                        B LoopForPadding

AddLengthBits       :   ADDI X9,XZR,#56
                        STRH X26 ,[X19, X9]
                        
                        ADDI X10, XZR, #0
CopyABCD            :   LDRSW X11 ,[X22, X10]
                        STRSW X11 ,[X20, X10]
                        ADDI X10, X10, #4
                        SUBIS XZR, X10, #16
                        B.EQ ProcessOuterLoop
                        B CopyABCD

                        ADD X9, XZR, XZR// p = 0
ProcessOuterLoop    :   ADD X10, XZR, XZR //q = 0

ProcessInnerLoop    :   LDR X11 [X23, X9]//X11 = M[p]
                        MUL X11, X11, X10//X11 = q*M[p]
                        LDR X12 [X24, X10]//X12 = O[q]
                        ADD X11, X11, X12//X11 = q*M[p]+O[p]
                        AND X11, X11, #15//X11 = (q*M[p]+O[p])%16
                        LDRSW X14, [X20, #0] //X14 = abcd[0]
                        LDRSW X15, [X20, #4] //X15 = abcd[1]
                        LDRSW X16, [X20, #8] //X16 = abcd[2]
                        LDRSW X17, [X20, #16]//X17 = abcd[3]
                        ADDI X12, XZR, X9//X12 = p
                        SUBS XZR, XZR, X12//check if p == 0
                        B.EQ IfpEqual0
                        SUBIS X12, X12, #1
                        B.EQ IfpEqual1
                        SUBIS X12, X12, #1
                        B.EQ IfpEqual2
                        SUBIS X12, X12, #1
                        B.EQ IfpEqual3
EndofFunct:             LSL X13, X9, #4//X13 = 16*p
                        ADD X13, X13, X10//X13 = 16*p+q
                        LDR X13, [X21 , X13]//X13 = K[16*p+q]
                        //compute word[g]
                        LDR X17, [X26 , X11] //X1 = word[g]
                        LDR X14, [X20, #0] //X14 = abcd[0]
                        ADD X17,X17,X13 
                        ADD X17,X17,X14
                        ADD X17,X17,X18 // first parameter for rol function
                        //X1 is 2nd parameter to rol function
EndOfFComputation   :   ADDI X10, X10, #1
                        SUBIS XZR, X10, #16
                        B.EQ EndOfInnerLoop
                        B ProcessInnerLoop

EndOfInnerLoop      :   ADDI X9, X9, #1
                        SUBIS XZR, X9, #4
                        B.EQ EndOfOuterLoop
                        B ProcessOuterLoop

EndOfOuterLoop      :  

EndOfFunctionMD5Hash    

//X18 will store result of func(abcd) 
//Assume X0 = 0b0000_0000_0000_0000_1111_1111_1111_1111
//X1 will get result of rot
IfpEqual0           :   AND X18,X14,X15
                        EOR X14,X14,X0//not operation 
                        AND X14,X14,X16
                        ORR X18,X18,X14

                        AND X14,X10,#3 //X14 = q%4
                        ADDI X14,X14,#0
                        LDR X1,[X25,x14] //rot[0][q%4]
                        
                        B EndofFunct

IfpEqual1           :   AND X18,X14,X16
                        EOR X17,X17,X0//not operation 
                        AND X17,X17,X15
                        ORR X18,X18,X17

                        AND X14,X10,#3 //X14 = q%4
                        ADDI X14,X14,#4
                        LDR X1,[X25,x14] //rot[1][q%4]
                        B EndofFunct

IfpEqual2           :   AND X18,X15,X16
                        EOR X18,X18,X17//xor operation 

                        AND X14,X10,#3 //X14 = q%4
                        ADDI X14,X14,#8
                        LDR X1,[X25,x14] //rot[2][q%4]
                        B EndofFunct

IfpEqual3           :   EOR X17,X17,X0//not operation 
                        ORR X18,X15,X17
                        EOR X18,X18,X16

                        AND X14,X10,#3 //X14 = q%4
                        ADDI X14,X14,#12
                        LDR X1,[X25,x14] //rot[3][q%4]
                        B EndofFunct


