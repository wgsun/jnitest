package rj

/**
 *@author:wgsun
 *2022/7/13
 *desc:
 */
object RJCtrl {

    init {
        System.loadLibrary("native-rj")
    }

    external fun rjdva_Init(
        deviceId: String,
        ip: String,
        path: String,
        config: String,
        bPureVision: Boolean,
        bCameraFormatMJPEG: Boolean
    ): Boolean

    external fun rjdva_OpenDoorCallback(OrderId: String)

    external fun rjdva_PushVDataFrame(
        jpdata: ByteArray?,
        nDataSize: Int,
        nFrameId: Int,
        llTimeStamp: Long,
        CameraPos: Int
    ): Int

    /**
     * @param fValue //当前重力值（去皮，所有重力传感器总和）
     * @param nFrameId //帧号
     * @param llTimeStamp //当前帧的时间戳ms
     * @param pfValueLayer //每一层的重力值
     * @param nLayers //传感器层数
     * @return
     */
    external fun rjdva_PushGDataFrame(
        fValue: Float,
        nFrameId: Int,
        llTimeStamp: Long,
        pfValueLayer: FloatArray?,
        nLayers: Int
    ): Boolean

    external fun rjdva_SendDataPacket(orderId: String?, token: String?, zipPath: String?): Int

    external fun rjdva_CloseDoorCallback(errorCode: Int): Int

    external fun rjdva_GetSDKVersion(): String?

    external fun rjdva_PowerOffCloseDoorCallback(stateCode: Int): Int

    external fun rjdva_SwitchRecord(bSwitch: Boolean): Boolean

    external fun rjdva_SetAmediaColorFormat(nFormat: Int): Boolean

    external fun CheckDataPacketBeforeSend(
        strOrderId: String?,
        token: String?,
        zipPath: String?
    ): Boolean

    external fun rjdva_UpdateAuthorizationStatus(bSuccess: Boolean): Boolean

    external fun rjdva_ChangeCameraLocation(bIsAnother: Boolean): Boolean
}