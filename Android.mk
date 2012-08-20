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
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_MODULE := lava-gtest-wrapper
include $(BUILD_EXECUTABLE)

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
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_MODULE := lava-gtest-wrapper
LOCAL_CFLAGS += -g
include $(BUILD_HOST_EXECUTABLE)
