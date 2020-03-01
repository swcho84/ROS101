/** @file
 *  @brief MAVLink comm protocol generated from cju_swcho.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_CJU_SWCHO_H
#define MAVLINK_CJU_SWCHO_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_CJU_SWCHO.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 0

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 178, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_CJU_SWCHO

// ENUM DEFINITIONS


/** @brief  */
#ifndef HAVE_ENUM_MAV_SYSTEM
#define HAVE_ENUM_MAV_SYSTEM
typedef enum MAV_SYSTEM
{
   MAV_SYS_ID=1, /* System ID | */
   MAV_SYSTEM_ENUM_END=2, /*  | */
} MAV_SYSTEM;
#endif

/** @brief  */
#ifndef HAVE_ENUM_MAV_COMPONENT
#define HAVE_ENUM_MAV_COMPONENT
typedef enum MAV_COMPONENT
{
   MAV_COMP_ID_FMCU=1, /* Component ID of FMCU | */
   MAV_COMP_ID_SMCU=2, /* Component ID of SMCU | */
   MAV_COMP_ID_PMU=3, /* Component ID of Power Module | */
   MAV_COMP_ID_DPM=4, /* Component ID of Display Module | */
   MAV_COMP_ID_MSU_1=11, /* Component ID of Multi Sensor Unit 1 | */
   MAV_COMP_ID_MSU_2=12, /* Component ID of Multi Sensor Unit 2 | */
   MAV_COMP_ID_MSU_3=13, /* Component ID of Multi Sensor Unit 3 | */
   MAV_COMP_ID_MSU_4=14, /* Component ID of Multi Sensor Unit 4 | */
   MAV_COMP_ID_CAMERA=100, /*  | */
   MAV_COMP_ID_NL_LIDAR_ADAPTER=101, /*  | */
   MAV_COMP_ID_IMU=200, /*  | */
   MAV_COMP_ID_IMU_2=201, /*  | */
   MAV_COMP_ID_IMU_3=202, /*  | */
   MAV_COMP_ID_GPS=220, /*  | */
   MAV_COMPONENT_ENUM_END=221, /*  | */
} MAV_COMPONENT;
#endif

/** @brief Indicates the severity level, generally used for status messages to indicate their relative urgency. Based on RFC-5424 using expanded definitions at: http://www.kiwisyslog.com/kb/info:-syslog-message-levels/. */
#ifndef HAVE_ENUM_MAV_SEVERITY
#define HAVE_ENUM_MAV_SEVERITY
typedef enum MAV_SEVERITY
{
   MAV_SEVERITY_EMERGENCY=0, /* System is unusable. This is a "panic" condition. | */
   MAV_SEVERITY_ALERT=1, /* Action should be taken immediately. Indicates error in non-critical systems. | */
   MAV_SEVERITY_CRITICAL=2, /* Action must be taken immediately. Indicates failure in a primary system. | */
   MAV_SEVERITY_ERROR=3, /* Indicates an error in secondary/redundant systems. | */
   MAV_SEVERITY_WARNING=4, /* Indicates about a possible future error if this is not resolved within a given timeframe. Example would be a low battery warning. | */
   MAV_SEVERITY_NOTICE=5, /* An unusual event has occured, though not an error condition. This should be investigated for the root cause. | */
   MAV_SEVERITY_INFO=6, /* Normal operational messages. Useful for logging. No action is required for these messages. | */
   MAV_SEVERITY_DEBUG=7, /* Useful non-operational messages that can assist in debugging. These should not occur during normal operation. | */
   MAV_SEVERITY_ENUM_END=8, /*  | */
} MAV_SEVERITY;
#endif

/** @brief result from a mavlink command */
#ifndef HAVE_ENUM_MAV_RESULT
#define HAVE_ENUM_MAV_RESULT
typedef enum MAV_RESULT
{
   MAV_RESULT_ACCEPTED=0, /* Command ACCEPTED and EXECUTED | */
   MAV_RESULT_TEMPORARILY_REJECTED=1, /* Command TEMPORARY REJECTED/DENIED | */
   MAV_RESULT_UNSUPPORTED=3, /* Command UNKNOWN/UNSUPPORTED | */
   MAV_RESULT_FAILED=4, /* Command executed, but failed | */
   MAV_RESULT_ENUM_END=5, /*  | */
} MAV_RESULT;
#endif

