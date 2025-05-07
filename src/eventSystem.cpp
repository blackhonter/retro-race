#include "eventSystem.h"

EventSystem* EventSystem::instance()
{
	static EventSystem instance;

	return &instance;
}

bool EventSystem::al_ready_registered(string event_id, Listner* client)
{
	bool is_al_ready_registered = false;

	pair<multimap<string, Listner*>::iterator, multimap<string, Listner*>::iterator> range;

	range = database.equal_range(event_id);

	for( multimap<string, Listner*>::iterator i = range.first; i != range.second; i++ )
	{
		if( (*i).second ==  client)
		{
			is_al_ready_registered = true;

			break;
		}
	}

	return is_al_ready_registered;
}

void EventSystem::dispatch_event(Event* event)
{
	pair<multimap<string, Listner*>::iterator, multimap<string, Listner*>::iterator> range;

	range = database.equal_range(event->event_id());

	for( multimap<string, Listner*>::iterator i = range.first; i != range.second; i++ )
	{
		(*i).second->handle_event(event);
	}
}

void EventSystem::register_client(string event_id, Listner* client)
{
	if(client || !al_ready_registered(event_id, client) )
	{
		database.insert( make_pair(event_id, client) );
	}
}

void EventSystem::unregister_client(string event_id, Listner* client)
{
	pair<multimap<string, Listner*>::iterator, multimap<string, Listner*>::iterator> range;

	range = database.equal_range(event_id);

	for( multimap<string, Listner*>::iterator i = range.first; i != range.second; i++ )
	{
		if( (*i).second ==  client)
		{
			i = database.erase(i);

			break;
		}
	}
}

void EventSystem::unregister_all_clients(Listner* client)
{
	multimap<string, Listner*>::iterator i = database.begin();

	while( i != database.end() )
	{
		if( (*i).second ==  client)
		{
			i = database.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void EventSystem::send_event(string event_id, void* data)
{
	Event newEvent(event_id, data);

	current_events.push_back(newEvent);
}

void EventSystem::process_events()
{
	while( current_events.size() )
	{
		dispatch_event(&current_events.front());

		current_events.pop_front();
	}
}

void EventSystem::clear_events()
{
	current_events.clear();
}

void EventSystem::shut_down()
{
	database.clear();
	current_events.clear();
}