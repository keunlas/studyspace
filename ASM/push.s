# 目的: 展示函数如何工作
#       本程序将计算
#       2^3 + 5^2 = 8 + 25 = 33

# 数据都在寄存器
# 所以数据段没有内容
.data

# 代码段
.text

.globl _start
_start:
  pushq $3

  # exit(result)
  movq (%rsp), %rdi   # 把结果作为返回值返回
  movq $60, %rax
  syscall
