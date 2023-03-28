#include "User.h"

User::User(){
	this->id_user = -1;
	this->user_first_name = this->user_name = "";
}

User::User(const int id_user, const std::string& user_name, const std::string& user_first_name, const int user_age){
	this->id_user = id_user;
	this->user_name = user_name;
	this->user_first_name = user_first_name;
	this->age = user_age;
}

std::string User::get_user_name() const{
	return this->user_name;
}

int User::get_user_age() const{
	return this->age;
}

int User::get_user_id() const{
	return this->id_user;
}

std::string User::get_user_first_name() const{
	return this->user_first_name;
}

bool User::operator==(const User& ot) const{
	return this->id_user==ot.id_user && this->user_name==ot.user_name && this->user_first_name==ot.user_first_name
		&& this->age==ot.age;
}

void User::set_user_name(const std::string& name){
	this->user_name = name;
}

void User::set_user_first_name(const std::string& first_name){
	this->user_first_name = first_name;
}

void User::set_user_age(const int age){
	this->age = age;
}

bool User::operator!=(const User& ot) const{
	return !(ot.id_user==this->id_user);
}

std::ostream& operator<<(std::ostream& stream, const User& user){
	stream << "[Name]-> " << user.get_user_name() << " [First name]-> " << user.get_user_first_name() << " [Age]-> " << user.get_user_age();
	stream << " [ID]:-> " << user.get_user_id();
	return stream;
}