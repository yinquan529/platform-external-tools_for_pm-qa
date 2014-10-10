include $(call all-subdir-makefiles)
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= main.c bc.c scan.c execute.c load.c storage.c util.c global.c warranty.c  number.c
LOCAL_MODULE := bc
systemtarball: bc
LOCAL_SHARED_LIBRARIES := libcutils libc
LOCAL_MODULE_TAGS := tests
LOCAL_MODULE_PATH := $(TARGET_OUT_EXECUTABLES)
include $(BUILD_EXECUTABLE)
