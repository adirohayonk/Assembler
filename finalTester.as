;0-number,1-label,2-matrix,3-register

;check array data
emptyCallArr: .data
array: .data 1,2,3,4,5,6,7,8
bigNumbers: .data 123,456,789,1010
arrayWithLetters: .data a,b,c
symbolsArray: .data @,$,%,&,*,-,(,),2)
letterInMiddle: .data 1,2,3,4,a,5
plusMinus: .data 1,-2,-7,8,9,10
missComma: .data 1 2,3 4,5 6,7
manyComma: .data 1,2,,3,,,4,5,,8
commaAtEnd: .data 1,2,3,4,5,
singleNumber: .data 123456789
floatInData: .data 1.2,3.4,5.6,7.8

;check string data
emptyCallStr: .string
hello: .string "hello"
withoutQuotesAtEnd: .string "abcd
withoutQuotesAtStart: .string abcd"
withoutQuotesAtAll: .string bye
weirdSymbolsString: .string "@#$%&*-+()!"'://"

;check matrix data
emptyCallMat: ..mat
emptyMatrix: .mat [2][3]
M1: .mat [2][2] 1,2,3,4
tooLittleElements: .mat [2][2] 1,2,3
tooManyElements: .mat [2][2] 1,2,3,4,5,6
floatInMatrix: .mat [2][2] 1.2,2.3,4,5

;check externalData
regularExtern: .extern A
labelNotLetter: .extern -%;wia
numberLabel: .extern a123b

;weird commands test
noExistCommand: help
symbolsCommand: -$-$@A
wrongLettersCommands1: Mov
wrongLettersCommands2: adD
wrongLettersCommands3: lEa
wrongLettersCommands4: DEC
wrongLettersCommands5: PrN

;test mov command
secondParamWrong1Mov: mov #-1,#1
secondParamWrong2Mov: mov hello,#-6
secondParamWrong3Mov: mov array,#-7
secondParamWrong4Mov: mov M1,#4
emptyCallMov: mov
onlyOneParamMov: mov r2
tooMuchCommasMov: mov r1,,r2
noCommaMov: mov #2 r1

;test add command
secondParamWrong1Add: add #-1,#1
secondParamWrong2Add: add hello,#-6
secondParamWrong3Add: add array,#-7
secondParamWrong4Add: add M1,#4
emptyCallAdd: add
onlyOneParamAdd: add r2
tooMuchCommasAdd: add r1,,r2
noCommaAdd: add #2 r1

;test sub command
secondParamWrong1Sub: sub #-1,#1
secondParamWrong2Sub: sub hello,#-6
secondParamWrong3Sub: sub array,#-7
secondParamWrong4Sub: sub M1,#4
emptyCallSub: sub
onlyOneParamSub: sub r2
tooMuchCommasSub: sub r1,,r2
noCommaSub: sub #2 r1

;test cmp command
secondParamWrong1Cmp: cmp #-1,#
secondParamWrong2Cmp: cmp hello,
secondParamWrong3Cmp: cmp array,#-7
secondParamWrong4Cmp: cmp M1,#4
emptyCallCmp: cmp
onlyOneParamCmp: cmp r2
tooMuchCommasCmp: cmp r1,,r2
noCommaCmp: cmp #2 r1


;test rts command
rtsWithArguments1: rts r1
rtsWithArguments2: rts r1,#-2
