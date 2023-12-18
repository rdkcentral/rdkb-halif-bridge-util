/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2023 RDK Management
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
/**
*
* @file bridge_util_hal.h
* @brief For Bridge Util Component: Bridge Utils OEM Layer
*/

#ifndef  _BRIDGE_UTIL_OEM_H
#define  _BRIDGE_UTIL_OEM_H

/**
 * @defgroup BRIDGE_UTIL_OEM BRIDGE UTIL OEM
 *
 * @defgroup BRIDGE_UTIL_OEM_DATA_TYPES BRIDGE UTIL OEM Data Types
 * @ingroup  BRIDGE_UTIL_OEM
 *
 * @defgroup BRIDGE_UTIL_OEM_APIS BRIDGE UTIL OEM APIs
 * @ingroup  BRIDGE_UTIL_OEM
 *
 **/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>

#include "OvsAgentApi.h"

/**
 * @addtogroup BRIDGE_UTIL_OEM_DATA_TYPES
 * @{
 */

#define BRIDGE_UTIL_LOG_FNAME "/rdklogs/logs/bridgeUtils.log" 						// **< Defines Log file path

#define GRE_HANDLER_SCRIPT "/etc/utopia/service.d/service_multinet/handle_gre.sh"	// **< Defines GRE handler script path

#define TOTAL_IFLIST_SIZE 	1024		// **< Defines Total Interface List size
#define BRIDGE_NAME_SIZE  	64			// **< Defines Bridge name size
#define IFACE_NAME_SIZE  	64			// **< Defines Interface name size

#define IFLIST_SIZE			256			// **< Defines 
#define MAX_LOG_BUFF_SIZE	1024		// **< Defines Interface List size
#define TIMESTAMP			64			// **< Defines Timestamp value

#define  INTERFACE_EXIST       0		// **< Defines value for Existing IF
#define  INTERFACE_NOT_EXIST  -1		// **< Defines value for non existing IF 

extern int DeviceMode; // router = 0, bridge = 2

extern int MocaIsolation_Val; 								// Global variable declaring MocaIsolation value

extern int need_wifi_gw_refresh;							// Global flag to indicate whether wifi gateway refresh needed
extern int need_switch_gw_refresh;							// Global flag to indicate whether switch gateway refresh needed
extern int syncMembers;										// Global variable for synchronisation purpose				
extern int BridgeOprInPropgress;							// Gloabal variable indicating bridge operation in progress
extern FILE *logFp;											// File pointer for logging
extern char log_buff[MAX_LOG_BUFF_SIZE];					// Global character buffer for log messages
extern char log_msg_wtime[MAX_LOG_BUFF_SIZE+TIMESTAMP];		// Global character buffer for log messages with timestamp
extern char primaryBridgeName[64];							// Global character buffer for primary bridge name
extern int PORT2ENABLE;										// Gloabal variable for status of port
extern int ethWanEnabled;									// Global variable for status of Ethernet WAN
extern char ethWanIfaceName[64];							// Global character buffer for Ethernet Wan Interface name	

extern struct tm *timeinfo;									// Pointer to struct to access time related information
extern time_t utc_time;										// Variable to store UTC time

/**
 * @brief bridge_util_log(fmt ...) 
 * 
 * This macro logs formatted message using the provided format string and optional arguments.
 * message is written to log file if it is open or else it's printed to standard output.
 */
#define bridge_util_log(fmt ...)    {\
				    		snprintf(log_buff, MAX_LOG_BUFF_SIZE-1,fmt);\
				    		if(logFp != NULL){ \
                                                snprintf(log_buff, MAX_LOG_BUFF_SIZE-1,fmt);\
                                                utc_time = time(NULL);\
                                                timeinfo = gmtime(&utc_time);\
                                                snprintf(log_msg_wtime, MAX_LOG_BUFF_SIZE+TIMESTAMP-1,"%04d-%02d-%02d %02d:%02d:%02d ::: %s",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec,log_buff);\
                                    		fprintf(logFp,"%s", log_msg_wtime);\
                                    		fflush(logFp);}\
                                 	}


/**********************************************************************
                ENUMERATION DEFINITIONS
**********************************************************************/

