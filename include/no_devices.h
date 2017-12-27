//
// Created by sworddestiny on 17-12-8.
//

#ifndef LOGICMONITOR_NO_DEVICES_H
#define LOGICMONITOR_NO_DEVICES_H

#include "iface.h"
#include "logic_device.h"

namespace lm {

	/**
	 * 非门
	 */
	class no_device : public lgc_dev {
	public:

		no_device(const string &name, input *input);

		~no_device() override;

		signal get_signal(output *out_iface) override;

		void update_signal() override;

		input *getI() const;

		void setI(input *i);

		output *getO() const;

		void setO(output *o);

	private:
		input *i;
		output *o;

	};

	typedef no_device nodev;
}

#endif //LOGICMONITOR_NO_DEVICES_H
