#pragma once
#include "Event.h"
#include "List.h"
#include "subscription.h"

class Event_repository{
private:
	List<Event> allEvents;
	List<Subscription> subscriptions;
public:
	Event_repository();
	List<Event> get_all_events() const;
	void add_event(const Event& ev);
	void remove_event(const Event& ev);
	List<Subscription> get_all_subscriptions() const;
	void add_subscription(const Subscription& subscription);
	void remove_subscription(const Subscription& subscription);
	void remove_subsscription_where_id_user(int id_user);
	bool find_event(int id_event);
};