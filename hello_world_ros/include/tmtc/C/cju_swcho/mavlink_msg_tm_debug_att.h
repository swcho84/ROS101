#pragma once
// MESSAGE TM_DEBUG_ATT PACKING

#define MAVLINK_MSG_ID_TM_DEBUG_ATT 102

MAVPACKED(
typedef struct __mavlink_tm_debug_att_t {
 float roll; /*< */
 float pitch; /*< */
 float yaw; /*< */
}) mavlink_tm_debug_att_t;

#define MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN 12
#define MAVLINK_MSG_ID_TM_DEBUG_ATT_MIN_LEN 12
#define MAVLINK_MSG_ID_102_LEN 12
#define MAVLINK_MSG_ID_102_MIN_LEN 12

#define MAVLINK_MSG_ID_TM_DEBUG_ATT_CRC 5
#define MAVLINK_MSG_ID_102_CRC 5



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TM_DEBUG_ATT { \
    102, \
    "TM_DEBUG_ATT", \
    3, \
    {  { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_tm_debug_att_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_tm_debug_att_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_tm_debug_att_t, yaw) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TM_DEBUG_ATT { \
    "TM_DEBUG_ATT", \
    3, \
    {  { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_tm_debug_att_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_tm_debug_att_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_tm_debug_att_t, yaw) }, \
         } \
}
#endif

/**
 * @brief Pack a tm_debug_att message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param roll 
 * @param pitch 
 * @param yaw 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tm_debug_att_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float roll, float pitch, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN];
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pitch);
    _mav_put_float(buf, 8, yaw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN);
#else
    mavlink_tm_debug_att_t packet;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TM_DEBUG_ATT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TM_DEBUG_ATT_MIN_LEN, MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN, MAVLINK_MSG_ID_TM_DEBUG_ATT_CRC);
}

/**
 * @brief Pack a tm_debug_att message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param roll 
 * @param pitch 
 * @param yaw 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tm_debug_att_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float roll,float pitch,float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN];
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pitch);
    _mav_put_float(buf, 8, yaw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN);
#else
    mavlink_tm_debug_att_t packet;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TM_DEBUG_ATT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TM_DEBUG_ATT_MIN_LEN, MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN, MAVLINK_MSG_ID_TM_DEBUG_ATT_CRC);
}

/**
 * @brief Encode a tm_debug_att struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param tm_debug_att C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tm_debug_att_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_tm_debug_att_t* tm_debug_att)
{
    return mavlink_msg_tm_debug_att_pack(system_id, component_id, msg, tm_debug_att->roll, tm_debug_att->pitch, tm_debug_att->yaw);
}

/**
 * @brief Encode a tm_debug_att struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tm_debug_att C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tm_debug_att_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_tm_debug_att_t* tm_debug_att)
{
    return mavlink_msg_tm_debug_att_pack_chan(system_id, component_id, chan, msg, tm_debug_att->roll, tm_debug_att->pitch, tm_debug_att->yaw);
}

/**
 * @brief Send a tm_debug_att message
 * @param chan MAVLink channel to send the message
 *
 * @param roll 
 * @param pitch 
 * @param yaw 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_tm_debug_att_send(mavlink_channel_t chan, float roll, float pitch, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN];
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pitch);
    _mav_put_float(buf, 8, yaw);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TM_DEBUG_ATT, buf, MAVLINK_MSG_ID_TM_DEBUG_ATT_MIN_LEN, MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN, MAVLINK_MSG_ID_TM_DEBUG_ATT_CRC);
#else
    mavlink_tm_debug_att_t packet;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TM_DEBUG_ATT, (const char *)&packet, MAVLINK_MSG_ID_TM_DEBUG_ATT_MIN_LEN, MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN, MAVLINK_MSG_ID_TM_DEBUG_ATT_CRC);
#endif
}

/**
 * @brief Send a tm_debug_att message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_tm_debug_att_send_struct(mavlink_channel_t chan, const mavlink_tm_debug_att_t* tm_debug_att)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_tm_debug_att_send(chan, tm_debug_att->roll, tm_debug_att->pitch, tm_debug_att->yaw);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TM_DEBUG_ATT, (const char *)tm_debug_att, MAVLINK_MSG_ID_TM_DEBUG_ATT_MIN_LEN, MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN, MAVLINK_MSG_ID_TM_DEBUG_ATT_CRC);
#endif
}

#if MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_tm_debug_att_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float roll, float pitch, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pitch);
    _mav_put_float(buf, 8, yaw);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TM_DEBUG_ATT, buf, MAVLINK_MSG_ID_TM_DEBUG_ATT_MIN_LEN, MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN, MAVLINK_MSG_ID_TM_DEBUG_ATT_CRC);
#else
    mavlink_tm_debug_att_t *packet = (mavlink_tm_debug_att_t *)msgbuf;
    packet->roll = roll;
    packet->pitch = pitch;
    packet->yaw = yaw;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TM_DEBUG_ATT, (const char *)packet, MAVLINK_MSG_ID_TM_DEBUG_ATT_MIN_LEN, MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN, MAVLINK_MSG_ID_TM_DEBUG_ATT_CRC);
#endif
}
#endif

#endif

// MESSAGE TM_DEBUG_ATT UNPACKING


/**
 * @brief Get field roll from tm_debug_att message
 *
 * @return 
 */
static inline float mavlink_msg_tm_debug_att_get_roll(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field pitch from tm_debug_att message
 *
 * @return 
 */
static inline float mavlink_msg_tm_debug_att_get_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field yaw from tm_debug_att message
 *
 * @return 
 */
static inline float mavlink_msg_tm_debug_att_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a tm_debug_att message into a struct
 *
 * @param msg The message to decode
 * @param tm_debug_att C-struct to decode the message contents into
 */
static inline void mavlink_msg_tm_debug_att_decode(const mavlink_message_t* msg, mavlink_tm_debug_att_t* tm_debug_att)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    tm_debug_att->roll = mavlink_msg_tm_debug_att_get_roll(msg);
    tm_debug_att->pitch = mavlink_msg_tm_debug_att_get_pitch(msg);
    tm_debug_att->yaw = mavlink_msg_tm_debug_att_get_yaw(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN? msg->len : MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN;
        memset(tm_debug_att, 0, MAVLINK_MSG_ID_TM_DEBUG_ATT_LEN);
    memcpy(tm_debug_att, _MAV_PAYLOAD(msg), len);
#endif
}