/** @brief Sensor board mode */
#ifndef HAVE_ENUM_MAV_VALIDITY
#define HAVE_ENUM_MAV_VALIDITY
typedef enum MAV_VALIDITY
{
   MAV_VALIDITY_NOT_UPDATED=0, /* Not updated yet | */
   MAV_VALIDITY_VALID=1, /* Value has been updated, but not checked yet | */
   MAV_VALIDITY_UPDATED=2, /* VALID. User can use data | */
   MAV_VALIDITY_INVALID=3, /* INVALID. Don't use data | */
   MAV_VALIDITY_USED=4, /* Already used in calulcation | */
   MAV_VALIDITY_ENUM_END=5, /*  | */
} MAV_VALIDITY;
#endif

/** @brief Fmcu operation mode for state machine */
#ifndef HAVE_ENUM_MAV_FMCU_OP_MODE
#define HAVE_ENUM_MAV_FMCU_OP_MODE
typedef enum MAV_FMCU_OP_MODE
{
   OP_INIT=0, /* FMCU initialize mode | */
   OP_GUI=1, /* FMCU GUI connected mode | */
   OP_FLIGHT=2, /* FMCU flight mode | */
   MAV_FMCU_OP_MODE_ENUM_END=3, /*  | */
} MAV_FMCU_OP_MODE;
#endif

/** @brief Fmcu flight mode */
#ifndef HAVE_ENUM_MAV_FMCU_FLIGHT_MODE
#define HAVE_ENUM_MAV_FMCU_FLIGHT_MODE
typedef enum MAV_FMCU_FLIGHT_MODE
{
   FLIGHT_MODE_INIT=0, /* Flight initialize mode | */
   FLIGHT_MODE_MANUAL=1, /* Manual flight mode | */
   FLIGHT_MODE_ATTI=2, /* ATTI flight mode | */
   FLIGHT_MODE_GP=3, /* GP flight mode | */
   FLIGHT_MODE_FAILSAFE=4, /* Failsafe mode | */
   FLIGHT_MODE_RETURNHOME=5, /* Returnhome mode | */
   FLIGHT_MODE_AUTO=6, /* Auto flight mode | */
   MAV_FMCU_FLIGHT_MODE_ENUM_END=7, /*  | */
} MAV_FMCU_FLIGHT_MODE;
#endif

/** @brief Flight controller state */
#ifndef HAVE_ENUM_MAV_FMCU_STATE
#define HAVE_ENUM_MAV_FMCU_STATE
typedef enum MAV_FMCU_STATE
{
   STATE_DISARMED=0, /*  | */
   STATE_ARMED=1, /*  | */
   STATE_TAKEOFF=2, /*  | */
   STATE_FLYING=3, /*  | */
   MAV_FMCU_STATE_ENUM_END=4, /*  | */
} MAV_FMCU_STATE;
#endif

/** @brief Sensor board mode */
#ifndef HAVE_ENUM_MAV_SMCU_MODE
#define HAVE_ENUM_MAV_SMCU_MODE
typedef enum MAV_SMCU_MODE
{
   MAV_SMCU_MODE_INIT=0, /* SMCU Initialize mode | */
   MAV_SMCU_MODE_GYRO_CAL=1, /* Calibration mode for gyroscope | */
   MAV_SMCU_MODE_ACC_CAL=2, /* Calibration mode for accelerometer | */
   MAV_SMCU_MODE_MAG_CAL=3, /* Calibration mode for magnetormeter | */
   MAV_SMCU_MODE_RUN=4, /* SMCU Run moder | */
   MAV_SMCU_MODE_ENUM_END=5, /*  | */
} MAV_SMCU_MODE;
#endif

