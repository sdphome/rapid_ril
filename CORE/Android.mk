#
# Copyright 2010 Intrinsyc Software International, Inc.  All rights reserved.
#

ifeq ($(strip $(BOARD_HAVE_IFX6160)),true)

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    ND/te_base.cpp \
    ND/te.cpp \
    ND/systemmanager.cpp \
    ND/radio_state.cpp \
    silo.cpp \
    ND/silo_voice.cpp \
    ND/silo_network.cpp \
    ND/silo_sim.cpp \
    ND/silo_data.cpp \
    ND/silo_phonebook.cpp \
    ND/silo_sms.cpp \
    ND/channel_nd.cpp \
    channelbase.cpp \
    channel_atcmd.cpp \
    channel_data.cpp \
    channel_DLC2.cpp \
    channel_DLC6.cpp \
    channel_DLC8.cpp \
    channel_URC.cpp \
    port.cpp \
    ND/callbacks.cpp \
    ND/file_ops.cpp \
    ND/reset.cpp \
    ND/rildmain.cpp \
    ND/sync_ops.cpp \
    ND/thread_ops.cpp \
    cmdcontext.cpp \
    command.cpp \
    globals.cpp \
    rilchannels.cpp \
    response.cpp \
    request_info_table.cpp \
    thread_manager.cpp \
    ND/silo_factory.cpp \
    ND/MODEMS/te_inf_6260.cpp \
    ND/MODEMS/silo_voice_inf.cpp \
    ND/MODEMS/silo_sim_inf.cpp \
    ND/MODEMS/silo_sms_inf.cpp \
    ND/MODEMS/silo_data_inf.cpp \
    ND/MODEMS/silo_network_inf.cpp \
    ND/MODEMS/silo_phonebook_inf.cpp


LOCAL_SHARED_LIBRARIES := libcutils libutils

ifeq ($(TARGET_BUILD_VARIANT),eng)
LOCAL_CFLAGS += -DDEBUG
endif

# Activating this macro enables the optional Video Telephony feature
#LOCAL_CFLAGS += -DM2_VT_FEATURE_ENABLED

# Activating this macro enables the Call Failed Cause Notification feature
#LOCAL_CFLAGS += -DM2_CALL_FAILED_CAUSE_FEATURE_ENABLED

# Activating this macro enables the Rx Diversity feature
LOCAL_CFLAGS += -DM2_RXDIV_FEATURE_ENABLED

# Activating this macro enables PIN retry count feature
#LOCAL_CFLAGS += -DM2_PIN_RETRIES_FEATURE_ENABLED

# Remove comment character when SEEK for Android V2.2.2 is complete.
# This adds the RIL_E_INVALID_PARAMETER = 22 in ril.h
# Normally this is = 18 in the original SEEK V2.2.2 implementation.
# To be aligned with Android java framework, align these codes with:
# frameworks/base/telephony/java/com/android/internal/telephony/RILConstants.java
#LOCAL_CFLAGS += -DM2_SEEK_INVALID_PARAMETER_FEATURE_ENABLED


# Activating this macro enables SEEK for Android (for Ice Cream Sandwich)
#LOCAL_CFLAGS += -DM2_SEEK_FEATURE_ENABLED

# Activating this macro enables PIN caching (for modem cold reboot)
#LOCAL_CFLAGS += -DM2_PIN_CACHING_FEATURE_ENABLED


LOCAL_C_INCLUDES :=  \
    $(LOCAL_PATH)/ND  \
    $(LOCAL_PATH)/ND/MODEMS  \
    $(LOCAL_PATH)/MODEMS  \
    $(LOCAL_PATH)/../INC \
    $(LOCAL_PATH)/../UTIL/ND


#build shared library
LOCAL_PRELINK_MODULE := false
LOCAL_STRIP_MODULE := true
LOCAL_SHARED_LIBRARIES += librapid-ril-util
LOCAL_LDLIBS += -lpthread
LOCAL_CFLAGS += -DRIL_SHLIB -Os
LOCAL_MODULE:= librapid-ril-core
LOCAL_MODULE_TAGS:= optional
include $(BUILD_SHARED_LIBRARY)

endif
