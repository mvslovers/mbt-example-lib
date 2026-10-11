*        MITIME -- TIME DEC: HHMMSSth and 00YYDDDF, packed decimal.
*        Two arguments: the addresses of two fullwords.  Pointers only,
*        the high-order bit dropped, so C, COBOL and assembler call it
*        alike.  RC 0.
MITIME   CSECT
         STM   14,12,12(13)
         LR    12,15
         USING MITIME,12
         LR    2,1                keep the parameter list
         TIME  DEC                R0 time, R1 date
         L     3,0(,2)
         LA    3,0(,3)
         ST    0,0(,3)
         L     3,4(,2)
         LA    3,0(,3)
         ST    1,0(,3)
         LM    14,12,12(13)
         SR    15,15
         BR    14
         LTORG
         END