/** @brief Sensor board mode */
#ifndef HAVE_ENUM_MAV_SMCU_INIT_MODE
#define HAVE_ENUM_MAV_SMCU_INIT_MODE
typedef enum MAV_SMCU_INIT_MODE
{
   MAV_SMCU_INIT_MODE_PARAM=0, /*  | */
   MAV_SMCU_INIT_MODE_IMU=1, /*  | */
   MAV_SMCU_INIT_MODE_GPS=2, /*  | */
   MAV_SMCU_INIT_MODE_PRES=3, /*  | */
   MAV_SMCU_INIT_MODE_ACC_BIAS=4, /*  | */
   MAV_SMCU_INIT_MODE_EKF=5, /*  | */
   MAV_SMCU_INIT_MODE_ENUM_END=6, /*  | */
} MAV_SMCU_INIT_MODE;
#endif

/** @brief GPS fix status */
#ifndef HAVE_ENUM_MAV_GPS_FIX
#define HAVE_ENUM_MAV_GPS_FIX
typedef enum MAV_GPS_FIX
{
   MAV_GPS_NO_GPS=0, /*  | */
   MAV_GPS_NO_FIX=1, /*  | */
   MAV_GPS_3D_FIX=3, /*  | */
   MAV_GPS_DGPS=4, /*  | */
   MAV_GPS_RTK_FIX=5, /*  | */
   MAV_GPS_RTK_FLOAT=6, /*  | */
   MAV_GPS_FIX_ENUM_END=7, /*  | */
} MAV_GPS_FIX;
#endif

