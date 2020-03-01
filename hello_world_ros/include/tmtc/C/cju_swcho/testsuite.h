/** @file
 *    @brief MAVLink comm protocol testsuite generated from cju_swcho.xml
 *    @see http://qgroundcontrol.org/mavlink/
 */
#pragma once
#ifndef CJU_SWCHO_TESTSUITE_H
#define CJU_SWCHO_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_cju_swcho(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

    mavlink_test_cju_swcho(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_tm_debug_time(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TM_DEBUG_TIME >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_tm_debug_time_t packet_in = {
        123.0
    };
    mavlink_tm_debug_time_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time = packet_in.time;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TM_DEBUG_TIME_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TM_DEBUG_TIME_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tm_debug_time_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_tm_debug_time_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tm_debug_time_pack(system_id, component_id, &msg , packet1.time );
    mavlink_msg_tm_debug_time_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tm_debug_time_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.time );
    mavlink_msg_tm_debug_time_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_tm_debug_time_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tm_debug_time_send(MAVLINK_COMM_1 , packet1.time );
    mavlink_msg_tm_debug_time_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_tm_debug_att(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TM_DEBUG_ATT >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_tm_debug_att_t packet_in = {
        17.0,45.0,73.0
    };
    mavlink_tm_debug_att_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.roll = packet_in.roll;
        packet1.pitch = packet_in.pitch;
        packet1.yaw = packet_in.yaw;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TM_DEBUG_ATT_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TM_DEBUG_ATT_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tm_debug_att_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_tm_debug_att_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tm_debug_att_pack(system_id, component_id, &msg , packet1.roll , packet1.pitch , packet1.yaw );
    mavlink_msg_tm_debug_att_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tm_debug_att_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.roll , packet1.pitch , packet1.yaw );
    mavlink_msg_tm_debug_att_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_tm_debug_att_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_tm_debug_att_send(MAVLINK_COMM_1 , packet1.roll , packet1.pitch , packet1.yaw );
    mavlink_msg_tm_debug_att_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_cju_swcho(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_tm_debug_time(system_id, component_id, last_msg);
    mavlink_test_tm_debug_att(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // CJU_SWCHO_TESTSUITE_H
