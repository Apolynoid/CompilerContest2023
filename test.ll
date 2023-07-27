declare  i32 @getint()
declare  i32 @getch()
declare  float @getfloat()
declare  i32 @getarray(i32*)
declare  i32 @getfarray(float*)
declare  void @putint(i32)
declare  void @putch(i32)
declare  void @putfloat(float)
declare  void @putarray(i32, i32*)
declare  void @putfarray(i32, float*)
declare  void @_sysy_starttime(i32)
declare  void @_sysy_stoptime(i32)
declare  void @__aeabi_memcpy4(i32*, i32*, i32)
declare  void @__aeabi_memclr4(i32*, i32)
declare  void @__aeabi_memset4(i32*, i32, i32)
declare  void @llvm.memset.p0.i32(i32*, i8, i32, i1)
define i32 @deepWhileBr(i32 %arg_0, i32 %arg_1){
label_entry:
  %v0 = alloca i32
  store i32 %arg_0, i32* %v0
  %v1 = alloca i32
  store i32 %arg_1, i32* %v1
  %v2 = alloca i32
  %v3 = alloca i32
  %v4 = load i32, i32* %v0
  %v5 = load i32, i32* %v1
  %v6 = add i32 %v4, %v5
  store i32 %v6, i32* %v3
  br label %label_0
label_ret:
  %v7 = load i32, i32* %v2
  ret i32 %v7
label_0:
  %v8 = load i32, i32* %v3
  %v9 = icmp slt i32 %v8, 75
  br i1 %v9, label %label_1, label %label_2
label_1:
  %v10 = alloca i32
  store i32 42, i32* %v10
  %v11 = load i32, i32* %v3
  %v12 = icmp slt i32 %v11, 100
  br i1 %v12, label %label_3, label %label_4
label_2:
  %v13 = load i32, i32* %v3
  store i32 %v13, i32* %v2
  br label %label_ret
label_3:
  %v14 = load i32, i32* %v3
  %v15 = load i32, i32* %v10
  %v16 = add i32 %v14, %v15
  store i32 %v16, i32* %v3
  %v17 = load i32, i32* %v3
  %v18 = icmp sgt i32 %v17, 99
  br i1 %v18, label %label_5, label %label_6
label_4:
  br label %label_0
label_5:
  %v19 = alloca i32
  %v20 = load i32, i32* %v10
  %v21 = mul i32 %v20, 2
  store i32 %v21, i32* %v19
  %v22 = icmp eq i32 1, 1
  br i1 %v22, label %label_7, label %label_8
label_6:
  br label %label_4
label_7:
  %v23 = load i32, i32* %v19
  %v24 = mul i32 %v23, 2
  store i32 %v24, i32* %v3
  br label %label_8
label_8:
  br label %label_6
}
define i32 @main(){
label_entry:
  %v0 = alloca i32
  %v1 = alloca i32
  store i32 2, i32* %v1
  %v2 = load i32, i32* %v1
  %v3 = load i32, i32* %v1
  %v4 = call i32 @deepWhileBr(i32 %v2, i32 %v3)
  store i32 %v4, i32* %v0
  br label %label_ret
label_ret:
  %v5 = load i32, i32* %v0
  ret i32 %v5
}
