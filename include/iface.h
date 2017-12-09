//
// Created by sworddestiny on 17-12-6.
//

#ifndef LOGICMONITOR_IFACE_H
#define LOGICMONITOR_IFACE_H

#include "common.h"
#include "clock.h"
#include "logic_device.h"

namespace lm {
	class logic_device;

	/**
	 * 端口
	 */
	class iface {
	public:
		virtual ~iface();

		iface(const string &name, iface_type type);

	public:

		virtual signal get_signal() = 0;

		const string &getName() const;

		void setName(const string &name);

		iface_type getType() const;

		uuid getUid() const;

	private:
		uuid uid;
	protected:
		signal sgl;
		string name;
		iface_type type;
	};

	/**
	 * 输入端口
	 */
	class input_iface : public iface {
	public:
		explicit input_iface(const string &name, iface_type type);

		virtual void update_signal() = 0;

		virtual signal get_signal() override = 0;

	private:
	};

	/**
	 * 时钟端口
	 */
	class clock_iface : public input_iface {
	public:
		clock_iface(const string &name, clock *clk);

		~clock_iface() override;

		signal get_signal() override;

		void update_signal() override;

	private:
	protected:
		clock *clk;
	};

	/**
	 * 输出端口
	 */
	class output_iface : public iface {

	public:
		output_iface(const string &name, logic_device *device);

		~output_iface() override;

		void update_signal(signal sgl);

		signal get_signal() override;

	private:
	protected:
		logic_device *device;

	};

	/**
	 * 连接端口
	 */
	class link_iface : public input_iface {
	public:
		link_iface(const string &name, output_iface *out_iface);

		~link_iface() override;

	public:
		void update_signal() override;

		signal get_signal() override;

		output_iface *getOut_iface() const;

		void setOut_iface(output_iface *out_iface);

	private:
		output_iface *out_iface;
	};

	typedef input_iface input;
	typedef output_iface output;
	typedef link_iface link;
	typedef link_iface* linkp;

}


#endif //LOGICMONITOR_IFACE_H
