#include "Event.h"
#include <iostream>

Event::Event(){
    this->id_event = -1;
    this->description = "";
    this->title = "";
}

Event::Event(int id_event, const std::string& title, const std::string& description){
    this->id_event = id_event;
    this->title = title;
    this->description = description;
}

int Event::get_id_event() const{
    return this->id_event;
}

std::string Event::get_title() const{
    return this->title;
}

std::string Event::get_description() const{
    return this->description;
}

bool Event::operator==(const Event& ot) const{
    return this->id_event == ot.id_event;
}

std::ostream& operator<<(std::ostream& stream, const Event& ev){
    stream << "ID event: " << ev.get_id_event() << std::endl;
    stream << "Title: " << ev.get_title() << std::endl;
    stream << ev.get_description() << std::endl;    
    return stream;
}