/**
 * @enum Config
 *
 * @brief Enumerates configuration options for BridgeUtils API's.
 * 
 * This enumeration defines different configuration options for a system includes 
 * setting for network type, security and management features 
 * each option is represented by a named constant with an associated integer.
 * 
 */
enum Config {
	PRIVATE_LAN = 1,					// **< Private Lan configuration
	HOME_SECURITY = 2,					// **< Home Security configuration
	HOTSPOT_2G = 3,						// **< Hotspot 2G configuration
	HOTSPOT_5G = 4,						// **< Hotspot 5G configuration
	LOST_N_FOUND = 6,					// **< Lost and Found configuration
	HOTSPOT_SECURE_2G = 7,				// **< Hotspot Secure 2G configuration
	HOTSPOT_SECURE_5G = 8,				// **< Hotspot Secure 5G configuration
	MOCA_ISOLATION = 9,					// **< MOCA Isolation configuration
	MESH_BACKHAUL = 10,					// **< Mesh Backhaul configuration
	ETH_BACKHAUL = 11,					// **< ETH Backhaul configuration
	MESH = 12,							// **< Mesh configuration
	MESH_WIFI_BACKHAUL_2G = 13,			// **< Mesh Wifi backhaul 2G configuration
	MESH_WIFI_BACKHAUL_5G = 14			// **< Mesh Wifi backhaul 5G configuration
#if defined  (WIFI_MANAGE_SUPPORTED)
        ,MANAGE_WIFI_BRIDGE = 17		// **< Manage Wifi bridge configuration
#endif /* WIFI_MANAGE_SUPPORTED*/
};


/**
 * @enum INTERFACE_TYPE
 *
 * @brief Enumeration of Interface types for BridgeUtils API's.
 * 
 * This enum defines different interface types such as Wired, wireless 
 * interfaces for use with BridgeUtils API's
 */
enum INTERFACE_TYPE {
    IF_BRIDGE_BRIDGEUTIL = 1, 	// **< Represents Bridge Interface for BridgeUtil
    IF_VLAN_BRIDGEUTIL = 2,		// **< Represents Virtual Local Area Network Interface for BridgeUtil
    IF_GRE_BRIDGEUTIL = 3,		// **< Represents Generic Routing Encapsulation Interface for BridgeUtil
    IF_MOCA_BRIDGEUTIL = 4,		// **< Represents Multimedia Over Coax Alliance Interface for BridgeUtil
    IF_WIFI_BRIDGEUTIL = 5,		// **< Represents Wifi Interface for BridgeUtil
    IF_ETH_BRIDGEUTIL = 6,		// **<Represents Ethernet Interface for BridgeUtil
    IF_OTHER_BRIDGEUTIL			// **<Other/Unspecified Interface type for BridgeUtil
};


/**
 * @enum BridgeOpr
 *
 * @brief Enumerates different Operations related to  BridgeUtils API's.
 */
enum BridgeOpr {
	DELETE_BRIDGE = 0, 	// **< Operation to Delete bridge
	CREATE_BRIDGE = 1	// **< Operation to Create bridge
};


/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/
/**
 * @struct bridgeDetails
 * @brief Details of bridge configuration
 * 
 * This structure holds the details of bridge configuration including Names of bridge, 
 * virtual parent interface, VLAN ID, List of ithernet IF and Interface associated with bridge. 
*/

typedef struct bridgeDetails {
	char bridgeName[BRIDGE_NAME_SIZE];				// **< Name of bridge
	char vlan_name[BRIDGE_NAME_SIZE];				// **< Name of Virtual Local Area Network 
    	char VirtualParentIfname[BRIDGE_NAME_SIZE];	// **< Name of Virtual parent interface
	int  vlanID;									// **< ID of Virtual Local Area Network 
	char ethIfList[IFLIST_SIZE];					// **< List of Ethernet Interface
	char MoCAIfList[IFLIST_SIZE];					// **< List of Multimedia Over Coax Alliance Interface
	char GreIfList[IFLIST_SIZE];					// **< List of GRE Interface
	char WiFiIfList[IFLIST_SIZE];					// **< List of Wifi Interface
}bridgeDetails;


