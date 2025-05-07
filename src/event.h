#ifndef EVENT_H
	#define EVENT_H

	#include <string>

	using std::string;

	class Event
	{
		private:
			string m_event_id;
			void* m_parameter;

		public:
			Event(string event_id, void* parameter = 0)
			{
				this->m_event_id = event_id;
				this->m_parameter = parameter;
			}

			~Event() {}

			inline string event_id() const { return this->m_event_id; }
			inline void* parameter() { return this->m_parameter; }
	};

#endif