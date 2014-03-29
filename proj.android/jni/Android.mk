LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp

# [[[cog
# import list_classes
# cpps, includes = list_classes.listCppPaths()
#
# #### Write list of C++ files found
#
# cog.outl()
# for f in cpps:
#   cog.outl('LOCAL_SRC_FILES += %s' % f)
#
# #### Write list of subdirectories with source files found
#
# cog.outl()
# cog.outl('LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes/')
#
# #### Delete next 2 lines of code if you don't need list of subdirectories
#
# for d in includes:
#  cog.outl('LOCAL_C_INCLUDES += $(LOCAL_PATH)/%s' % d)
#
# cog.outl()
# ]]]

LOCAL_SRC_FILES += ../../Classes/AppDelegate.cpp
LOCAL_SRC_FILES += ../../Classes/Balls/Ball.cpp
LOCAL_SRC_FILES += ../../Classes/GameManager.cpp
LOCAL_SRC_FILES += ../../Classes/Lines/Line.cpp
LOCAL_SRC_FILES += ../../Classes/Paddles/Paddle.cpp
LOCAL_SRC_FILES += ../../Classes/Players/AIPlayer.cpp
LOCAL_SRC_FILES += ../../Classes/Players/HumanPlayer.cpp
LOCAL_SRC_FILES += ../../Classes/Players/Player.cpp
LOCAL_SRC_FILES += ../../Classes/Scenes/GameScene.cpp
LOCAL_SRC_FILES += ../../Classes/Utility/ConditionalSystem/ConditionalSystem.cpp
LOCAL_SRC_FILES += ../../Classes/Utility/Debug.cpp
LOCAL_SRC_FILES += ../../Classes/Utility/Easing.cpp
LOCAL_SRC_FILES += ../../Classes/Utility/Events/EventManager.cpp
LOCAL_SRC_FILES += ../../Classes/Utility/Events/IEventSubscriber.cpp
LOCAL_SRC_FILES += ../../Classes/Utility/Observable/Observable.cpp
LOCAL_SRC_FILES += ../../Classes/Utility/Observable/Observer.cpp
LOCAL_SRC_FILES += ../../Classes/Utility/SneakyInput/SneakyButton.cpp
LOCAL_SRC_FILES += ../../Classes/Utility/SneakyInput/SneakyButtonSkinnedBase.cpp
LOCAL_SRC_FILES += ../../Classes/Utility/SneakyInput/SneakyJoystick.cpp
LOCAL_SRC_FILES += ../../Classes/Utility/SneakyInput/SneakyJoystickSkinnedBase.cpp
LOCAL_SRC_FILES += ../../Classes/Utility/StateMachine/StateMachineState.cpp
LOCAL_SRC_FILES += ../../Classes/Utility/json/jsoncpp.cpp
LOCAL_SRC_FILES += ../../Classes/Utility/simplexnoise.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Balls
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Lines
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Paddles
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Players
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Scenes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Utility
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Utility/ConditionalSystem
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Utility/Events
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Utility/Observable
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Utility/SneakyInput
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Utility/StateMachine
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Utility/json

# [[[end]]]

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

#used for debugging
$(call import-add-path,D:/work/Cocos2D/cocos2d-x-2.2)
$(call import-add-path,D:/work/Cocos2D/cocos2d-x-2.2/cocos2dx/platform/third_party/android/prebuilt)
#$(call import-add-path,/cocos2d-x)
#$(call import-add-path,/cocos2d-x/cocos2dx/platform/third_party/android/prebuilt)
#----

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
# $(call import-module,external/Box2D)
# $(call import-module,external/chipmunk)
