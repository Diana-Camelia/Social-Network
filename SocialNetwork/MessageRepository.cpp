#include "MessageRepository.h"
#include <fstream>
#include <vector>

Message_repository::Message_repository(){
}

void Message_repository::add_message(const Message& message)
{
	this->all_messages.add(message);
}

void Message_repository::remove_message_id_user(int id_user){
	Message msg;
	for (int i = 0; i < this->all_messages.get_size(); i++){
		msg = this->all_messages.at(i);
		if (msg.get_id_user_receiver() == id_user || msg.get_id_user_sender() == id_user)
			this->all_messages.remove_at_position(i);
	}
}

List<Message> Message_repository::get_all_messages() const{
	return this->all_messages;
}

void Message_repository::remove_message(const Message& message){
	for (int i = 0; i < this->all_messages.get_size(); i++)
		if (this->all_messages.at(i) == message) {
			this->all_messages.remove_at_position(i);
			return;
		}
	throw(std::exception("There is no such message!\n"));
}