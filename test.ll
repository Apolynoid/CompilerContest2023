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
define i32 @ifElseIf(){
label_entry:
  %v0 = alloca i32
  %v1 = alloca i32
  store i32 5, i32* %v1
  %v2 = alloca i32
  store i32 10, i32* %v2
  %v3 = load i32, i32* %v1
  %v4 = icmp eq i32 %v3, 6
  br i1 %v4, label %label_0, label %label_3
label_ret:
  %v5 = load i32, i32* %v0
  ret i32 %v5
label_0:
  %v6 = load i32, i32* %v1
  store i32 %v6, i32* %v0
  br label %label_ret
label_1:
  %v7 = load i32, i32* %v2
  %v8 = icmp eq i32 %v7, 10
  br i1 %v8, label %label_7, label %label_5
label_2:
  %v9 = load i32, i32* %v1
  store i32 %v9, i32* %v0
  br label %label_ret
label_3:
  %v10 = load i32, i32* %v2
  %v11 = icmp eq i32 %v10, 11
  br i1 %v11, label %label_0, label %label_1
label_4:
  store i32 25, i32* %v1
  br label %label_6
label_5:
  %v12 = load i32, i32* %v2
  %v13 = icmp eq i32 %v12, 10
  br i1 %v13, label %label_11, label %label_9
label_6:
  br label %label_2
label_7:
  %v14 = load i32, i32* %v1
  %v15 = icmp eq i32 %v14, 1
  br i1 %v15, label %label_4, label %label_5
label_8:
  %v16 = load i32, i32* %v1
  %v17 = add i32 %v16, 15
  store i32 %v17, i32* %v1
  br label %label_10
label_9:
  %v18 = load i32, i32* %v1
  %v19 = sub i32 0, %v18
  store i32 %v19, i32* %v1
  br label %label_10
label_10:
  br label %label_6
label_11:
  %v20 = load i32, i32* %v1
  %v21 = sub i32 0, 5
  %v22 = icmp eq i32 %v20, %v21
  br i1 %v22, label %label_8, label %label_9
}
define i32 @main(){
label_entry:
  %v0 = alloca i32
  %v1 = call i32 @ifElseIf()
  call void @putint(i32 %v1)
  store i32 0, i32* %v0
  br label %label_ret
label_ret:
  %v2 = load i32, i32* %v0
  ret i32 %v2
}
