LOAD 0
STORE prog4
READ prog5
LOAD 0
STORE id2
test If
READ T1
SUB id2
BRNEG DONE
test <-
WRITE id2
DONE: NOOP
WRITE prog4
STOP
prog4 0
prog5 0
id2 0
T1 0
