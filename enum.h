#ifndef ENUM_H
#define ENUM_H
#include<QString>
//包含一些公共数据
typedef struct{
    int flag; //标识数据是什么
    QString strData;//具体的数据项
}struct_data;

//检测数据标识
enum enum_detection
{
    detection_dy, //电压
     detection_dl, //电流
     detection_aqcd,//安全触点
     detection_hxdlwz,//货箱吊笼位置
     detection_slyxsd, //矢量运行速度
    detection_pcjd,//平层精度（仅适用于简易升降机）
    detection_jgyl,//主要受力部位结构应力
                        //钢丝绳使用状态
    detection_gssnwbds, //钢丝绳内外部断丝

                    //吊笼/货厢静态水平度检测功能：
    detection_spd,//吊笼/货厢水平度

                    //吊笼/货厢运行加、减速度监测功能
    detection_jjsd,//吊笼/货厢的运行加减速度
    detection_zdjl,//制动距离的自动检测功能 制动距离
};

#endif // ENUM_H
