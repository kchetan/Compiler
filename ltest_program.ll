; ModuleID = 'main'

@arr = global [1000 x i32] zeroinitializer
@0 = private unnamed_addr constant [10 x i8] c"num = %d \00"
@1 = private unnamed_addr constant [4 x i8] c"%d \00"

define i32 @main() {
entry:
  %i50 = alloca i32
  %x = alloca i32
  %j18 = alloca i32
  %i12 = alloca i32
  %i4 = alloca i32
  %num = alloca i32
  %j = alloca i32
  %i = alloca i32
  store i32 0, i32* %i
  store i32 0, i32* %j
  store i32 0, i32* %num
  %num1 = load i32* %num
  store i32 7, i32* %num
  %num2 = load i32* %num
  %0 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([10 x i8]* @0, i32 0, i32 0), i32 %num2)
  %num3 = load i32* %num
  store i32 0, i32* %i4
  %i5 = load i32* %i4
  %lesstmp = icmp slt i32 %i5, %num3
  br i1 %lesstmp, label %forloop, label %afterforloop

forloop:                                          ; preds = %forloop, %entry
  %i6 = load i32* %i4
  %mulInstruct = mul i32 10, %i6
  %num7 = load i32* %num
  %remInstruct = urem i32 %mulInstruct, %num7
  %i8 = load i32* %i4
  %gep = getelementptr inbounds [1000 x i32]* @arr, i32 0, i32 %i8
  %arr = load i32* %gep
  store i32 %remInstruct, i32* %gep
  %i9 = load i32* %i4
  %addone = add i32 %i9, 1
  store i32 %addone, i32* %i4
  %lesstmp10 = icmp slt i32 %addone, %num3
  br i1 %lesstmp10, label %forloop, label %afterforloop

afterforloop:                                     ; preds = %forloop, %entry
  %num11 = load i32* %num
  store i32 0, i32* %i12
  %i15 = load i32* %i12
  %lesstmp16 = icmp slt i32 %i15, %num11
  br i1 %lesstmp16, label %forloop13, label %afterforloop14

forloop13:                                        ; preds = %afterforloop20, %afterforloop
  %i17 = load i32* %i12
  store i32 0, i32* %j18
  %j21 = load i32* %j18
  %lesstmp22 = icmp slt i32 %j21, %i17
  br i1 %lesstmp22, label %forloop19, label %afterforloop20

afterforloop14:                                   ; preds = %afterforloop20, %afterforloop
  %num49 = load i32* %num
  store i32 0, i32* %i50
  %i53 = load i32* %i50
  %lesstmp54 = icmp slt i32 %i53, %num49
  br i1 %lesstmp54, label %forloop51, label %afterforloop52

forloop19:                                        ; preds = %ifcont, %forloop13
  %i23 = load i32* %i12
  %gep24 = getelementptr inbounds [1000 x i32]* @arr, i32 0, i32 %i23
  %arr25 = load i32* %gep24
  %j26 = load i32* %j18
  %gep27 = getelementptr inbounds [1000 x i32]* @arr, i32 0, i32 %j26
  %arr28 = load i32* %gep27
  %cmpgtInst = icmp ugt i32 %arr25, %arr28
  %ifcond = icmp eq i1 %cmpgtInst, true
  br i1 %ifcond, label %then, label %else

afterforloop20:                                   ; preds = %ifcont, %forloop13
  %i46 = load i32* %i12
  %addone47 = add i32 %i46, 1
  store i32 %addone47, i32* %i12
  %lesstmp48 = icmp slt i32 %addone47, %num11
  br i1 %lesstmp48, label %forloop13, label %afterforloop14

then:                                             ; preds = %forloop19
  store i32 0, i32* %x
  %i29 = load i32* %i12
  %gep30 = getelementptr inbounds [1000 x i32]* @arr, i32 0, i32 %i29
  %arr31 = load i32* %gep30
  %x32 = load i32* %x
  store i32 %arr31, i32* %x
  %j33 = load i32* %j18
  %gep34 = getelementptr inbounds [1000 x i32]* @arr, i32 0, i32 %j33
  %arr35 = load i32* %gep34
  %i36 = load i32* %i12
  %gep37 = getelementptr inbounds [1000 x i32]* @arr, i32 0, i32 %i36
  %arr38 = load i32* %gep37
  store i32 %arr35, i32* %gep37
  %x39 = load i32* %x
  %j40 = load i32* %j18
  %gep41 = getelementptr inbounds [1000 x i32]* @arr, i32 0, i32 %j40
  %arr42 = load i32* %gep41
  store i32 %x39, i32* %gep41
  br label %ifcont

else:                                             ; preds = %forloop19
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %j43 = load i32* %j18
  %addone44 = add i32 %j43, 1
  store i32 %addone44, i32* %j18
  %lesstmp45 = icmp slt i32 %addone44, %i17
  br i1 %lesstmp45, label %forloop19, label %afterforloop20

forloop51:                                        ; preds = %forloop51, %afterforloop14
  %i55 = load i32* %i50
  %gep56 = getelementptr inbounds [1000 x i32]* @arr, i32 0, i32 %i55
  %arr57 = load i32* %gep56
  %1 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @1, i32 0, i32 0), i32 %arr57)
  %i58 = load i32* %i50
  %addone59 = add i32 %i58, 1
  store i32 %addone59, i32* %i50
  %lesstmp60 = icmp slt i32 %addone59, %num49
  br i1 %lesstmp60, label %forloop51, label %afterforloop52

afterforloop52:                                   ; preds = %forloop51, %afterforloop14
  ret i32 1
}

declare i32 @printf(i8*, ...)
