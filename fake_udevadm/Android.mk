include $(call all-subdir-makefiles)
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= fake_udevadm.c 
LOCAL_MODULE := fake_udevadm
systemtarball: fake_udevadm
LOCAL_STATIC_LIBRARIES := libcutils libc
LOCAL_MODULE_TAGS := tests
LOCAL_LDLIBS += -lrt
LOCAL_MODULE_PATH := $(TARGET_OUT_EXECUTABLES)
include $(BUILD_EXECUTABLE)
