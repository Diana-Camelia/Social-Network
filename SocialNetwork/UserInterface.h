#pragma once
#include "EntityService.h"

class UI{
private:
	EntityService& entity_service;
	void read_data_about_user(int& id_user, std::string& name, std::string& first_name, int& age);
	void read_data_about_friendship(int& id_user1, int& id_user2);
	void print_all_users();
	void add_user();
	void delete_user();
	void add_friendship();
	void remove_event();
	void view_events();
	void print_user_friends() ;
	void modify_user();
	void print_chat() ;
	void add_message();
	void print_all_users(const List<User>& all_users) ;
	void print_commands() ;
	void delete_friendship();
	void view_subscribers_for_event();
	void delete_message();
	void add_event();
	void add_subscription();
	void remove_subscription();
public:
	void start();
	UI(EntityService& entity_service);
};