       IDENTIFICATION DIVISION.
       PROGRAM-ID. MIFMTD.
      *    0CYYDDDF (CVTDATE, TIME DEC) -> 'YYYY.DDD'
       DATA DIVISION.
       WORKING-STORAGE SECTION.
       01  W-C       PIC 9.
       01  W-REST    PIC 9(5).
       01  W-YY      PIC 99.
       01  W-DDD     PIC 999.
       01  W-YEAR    PIC 9(4).
       LINKAGE SECTION.
       01  L-DATE    PIC S9(7) COMP-3.
       01  L-TEXT.
           05  L-YEAR    PIC 9(4).
           05  L-DOT     PIC X.
           05  L-DDD     PIC 999.
       PROCEDURE DIVISION USING L-DATE L-TEXT.
       MAIN-PARA.
           DIVIDE L-DATE BY 100000 GIVING W-C REMAINDER W-REST.
           DIVIDE W-REST BY 1000 GIVING W-YY REMAINDER W-DDD.
           COMPUTE W-YEAR = 1900 + W-C * 100 + W-YY.
           MOVE W-YEAR TO L-YEAR.
           MOVE '.' TO L-DOT.
           MOVE W-DDD TO L-DDD.
           MOVE 0 TO RETURN-CODE.
           GOBACK.
