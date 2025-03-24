# 工具
CXX := g++
CC := gcc
RM := rm -f

# GLAD 配置
GLAD_SRC := glad.c
GLAD_OBJ := glad.o

# TARGET 配置
TARGET := main.out
TARGET_SRCS := $(wildcard *.cpp)
TARGET_OBJS := $(patsubst %.cpp,%.o,$(TARGET_SRCS))
GL_FLAGS := -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
.PHONY: all clean rebuild

# 编译
all: $(TARGET)

$(TARGET): $(TARGET_OBJS) $(GLAD_OBJ)
	$(CXX) $^ -o $@ $(GL_FLAGS)

$(TARGET_OBJS): $(TARGET_SRCS)
%.o: %.cpp
	$(CXX) -c $< -o $@

# GLAD
$(GLAD_OBJ): $(GLAD_SRC)
	$(CC) -c $^ -o $@

# 清理
clean:
	$(RM) $(TARGET) $(TARGET_OBJS) $(GLAD_OBJ)

# 重建
rebuild: clean all
