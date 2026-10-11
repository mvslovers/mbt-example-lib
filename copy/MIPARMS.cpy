      *    MIPARMS -- the fields a COBOL program passes to mvsinfo:
      *    CALL 'MIJOBN' USING MI-JOBNAME
      *    CALL 'MIFMTD' USING MI-DATE MI-DATE-TEXT
      *    CALL 'MIFMTN' USING MI-NUM MI-NUM-TEXT
       01  MI-JOBNAME     PIC X(8).
       01  MI-DATE        PIC S9(7) COMP-3.
       01  MI-DATE-TEXT   PIC X(8).
       01  MI-NUM         PIC S9(9) COMP.
       01  MI-NUM-TEXT    PIC X(12).
