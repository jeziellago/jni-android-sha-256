//
// Created by Jeziel Lago on 2019-09-30.
//

#include "native-lib.h"
using namespace std;
using namespace picosha2;
extern "C"
JNIEXPORT jstring JNICALL
Java_com_jeziellago_jniteste_MainActivity_getAndroidId
        (JNIEnv *env, jobject context) {

    const int ANDROID_ID_SIZE = 15;
    const char *settings_name = "android/provider/Settings$Secure";
    const char *context_name = "android/content/Context";

    jclass class_settings_secure = env->FindClass(settings_name);
    jclass class_context = env->FindClass(context_name);

    if(class_settings_secure == nullptr || class_context == nullptr){
        return env->NewStringUTF("Not found!");
    }

    //Get the getContentResolver method
    jmethodID m_get_content_resolver = env->GetMethodID(
            class_context,
            "getContentResolver",
            "()Landroid/content/ContentResolver;");

    if(m_get_content_resolver == nullptr){
        return env->NewStringUTF("Not found ContentResolver");
    }

    // get Secure.ANDROID_ID
    jfieldID f_android_id = env->GetStaticFieldID(class_settings_secure, "ANDROID_ID", "Ljava/lang/String;");

    if(f_android_id == nullptr){
        return env->NewStringUTF("Not found ANDROID_ID field");
    }

    jobject s_android_id = env->GetStaticObjectField(class_settings_secure, f_android_id);

    //create a ContentResolver instance context.getContentResolver()
    jobject o_content_resolver = env->CallObjectMethod(context, m_get_content_resolver);
    if(o_content_resolver == nullptr || s_android_id == nullptr){
        return env->NewStringUTF("Not create content resolver instance!");
    }

    //get the method getString
    jmethodID m_get_string = env->GetStaticMethodID(
            class_settings_secure,
            "getString",
            "(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;");

    if(m_get_string == nullptr){
        return env->NewStringUTF("Not create content resolver instance string!");
    }

    //get the Android ID
    auto android_id = (jstring) env->CallStaticObjectMethod(class_settings_secure,
                                                        m_get_string,
                                                        o_content_resolver,
                                                        s_android_id);

    // generate SHA-256 from ANDROID_ID
    jboolean isCopy;
    const char *convertedValue = env->GetStringUTFChars(android_id, &isCopy);
    string src_comp = "(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;";
    string src_str = string(convertedValue, ANDROID_ID_SIZE) + src_comp;

    vector<unsigned char> hash(k_digest_size);
    hash256(src_str.begin(), src_str.end(), hash.begin(), hash.end());

    string hex_str = bytes_to_hex_string(hash.begin(), hash.end());

    return env->NewStringUTF(hex_str.c_str());
}

