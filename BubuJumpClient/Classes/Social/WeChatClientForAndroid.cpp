#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "WeChatClientForAndroid.h"

USING_NS_CC;

const char* CLASS_NAME = "com/touchthesky/www/WeChatClient";

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_quitGame(JNIEnv* env, jobject thiz)
{
    cocos2d::Director::getInstance()->end();
}

WeChatClientForAndroid::WeChatClientForAndroid()
{
    if (JniHelper::getStaticMethodInfo(this->_info, CLASS_NAME, "getInstance", "()Ljava/lang/Object;"))
    {
        this->_javaClient = this->_info.env->CallStaticObjectMethod(this->_info.classID, this->_info.methodID);
    }
}

WeChatClientForAndroid::~WeChatClientForAndroid()
{
    
}

void WeChatClientForAndroid::sendMessage(std::string message)
{
    if(JniHelper::getMethodInfo(this->_info, CLASS_NAME, "sendMessage", "(Ljava/lang/String;)V"))
    {
        jstring jMessage = this->_info.env->NewStringUTF(message.c_str());
        this->_info.env->CallVoidMethod(this->_javaClient, this->_info.methodID, jMessage);
        this->_info.env->DeleteLocalRef(jMessage);
    }
}

#endif
