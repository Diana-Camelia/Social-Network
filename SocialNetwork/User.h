#pragma once
#include <string>
#include <iostream>

class User{
private:
	int id_user,age;
	std::string user_first_name;
	std::string user_name;
public:
	User();
	User(const int id, const std::string& user_name, const std::string& user_first_name, const int age);
	int get_user_id() const;
	int get_user_age() const;
	std::string get_user_name() const;
	std::string get_user_first_name() const;
	bool operator==(const User& ot) const;
	void set_user_name(const std::string& name);
	void set_user_first_name(const std::string& first_name);
	void set_user_age(const int age);
	bool operator!=(const User& ot) const;
	friend std::ostream& operator << (std::ostream& stream, const User& user);
};