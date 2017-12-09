//
// Created by sworddestiny on 17-12-6.
//

#ifndef LOGICMONITOR_LOGIC_DEVICE_H
#define LOGICMONITOR_LOGIC_DEVICE_H

#include "iface.h"

namespace lm {
	class output_iface;
	typedef output_iface output;

	/**
	 * 逻辑器件
	 */
	class logic_device {
	public:
		explicit logic_device(const string &name);

		virtual ~logic_device();

		virtual signal get_signal(output *out_iface)=0;

		virtual void update_signal()=0;

		uuid getUid() const;

	private:
		uuid uid;
	protected:
		string name;
	};

	typedef logic_device lgc_dev;
}


#endif //LOGICMONITOR_LOGIC_DEVICE_H
