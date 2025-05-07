#ifndef LISTNER_H
	#define LISTNER_H

	#include "event.h"

	class Listner
	{
		public:
			Listner() {}
			virtual ~Listner() {}

			virtual void handle_event(Event* event) = 0;
	};

#endif