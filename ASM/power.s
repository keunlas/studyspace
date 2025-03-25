# 目的: 展示函数如何工作
#       本程序将计算
#       3^3 + 5^2 = 27 + 25 = 52

# 数据都在寄存器
# 所以数据段没有内容
.data

# 代码段
.text

.globl _start
_start:
  pushq $3          # 压入第二个参数
  pushq $3          # 压入第一个参数
  call power        # 调用函数
  addq $16, %rsp    # 栈指针向后移动

  pushq %rax        # 结果在 %rax 中
                    # 保存进栈 %rsp

  pushq $2          # 压入第二个参数
  pushq $5          # 压入第一个参数
  call power        # 调用函数
  addq $16, %rsp    # 栈指针向后移动

  popq %rbx         # 结果在 %rax 中
                    # 把之前的结果存入 %rbx

  addq %rax, %rbx   # 两次结果相加, 存入 %rbx

  # exit(result)
  movq %rbx, %rdi   # 把结果作为返回值返回
  movq $60, %rax
  syscall

.type power, @function
power:
  pushq %rbp           # 保存旧的基址指针
  movq %rsp, %rbp      # 将基址指针设置为栈指针

  subq $8, %rsp        # 为本地存储保留空间

  movq 16(%rbp), %rbx  # 读取第一个参数
  movq 24(%rbp), %rcx  # 读取第二个参数

  movq %rbx, -8(%rbp)  # 存储当前结果

power_loop_start:
  cmpq $1, %rcx        # 如果已经是 1 次方, 已获得结果
  je end_power

  movq -8(%rbp), %rax  # 将当前结果移入 rax
  imulq %rbx, %rax     # 用底数乘当前结果
  movq %rax, -8(%rbp)  # 保存当前结果
  decq %rcx            # 指数递减

  jmp power_loop_start # 递减后, 继续进行幂计算

end_power:
  movq -8(%rbp), %rax  # 返回值移入 rax

  movq %rbp, %rsp      # 恢复栈指针
  popq %rbp            # 恢复基址指针
  ret
