# Example directory structure: ディレクトリ構成例
#
# root/
#   |
#   + main.cpp (your code)
#   |
#   + Makefile (your makefile): This file
#   |
#   + sstd/
#       |
#       + sstd.hpp (head file that you need to include)
#       |
#       + Makefile (Makefile that you need to '$ make')
#       |
#       + make_temp/
#       |   |
#       |   + src/
#       |      |
#       |      + *.d
#       |      |
#       |      + *.o (object files that you need to link "./sstd/make_temp/*.o")
#       |
#       + src/
#           |
#           + *.cpp
#           |
#           + *.hpp
#           |
#           + *.h

# .o: Objects file
# .d: Depends file

#============================================================
# Please set each item: 各項目を設定してください

# Source files
SRCS = ./main.cpp

# Name of generate file: 生成ファイル名
TARGET = exe

# remove files
RMs = *.stackdump tmpDir

# Options: コンパイルオプション
CFLAGS  = -L./sstd/lib -I./sstd/include -lsstd # sstd
#CFLAGS += -L./googletest-master/build/lib -I./googletest-master/googletest/include -lgtest -pthread # google test
CFLAGS += -std=c++11 # CFLAGS += -std=gnu++0x
CFLAGS += -fopenmp -fpermissive # OpenMP
CFLAGS += -Wall
CFLAGS += -O3

# remove file name
RMFLIES = ''

#============================================================

BACKUP_DIR   = ./backup
ALL_FILES    = $(wildcard ./*)
TMP_DIRS     = $(wildcard ./tmp_*)
LIBS_DIRS    = ./googletest-master
BACKUP_FILES = $(filter-out ./$(TARGET) $(TMP_DIRS) $(BACKUP_DIR) $(LIBS_DIRS), $(ALL_FILES))
TIME_STAMP   = `date +%Y_%m%d_%H%M`


# when you need to check the change of files in lib, you need to change file name to a not-existing name like "FORCE_XXX".
LIB_SSTD = FORCE_SSTD
#LIB_SSTD = ./sstd/lib/libsstd.a


$(TARGET): $(LIB_SSTD) $(SRCS)
	@echo "\n============================================================\n"
	@echo "SRCS: \n$(SRCS)\n"
	@echo "CFLAGS: \n$(CFLAGS)"
	@echo "\n============================================================\n"
	$(CXX) -o $(TARGET) $(SRCS) $(CFLAGS)
	@echo ""


$(LIB_SSTD):
	@(cd ./sstd; make -j)


.PHONY: all
all:
	@(make clean)
	@(make -j)


patch            := *.stackdump
patch_txt_exists := $(shell find -name $(patch))
.PHONY: clean
clean:
	-rm -rf $(TARGET)
	@(cd ./sstd; make clean)
	-rm -rf $(RMs)
	@(find . -name "__pycache__" -type d | xargs rm -rf)
	$(if $(patch_txt_exists) ,$(rm *.stackdump))
	-rm -rf $(RMFLIES)


.PHONY: steps
steps: $(SRCS)
	@(cd ./sstd; make steps)
	@echo ""
	@echo "$^" | xargs wc -l


.PHONY: zip
zip:
	@mkdir -p $(BACKUP_DIR)
	zip -r $(BACKUP_DIR)/${TIME_STAMP}$(m).zip $(BACKUP_FILES)
.PHONY: backup
backup:
	@(make clean)
	@(make zip)
	@(make)
# when you need comments for backup, just type
# $ make backup m=_comment_will_be_inserted_after_the_date


