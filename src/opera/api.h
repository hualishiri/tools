#ifndef TOOLS_OPERA_API_H_
#define TOOLS_OPERA_API_H_

namespace tools {

struct SCSMXPHead{
unsigned short  length;//报文长度
unsigned short  reserve;//备用
unsigned int    send;//报文源地址
unsigned char   recv;//报文目的地址
unsigned char   seq_no;//序列号
unsigned char   ack_no;//确认号
unsigned char   flag;//报文标识
unsigned char   unit_num;//信息单元个数
unsigned char   unit_seq;//信息单元序号
unsigned char   unit_flag;//信息单元标识
unsigned short   unit_length;//信息单元长度
unsigned int     time_stamp;//时戳，0.1ms
};

struct WdTgtTrk{
unsigned int  Pos : 1;//B0:经纬高，有其中任一个则填1
unsigned int  DBE : 1;//B1:方位距离仰角，有其中任一个则填1
unsigned int  VelRadius : 1;//B2相对航速，表示径向速度
unsigned int  VelCourseRel : 1;//B3:相对航速航向
unsigned int  VelCourseAbs: 1;//B4:绝对航速航向
unsigned int  Reserve1:1; //B5
unsigned int  Reserve2:1; //B6
unsigned int  Reserve3:1; //B7
unsigned int  Reserve4:1; //B8
unsigned int  Reserve5:1; //B9
unsigned int  Reserve6:1; //B10
unsigned int  Reserve7:1; //B11
unsigned int  Reserve8:1; //B12
unsigned int  Reserve9:1; //B13
unsigned int  Reserve10:1; //B14
unsigned int  TgtName:1; //B15名称
unsigned int  TgtAttr:1; //B16 属性
unsigned int  TgtType:1; //B17 类型
unsigned int  TgtKind:1; //B18 种类
unsigned int  TgtNation:1; //B19 国籍
unsigned int  TgtBoardID:1; //B20 机舷号
unsigned int  TgtPlatModel:1; //B21 平台号
unsigned int  TgtArmCivil:1; //B22 军民
unsigned int  Reserve11:1; //B23
unsigned int  Reserve12:1; //B24
unsigned int  Reserve13:1; //B25
unsigned int  Reserve14:1; //B26
unsigned int  Reserve15:1; //B27
unsigned int  Reserve16:1; //B28
unsigned int  Reserve17:1; //B29
unsigned int  Reserve18:1; //B30
unsigned int  Reserve19:1; //B31
};

struct SrcTgtTrk //原始航迹报文
{
short  nPlatID;//平台号
short  nInfSrcID;//信源号
int    batch;//批号
 
char  nInfSrcType; //信源类型 （1：普通雷达）
char nTgtBuildFlag;//目标生成方式
char  nTrkStatus; //航迹状态（1新航迹 2更新航迹 3撤消航迹 4丢失航迹）
char  nTrkDim; //航迹维数（1三坐标 2距离方位 3纯方位 4方位俯仰）
char  bDetectPt; //外推标记
char bTrkTrackOk;//航迹跟踪标记
char nFastCorr;//快速关联标记
char nReserve2;
 
long lTime;//目标更新时刻，单位：毫秒
long lRcvTime;//接收时刻， 单位：毫秒
char nTrkQuality;//航迹质量等级
char nRealInfoFlag;//情报类型
char nRdrWorkMode;//工作模式
char nWarningFlag;//告警标识
 
WdTgtTrk nWdTrk;//控制字
 
float dLon;//经度 单位：0.001度
float dLat;//纬度  单位：0.001度
float dAlt;//高度 单位：米
 
float  fDistance;//距离 单位：米
float  fBear;//方位  单位：度
float  fElev;//仰角  单位：度
 
float  fSpeed;//绝对水平速度 单位：米
float  fCourse; //绝对航向 单位：度
float  fvz; //z速度 单位：米/秒
 
float fReSpeed;//相对航速
float fReCourse;//相对航向
 
float  fErrDisX;//距离精度 单位：米
float  fErrBearY; //方位精度 单位：度
float  fErrElevZ; //仰角精度 单位：度
 
char nTgtNum;//目标数量 
char  nArmyCivil;//军民
char  nAttr;//属性
char  nType;//类型
short  nKind;//种类
short  nNation;//国籍
//short  nKind;//种类
short  nModel;//目标型号
short nReserve3;//备用
 
char nReserve4;
char nReserve5;
char nReserve6;
char nReserve7;
char nReserve8;
char nReserve9;
char nReserve10;
char nReserve11;
 
long nRadarT; //天线扫描周期 单位：0.001秒
};

} //namespace tools

#endif //TOOLS_OPERA_API_H_
