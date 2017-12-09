//
// Created by sworddestiny on 17-12-6.
//

#include "include/logic_device.h"
using namespace lm;

logic_device::logic_device(const string &name) : name(name), uid(get_uuid()) {}

uuid logic_device::getUid() const {
	return uid;
}

logic_device::~logic_device() = default;
