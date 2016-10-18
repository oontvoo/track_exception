#include <jvmti.h>
#include <stdio.h>

static jclass NullPointerException;
static jfieldID detailMessage;

void JNICALL VMInit(jvmtiEnv* jvmti, JNIEnv* env, jthread thread) {
  jclass localNPE = env->FindClass("java/lang/NullPointerException");
  NullPointerException = (jclass) env->NewGlobalRef(localNPE);

  jclass Throwable = env->FindClass("java/lang/Throwable");
  detailMessage = env->GetFieldID(Throwable, "detailMessage", "Ljava/lang/String;");
}

void JNICALL ExceptionCallback(jvmtiEnv* jvmti, JNIEnv* env, jthread thread,
                               jmethodID method, jlocation location, jobject exception,
                               jmethodID catch_method, jlocation catch_location) {
  if (env->IsInstanceOf(exception, NullPointerException)) {
    char buf[32];
    sprintf(buf, "location=%ld", (long)location);
    env->SetObjectField(exception, detailMessage, env->NewStringUTF(buf));
  }
}

JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM* vm, char* options, void* reserved) {
  jvmtiEnv* jvmti;
  vm->GetEnv((void**)&jvmti, JVMTI_VERSION_1_0);

  jvmtiCapabilities capabilities = {0};
  capabilities.can_generate_exception_events = 1;
  jvmti->AddCapabilities(&capabilities);

  jvmtiEventCallbacks callbacks = {0};
  callbacks.VMInit = VMInit;
  callbacks.Exception = ExceptionCallback;
  jvmti->SetEventCallbacks(&callbacks, sizeof(callbacks));
  jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_VM_INIT, NULL);
  jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_EXCEPTION, NULL);
  return 0;
}
