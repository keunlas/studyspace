# 定义变量
AS = as
LD = ld
OBJS = $(patsubst %.s, %.o, $(wildcard *.s))
TARGETS = $(patsubst %.s, %.out, $(wildcard *.s))
.PHONY: all clean rebuild

# 默认目标
all: $(TARGETS)

# 编译目标
$(TARGETS): $(OBJS)

%.o: %.s
	$(AS) $< -o $@

%.out: %.o
	$(LD) $< -o $@

# 清理目标文件和可执行文件
clean:
	rm -f $(OBJS) $(TARGETS)

# 重新编译
rebuild: clean all
