//
// Created by 研发 on 2016/6/30.
//主要实现的是原生的TCP连接.把服务端与客户端都写到一起了
//
#include "com_jin_jni_JniLoad.h"
#include "stdio.h"
#include <stdarg.h>
#include "errno.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stddef.h>
#define MAX_BUFFER_SIZE 80
#define INET_ADDRESTRLEN 100
// C++ 必须手动释放内存
static void LogMessage (JNIEnv * env, jobject obj, const char* format, ...) {
    static jmethodID methodID = NULL;
    if (NULL == methodID) {
        jclass clazz = env->GetObjectClass(obj);
        methodID = env->GetMethodID(clazz, "logMessage", "(Ljava/lang/String;)V");

        env->DeleteLocalRef(clazz);
    }
    if (NULL != methodID) {
        // 格式化日志消息
        char buffer[MAX_BUFFER_SIZE];
        va_list ap;
        va_start(ap, format);
        vsnprintf(buffer, MAX_BUFFER_SIZE, format, ap);
        va_end(ap);
        // 将缓冲区的内容写到JAVA的字符串里面
        jstring message = env->NewStringUTF(buffer);
        if (NULL != message)
        {
            env->CallVoidMethod(obj, methodID, message);
            env->DeleteLocalRef(message);
        }        
    }
}

/**
 * 用给定的异常类抛出异常.
 */
static void ThrowException(JNIEnv *env, const char* className, const char* message) {
    // 获取异常类
    jclass clazz = env->FindClass(className);
    if (NULL != clazz) {
        env->ThrowNew(clazz, message);
        env->DeleteLocalRef(clazz);
    }
}

/**
 *用给定的异常类和基于错误号的错误消息抛出新异常
 */
static void TrowErrnoException (JNIEnv *env, const char* className, int errnum) {
    char buffer[MAX_BUFFER_SIZE];
    // 获取错误号消息
    if (-1 == strerror_r(errnum, buffer, MAX_BUFFER_SIZE)) {
        strerror_r(errno, buffer, MAX_BUFFER_SIZE);
    }

    ThrowException(env, className, buffer);
}
static int NewTcpSocket(JNIEnv *env, jobject jobj) {
    LogMessage(env, jobj, "Constructiing new TCP socket ...");
    int tcpSocket = socket(PF_INET, SOCK_STREAM, 0);
    // 检查构造是否正确
    if (-1 == tcpSocket) {
        // 抛出异常
        TrowErrnoException(env, "java/io/IOException", errno);
    }
    return tcpSocket;
}
static void bindSocketToPort(JNIEnv *env, jobject obj, int sd, unsigned short port) {
    struct sockaddr_in address;
    // 用来对一段内存进行初始化,将某段内存全部重置为某个数字或者ASCII的一个编码
    memset(&address, 0, sizeof(address));
    // 将32函数,从主机字节顺序调整为网络字节顺序
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    // 如果在地址结构中将端口号设置为零,bind函数会将第一个可用端口号分配给socket.可用用getsocketname函数
    // 在socket中检索到这个端口号

    if (-1 == bind(sd, (struct sockaddr*) &address, sizeof(address))){

    }
}

static unsigned short GetSocketPort(JNIEnv *env, jobject obj, int sd) {
    unsigned short port = 0;
    struct sockaddr_in address;
    socklen_t addressLength = sizeof(address);
    if (-1 == getsockname(sd, (struct sockaddr*) &address, &addressLength)) {
        ThrowException(env, "java/io/IOException", "nimei");
    } else {
        port = ntohs(address.sin_port);
    }
    return port;
}
/**
 * 监听指定的待处理链接的backlog的socket,当backlog已满载时拒绝新的连接
 *
 * 通过listener监听输入连接只是简单的将输入连接放进一个队列里面并等待应用程序显示的接受他们
 */
static void ListenOnSocket(JNIEnv *env, jobject obj, int socketDescriptor, int backlog) {
    if (-1 == listen(socketDescriptor, backlog)) {
        // 代表抛出异常
        ThrowException(env, "java/io/IOException", "bang");
    }
}

static void LogAddress(JNIEnv *env, jobject obj, const char* message, const struct sockaddr_in* address) {
    char ip[INET_ADDRESTRLEN];
    if (NULL == inet_ntop(PF_INET, &(address->sin_addr), ip, INET_ADDRESTRLEN)){
        
    } else {
        // 将端口转成主机顺序.
        unsigned short port = ntohs(address->sin_port);
        LogMessage(env, obj, "%s %s:%hu.", message, ip, port);
    };
}
/**
 * 阻塞函数,连接
 */
static int AcceptOnSocket (JNIEnv * env, jobject obj, int socketDescript) {
    struct sockaddr_in address;
    socklen_t addressLength = sizeof(address);
    
    // 阻塞等待进来的客户连接
    int clientSocket = accept(socketDescript, (struct sockaddr*)&address, &addressLength);
    if (-1 == clientSocket) {
        
    } else {
        LogAddress(env, obj, "client connect from", &address);
    }
    return clientSocket;
   
}
/**
 * 阻塞并接受来自socket的数据放到缓冲区
 */
static ssize_t ReceiveFromSocket(JNIEnv *env, jobject obj, int socketDescript, char* buffer, size_t bufferSize) {
    ssize_t recv_size = recv(socketDescript, buffer, bufferSize, 0);
    // 如果接收失败
    if (-1 == recv_size) {
        TrowErrnoException(env, "java/io/IOException", errno);
    } else {
        // 以NULL结尾缓冲区形成一个字符创
        buffer[recv_size] = NULL;
        // 如果数据接收成功
        if (recv_size >0) {
            // 链接数据
        } else {
            // 连接失败
        }
    }
    return recv_size;
}
/**
 * 通过socket发送数据
 */
