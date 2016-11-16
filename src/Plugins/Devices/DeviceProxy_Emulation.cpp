/*
 * This file is not part of original USBProxy.
 * This DeviceProxy doesn't actually do nothing. It doesn't communicate with a real device (like libUSB one).
 * What we do is redirect all requests and packets to the Attack class, which knows how to parse them.
 *
 * Author: Skazza
 */

#include "DeviceProxy_Emulation.h"

DeviceProxy_Emulation::DeviceProxy_Emulation(ConfigParser * cfg) {
	this->cfg = cfg;
}

DeviceProxy_Emulation::~DeviceProxy_Emulation() {}

int DeviceProxy_Emulation::connect() {
	connected = true;
	this->initAttack();
	return 0;
}

int DeviceProxy_Emulation::connect(int timeout) {
	connected = true;
	this->initAttack();
	return 0;
}

void DeviceProxy_Emulation::disconnect() {
	connected = false;
}

void DeviceProxy_Emulation::reset() {

}

bool DeviceProxy_Emulation::is_connected() {
	return connected;
}

int DeviceProxy_Emulation::control_request(const usb_ctrlrequest *setup_packet, int *nbytes, __u8* dataptr) {
	return this->attack->parseSetupRequest(*setup_packet, nbytes, dataptr);
}

int DeviceProxy_Emulation::control_request(const usb_ctrlrequest *setup_packet, int *nbytes, __u8* dataptr,int timeout) {
	return this->attack->parseSetupRequest(*setup_packet, nbytes, dataptr);
}

void DeviceProxy_Emulation::send_data(__u8 endpoint,__u8 attributes,__u16 maxPacketSize,__u8* dataptr,int length) {

}

void DeviceProxy_Emulation::receive_data(__u8 endpoint,__u8 attributes,__u16 maxPacketSize,__u8** dataptr, int* length) {
	/* Need an "AttackParser" to know what to do with received data? */
	*length = 0;
}

void DeviceProxy_Emulation::receive_data(__u8 endpoint,__u8 attributes,__u16 maxPacketSize,__u8** dataptr, int* length,int timeout) {
	/* Need an "AttackParser" to know what to do with received data? */
	*length = 0;
}

void DeviceProxy_Emulation::setConfig(Configuration* fs_cfg,Configuration* hs_cfg,bool hs) {

}

bool DeviceProxy_Emulation::is_highspeed() {
	return false;
}

void DeviceProxy_Emulation::set_endpoint_interface(__u8 endpoint, __u8 interface) {

}

void DeviceProxy_Emulation::claim_interface(__u8 interface) {

}

void DeviceProxy_Emulation::release_interface(__u8 interface) {

}

__u8 DeviceProxy_Emulation::get_address() {
	return 0;
}

/* We use a method because we load the Attack class to use from the config file. */
void DeviceProxy_Emulation::initAttack() {
	this->attack = AttackFactory::createInstance("keyboard");
	this->attack->setDevice(device);
}

static DeviceProxy_Emulation *proxy;

extern "C" {
	DeviceProxy * get_deviceproxy_plugin(ConfigParser *cfg) {
		proxy = new DeviceProxy_Emulation(cfg);
		return (DeviceProxy *) proxy;
	}

	void destroy_plugin() {
		delete proxy;
	}
}
