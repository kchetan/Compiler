; ModuleID = 'main'

@y = external global i32
@x = external global i32
@arr = external global [4 x i32]*
@0 = private unnamed_addr constant [3 x i8] c"%d\00"
@1 = private unnamed_addr constant [11 x i8] c"yolo %d %d\00"

define i32 @sub(i32 %a, i32 %b) {
entry:
  %r19 = alloca i1
  %r = alloca i1
  %q = alloca i32
  %p = alloca i32
  %i = alloca i32
  %a1 = alloca i32
  store i32 %a, i32* %a1
  %b2 = alloca i32
  store i32 %b, i32* %b2
  store i32 1, i32* %i
  %i3 = load i32* %i
  %lesstmp = icmp slt i32 %i3, 3
  br i1 %lesstmp, label %loop, label %afterloop

loop:                                             ; preds = %ifcont28, %then, %entry
  %a4 = load i32* %a1
  %b5 = load i32* %b2
  %cmpgtInst = icmp ugt i32 %a4, %b5
  %ifcond = icmp eq i1 %cmpgtInst, true
  br i1 %ifcond, label %then, label %else18

afterloop:                                        ; preds = %ifcont28, %then, %entry
  %a32 = getelementptr inbounds i32* %a1
  %0 = call i32 (i8*, i32*, ...)* @scanf(i8* getelementptr inbounds ([3 x i8]* @0, i32 0, i32 0), i32* %a32)
  %a33 = load i32* %a1
  %b34 = load i32* %b2
  %1 = call i32 ( ...)* @printf(i8* getelementptr inbounds ([11 x i8]* @1, i32 0, i32 0), i32 %a33, i32 %b34)
  ret i32 0

then:                                             ; preds = %loop
  store i32 0, i32* %p
  store i32 0, i32* %q
  store i1 false, i1* %r
  %q6 = load i32* %q
  %p7 = load i32* %p
  %addInstruct = add i32 %q6, %p7
  %p8 = load i32* %p
  store i32 %addInstruct, i32* %p
  %i9 = load i32* %i
  %nextvar = add i32 %i9, 1
  store i32 %nextvar, i32* %i
  %lesstmp10 = icmp slt i32 %nextvar, 3
  br i1 %lesstmp10, label %loop, label %afterloop
  %b11 = load i32* %b2
  %a12 = load i32* %a1
  %cmpgtInst13 = icmp ugt i32 %b11, %a12
  %ifcond14 = icmp eq i1 %cmpgtInst13, true
  br i1 %ifcond14, label %then15, label %else

then15:                                           ; preds = %then
  %b16 = load i32* %b2
  %a17 = load i32* %a1
  store i32 %b16, i32* %a1
  br label %ifcont

else:                                             ; preds = %then
  br label %ifcont

ifcont:                                           ; preds = %else, %then15
  br label %ifcont20

else18:                                           ; preds = %loop
  store i1 false, i1* %r19
  br label %ifcont20

ifcont20:                                         ; preds = %else18, %ifcont
  %b21 = load i32* %b2
  %a22 = load i32* %a1
  %cmpisEqualInst = icmp eq i32 %b21, %a22
  %ifcond23 = icmp eq i1 %cmpisEqualInst, true
  br i1 %ifcond23, label %then24, label %else27

then24:                                           ; preds = %ifcont20
  %b25 = load i32* %b2
  %a26 = load i32* %a1
  store i32 %b25, i32* %a1
  br label %ifcont28

else27:                                           ; preds = %ifcont20
  br label %ifcont28

ifcont28:                                         ; preds = %else27, %then24
  %i29 = load i32* %i
  %nextvar30 = add i32 %i29, 1
  store i32 %nextvar30, i32* %i
  %lesstmp31 = icmp slt i32 %nextvar30, 3
  br i1 %lesstmp31, label %loop, label %afterloop
}

declare i32 @scanf(i8*, i32*, ...)

declare i32 @printf(i8*, i32, i32, ...)

define i32 @add(i32 %a) {
entry:
  %flag = alloca i1
  %a1 = alloca i32
  store i32 %a, i32* %a1
  store i1 false, i1* %flag
  %flag2 = load i1* %flag
  store i1 false, i1* %flag
  %callfunction = call i32 @sub(i32 2, i32 3)
  ret i32 %callfunction
}

define i32 @main() {
entry:
  %callfunction = call i32 @sub(i32 2, i32 4)
  ret i32 %callfunction
}