/** @} */  //END OF GROUP BRIDGE_UTIL_OEM_DATA_TYPES

/**
 * @addtogroup BRIDGE_UTIL_OEM_APIS
 * @{
 */


/* updateBridgeInfo() function */
/**
* @brief Provides generic changes which needs to be configured after creating/updating/deleting bridge.
* @param[in] bridgeInfo - Pointer to bridgeDetails structure that will hold the complete bridge information.
*
* @param[in] ifNameToBeUpdated - Is a 64 byte character array where the interface is to be deleted and updated, applicable only during sync. It is vendor specific.
* @param[in] Opr - It is an enumeration that defines the different network interface or bridge. It provides information about operations whether the request creating/updating/deleting bridge.
* \n The range of acceptable values is 1 to 4 based on OVS_CMD enum type.
* 
* @param[in] type - It is an enumeration that defines the different types of interfaces and in case of sync delete the value is set to unknown/other.
* \n The range of acceptable values is 1 to 7 based on INTERFACE_TYPE enum type.
* 
* @return The status of the operation.
* @retval Returns 0 on success or -1 on negative error code.
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*/

extern int updateBridgeInfo(bridgeDetails *bridgeInfo, char* ifNameToBeUpdated, int Opr , int type);



/* checkIfExists() function */
/**
* @brief Check if interface is created.
* @param[in] iface_name - It is a 64 byte character array which represents the name of the interface. It is vendor specific.
* @return The status of the operation.
* @retval Returns 0 on success or -1 on negative error code.
*
*/
extern int checkIfExists(char* iface_name);


/* removeIfaceFromList() function */
/**
* @brief Remove interface from the list of interfaces.
* @param[in] str - It is a 64 byte character array which has the list of interfaces name. It is vendor specific.
* @param[in] sub - It is a 64 byte character array that represents the interface name that needs to be removed from the list. It is vendor specific.
* @return The status of the operation.
* @retval void
*
*/
extern void removeIfaceFromList(char *str, const char *sub);


/* checkIfExistsInBridge() function */
/**
* @brief Check if interface is attached to bridge.
* @param[in] iface_name - It is a 64 byte character array which represents the interface name. It is vendor specific.
* @param[in] bridge_name - It is a 64 byte character array which represents the bridge name.It is vendor specific.
* @return The status of the operation.
* @retval Returns  0 on success or -1 on negative error code.
*
*/
extern int checkIfExistsInBridge(char* iface_name, char *bridge_name);


/* HandlePreConfigVendor() function */
/**
* @brief Provides OEM/SOC specific changes which needs to be configured before creating/updating/deleting bridge.
* @param[in] bridgeInfo - Pointer to bridgeDetails structure that will hold the complte bridge information.
* 
* @param[in] InstanceNumber - It is an enumeration that defines the instance number for configuration.
* \n The range of acceptable values is 1 to 14 based on Config enum type.
* 
* @return The status of the operation.
* @retval Returns 0 on success or -1 on negative error code.
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*/
int HandlePreConfigVendor(bridgeDetails *bridgeInfo,int InstanceNumber);


/* HandlePostConfigVendor() function */
/**
* @brief Provides OEM/SOC specific changes which needs to be configured after creating/updating/deleting bridge.
* @param[in] bridgeInfo - Pointer to bridgeDetails structure that will hold the complete bridge information.
* 
* @param[in] Config - It is an enumeration that defines the instance number for configuration.
* \n The range of acceptable values is 1 to 14 based on Config enum type.
* 
* @return The status of the operation.
* @retval 0 on success or -1 on negative error code.
*
* @remark The caller is responsible for providing a valid memory location for the function arguments.
*/
int HandlePostConfigVendor(bridgeDetails *bridgeInfo,int Config);


/* getVendorIfaces() function */
/**
* @brief Provides vendor interface information for creating/updating/deleting bridge.
*
* @return The status of the operation.
* @retval vendor interface which is a 64 byte character array or NULL.
*
*/
char *getVendorIfaces();
/** @} */  //END OF BRIDGE_UTIL_OEM_APIS
#endif
