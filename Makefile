# 디렉토리 경로 설정
SRC_DIR = ./srcs
INC_DIR = ./inc
BUILD_DIR = ./build
TARGET = os_team6_test

# 컴파일러 및 옵션
CC = gcc
CFLAGS = -Wall -I$(INC_DIR)

# 소스 파일 목록
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/cat.c \
       $(SRC_DIR)/clear.c \
       $(SRC_DIR)/tail.c \
       $(SRC_DIR)/utility.c \
       $(SRC_DIR)/stack.c \
       $(SRC_DIR)/user.c \
       $(SRC_DIR)/dir.c \
       $(SRC_DIR)/globals.c

# 오브젝트 파일 목록
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# 전체 빌드
all: $(BUILD_DIR)/$(TARGET)

# 실행 파일 생성
$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -lpthread

# .c -> .o 컴파일 규칙
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 정리
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
