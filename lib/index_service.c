#include <stdio.h>
#include <string.h>
#include "index_service.h"

#define MAX_KEY_WORDS_LENGTH 10
#define MIN_LENGTH_OF_WORD 4

JNIEXPORT jobjectArray JNICALL Java_bg_nbu_java_server_plugin_IndexService_index(JNIEnv *env, jobject obj, jstring str)
{
  char *keywords[MAX_KEY_WORDS_LENGTH];
  int index = 0;

  if (str != NULL)
  {
    const char *line = (*env)->GetStringUTFChars(env, str, NULL);
    
    char *word;
  
  
    word = strtok((char *) line, " ");
    while (word != NULL)
    {
      if (strlen(word) > MIN_LENGTH_OF_WORD)
      {
        keywords[index] = word;
        index++;
      }
      if (index == MAX_KEY_WORDS_LENGTH)
      {
        break;
      }
      word = strtok (NULL, " ");
    }
  }
  jobjectArray ret;
  int i;
  ret = (jobjectArray)(*env)->NewObjectArray(env, index, (*env)->FindClass(env, "java/lang/String"), (*env)->NewStringUTF(env, ""));

  for (i = 0; i < index; i++)
  {
    (*env)->SetObjectArrayElement(env, ret, i, (*env)->NewStringUTF(env, keywords[i]));
  }
  return(ret);
}
