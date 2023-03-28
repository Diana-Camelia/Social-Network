#pragma once
#include <string>

class Message{
private:
	int id_user_sender;
	std::string message;
	int id_user_receiver;
public:
	Message(int id_sender, int id_receiver, const std::string& message);
	int get_id_user_sender() const;
	int get_id_user_receiver() const;
	bool operator==(const Message& ot);
	std::string get_message() const;
	Message();
};