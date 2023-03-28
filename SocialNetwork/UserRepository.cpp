#include "UserRepository.h"
#include <fstream>
#include <vector>

void User_repository_file::read_from_file(){
	std::ifstream f(this->file_name);
	if (!f.is_open())
		throw(std::exception("Unable to open the file!\n"));
	std::string string;
	std::vector<std::string>parts;
	parts.reserve(4);
	std::string name;
	int id_user;
	std::string first_name;
	int age;
	while (std::getline(f, string)){
		this->separate_string(string, parts);
		id_user = std::stoi(parts.at(0));
		name = parts.at(1);
		first_name = parts.at(2);
		age = std::stoi(parts.at(3));
		User utilizator = User(id_user, name, first_name, age);
		this->users.add(utilizator);
		parts.clear();
	}
}

void User_repository_file::write_to_file(){
	std::ofstream out(this->file_name);
	if (!out.is_open())
		throw(std::exception("Unable to open the file!\n"));
	SetIterator<User> it = this->users.iterator();
	while (it.valid()){
		User utilizator = it.get_element();
		out << utilizator.get_user_id() << ";" << utilizator.get_user_name() << ";" << utilizator.get_user_first_name() << ";" << utilizator.get_user_age() << "\n";
		it.next();
	}
	out.close();
}

void User_repository_file::separate_string(std::string str, std::vector<std::string>& parts){
	// transforming a string into an entity
	for (int i = 1; i < 4; i++) {
		const size_t pos = str.find_first_of(';');
		const std::string part = str.substr(0, pos);
		parts.push_back(part);
		str = str.substr(pos + 1, str.length());
	}
	parts.push_back(str);
}

User_repository_file::User_repository_file(const std::string& file_name) :users{
	OrderdSet<User>([](const User& utz1,const User& utz2) {
		return utz1.get_user_id() < utz2.get_user_id(); }) } {
	this->file_name = file_name;
	this->read_from_file();
}

OrderdSet<User>& User_repository_file::get_all_users(){
	return this->users;
}

void User_repository_file::remove_user(const User& user){
	if (!this->users.remove(user))
		throw(std::exception("There is no such a user!\n"));
	this->write_to_file();
}

void User_repository_file::add_user(const User& user){
	if (!this->users.add(user))
		throw(std::exception("This ID is already taken!\n"));
	this->write_to_file();
}

User User_repository_file::get_user_with_id(int is_user){
	SetIterator<User> it = this->users.iterator();
	while (it.valid()){
		User user = it.get_element();
		if (user.get_user_id() == is_user)
			return user;
		it.next();
	}
	return User(-1, "", "", -1);
}

void User_repository_file::modify_user(int id_user, const std::string& new_name, const std::string& new_first_name, const int new_age) {
	SetIterator<User> it = this->users.iterator();
	while (it.valid()) {
		User user = it.get_element();
		if (user.get_user_id() == id_user) {
			it.get_element().set_user_first_name(new_first_name);
			it.get_element().set_user_name(new_name);
			it.get_element().set_user_age(new_age);
			this->write_to_file();
			return;
		}
		it.next();
	}
	throw(std::exception("User not found!\n"));
}