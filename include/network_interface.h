/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#ifndef _NETWORK_INTERFACE_H_
#define _NETWORK_INTERFACE_H_

/** \def MAX_IF_NAME_SIZE
    \brief Size of a network interface's name string.
    Defines the maximum size of a network interface's name.
    Includes space for the null character at the end of the string.
*/
#define MAX_IF_NAME_SIZE     16
/** \def MAX_IP_ADDR_SIZE
    \brief Size of a network IP Address string.
    Defines the maximum size of a network IP Address with the format
    "xxx.xxx.xxx.xxx" Includes space for the null character at the end
    of the string.
*/
#define MAX_IP_ADDR_SIZE     16
/** \def MAX_BRIDGE_NAME_SIZE
    \brief Size of a network bridge name string.
    Defines the maximum size of a network bridge's name.
    Includes space for the null character at the end of the string.
*/
#define MAX_BRIDGE_NAME_SIZE 16
/**
 * @brief Interface Type.
 *
 * Enumeration that defines the different types of network interfaces
 * supported by the Gateway Config table.
 */
typedef enum IF_TYPE
{
    OTHER_IF_TYPE =  0, /**< Some other network interface type. */
    BRIDGE_IF_TYPE, /**< Network bridge interface type. */
    ETH_IF_TYPE, /**< Network ethernet interface type. */
    GRE_IF_TYPE, /** Network GRE interface type. */
    VLAN_IF_TYPE /** Network VLAN interface type. */
} IF_TYPE;
/**
 * @brief Network Interface/Bridge Commands.
 *
 * Enumeration that defines the different network interface or bridge
 * commands supported by the Gateway Config table.
 */
typedef enum BR_CMD
{
    IF_UP_CMD =  0, /**< Network interface up command. */
    IF_DOWN_CMD, /**< Network interface down command. */
    IF_DELETE_CMD, /** Network interface delete command. */
    BR_REMOVE_CMD /** Network bridge removal command. */
} BR_CMD;
/**
 * @brief To add a transaction that has been initiated to the transaction store.
 *
 * @param[in] trans_uuid Transaction UUID unique identifier for the message/transaction.
 * @return boolean true indicating success, false indicating failure.
 */
 /**
 * @brief Gateway Config Table data.
 *
 * Structure that contains data related to the Gateway Config table.
 */
typedef struct Gateway_Config_Non_Ovs_Bridge
{
    char if_name[MAX_IF_NAME_SIZE]; /**< Network interface name. */
    char inet_addr[MAX_IP_ADDR_SIZE]; /**< Network IP Address. */
    char netmask[MAX_IP_ADDR_SIZE]; /**< Network netmask. */
    char gre_remote_inet_addr[MAX_IP_ADDR_SIZE]; /**< GRE remote IP Address. */
    char gre_local_inet_addr[MAX_IP_ADDR_SIZE]; /**< GRE local IP Address. */
    char parent_ifname[MAX_IF_NAME_SIZE]; /**< Parent network interface name. */
    char parent_bridge[MAX_BRIDGE_NAME_SIZE]; /**< Parent network bridge name. */
    int mtu; /**< MTU packet size in bytes. */
    int vlan_id; /**< VLAN ID. */
    IF_TYPE if_type; /**< Network interface type. */
    BR_CMD if_cmd; /**< Network interface/bridge command. */
} Gateway_Config_Non_Ovs_Bridge;
typedef Gateway_Config_Non_Ovs_Bridge Gateway_Config_t;
#endif
