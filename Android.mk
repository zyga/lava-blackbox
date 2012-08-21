LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := lava-gtest-wrapper
LOCAL_MODULE_TAGS := tests
LOCAL_SRC_FILES:= \
	src/bundle.c \
	src/debug.c \
	src/json-format.c \
	src/json-test.c \
	src/text-utils.c \
	src/uuid.c \
	src/lava-gtest-wrapper.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_MODULE := lava-gtest-wrapper
LOCAL_MODULE_TAGS := tests
LOCAL_SRC_FILES:= \
	src/bundle.c \
	src/debug.c \
	src/json-format.c \
	src/json-test.c \
	src/text-utils.c \
	src/uuid.c \
	src/lava-gtest-wrapper.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_CFLAGS += -g
include $(BUILD_HOST_EXECUTABLE)

# So we also need to ship a few scripts. Sadly Android makes this pretty much
# complicated (we cannot just extend PRODUCT_COPY_FILES) so we'll cheat and use
# BUILD_PREBUILT helper and just place them carefully where we want them.
include $(CLEAR_VARS)
LOCAL_MODULE := lava-wrapper
LOCAL_MODULE_TAGS := tests
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_PATH := $(PRODUCT_OUT)/system/bin
LOCAL_SRC_FILES := lava-wrapper
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := lava-wrapper-finder-gtest
LOCAL_MODULE_TAGS := tests
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_PATH := $(PRODUCT_OUT)/system/bin
LOCAL_SRC_FILES := lava-wrapper-finder-gtest
include $(BUILD_PREBUILT)
