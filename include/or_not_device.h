//
// Created by sworddestiny on 17-12-7.
//

#ifndef LOGICMONITOR_OR_NOT_DEVICE_H
#define LOGICMONITOR_OR_NOT_DEVICE_H

#include "logic_device.h"
#include "iface.h"

namespace lm {

	/**
	 * 或非门
	 */
	class or_not_device :public lgc_dev{
	public:
		or_not_device(const string &name, input *a, input *b);

		signal get_signal(output *out_iface) override;

		void update_signal() override;

	public:
		input *getA() const;

		void setA(input *a);

		input *getB() const;

		void setB(input *b);

		output *getO() const;

		void setO(output *o);

		~or_not_device() override ;

	private:
		input *a;
		input *b;

		output *o; // o = ~(a|b)
	};

	typedef or_not_device nor;
}

#endif //LOGICMONITOR_OR_NOT_DEVICE_H
