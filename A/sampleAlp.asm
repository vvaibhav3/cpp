
// case - DS , DC , forward ref. & multiple LTORG  
- START - 300
- MOVER AREG A
L1 ADD BREG B
- MOVER CREG ='5'
- LTORG - -
- MOVEM DREG ='7'
- LTORG - -
A DC - 100
B DS - 2
- END - - 

// case - error of register
- START - 300
- MOVER AREZ A
L1 ADD BREG B
- MOVER CREG ='5'
- LTORG - -
- MOVEM DREG ='7'
- LTORG - -
A DC - 100
B DS - 2
- END - - 

//case - double def
- START - 300
A DC - 200
- MOVER AREG A
L1 ADD BREG B
- MOVER CREG ='5'
- LTORG - -
- MOVEM DREG ='7'
- LTORG - -
A DC - 100
B DS - 2
- END - - 

// case - EQU
- START - 300
- MOVER AREG A
L1 MOVER BREG B
- MOVER CREG ='5'
- LTORG - -
X EQU - L1
A DC - 100
B DS - 2
- END - - 

// case - allocating memory to litral after END
- START - 300
- MOVER AREG A
L1 ADD BREG B
- MOVER CREG ='5'
- LTORG - -
- MOVEM DREG ='7'
A DC - 100
B DS - 2
- END - - 

// case - check error of symbol
- START - 300
- MOVER AREG A
L1 MOVER BREG B
- MOVER CREG ='5'
- LTORG - -
- MOVEM DREG D
A DC - 100
B DS - 2
C DC - 02
- END - - 

//case - mnemonic error
- START - 300
- MOVE AREG A
L1 MOVER BREG B
- MOVER CREG ='5'
- LTORG - -
- MOVEM DREG D
A DC - 100
B DS - 2
C DC - 02
- END - -