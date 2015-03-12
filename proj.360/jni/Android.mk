LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(COCOS_X_ROOT))
$(call import-add-path,$(COCOS_X_ROOT)/external)
$(call import-add-path,$(COCOS_X_ROOT)/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

#目录下所有*.cpp文件;  
CLASS_FILES := $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
CLASS_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/*/*.cpp)
CLASS_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/*/*.c)
CLASS_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/*/*.h)
CLASS_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/*/*/*.cpp)
CLASS_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/*/*/*.c)
CLASS_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/*/*/*.h)
CLASS_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/*/*/*/*.cpp)
CLASS_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/*/*/*/*.c)
CLASS_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/*/*/*/*.h)
CLASS_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/*/*/*/*/*.cpp)
CLASS_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/*/*/*/*/*.c)
CLASS_FILES += $(wildcard $(LOCAL_PATH)/../../Classes/*/*/*/*/*.h)
CLASS_FILES += $(wildcard $(LOCAL_PATH)/../../proj.ios_mac/ios/jsoncpp/*/*/*.c)
CLASS_FILES += $(wildcard $(LOCAL_PATH)/../../proj.ios_mac/ios/jsoncpp/*/*/*.cpp)
CLASS_FILES += $(wildcard $(LOCAL_PATH)/../../proj.ios_mac/ios/jsoncpp/*/*/*.h)

CLASS_FILES := $(CLASS_FILES:$(LOCAL_PATH)/%=%)  

LOCAL_SRC_FILES := hellocpp/main.cpp \
LOCAL_SRC_FILES += $(CLASS_FILES)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../proj.ios_mac/ios/jsoncpp/include/json

LOCAL_STATIC_LIBRARIES := cocos2dx_static

LOCAL_LDLIBS += -L$(call host-path,$(NDK_ROOT)/sources/cxx-stl/llvm-libc++/libs/$(TARGET_ARCH_ABI)) -lc++_static

include $(BUILD_SHARED_LIBRARY)


$(call import-module,./prebuilt-mk)