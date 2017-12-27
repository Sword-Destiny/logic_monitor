//
// Created by sworddestiny on 17-12-6.
//

#ifndef LOGICMONITOR_COMMON_H
#define LOGICMONITOR_COMMON_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <numeric>
#include <algorithm>

using namespace std;

#define lm logic_monitor

#define SIGNAL_ZERO false
#define SIGNAL_ONE  true

namespace lm {

	typedef bool signal;

	/**
	 * 端口类型
	 */
	enum iface_type {
		CLOCK_IFACE = 0,
		LINK_IFACE = 1,
		OUTPUT_IFACE = 2,
		INPUT_IFACE = 3,
	};

	typedef long logic_time;

	typedef long uuid;

	uuid get_uuid();

}

#endif //LOGICMONITOR_COMMON_H
