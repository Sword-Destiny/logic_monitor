//
// Created by sworddestiny on 17-12-6.
//

#ifndef LOGICMONITOR_NOT_DEVICE_H
#define LOGICMONITOR_NOT_DEVICE_H

#include "iface.h"
#include "logic_device.h"

namespace lm {

	/**
	 * 非门
	 */
	class not_device : public lgc_dev {
	public:

		not_device(const string &name, input *input);

		~not_device() override;

		signal get_signal(output *out_iface) override;

		void update_signal() override;

		input *getInput() const;

		void setInput(input *input);

		output *getOutput() const;

		void setOutput(output *o);

	private:
		input *i;
		output *o; // o = ~i

	};

	typedef not_device nd;
}


#endif //LOGICMONITOR_NOT_DEVICE_H
