#pragma once
#include <string>

class Event{
private:
	int id_event;
	std::string title;
	std::string description;
public:
	Event();
	Event(int id_event, const std::string& title, const std::string& description);
	int get_id_event() const;
	std::string get_title() const;
	std::string get_description() const;
	bool operator ==(const Event& ot) const;
	friend std::ostream& operator<< (std::ostream& stream, const Event& ev);
};