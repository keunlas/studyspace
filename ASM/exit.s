# 目的: 该程序程序启动后直接退出, 并返回一个状态码

.text
.globl _start

_start:
  # movl $1, %eax
  # movl $88, %ebx
  # int $0x80

  # 现代 64 位更推荐的方法是使用 syscall
  # 可以节省中断的开销
  movl $60, %eax
  movl $88, %edi
  syscall
