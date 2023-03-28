#include "FriendShip.h"

Friendship::Friendship(int id_user1, int id_user2){
	this->id_user2 = id_user1;
	this->id_user1 = id_user2;
}

Friendship::Friendship(){
	this->id_user1 = -1;
	this->id_user2 = -1;
}

int Friendship::get_user2_id() const{
	return this->id_user2;
}
int Friendship::get_user1_id() const{
	return this->id_user1;
}

bool Friendship::operator!=(const Friendship& ot) const{
	return !(ot == *this);
}

bool Friendship::operator==(const Friendship& ot) const{
	bool equal = (ot.id_user2 ==this->id_user1 && ot.id_user1 == this->id_user2) || (this->id_user1 == ot.id_user1 && this->id_user2 == ot.id_user2);
	return equal;
}