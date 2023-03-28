#include "FriendShipRepository.h"
#include <fstream>


Friendship_repository::Friendship_repository(){
}

List<Friendship>& Friendship_repository::get_all_friends(){
	return this->all_friends;
}

void Friendship_repository::add_friend(const Friendship& friendship){
	for (int i = 0; i < this->all_friends.get_size(); i++){
		if (this->all_friends[i] == friendship)
			throw(std::exception("This friendship already exists!\n"));
	}
	this->all_friends.add(friendship);
}

void Friendship_repository::delete_friend(const Friendship& friendship){
	for (int i = 0; i < this->all_friends.get_size(); i++){
		if (this->all_friends.at(i) == friendship) {
			this->all_friends.remove_at_position(i);
			return;
		}
	}
	throw(std::exception("There is no such friendship!"));
}

void Friendship_repository::remove_friend_where_id(int id_user){
	Friendship fr;
	for (int i = 0; i < this->all_friends.get_size(); i++){
		fr = this->all_friends.at(i);
		if (fr.get_user1_id() == id_user || fr.get_user2_id()==id_user)
			this->all_friends.remove_at_position(i);
	}
}

bool Friendship_repository::find_friend(const Friendship& friendship) const{
	for (int i = 0; i < this->all_friends.get_size(); i++)
		if (this->all_friends.at(i) == friendship)
			return true;
	return false;
}
