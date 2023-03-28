#pragma once
#include "list.h"
#include "Message.h"

class Message_repository{
private:
	List<Message> all_messages;
public:
	Message_repository();
	void remove_message(const Message& message);
	List<Message> get_all_messages() const;
	void add_message(const Message& message);
	void remove_message_id_user(int id_user);
};