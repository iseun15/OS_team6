#필드 자동화 위한 파일

# 디렉토리 설정
SRC_DIR = ./srcs
INC_DIR = ./inc
BUILD_DIR = ./build
RES_DIR = ./resources

# 실행파일 이름
TARGET = os_team6

# 추후 삭제 / 없어도 되는데 오류 보기 위해서 넣어둠
CC = gcc
CFLAGS = -Wall -I$(INC_DIR)

# 소스 및 오브젝트 파일 리스트 자동 추출
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# 기본 빌드 명령
$(TARGET): $(OBJS)|$(RES_DIR)
	$(CC) -o $@ $^ -lpthread

# .c 파일 =>  .o 파일
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# resource 생성
$(RES_DIR):
	mkdir -p $(RES_DIR)


clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean   #만약 clean 파일 존재하면, 파일이 아니라 명령어로 작동할 수 있게 함