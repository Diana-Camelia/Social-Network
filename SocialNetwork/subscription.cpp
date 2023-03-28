#include "subscription.h"

Subscription::Subscription(){
	this->id_event = this->id_subscriber = -1;
}

Subscription::Subscription(int id_event, int id_subscriber){
	this->id_event = id_event;
	this->id_subscriber = id_subscriber;
}

bool Subscription::operator==(const Subscription& ot){
	return this->id_event == ot.id_event && this->id_subscriber == ot.id_subscriber;
}

int Subscription::get_id_subscriber() const{
	return this->id_subscriber;
}

int Subscription::get_id_event() const{
	return this->id_event;
}