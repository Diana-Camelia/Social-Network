#pragma once

class Friendship{
private:
	int id_user1, id_user2;
public:
	Friendship();
	Friendship(int id_user1, int id_user2);
	bool operator==(const Friendship& ot) const;
	int get_user1_id() const;
	int get_user2_id() const;
	bool operator!=(const Friendship& ot) const;
};