/** @brief  */
#ifndef HAVE_ENUM_MAV_FC_GAIN
#define HAVE_ENUM_MAV_FC_GAIN
typedef enum MAV_FC_GAIN
{
   FC_GAIN_ROLL_P=0, /* Proportional Gain of Roll | */
   FC_GAIN_ROLL_I=1, /* Integral Gain of Roll | */
   FC_GAIN_ROLL_D=2, /* Derivative Gain of Roll | */
   FC_GAIN_PITCH_P=3, /* Proportional Gain of Pitch | */
   FC_GAIN_PITCH_I=4, /* Integral Gain of Pitch | */
   FC_GAIN_PITCH_D=5, /* Derivative Gain of Pitch | */
   FC_GAIN_R_P=6, /* Proportional Gain of r | */
   FC_GAIN_R_I=7, /* Integral Gain of r | */
   FC_GAIN_MANUAL_YAW_P=8, /* Proportional Gain of Manual Yaw | */
   FC_GAIN_MANUAL_YAW_I=9, /* Integral Gain of Manual Yaw | */
   FC_GAIN_MANUAL_YAW_D=10, /* Derivative gain of Manual Yaw | */
   FC_GAIN_ATT_CMD_LIMIT=11, /* Proportional gain of altitude | */
   FC_GAIN_EULER_I_LIMIT=12, /*  | */
   FC_GAIN_ALT_P=13, /* Proportional gain of altitude | */
   FC_GAIN_ALT_I=14, /* Integral gain of altitude | */
   FC_GAIN_ALT_D=15, /* Derivative gain of altitude | */
   FC_GAIN_ALT_I_LARGE=16, /* Integral gain of altitude for take off | */
   FC_GAIN_ALT_CVT=17, /* Altitude error to convert command | */
   FC_GAIN_ALT_CVT_D=18, /* Altitude error to convert command | */
   FC_GAIN_U_P=19, /* Proportional gain of body x velocity | */
   FC_GAIN_U_I=20, /* Integral gain of body x velocity | */
   FC_GAIN_U_D=21, /* Derivative gain of body x velocity | */
   FC_GAIN_V_P=22, /* Proportional gain of body y velocity | */
   FC_GAIN_V_I=23, /* Integral gain of body y velocity | */
   FC_GAIN_V_D=24, /* Derivative gain of body y velocity | */
   FC_GAIN_OUTER_P=25, /* Outer gain, proportional | */
   FC_GAIN_OUTER_I=26, /* Outer gain, integral | */
   FC_GAIN_OUTER_D=27, /* Outer gain, derivative | */
   FC_GAIN_DECEL_I=28, /* Deceleration I gain | */
   FC_GAIN_DECEL_P_COMPENSATOR=29, /* Deceleration P gain compensator | */
   FC_GAIN_DECEL_CMD_FILTER=30, /* Deceleration euler cmd rate of change limit | */
   FC_GAIN_LPF_W=31, /* Low Pass Filter Frequency of W | */
   FC_GAIN_LPF_UV=32, /* Low Pass Filter Frequency of UV | */
   FC_GAIN_LPF_PQ=33, /* Low Pass Filter Frequency of p and q | */
   FC_GAIN_LPF_EULER=34, /* Low Pass Filter Frequency of Euler Angle | */
   FC_GAIN_LPF_GPS=35, /* Low Pass Filter Frequency of Euler Angle Command | */
   FC_GAIN_LPF_ALT=36, /* Low Pass Filter Frequency of ALT | */
   FC_GAIN_LPF_VEL_CMD=37, /* Low Pass Filter Frequency of Velocity Command | */
   FC_GAIN_R_LIMIT=38, /* YAW Rate limit | */
   FC_GAIN_ALT_P_POWER=39, /* ALT pterm cvt power | */
   FC_GAIN_UV_F=40, /* Feed-forward gain of UV | */
   FC_GAIN_AUTO_YAW_P=41, /* Proportional Gain of Auto Yaw | */
   FC_GAIN_AUTO_YAW_I=42, /* Integral Gain of Auto Yaw | */
   FC_GAIN_AUTO_YAW_D=43, /* Derivative gain of Auto Yaw | */
   FC_GAIN_AUTO_VEL_X_P=44, /* Proportional Gain of Velocity X | */
   FC_GAIN_AUTO_VEL_X_I=45, /* Integral Gain of Auto Velocity X | */
   FC_GAIN_AUTO_VEL_X_D=46, /* Derivative gain of Auto Velocity X | */
   FC_GAIN_AUTO_VEL_Y_P=47, /* Proportional Gain of Velocity Y | */
   FC_GAIN_AUTO_VEL_Y_I=48, /* Integral Gain of Auto Velocity Y | */
   FC_GAIN_AUTO_VEL_Y_D=49, /* Derivative gain of Auto Velocity Y | */
   FC_GAIN_RESERVED_1=50, /* Reserved gain 1 | */
   FC_GAIN_RESERVED_2=51, /* Reserved gain 2 | */
   FC_GAIN_RESERVED_3=52, /* Reserved gain 3 | */
   FC_GAIN_RESERVED_4=53, /* Reserved gain 4 | */
   FC_GAIN_RESERVED_5=54, /* Reserved gain 5 | */
   FC_GAIN_RESERVED_6=55, /* Reserved gain 6 | */
   FC_GAIN_RESERVED_7=56, /* Reserved gain 7 | */
   FC_GAIN_RESERVED_8=57, /* Reserved gain 8 | */
   FC_GAIN_RESERVED_9=58, /* Reserved gain 9 | */
   FC_GAIN_RESERVED_10=59, /* Reserved gain 10 | */
   FC_GAIN_RESERVED_11=60, /* Reserved gain 11 | */
   FC_GAIN_RESERVED_12=61, /* Reserved gain 12 | */
   MAV_FC_GAIN_ENUM_END=62, /*  | */
} MAV_FC_GAIN;
#endif

