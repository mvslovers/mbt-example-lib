*        MIJOBN -- the job name, from PSATOLD -> TCBTIO -> TIOCNJOB.
*        One argument: the address of an 8-byte field.  Pointers only,
*        the high-order bit dropped, so C, COBOL and assembler call it
*        alike.  RC 0.
MIJOBN   CSECT
         STM   14,12,12(13)
         L     2,0(,1)            the 8-byte field
         LA    2,0(,2)            drop the VL bit (24-bit address)
         L     3,X'21C'(0,0)      PSATOLD: our TCB
         L     3,12(,3)           TCBTIO: the TIOT
         MVC   0(8,2),0(3)        TIOCNJOB
         LM    14,12,12(13)
         SR    15,15
         BR    14
         END
