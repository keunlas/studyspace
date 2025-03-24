# 目的: 寻找一组数据的最大值
#
# 变量: 寄存器有以下用途
#     %edi - 保存正在检测的数据项索引
#     %ebx - 保存已经找到的最大数据项
#     %eax - 当前数据项
#
# 内存位置:
#     data_items - 包含数据项, 0 表示数据结束

# 数据段
.data
    data_items: .long 3, 123, 75, 54, 34 ,44, 33, 22, 11, 66, 0

# 代码段
.text
.globl _start

_start:
    movl $0, %edi                       # 从 0 位置开始
    movl data_items(, %edi, 4), %eax    # 加载数据, 比例因子为 4
    movl %eax, %ebx                     # 先默认第一项为最大值

start_loop:
    cmpl $0, %eax                       # 如果数据为 0, 到达末尾
    je loop_exit                        # goto 到退出标签

    incl %edi                           # 索引自增
    movl data_items(, %edi, 4), %eax    # 将下一个数据移动到寄存器
    cmpl %ebx, %eax                     # 比较数值
    jle start_loop                      # 如果 %eax 值小则继续循环
    movl %eax, %ebx                     # 否则记录新的最大值
    jmp start_loop                      # 开始下次循环

loop_exit:
    # 此时 %ebx 已经存放有最大值
    # 并且 %ebx 会作为状态码返回
    # movl $1, %eax
    # int $0x80

    # 现代 64 位更推荐的方法是使用 syscall
    # 可以节省中断的开销
    movl %ebx, %edi                     # exit 调用参数在 %edi
    movl $60, %eax                      # exit 调用号为 60
    syscall

