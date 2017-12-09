//
// Created by sworddestiny on 17-12-8.
//

#ifndef LOGICMONITOR_AND_DEVICE_H
#define LOGICMONITOR_AND_DEVICE_H


#include "iface.h"
#include "logic_device.h"
#include "and_not_device.h"
#include "not_device.h"

namespace lm {
	/**
	 * 与门
	 * o = ~(~(a&b))
	 */
	typedef class and_device : public lgc_dev {
	public:

		and_device(const string &name, input *a, input *b);

		signal get_signal(output *out_iface) override;

		void update_signal() override;

		~and_device() override;

	private:
		input *a;
		input *b;

		nand2 dnand; // dnand = ~(a&b)
		output onand;
		link lnand;
		nd dn; // ~(dnand)

		output *o;
	public:
		input *getA() const;

		void setA(input *a);

		input *getB() const;

		void setB(input *b);

		output *getO() const;

		void setO(output *o);
	} and2;

}

#endif //LOGICMONITOR_AND_DEVICE_H
