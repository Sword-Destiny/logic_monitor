//
// Created by sworddestiny on 17-12-7.
//

#ifndef LOGICMONITOR_AND_NOT_DEVICE_H
#define LOGICMONITOR_AND_NOT_DEVICE_H

#include "iface.h"
#include "logic_device.h"

namespace lm {
	/**
	 * 与非门
	 * o = ~(a&b)
	 */
	typedef class and_not_device : public lgc_dev {
	public:
		and_not_device(const string &name, input *a, input *b);

		signal get_signal(output *out_iface) override;

		void update_signal() override;

	public:
		input *getA() const;

		void setA(input *a);

		input *getB() const;

		void setB(input *b);

		output *getO() const;

		void setO(output *o);

		~and_not_device() override;

	private:
		input *a;
		input *b;

		output *o;
	} nand, nand2;

}


#endif //LOGICMONITOR_AND_NOT_DEVICE_H
