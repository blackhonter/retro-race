#ifndef EVENTSYSTEM_H
	#define EVENTSYSTEM_H

	#include <string>
	#include <list>
	#include <map>
	#include <stdbool.h>

	#include "event.h"
	#include "listner.h"

	using std::multimap;
	using std::list;
	using std::pair;
	
	class EventSystem
	{
		private:
			//Singleton
			EventSystem(){}
			~EventSystem(){ this->shut_down(); }

			EventSystem(const EventSystem& rhs);
			EventSystem& operator=(const EventSystem& rhs);

			multimap<string, Listner*> database;
			list<Event> current_events;

			bool al_ready_registered(string event_id, Listner* client);
			void dispatch_event(Event* event);

		public:
			static EventSystem* instance();

			void register_client(string event_id, Listner* client);
			void unregister_client(string event_id, Listner* client);
			void unregister_all_clients(Listner* client);

			void send_event(string event_id, void* data = 0);
			void process_events();
			void clear_events();

			void shut_down();
	};

#endif