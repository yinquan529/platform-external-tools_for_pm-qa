include $(call all-subdir-makefiles)
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := tests
LOCAL_MODULE := fake_sudo
systemtarball: fake_sudo
LOCAL_SRC_FILES := fake_sudo
LOCAL_MODULE_PATH := $(TARGET_OUT_EXECUTABLES)
include $(BUILD_PREBUILT)
