#include "Message.h"

Message::Message(){
	this->message = "";
	this->id_user_sender = -1;
	this->id_user_receiver = -1;
}

Message::Message(int id_sender, int id_receiver, const std::string& message){
	this->message = message;
	this->id_user_sender = id_sender;
	this->id_user_receiver = id_receiver;
}

std::string Message::get_message() const{
	return this->message;
}

int Message::get_id_user_receiver() const{
	return this->id_user_receiver;
}

int Message::get_id_user_sender() const{
	return this->id_user_sender;
}

bool Message::operator==(const Message& ot){
	bool equal= this->message == ot.message&& this->id_user_sender == ot.id_user_sender && this->id_user_receiver == ot.id_user_receiver;
	return equal;
}