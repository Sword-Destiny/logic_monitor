//
// Created by sworddestiny on 17-12-6.
//

#ifndef LOGICMONITOR_DOCUMENT_H
#define LOGICMONITOR_DOCUMENT_H

#include "common.h"
#include "logic_device.h"
#include "iface.h"
#include "clock.h"

namespace lm {

	/**
	 * 一个模拟的逻辑图
	 */
	class logic_document {
	public:

		explicit logic_document(const string &title);

		~logic_document();

		const string &getTitle() const;

		void setTitle(const string &title);

		void update_document();

	public:
		string title;
		list<lm::logic_device*> devices;
		list<lm::iface*> ifaces;
		list<lm::clock*> clocks;
	};

	typedef logic_document logic_doc;
}

#endif //LOGICMONITOR_DOCUMENT_H
