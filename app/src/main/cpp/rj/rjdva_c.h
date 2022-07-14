#ifndef _RJDVA_C_H
#define _RJDVA_C_H

#include<string>

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************************************/
//! \ingroup STRUCTS
//! \struct GDATAFRAME
//! 重力帧相关信息
/************************************************************************************************/
typedef struct _gDataFrame
{
    float fValue;               //当前重力值（去皮，所有重力传感器总和）
    int nFrameId;               //帧号
    long long llTimeStamp;      //当前帧的时间戳ms
    float *pfValueLayer;        //每一层的重力值
    int nLayers;                //传感器层数
}GDataFrame;

/************************************************************************************************/
//! \ingroup STRUCTS
//! \struct VDATAFRAME
//! 视觉帧相关数据
/************************************************************************************************/

typedef struct _vDataFrame
{
    unsigned char* pData ;       //当前帧数据指针地址
    unsigned int nDataSize;     //当前帧数据大小
    int nFrameId;               //帧号
    long long llTimeStamp;      //当前帧的时间戳ms
    char strCameraPos[2];   //相机位置信息，如TR，DR，分别代表右上与右下相机

}VDataFrame;


/**
*   @brief  执行算法初始化，软件启动时调用
*   @param  strDeviceId - 设备ID
*   @param  strServerIpPort - 锐捷AI云平台IP与Port组成的字符串，如"0.0.0.0:9999"
*   @param  strWorkspacePath - 数据包存储路径
*   @param  strInfoJson - 包含相关信息的json格式的字符串内容
 *  @param  bPureVision - 区分带重力和纯视觉版本
*   @param  bCameraFormatMJPEG - 区分相机数据格式 true-MJPEG false-H264
*   @return 初始化成功返回true, 失败返回false
*/
bool rjdva_Init(const char* strDeviceId, const char* strServerIpPor,
           const char* strWorkspacePath, const char* strInfoJson,
                const bool &bPureVision, const bool &bCameraFormatMJPEG);

/**
*   @brief  开门回调函数，收到门锁打开信号时调用此函数
*   @param  strOrderId - 订单编号
*   @return 调用成功返回true, 失败返回false
*/
bool rjdva_OpenDoorCallback(const char* strOrderId);

/**
*   @brief  开门成功后，获取相机原始数据写入
*   @param  vDataFrame - 由相机原始数据等信息组成的结构体
*   @return 调用成功返回true, 失败返回false
*/
bool rjdva_PushVDataFrame(VDataFrame vDataFrame);

/**
*   @brief  开门成功后，获取重力去皮后的数据并写入
*   @param  gDataFrame - 由重力数据等信息组成的结构体
*   @return 调用成功返回true, 失败返回false
*/
bool rjdva_PushGDataFrame(GDataFrame gDataFrame);

/**
*   @brief  发送算法数据包至锐捷AI识别平台
*   @param strOrderId - 订单编号
*   @param strToken - token信息
*   @param strZipPath - ZIP包保存路径
*   @return 1）0 - 本次调用成功发送数据；
		2）101 - 本次调用未能成功发送数据
		3）102 - 本次调用未能成功发送数据，原因是授权过期
		4）103 - 本次调用未能成功发送数据，原因是授权数不足
        5) 104 - 本次调用未能成功发送数据，原因是未进行授权
*/
int rjdva_SendDataPacket(const char* strOrderId, const char* strToken, char* strZipPath);

/**
*   @brief  关门回调函数，收到门锁关闭信号时调用此函数
*   @param nStateCode - 设备状态码，用于反馈上层捕获到的异常；若上层不进行异常捕获，设置为0即可
*   @return 调用成功返回true, 失败返回false
*/
bool rjdva_CloseDoorCallback( const int nStateCode );

/**
*   @brief  获取SDK版本号
*   @param strSDKVersion - SDK版本信息
*   @return 调用成功返回true, 失败返回false
*/
bool rjdva_GetSDKVersion(char* strSDKVersion);

/**
*   @brief  断电应急关门回调函数，发生断电情况时调用此函数，保存相机数据
*   @param nStateCode - 设备状态码，用于反馈上层捕获到的异常；若上层不进行异常捕获，设置为0即可
*   @return 调用成功返回true, 失败返回false
*/
bool rjdva_PowerOffCloseDoorCallback( const int nStateCode );

/**
*   @brief  开启/关闭文件记录功能
*   @param  bSwitch - 开启/关闭
*   @return 调用成功返回true, 失败返回false
*/
bool rjdva_SwitchRecord( const bool &bSwitch );

/**
*   @brief  调整视频编码的格式（目前支持19/21）
*   @param  nFormat - 编码格式
*   @return 调用成功返回true, 失败返回false
*/
bool rjdva_SetAmediaColorFormat( const int &nFormat );

/**
*   @brief 发送算法数据包之前需要进行文件校验相关处理
*   @param strOrderId - 订单编号
*   @param strToken - token信息
*   @param strZipPath - ZIP包保存路径
*   @return 调用成功返回true, 失败返回false
*/
bool CheckDataPacketBeforeSend(const char* strOrderId, const char* strToken, char* strZipPath);

/**
*   @brief  更新授权状态
*   @param  bSuccess - 授权成功状态
*   @return 调用成功返回true, 失败返回false
*/
bool rjdva_UpdateAuthorizationStatus(const bool &bSuccess);

/**
*   @brief  变更相机方位信息
*   @param  bIsAnother - 相机方位信息
*   @return 调用成功返回true, 失败返回false
*/
bool rjdva_ChangeCameraLocation(const bool &bIsAnother);



#ifdef __cplusplus
}
#endif

#endif
