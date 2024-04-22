/*
 * StdTypes.h
 *
 *  Created on: Jan 19, 2024
 *      Author: praskumt
 */

#ifndef STDTYPES_H_
#define STDTYPES_H_

//Types
typedef char char_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
//typedef unsigned int uint32_t;
//typedef unsigned int long uint64_t;
//typedef int int32_t;
//typedef char int8_t;
typedef int bool_t;
//typedef int size_t;

//Types
typedef signed int int_t;
typedef unsigned int uint_t;
//typedef uint32_t     TickType_t;
//typedef TickType_t systime_t;

/**
 * @brief Duplex mode
 **/

typedef enum
{
   NIC_UNKNOWN_DUPLEX_MODE = 0,
   NIC_HALF_DUPLEX_MODE    = 1,
   NIC_FULL_DUPLEX_MODE    = 2
} NicDuplexMode;

/**
 * @brief Link state
 **/

typedef enum
{
   NIC_LINK_STATE_DOWN = 0,
   NIC_LINK_STATE_UP   = 1,
   NIC_LINK_STATE_AUTO = 2
} NicLinkState;


/**
 * @brief Link speed
 **/

typedef enum
{
   NIC_LINK_SPEED_UNKNOWN = 0,
   NIC_LINK_SPEED_10MBPS  = 10000000,
   NIC_LINK_SPEED_100MBPS = 100000000,
   NIC_LINK_SPEED_1GBPS   = 1000000000
} NicLinkSpeed;









#endif /* STDTYPES_H_ */
