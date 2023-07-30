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
define i32 @FourWhile(){
label_entry:
  %v0 = alloca i32
  %v1 = alloca i32
  store i32 5, i32* %v1
  %v2 = alloca i32
  %v3 = alloca i32
  store i32 6, i32* %v2
  store i32 7, i32* %v3
  %v4 = alloca i32
  store i32 10, i32* %v4
  br label %label_0
label_ret:
  %v5 = load i32, i32* %v0
  ret i32 %v5
label_0:
  %v6 = load i32, i32* %v1
  %v7 = icmp slt i32 %v6, 20
  br i1 %v7, label %label_1, label %label_2
label_1:
  %v8 = load i32, i32* %v1
  %v9 = add i32 %v8, 3
  store i32 %v9, i32* %v1
  br label %label_3
label_2:
  %v10 = load i32, i32* %v1
  %v11 = load i32, i32* %v2
  %v12 = load i32, i32* %v4
  %v13 = add i32 %v11, %v12
  %v14 = add i32 %v10, %v13
  %v15 = load i32, i32* %v3
  %v16 = add i32 %v14, %v15
  store i32 %v16, i32* %v0
  br label %label_ret
label_3:
  %v17 = load i32, i32* %v2
  %v18 = icmp slt i32 %v17, 10
  br i1 %v18, label %label_4, label %label_5
label_4:
  %v19 = load i32, i32* %v2
  %v20 = add i32 %v19, 1
  store i32 %v20, i32* %v2
  br label %label_6
label_5:
  %v21 = load i32, i32* %v2
  %v22 = sub i32 %v21, 2
  store i32 %v22, i32* %v2
  br label %label_0
label_6:
  %v23 = load i32, i32* %v3
  %v24 = icmp eq i32 %v23, 7
  br i1 %v24, label %label_7, label %label_8
label_7:
  %v25 = load i32, i32* %v3
  %v26 = sub i32 %v25, 1
  store i32 %v26, i32* %v3
  br label %label_9
label_8:
  %v27 = load i32, i32* %v3
  %v28 = add i32 %v27, 1
  store i32 %v28, i32* %v3
  br label %label_3
label_9:
  %v29 = load i32, i32* %v4
  %v30 = icmp slt i32 %v29, 20
  br i1 %v30, label %label_10, label %label_11
label_10:
  %v31 = load i32, i32* %v4
  %v32 = add i32 %v31, 3
  store i32 %v32, i32* %v4
  br label %label_9
label_11:
  %v33 = load i32, i32* %v4
  %v34 = sub i32 %v33, 1
  store i32 %v34, i32* %v4
  br label %label_6
}
define i32 @main(){
label_entry:
  %v0 = alloca i32
  %v1 = call i32 @FourWhile()
  store i32 %v1, i32* %v0
  br label %label_ret
label_ret:
  %v2 = load i32, i32* %v0
  ret i32 %v2
}
