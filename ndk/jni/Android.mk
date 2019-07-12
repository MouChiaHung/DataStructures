LOCAL_PATH := $(call my-dir)
MY_FILES_PATH  :=  $(LOCAL_PATH) \
                   #$(LOCAL_PATH)/../../Classes

MY_FILES_SUFFIX := %.cpp %.c

My_All_Files := $(foreach src_path,$(MY_FILES_PATH), $(shell find $(src_path) -type f) ) 
My_All_Files := $(My_All_Files:$(MY_CPP_PATH)/./%=$(MY_CPP_PATH)%)
MY_SRC_LIST  := $(filter $(MY_FILES_SUFFIX),$(My_All_Files)) 
MY_SRC_LIST  := $(MY_SRC_LIST:$(LOCAL_PATH)/%=%)

$(warning *-*-*-*-* MY_SRC_LIST *-*-*-*-*)
$(warning $(MY_SRC_LIST))
$(warning *-*-*-*-*-*-*-*-*-*-*-*-*-*-*)
$(warning  )

include $(CLEAR_VARS)

LOCAL_MODULE := main
#LOCAL_MODULE_PATH := $(LOCAL_PATH)
#LOCAL_SRC_FILES := $(MY_SRC_LIST)
LOCAL_SRC_FILES := ./main.cpp   

LOCAL_C_INCLUDES += $(LOCAL_PATH)/
#LOCAL_C_INCLUDES += $(NDK)/sources/cxx-stl/stlport/stlport		  

LOCAL_CPP_EXTENSION := .cxx .cpp .cc

#LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
#LOCAL_LDLIBS +=-fpic -fPIE -pie
#LOCAL_LDLIBS +=-landroid -llog -lz

LOCAL_CPPFLAGS := -fexceptions -frtti
LOCAL_CPPFLAGS += -std=c++11 -D__cplusplus=201103L

include $(BUILD_EXECUTABLE)  