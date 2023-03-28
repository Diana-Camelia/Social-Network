#pragma once
#include "list.h"
#include "FriendShip.h"
#include <string>

class Friendship_repository{
private:
	List<Friendship> all_friends;
public:
	Friendship_repository();
	List<Friendship>& get_all_friends();
	void add_friend(const Friendship& friendship);
	bool find_friend(const Friendship& friendship) const;
	void delete_friend(const Friendship& friendship);
	void remove_friend_where_id(int id_user);
};