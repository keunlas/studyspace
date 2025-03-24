.data
  sum: .long 0

.text
.globl _start

_start:
  addl $10, sum  # sum += '\n'
  shll $8, sum   # sum << 8
  addl $65, sum  # sum += 'A'
  shll $8, sum   # sum << 8
  addl $66, sum  # sum += 'B'
  shll $8, sum   # sum << 8
  addl $67, sum  # sum += 'C'
  # Now, sum is 0x10656667 equal "CBA\n" in memory.

  # write(1, &sum, 4)
  mov $1, %rdi   # fd
  lea sum, %rsi  # buf
  movq $4, %rdx  # len
  mov $1, %rax   # sys_write
  syscall

  # exit(0)
  mov $0, %rdi   # status
  mov $60, %rax  # sys_exit
  syscall