static ssize_t SendToSocket(JNIEnv *env, jobject obj, int socketDescript, const char* buffer, size_t bufferSize) {
    LogMessage(env, obj, " send .. message");
    ssize_t sentSize = send(socketDescript, buffer, bufferSize, 0);
    if (-1 == sentSize) {

    } else {
        if (sentSize > 0) {

        } else {
            LogMessage(env, obj, "没有连接");
        }
    }
}
/**
 * 开始连接
 */
void Java_com_jin_jni_JniLoad_nativeStartTcpServer(JNIEnv *env, jobject jobj, jint port) {
    // 构造新的TCP socket
    int serverSocket = NewTcpSocket(env, jobj);
    if (NULL == env->ExceptionOccurred()) {
        // 将socket绑定到一个端口上.
        bindSocketToPort(env, jobj, serverSocket, (unsigned short)port);
        if (NULL != env->ExceptionOccurred()) {
            goto exit;
        }
        // 如果请求了随机端口号
        GetSocketPort(env, jobj, serverSocket);
        if (NULL != env->ExceptionOccurred()) {
            goto exit;
        }
        // 监听有4个等待连接的backlog的socket
        ListenOnSocket(env, jobj, serverSocket, 4);
        if (NULL != env->ExceptionOccurred()) {
            goto exit;
        }
        // 接收socket的一个客户连接
        int clientSocket = AcceptOnSocket(env, jobj, serverSocket);
        if (NULL != env->ExceptionOccurred()) {
            goto exit;
        }

        char buffer[MAX_BUFFER_SIZE];
        ssize_t recvSize;
        ssize_t sentSize;
        // 接收并发送数据
        while (1) {
            // 从socket接收
            recvSize = ReceiveFromSocket(env, jobj, clientSocket, buffer, MAX_BUFFER_SIZE);
            if ((0 == recvSize)  || (NULL != env->ExceptionOccurred()))
                break;

            sentSize = SendToSocket(env, jobj, clientSocket, buffer, (size_t)recvSize);
            if ((0 == sentSize) || (NULL != env->ExceptionOccurred()))
                break;
            }
        close(clientSocket);
    }
    exit:
    if (serverSocket > 0)
    {
        close(serverSocket);
    }


}
static void ConnectToAddress(JNIEnv *env, jobject obj, int socketDescription, const char* ip,
                             unsigned short port) {
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = PF_INET;
    // 将IP地址字符串转成网络的
    if (0 == inet_aton(ip, &(address.sin_addr))) {
        ThrowException(env, "java/io/IOException", "dheh");
    } else {
        // 将端口号转成网络的字节
        address.sin_port = htonl(port);
        if (-1 == connect(socketDescription, (const sockaddr*) &address, sizeof(address)))
            ThrowException(env, "java/io/IOException", "dde");
        else {
            // 连接成功
        }

    }
}
static void startTCPClient(JNIEnv *env, jobject obj, jstring ip, jint port, jstring message) {
    int clientSocket = NewTcpSocket(env, obj);
    if (NULL == env->ExceptionOccurred()) {
        const char *ipAddress = env->GetStringUTFChars(ip, NULL);
        if (NULL == ipAddress)
            goto exit;
        ConnectToAddress(env, obj, clientSocket, ipAddress, (unsigned short) port);
        env->ReleaseStringUTFChars(ip, ipAddress);
        
        if (NULL != env->ExceptionOccurred()) 
            goto exit;

        const char *messageText = env->GetStringUTFChars(message, NULL);
        if (NULL == messageText)
            goto exit;
        // 获取消息的大小
        jsize messageSize = env->GetStringUTFLength(message);
        SendToSocket(env, obj, clientSocket, messageText, messageSize);
        env->ReleaseStringUTFChars(message, messageText);

        if (NULL != env->ExceptionOccurred())
            goto exit;
        char buffer[MAX_BUFFER_SIZE];
        ReceiveFromSocket(env, obj, clientSocket, buffer, MAX_BUFFER_SIZE);
    }
    exit:
    if (clientSocket > 0)
    {
        close(clientSocket);
    }
}

static int NewUdpSocket(JNIEnv *env, jobject obj) {
    LogMessage(env, obj, "connect a new udp");
    int udpsocket = socket(PF_INET, SOCK_DGRAM, 0);
    if (-1 == udpsocket)
    {
        ThrowException(env, "java/io/IOException", "exception");
    }
    return udpsocket;
}

static ssize_t ReceiveDatagramFromSocket(JNIEnv *env, jobject obj, int socketDescription, struct sockaddr_in* address,char* buffer, size_t bufferSize) {
    socklen_t addressLength = sizeof(struct sockaddr_in);
    ssize_t recvSize = recvfrom(socketDescription, buffer, bufferSize, 0, (const sockaddr*)address, &addressLength);
    if (-1 == recvSize) {
        ThrowException(env, "java/io/IOException", "");
    } else {
        buffer[recvSize] = NULL;
        if (recvSize > 0) {
            
        }
        return recvSize;
    }
}
static ssize_t SendDatagramFromSocket(JNIEnv* env, jobject obj, int socketDescription, struct sockaddr_in* address, char* buffer, size_t bufferSize) {
    ssize_t sentsize = sendto(socketDescription, buffer, bufferSize, 0, (const sockaddr*) address, sizeof(struct sockaddr_in));
    if (-1 == sentsize) {

    } else if (sentsize >0) {

    } else {

    }
    return sentsize;
}

jint JNICALL Java_com_jin_jni_JniLoad_what
(JNIEnv *env, jclass jclazz){
    jint a = 1;
    a += 10;
    return a;
};

