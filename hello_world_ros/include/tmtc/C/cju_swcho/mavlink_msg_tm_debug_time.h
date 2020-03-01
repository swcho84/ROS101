#pragma once
// MESSAGE TM_DEBUG_TIME PACKING

#define MAVLINK_MSG_ID_TM_DEBUG_TIME 101

MAVPACKED(
typedef struct __mavlink_tm_debug_time_t {
 double time; /*< */
}) mavlink_tm_debug_time_t;

#define MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN 8
#define MAVLINK_MSG_ID_TM_DEBUG_TIME_MIN_LEN 8
#define MAVLINK_MSG_ID_101_LEN 8
#define MAVLINK_MSG_ID_101_MIN_LEN 8

#define MAVLINK_MSG_ID_TM_DEBUG_TIME_CRC 178
#define MAVLINK_MSG_ID_101_CRC 178



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TM_DEBUG_TIME { \
    101, \
    "TM_DEBUG_TIME", \
    1, \
    {  { "time", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_tm_debug_time_t, time) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TM_DEBUG_TIME { \
    "TM_DEBUG_TIME", \
    1, \
    {  { "time", NULL, MAVLINK_TYPE_DOUBLE, 0, 0, offsetof(mavlink_tm_debug_time_t, time) }, \
         } \
}
#endif

/**
 * @brief Pack a tm_debug_time message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tm_debug_time_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               double time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN];
    _mav_put_double(buf, 0, time);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN);
#else
    mavlink_tm_debug_time_t packet;
    packet.time = time;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TM_DEBUG_TIME;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TM_DEBUG_TIME_MIN_LEN, MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN, MAVLINK_MSG_ID_TM_DEBUG_TIME_CRC);
}

/**
 * @brief Pack a tm_debug_time message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tm_debug_time_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   double time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN];
    _mav_put_double(buf, 0, time);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN);
#else
    mavlink_tm_debug_time_t packet;
    packet.time = time;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TM_DEBUG_TIME;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TM_DEBUG_TIME_MIN_LEN, MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN, MAVLINK_MSG_ID_TM_DEBUG_TIME_CRC);
}

/**
 * @brief Encode a tm_debug_time struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param tm_debug_time C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tm_debug_time_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_tm_debug_time_t* tm_debug_time)
{
    return mavlink_msg_tm_debug_time_pack(system_id, component_id, msg, tm_debug_time->time);
}

/**
 * @brief Encode a tm_debug_time struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tm_debug_time C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tm_debug_time_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_tm_debug_time_t* tm_debug_time)
{
    return mavlink_msg_tm_debug_time_pack_chan(system_id, component_id, chan, msg, tm_debug_time->time);
}

/**
 * @brief Send a tm_debug_time message
 * @param chan MAVLink channel to send the message
 *
 * @param time 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_tm_debug_time_send(mavlink_channel_t chan, double time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN];
    _mav_put_double(buf, 0, time);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TM_DEBUG_TIME, buf, MAVLINK_MSG_ID_TM_DEBUG_TIME_MIN_LEN, MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN, MAVLINK_MSG_ID_TM_DEBUG_TIME_CRC);
#else
    mavlink_tm_debug_time_t packet;
    packet.time = time;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TM_DEBUG_TIME, (const char *)&packet, MAVLINK_MSG_ID_TM_DEBUG_TIME_MIN_LEN, MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN, MAVLINK_MSG_ID_TM_DEBUG_TIME_CRC);
#endif
}

/**
 * @brief Send a tm_debug_time message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_tm_debug_time_send_struct(mavlink_channel_t chan, const mavlink_tm_debug_time_t* tm_debug_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_tm_debug_time_send(chan, tm_debug_time->time);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TM_DEBUG_TIME, (const char *)tm_debug_time, MAVLINK_MSG_ID_TM_DEBUG_TIME_MIN_LEN, MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN, MAVLINK_MSG_ID_TM_DEBUG_TIME_CRC);
#endif
}

#if MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_tm_debug_time_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  double time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_double(buf, 0, time);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TM_DEBUG_TIME, buf, MAVLINK_MSG_ID_TM_DEBUG_TIME_MIN_LEN, MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN, MAVLINK_MSG_ID_TM_DEBUG_TIME_CRC);
#else
    mavlink_tm_debug_time_t *packet = (mavlink_tm_debug_time_t *)msgbuf;
    packet->time = time;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TM_DEBUG_TIME, (const char *)packet, MAVLINK_MSG_ID_TM_DEBUG_TIME_MIN_LEN, MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN, MAVLINK_MSG_ID_TM_DEBUG_TIME_CRC);
#endif
}
#endif

#endif

// MESSAGE TM_DEBUG_TIME UNPACKING


/**
 * @brief Get field time from tm_debug_time message
 *
 * @return 
 */
static inline double mavlink_msg_tm_debug_time_get_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_double(msg,  0);
}

/**
 * @brief Decode a tm_debug_time message into a struct
 *
 * @param msg The message to decode
 * @param tm_debug_time C-struct to decode the message contents into
 */
static inline void mavlink_msg_tm_debug_time_decode(const mavlink_message_t* msg, mavlink_tm_debug_time_t* tm_debug_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    tm_debug_time->time = mavlink_msg_tm_debug_time_get_time(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN? msg->len : MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN;
        memset(tm_debug_time, 0, MAVLINK_MSG_ID_TM_DEBUG_TIME_LEN);
    memcpy(tm_debug_time, _MAV_PAYLOAD(msg), len);
#endif
}
