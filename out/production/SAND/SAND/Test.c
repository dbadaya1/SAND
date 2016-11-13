 #include <stdio.h>  
// #include "Test.h"
 #include <stdlib.h>
#include <jni.h>
#include <pthread.h>

JNIEnv* create_vm(JavaVM **jvm)
{
    JNIEnv* env;
    JavaVMInitArgs args;
    JavaVMOption options;
    args.version = JNI_VERSION_1_8;
    args.nOptions = 1;
    options.optionString = "-Djava.class.path=.";
    args.options = &options;
    args.ignoreUnrecognized = 0;
    int rv;
    rv = JNI_CreateJavaVM(jvm, (void**)&env, &args);
    if (rv < 0 || !env)
        printf("Unable to Launch JVM %d\n",rv);
    else
        printf("Launched JVM! :)\n");
    return env;
}

void * launchGUI(void * jvm) {
    JNIEnv *env;
    (*(JavaVM *)jvm)->AttachCurrentThread(jvm,(void**)&env, NULL);


    jclass mainClass = (*env)->FindClass(env, "Test");
    if(mainClass == NULL)
    printf("fgfd");

    jmethodID mainMethod = (*env)->GetStaticMethodID(env, mainClass, "main", "([Ljava/lang/String;)V");

    (*env)->CallStaticVoidMethod(env, mainClass, mainMethod, NULL);

    while(1) {}
    return NULL;
}

void invoke_class(JNIEnv* env)
{
//jint ver = (*env)->GetVersion(env);
      // printf("%d.%d \n",(ver>>16)&0x0f,ver&0x0f);

 jclass mainClass = (*env)->FindClass(env, "Test");
    if(mainClass == NULL)
    printf("fgfd");

    jmethodID mainMethod = (*env)->GetStaticMethodID(env, mainClass, "main", "([Ljava/lang/String;)V");

    (*env)->CallStaticVoidMethod(env, mainClass, mainMethod, NULL);


    jclass hello_world_class;
    jmethodID main_method;
    jmethodID square_method;
    jmethodID power_method;
    jint number=20;
    jint exponent=3;
    hello_world_class = (*env)->FindClass(env, "Test");
    if(hello_world_class == NULL) {
        printf("null");
    }

//jclass clsClazz = (*env)->GetObjectClass(env,hello_world_class);

  //  jmethodID mid_getName = (*env)->GetMethodID(env, clsClazz, "getName", "()Ljava/lang/String;");
  //  jstring name = (*env)->CallObjectMethod(env, hello_world_class, mid_getName);
   //const char *nativeString = (*env)->GetStringUTFChars(env, name, 0);
 //  printf("%s",nativeString);

//main_method = (*env)->GetStaticMethodID(env, main, "main", "([Ljava/lang/String;)V");
 //(*env)->CallStaticVoidMethod(env, main, main_method, NULL);

/*
    square_method = (*env)->GetStaticMethodID(env, hello_world_class, "square", "(I)I");
    power_method = (*env)->GetStaticMethodID(env, hello_world_class, "power", "(II)I");
    printf("%d squared is %d\n", number,
        (*env)->CallStaticIntMethod(env, hello_world_class, square_method, number));
    printf("%d raised to the %d power is %d\n", number, exponent,
        (*env)->CallStaticIntMethod(env, hello_world_class, power_method, number, exponent));
*/
}

int main(int argc, char **argv)
{
    JavaVM *jvm;
    JNIEnv *env;
    env = create_vm(&jvm);
    if(env == NULL)
        return 1;
invoke_class(env);
  //  launchGUI(jvm);
   // invoke_class(env);
/*
    pthread_t launchGUI_thread;

    if(pthread_create(&launchGUI_thread, NULL, launchGUI, jvm)) {

        fprintf(stderr, "Error creating thread\n");
        return 1;

    }

    if(pthread_join(launchGUI_thread, NULL)) {

        fprintf(stderr, "Error joining thread\n");
        return 2;

    }
*/
    return 0;

}