/** @brief  */
#ifndef HAVE_ENUM_MAV_SMCU_PARAM
#define HAVE_ENUM_MAV_SMCU_PARAM
typedef enum MAV_SMCU_PARAM
{
   SC_PARAM_IMU_CASE_TO_BODY_R=0, /*  | */
   SC_PARAM_IMU_CASE_TO_BODY_P=1, /*  | */
   SC_PARAM_IMU_CASE_TO_BODY_Y=2, /*  | */
   SC_PARAM_GYRO_SENSOR_TO_CASE_R=3, /*  | */
   SC_PARAM_GYRO_SENSOR_TO_CASE_P=4, /*  | */
   SC_PARAM_GYRO_SENSOR_TO_CASE_Y=5, /*  | */
   SC_PARAM_GYRO_BIAS_X=6, /*  | */
   SC_PARAM_GYRO_BIAS_Y=7, /*  | */
   SC_PARAM_GYRO_BIAS_Z=8, /*  | */
   SC_PARAM_GYRO_CUT_OFF_REQ=9, /*  | */
   SC_PARAM_ACC_SENSOR_TO_CASE_X=10, /*  | */
   SC_PARAM_ACC_SENSOR_TO_CASE_Y=11, /*  | */
   SC_PARAM_ACC_SENSOR_TO_CASE_Z=12, /*  | */
   SC_PARAM_ACC_BIAS_X=13, /*  | */
   SC_PARAM_ACC_BIAS_Y=14, /*  | */
   SC_PARAM_ACC_BIAS_Z=15, /*  | */
   SC_PARAM_ACC_SF_X=16, /*  | */
   SC_PARAM_ACC_SF_Y=17, /*  | */
   SC_PARAM_ACC_SF_Z=18, /*  | */
   SC_PARAM_ACC_CUT_OFF_REQ=19, /*  | */
   SC_PARAM_MAG_SENSOR_TO_BODY_R=20, /*  | */
   SC_PARAM_MAG_SENSOR_TO_BODY_P=21, /*  | */
   SC_PARAM_MAG_SENSOR_TO_BODY_Y=22, /*  | */
   SC_PARAM_MAG_MAX_X=23, /*  | */
   SC_PARAM_MAG_MAX_Y=24, /*  | */
   SC_PARAM_MAG_MAX_Z=25, /*  | */
   SC_PARAM_MAG_MIN_X=26, /*  | */
   SC_PARAM_MAG_MIN_Y=27, /*  | */
   SC_PARAM_MAG_MIN_Z=28, /*  | */
   SC_PARAM_MAG_BIAS_X=29, /*  | */
   SC_PARAM_MAG_BIAS_Y=30, /*  | */
   SC_PARAM_MAG_BIAS_Z=31, /*  | */
   SC_PARAM_MAG_SF_X=32, /*  | */
   SC_PARAM_MAG_SF_Y=33, /*  | */
   SC_PARAM_MAG_SF_Z=34, /*  | */
   SC_PARAM_IMU_SENSOR_TO_CASE_R=35, /*  | */
   SC_PARAM_IMU_SENSOR_TO_CASE_P=36, /*  | */
   SC_PARAM_IMU_SENSOR_TO_CASE_Y=37, /*  | */
   SC_PARAM_GPS_MOUNT_OFFSET_X=38, /*  | */
   SC_PARAM_GPS_MOUNT_OFFSET_Y=39, /*  | */
   SC_PARAM_GPS_MOUNT_OFFSET_Z=40, /*  | */
   SC_PARAM_MAG_DECLINATION=41, /*  | */
   SC_PARAM_IMU_MOUNT_OFFSET_X=42, /*  | */
   SC_PARAM_IMU_MOUNT_OFFSET_Y=43, /*  | */
   SC_PARAM_IMU_MOUNT_OFFSET_Z=44, /*  | */
   SC_PARAM_EKF_GPS_SIGMA=45, /*  | */
   MAV_SMCU_PARAM_ENUM_END=46, /*  | */
} MAV_SMCU_PARAM;
#endif

/** @brief MC Mode */
#ifndef HAVE_ENUM_MC_MODE
#define HAVE_ENUM_MC_MODE
typedef enum MC_MODE
{
   MC_MODE_RC=0, /* RC mode | */
   MC_MODE_GUIDE=1, /* Guide mode | */
   MC_MODE_AUTO=2, /* Auto mode. MC control FC with mission | */
   MC_MODE_BOOT=3, /* Boot mode. Not all nodes are ready | */
   MC_MODE_SAFE_HOLD=255, /* Safe hold mode | */
   MC_MODE_ENUM_END=256, /*  | */
} MC_MODE;
#endif

