@a = global i32 0
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
define i32 @func(i32 %arg_0){
label_entry:
  %v0 = alloca i32
  store i32 %arg_0, i32* %v0
  %v1 = alloca i32
  %v2 = load i32, i32* %v0
  %v3 = sub i32 %v2, 1
  store i32 %v3, i32* %v0
  %v4 = load i32, i32* %v0
  store i32 %v4, i32* %v1
  br label %label_ret
label_ret:
  %v5 = load i32, i32* %v1
  ret i32 %v5
}
define i32 @main(){
label_entry:
  %v0 = alloca i32
  %v1 = alloca i32
  store i32 10, i32* @a
  %v2 = load i32, i32* @a
  %v3 = call i32 @func(i32 %v2)
  store i32 %v3, i32* %v1
  %v4 = load i32, i32* %v1
  store i32 %v4, i32* %v0
  br label %label_ret
label_ret:
  %v5 = load i32, i32* %v0
  ret i32 %v5
}
