LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := tests
LOCAL_SRC_FILES:= \
	src/bundle.c \
	src/debug.c \
	src/json-format.c \
	src/json-test.c \
	src/text-utils.c \
	src/uuid.c \
    src/lava-wrapper.c
LOCAL_MODULE := lava-wrapper 
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
	src/bundle.c \
	src/debug.c \
	src/json-format.c \
	src/json-test.c \
	src/text-utils.c \
	src/uuid.c \
    src/lava-wrapper.c
LOCAL_MODULE := lava-wrapper 
LOCAL_MODULE_TAGS := tests
LOCAL_CFLAGS += -g
include $(BUILD_HOST_EXECUTABLE)
