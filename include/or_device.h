//
// Created by sworddestiny on 17-12-8.
//

#ifndef LOGICMONITOR_OR_DEVICE_H
#define LOGICMONITOR_OR_DEVICE_H

#include "iface.h"
#include "logic_device.h"
#include "or_not_device.h"
#include "not_device.h"

namespace lm {
	/**
	 * 或门
	 * o = ～(～(a|b))
	 */
	typedef class or_device : public lgc_dev {
	public:

		or_device(const string &name, input *a, input *b);

		signal get_signal(output *out_iface) override;

		void update_signal() override;

		~or_device() override;

	private:
		input *a;
		input *b;

		nor dnor; // ~(a|b)
		output onor;
		link lnor;
		nd dn; // ~(~(a|b))

		output *o;
	public:
		input *getA() const;

		void setA(input *a);

		input *getB() const;

		void setB(input *b);

		output *getO() const;

		void setO(output *o);
	} or2;

}

#endif //LOGICMONITOR_OR_DEVICE_H
