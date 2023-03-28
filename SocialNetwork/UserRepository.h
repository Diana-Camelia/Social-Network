#pragma once
#include "OrderdSet.h"
#include "User.h"

class User_repository_file{
private:
	void read_from_file();
	void write_to_file();
	std::string file_name;
	OrderdSet<User> users;
	void separate_string(std::string str,std::vector<std::string>& parts);
public:
	User_repository_file(const std::string& file_name);
	void remove_user(const User& user);
	User get_user_with_id(int id_user);
	void modify_user(int id_user, const std::string& new_name, const std::string& new_first_name, const int new_age);
	void add_user(const User& user);
	OrderdSet<User>& get_all_users();
};