include $(call all-subdir-makefiles)
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := tests
LOCAL_MODULE := pm-suspend
systemtarball: pm-suspend
LOCAL_SRC_FILES := pm-suspend
LOCAL_MODULE_PATH := $(TARGET_OUT_EXECUTABLES)
include $(BUILD_PREBUILT)