/** @brief FC Guidance Mode */
#ifndef HAVE_ENUM_FC_AUTO_MODE
#define HAVE_ENUM_FC_AUTO_MODE
typedef enum FC_AUTO_MODE
{
   FC_AUTO_MODE_TAKE_OFF=0, /*  | */
   FC_AUTO_MODE_LANDING=1, /*  | */
   FC_AUTO_MODE_WAYPOINT=2, /*  | */
   FC_AUTO_MODE_RC_VEL_CTRL=3, /*  | */
   FC_AUTO_MODE_INSPECTION=4, /*  | */
   FC_AUTO_MODE_MC_VEL_CTRL=5, /*  | */
   FC_AUTO_MODE_ENUM_END=6, /*  | */
} FC_AUTO_MODE;
#endif

/** @brief  */
#ifndef HAVE_ENUM_FC_YCMD_TYPE
#define HAVE_ENUM_FC_YCMD_TYPE
typedef enum FC_YCMD_TYPE
{
   FC_YCMD_ANGLE_REL=0, /*  | */
   FC_YCMD_ANGLE_ABS=1, /*  | */
   FC_YCMD_RATE=2, /*  | */
   FC_YCMD_FOWARD=3, /*  | */
   FC_YCMD_TYPE_ENUM_END=4, /*  | */
} FC_YCMD_TYPE;
#endif

/** @brief  */
#ifndef HAVE_ENUM_MC_MISSION_EVENT
#define HAVE_ENUM_MC_MISSION_EVENT
typedef enum MC_MISSION_EVENT
{
   MISSION_STARTED=0, /*  | */
   MISSION_FINISHED=1, /*  | */
   MISSION_STOPPED_BY_USER=2, /*  | */
   MISSION_STOPPED_BY_SYSTEM=3, /*  | */
   MC_MISSION_EVENT_ENUM_END=4, /*  | */
} MC_MISSION_EVENT;
#endif

/** @brief  */
#ifndef HAVE_ENUM_MEM_BLOCK_TYPE
#define HAVE_ENUM_MEM_BLOCK_TYPE
typedef enum MEM_BLOCK_TYPE
{
   MBT_SYSTEM_MEMORY=0, /* MCU system memory including FLASH, REM. |Start address| Size|  */
   MBT_SDLOG=1, /* Log data at SDcard memory. |Start address| Size|  */
   MBT_JUMP_TO_BOOTLOADER=2, /* Request jump to bootloader area. |not used| not used|  */
   MBT_START_DFU=3, /* Start device firmware update. |End address| CRC value|  */
   MBT_ABORT_DFU=4, /* Abort device firmware update. |not used| not used|  */
   MBT_DFU_RESULT=5, /* DFU result. |Result code, 0:OK, 1:Erase fail, 2:PGM fail, 3:Verify fail, 4:Time out, 5:CRC error, 6:Size error| not used|  */
   MBT_SDLOG_ERASE_ALL=6, /* Erase all sdlog data. |not used| not used|  */
   MBT_SDLOG_RECOVERY=7, /* Log recovery. |not used| not used|  */
   MBT_SDLOG_START=8, /* Start log. |not used| not used|  */
   MBT_SDLOG_STOP=9, /* Stop log. |not used| not used|  */
   MBT_SYSTEM_RESET=10, /* System reset. |not used| not used|  */
   MBT_HEARTBEAT_PERIOD=11, /* Set heartbeat period |0:disable, others:period in milliseconds| not used|  */
   MBT_GET_HW_ERROR=12, /* Get hardware error counts |not used| not used|  */
   MBT_CLEAR_HW_ERROR=13, /* Clear hardware error counts |not used| not used|  */
   MBT_JUMP_TO_APP=14, /* Request jump to app area. |not used| not used|  */
   MEM_BLOCK_TYPE_ENUM_END=15, /*  | */
} MEM_BLOCK_TYPE;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_tm_debug_time.h"
#include "./mavlink_msg_tm_debug_att.h"

// base include


#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 0

#if MAVLINK_THIS_XML_IDX == MAVLINK_PRIMARY_XML_IDX
# define MAVLINK_MESSAGE_INFO {{"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, MAVLINK_MESSAGE_INFO_TM_DEBUG_TIME, MAVLINK_MESSAGE_INFO_TM_DEBUG_ATT, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}, {"EMPTY",0,{{"","",MAVLINK_TYPE_CHAR,0,0,0}}}}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_CJU_SWCHO_H
