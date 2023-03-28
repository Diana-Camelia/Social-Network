#pragma once
#include "FriendShipRepository.h"
#include "MessageRepository.h"
#include "UserRepository.h"
#include "EventsRepository.h"

class EntityService{
private:
	Friendship_repository& friendship_repository;
	Message_repository& messages_repository;
	User_repository_file& users_repository;
	Event_repository& event_repository;
	void validate_user(const User& user);
	void validate_event(const Event& ev);
	void validate_message(const Message& message);
	void validate_subscription(const Subscription& subsc);
public:
	EntityService(Friendship_repository& repoPrietenie, User_repository_file& repoUtilizatori, Message_repository& repoMesaje, Event_repository& event_repository);
	void remove_friend(int id_user1, int id_user2);
	void add_friend(int id_user1, int id_user2);
	void add_user(int id_user1, const std::string& name, const std::string& first_name,const  int age);
	void add_event(int id_event, const std::string& title, const std::string& description);
	List<Event> get_all_events();
	void modify_user(int id_user, const std::string& new_name, const std::string& new_first_name, const int new_age);
	void delete_message(int id_user1, int id_user2, const std::string& mesaj);
	void remove_event(int id_event);
	void add_message(int id_user1, int id_user2, const std::string& message);
	void remove_user(int id_user1, const std::string& name, const std::string& first_name, const int age);
	User get_user_with_id(int id_user);
	OrderdSet<User> get_all_users();
	List<Message> get_chat(int id_user1, int id_user2);
	List<User> get_friends(int id_user);
	List<int> get_subscribers_id_for_event(int id_event);
	void add_subscription(int id_event,int id_user);
	void remove_subscription(int id_event, int id_user);
};