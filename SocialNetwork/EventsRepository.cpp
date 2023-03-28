#include "EventsRepository.h"

Event_repository::Event_repository(){
}

List<Event> Event_repository::get_all_events() const{
	return this->allEvents;
}

void Event_repository::add_event(const Event& ev){
	for (int i = 0; i < this->allEvents.get_size(); i++){
		if (this->allEvents[i] == ev) // if event is in the list
			throw(std::exception("This event already exists!\n"));
	}
	this->allEvents.add(ev);
}

void Event_repository::remove_event(const Event& ev){
	for (int i = 0; i < this->allEvents.get_size(); i++){
		if (this->allEvents[i] == ev) { // if event is in the list
			this->allEvents.remove_at_position(i);
			return;
		}
	}
	throw(std::exception("Event not found in the list!\n"));
}

List<Subscription> Event_repository::get_all_subscriptions() const{
	return this->subscriptions;
}

void Event_repository::add_subscription(const Subscription& subscription){
	for (int i = 0; i < this->subscriptions.get_size();i++){
		if (this->subscriptions[i] == subscription) { // if subscription is in the list
			throw(std::exception("This subscription already exists!\n"));
		}
	}
	this->subscriptions.add(subscription);
}

void Event_repository::remove_subscription(const Subscription& subscription){
	for (int i = 0; i < this->subscriptions.get_size(); i++){
		if (this->subscriptions[i] == subscription){ // if subscription is in the list{
			this->subscriptions.remove_at_position(i);
			return;
		}
	}
	throw(std::exception("Subscription not found!\n"));
}

void Event_repository::remove_subsscription_where_id_user(int id_user){
	for (int i = 0; i < this->subscriptions.get_size(); i++){
		if (this->subscriptions[i].get_id_subscriber()==id_user) { // if subscription is in the list
			this->subscriptions.remove_at_position(i);
		}
	}
}

bool Event_repository::find_event(int id_event){
	for (int i = 0; i < this->allEvents.get_size(); i++){
		if (this->allEvents[i].get_id_event() == id_event)
			return true;
	}
	return false;
}