#
#	样板Makefile文件,集体项目根据实际情况进行简单修改即可
#	Author : lzy
.PHONY:all clean
#当前目录
MODULE_NAME := $(notdir $(shell pwd))
BUILD		:= LIB

ifeq ("$(ROOT_DIR)","")
	$(error "Do not set the project directory, you should run 'source toos/setev.sh' in the project root directory")
else
include $(ROOT_DIR)/tools/Makefile.rule
endif
