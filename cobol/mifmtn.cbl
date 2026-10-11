       IDENTIFICATION DIVISION.
       PROGRAM-ID. MIFMTN.
      *    a binary fullword -> 'ZZZ,ZZZ,ZZ9-', the edited picture
       DATA DIVISION.
       LINKAGE SECTION.
       01  L-NUM     PIC S9(9) COMP.
       01  L-TEXT    PIC ZZZ,ZZZ,ZZ9-.
       PROCEDURE DIVISION USING L-NUM L-TEXT.
       MAIN-PARA.
           MOVE L-NUM TO L-TEXT.
           MOVE 0 TO RETURN-CODE.
           GOBACK.
