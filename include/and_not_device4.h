//
// Created by sworddestiny on 17-12-7.
//

#ifndef LOGICMONITOR_AND_NOT_DEVICE4_H
#define LOGICMONITOR_AND_NOT_DEVICE4_H

#include "logic_device.h"
#include "iface.h"

namespace lm {

	/**
	 * 4输入与非门
	 */
	typedef class and_not_device4 : public lgc_dev {
	public:
		and_not_device4(const string &name, input *a, input *b, input *c, input *d);

		signal get_signal(output *out_iface) override;

		void update_signal() override;

	public:
		input *getA() const;

		void setA(input *a);

		input *getB() const;

		void setB(input *b);

		input *getC() const;

		void setC(input *c);

		input *getD() const;

		void setD(input *d);

		output *getO() const;

		void setO(output *o);

		~and_not_device4() override;

	private:
		input *a;
		input *b;
		input *c;
		input *d;

		output *o;
	} nand4;
}

#endif //LOGICMONITOR_AND_NOT_DEVICE4_H
