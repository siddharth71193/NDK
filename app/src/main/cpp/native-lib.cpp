#include <jni.h>
#include <string>
#include <android/log.h>


#define MAX 100000

static jlong fib(jlong n){

    jlong prev = -1;

    jlong res = 1;

    for (jlong i = 0; i<= n; i++)
    {
        jlong sum = res + prev;
        prev = res;
        res = sum ;
    }
    return res;
}

jint res_siz = 0;

jint mult(jint x, jint* res, jint res_s) {

    jint carry = 0;

    for (jint i = 0; i < res_s; i++) {
        jint product = res[i] * x + carry;
        res[i] = product % 10;
        carry = product / 10;
    }

    while (carry) {
        res[res_s] = carry % 10;
        carry = carry / 10;
        res_s++;
    }
    return res_s;
}

jint* exp(int x, int n)
{
    jint* res;
    res = (jint*)malloc(MAX*sizeof(jint));
    res[0] = 1;
    if(n == 0)
    {
        return res;
    }

    jint temp = x;

    while (temp != 0) {
        res[res_siz++] = temp % 10;
        temp = temp / 10;
    }

    for (jint i = 2; i <= n; i++)
        res_siz = mult(x, res, res_siz);

    return res;
}

jint mult1(jint x, jint res[], jint res_s);

jint res_size = 1;

jint* factorial(jint n)
{
    jint *res;
    res = (jint*)malloc(MAX*sizeof(jint));

    res[0] = 1;

    for (jint x=2; x<=n; x++)
        res_size = mult1(x, res, res_size);

    return res;
}

jint mult1(jint x, jint res[], jint res_s)
{
    jint carry = 0;

    for (jint i=0; i<res_s; i++)
    {
        jint product = res[i] * x + carry;
        res[i] = product % 10;
        carry  = product/10;
    }

    while (carry)
    {
        res[res_size] = carry%10;
        carry = carry/10;
        res_s++;
    }
    return res_s;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_root_ndkpro_Operation_fibonacci(JNIEnv *env, jclass type, jlong n) {
        return  fib(n);
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_root_ndkpro_Operation_factorial(JNIEnv *env, jclass type, jint n) {
    jintArray  a;
    res_size = 1;
    jint *b = factorial(n);
    jint size = sizeof(b)/ sizeof(b[0]);
    a = env->NewIntArray(res_size);
    (env)->ReleaseIntArrayElements(a, b,NULL);
    return a;
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_root_ndkpro_Operation_power(JNIEnv *env, jclass type, jint n, jint x) {
    jintArray  a;
    res_siz = 0;
    jint *b = exp(n,x);
    a = env->NewIntArray(res_siz);
    (env)->ReleaseIntArrayElements(a, b,NULL);
    return a;
}
