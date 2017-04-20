/*
 * S2E_Packet.h
 *
 *  Created on: 2014. 3. 20.
 *      Author: Raphael
 */

#ifndef __CONFIGDATA_H__
#define __CONFIGDATA_H__

#include <stdint.h>
#include "wizchip_conf.h"

#define TCP_CLIENT_MODE		0
#define TCP_SERVER_MODE		1
#define TCP_MIXED_MODE		2
#define UDP_MODE			3

enum baud {
	baud_300 = 300,
	baud_600 = 600,
	baud_1200 = 1200,
	baud_2400 = 2400,
	baud_4800 = 4800,
	baud_9600 = 9600,
	baud_19200 = 19200,
	baud_38400 = 38400,
	baud_57600 = 57600,
	baud_115200 = 115200,
	baud_230400 = 230400
};

enum word_len {
	word_len7 = 7,
	word_len8 = 8,
	word_len9 = 9
};

enum stop_bit {
	stop_bit1 = 1,
	stop_bit2 = 2
};

enum parity {
	parity_none = 0,
	parity_odd = 1,
	parity_even = 2
};

enum flow_ctrl {
	flow_none = 0,
	flow_rts_cts = 1,
	flow_rs422 = 2,
	flow_rs485 = 3,
};

enum net_state {
	net_disconnect = 0,
	net_connect = 1,
	net_udp = 2
};

struct __network_info_common {
	uint8_t mac[6];
	uint8_t local_ip[4];
	uint8_t gateway[4];
	uint8_t subnet[4];
} __attribute__((packed));

struct __network_info {
	uint8_t working_mode;
	uint8_t state;	// ?�뜝�럩�룇???�뜝��源� TCP??野껋럩�뒭 Not Connected, Connected, UDP??野껋럩�뒭 UDP
	uint8_t remote_ip[4];			// Must Be 4byte Alignment
	uint16_t local_port;
	uint16_t remote_port;

	uint16_t inactivity;
	uint16_t reconnection;

	uint16_t packing_time;	// 0~65535
	uint8_t packing_size;		// 0~255
	uint8_t packing_delimiter[4];
	uint8_t packing_delimiter_length;	// 0~4
	uint8_t packing_data_appendix;	// 0~2(�뤃�됲뀋?�뜝�럡�돱筌욑옙 ?�뜝�럩�꽊, �뤃�됲뀋??+1獄쏅뗄�뵠??繹먮슪�삕? ?�뜝�럩�꽊, �뤃�됲뀋??+2獄쏅뗄�뵠??繹먮슪�삕? ?�뜝�럩�꽊)
} __attribute__((packed));

struct __serial_info {
	uint32_t baud_rate;	// �뜝?Baud Rate癰귢쑬以� �굜遺얜굡 �겫占�??
	uint8_t data_bits;	// 7, 8, 9 and more?
	uint8_t parity;			// None, odd, even
	uint8_t stop_bits;	// 1, 1.5, 2
	uint8_t flow_control;	// None, RTS/CTS, XON/XOFF, DST/DTR, RTS Only for RS422/485
} __attribute__((packed));

struct __options {
	char pw_setting[10];
	char pw_connect[10];

	uint8_t dhcp_use;

	uint8_t dns_use;
	uint8_t dns_server_ip[4];
	char dns_domain_name[50];

	uint8_t serial_command;			// Serial Command Mode ?�뜝�럩�뒠 ?�뜝�룞�삕?
	uint8_t serial_trigger[3];		// Serial Command Mode 筌욊쑴�뿯???�뜝��釉� Trigger �굜遺얜굡
} __attribute__((packed));

typedef struct __S2E_Packet {
	uint16_t packet_size;
	uint8_t module_type[3]; // 筌뤴뫀諭�??�넫�굝履잒퉪袁⑥쨮 �굜遺얜굡�뜝?�겫占�?�뜝��釉��뜝??�뜝�룞�삕? ?�뜝�럩�뒠?�뜝�럥�뼄.
	uint8_t module_name[25];
	uint8_t fw_ver[3];			// 10筌욊쑴�땾. Major Version . Minor Version . Maintenance Version 甕곌쑴�읈?�뜝�럥以� ?�뜝�럥�룭
	struct __network_info_common network_info_common;
	struct __network_info network_info[1];	// ?�뜝�럥�쑎�뜝??�뜝�럩�룇???�뜝�럩�뒠??野껋럩�뒭
	struct __serial_info serial_info[1];	// ?�뜝�럥�쑎�뜝??�뜝�럥�봺?�뜝�럩�뱽 ?�뜝�럩�뒠??野껋럩�뒭
	struct __options options;
} __attribute__((packed)) S2E_Packet;


S2E_Packet* get_S2E_Packet_pointer();
void set_S2E_Packet_to_factory_value();
void load_S2E_Packet_from_storage();
void save_S2E_Packet_to_storage();
void get_S2E_Packet_value(void *dest, const void *src, uint16_t size);
void set_S2E_Packet_value(void *dest, const void *value, const uint16_t size);
void set_S2E_Packet(wiz_NetInfo *net);
void get_S2E_Packet(wiz_NetInfo *net);

void display_Net_Info();
void Mac_Conf();
void Net_Conf();
void set_dhcp_mode();
void set_static_mode();
void set_mac(uint8_t *mac);
// void check_mac_address();
uint8_t check_mac_address();

void erase_eeprom();

#endif /* S2E_PACKET_H_ */
