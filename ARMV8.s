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

MD5Hash             :   ADDI X9, XZR, #128// X9 = 0b10000000
                        STURB X9, [X19,[X26]]//@@doubtful, I don't think we can put register in offset field
                        ADD X9, XZR, X26//reinitialize X9 = with &msg[len]
                        ADDI X9, X9, #1//X9 = &msg[len+1]
 
LoopForPadding      :   STURB XZR, [X19, X9]// STURB XZR, [X9, #0]
                        ADDI X9, X9, #1
                        SUBIS XZR, X9, #64
                        B.EQ AddLengthBits
                        B LoopForPadding

AddLengthBits       :   ADDI X9,XZR,#56 //ADDI X9,X19,#56
                        STURH X26 ,[X19, X9]// STURH X26 ,[X9, #0]
                        ADDI X9, XZR, #0//set X9 to zero

                        //can we assume that h[4] is already initialised to abcd[4]
                        ADDI X10, XZR, #0//set X10 to zero i = 0
                        //LSL X13 , X10, #3// i = 8*i
                        //ADD X13, X13 , X22
CopyABCD            :   LDURW X11 ,[X22, X10]//LDUR X11 ,[X13, #0]
                        STURW X11 ,[X20, X10]
                        ADDI X10, X10, #4//ADDI X10, X10, #1
                        SUBIS XZR, X10, #16//SUBIS XZR, X10, #4
                        B.EQ ProcessOuterLoop
                        B CopyABCD

ProcessOuterLoop    :   ADDI X10, XZR, #0 

    ProcessInnerLoop    :   LDUR X11 [X23, X9]
                            MUL X11, X11, X10
                            LDUR X12 [X24, X10]
                            ADD X11, X11, X12
                            AND X11, X11, #15
                            ADDI X12, XZR, X9
                            SUBS XZR, XZR, X12
                            B.EQ IfpEqual0
                            SUBIS X12, X12, #1
                            B.EQ IfpEqual1
                            SUBIS X12, X12, #1
                            B.EQ IfpEqual2
                            SUBIS X12, X12, #1
                            B.EQ IfpEqual3
        IfpEqual0           :
        IfpEqual1           :
        IfpEqual2           :
        IfpEqual3           :

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




