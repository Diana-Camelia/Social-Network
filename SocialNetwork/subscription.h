#pragma once
#include "Event.h"

class Subscription{
private:
	int id_subscriber;
	int id_event;
public:
	Subscription();
	Subscription(int id_event, int id_subscriber);
	bool operator ==(const Subscription& ot);
	int get_id_subscriber() const;
	int get_id_event() const;
};