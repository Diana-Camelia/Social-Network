#include "EntityService.h"
#include <vector>

void EntityService::validate_message(const Message& message){ 
	std::string err = "";
	int id_user_sender = message.get_id_user_sender();
	int id_user_receiver = message.get_id_user_receiver();
	if (this->users_repository.get_user_with_id(id_user_sender).get_user_id() == -1)
		err += "There is no receiver with this id!\n";
	if (this->users_repository.get_user_with_id(id_user_sender).get_user_id() == -1)
		err += "There is no sender with this id!\n";
	if (err.length() > 0)
		throw(std::exception(err.c_str()));
	Friendship friendship = Friendship(id_user_sender, id_user_receiver);
	//check if friendship exists: 
	if (!this->friendship_repository.find_friend(friendship))
		throw(std::exception("Messages can be sended only between friends!\n"));
}

void EntityService::validate_subscription(const Subscription& subsc){
	bool id_event_found = this->event_repository.find_event(subsc.get_id_event());
	std::string error = "";
	if (!id_event_found)
		error += "No event with this id!\n";
	bool found_user = this->users_repository.get_user_with_id(subsc.get_id_subscriber()).get_user_id() != -1;
	if(!found_user)
		error += "No user with this id!\n";
	if (error.size() > 0)
		throw(std::exception(error.c_str()));
}

void EntityService::validate_user(const User& user){
	std::string errori = "";
	if (user.get_user_id() <= 0)
		errori += "Invalid ID!\n";
	if (user.get_user_name() == "")
		errori += "Invalid Name!\n";
	if (user.get_user_first_name() == "")
		errori += "Invalid First Name!\n";
	if (user.get_user_age() <= 0)
		errori += "Invalid Age!\n";
	if (errori.length() > 0)
		throw(std::exception(errori.c_str()));
}

void EntityService::validate_event(const Event& ev){
	std::string error;
	if(ev.get_title()=="")
		error += "Event title is empty!\n";
	if (ev.get_description() == "")
		error += "Event description is empty!\n";
	if (ev.get_id_event() <= 0)
		error += "Invalid event ID!\n";
	if (error.size() > 0)
		throw(std::exception(error.c_str()));
}

EntityService::EntityService(Friendship_repository& repoFriendship, User_repository_file& repoUtilizatori, Message_repository& repoMesaje, Event_repository& event_repository) : friendship_repository{ repoFriendship }, users_repository{ repoUtilizatori }, messages_repository{ repoMesaje }, event_repository{event_repository}{
}

void EntityService::add_friend(int id_user1, int id_user2){
	if (id_user1 <= 0 || id_user2 <= 0)
		throw(std::exception("Invalid User Id!"));
	if (this->users_repository.get_user_with_id(id_user1).get_user_id()!=-1 && this->users_repository.get_user_with_id(id_user2).get_user_id()!=-1){
		Friendship friendship = Friendship(id_user1, id_user2);
		this->friendship_repository.add_friend(friendship);
	}
	else
		throw(std::exception("No users with these ID's!"));
}

void EntityService::remove_friend(int id_user1, int id_user2){
	if (id_user1 <= 0 || id_user2 <= 0)
		throw(std::exception("Invalid ID!\n"));
	Friendship friendship = Friendship(id_user1, id_user2);
	friendship_repository.delete_friend(friendship);
}

void EntityService::add_message(int idExpeditor, int idReceptor, const std::string& mesajText){
	Message mesaj = Message(idExpeditor, idReceptor, mesajText);
	this->validate_message(mesaj);
	this->messages_repository.add_message(mesaj);
}

void EntityService::remove_user(int idUser, const std::string& nume, const std::string& prenume, int const varsta){
	User utilizator = User(idUser, nume, prenume, varsta);
	this->validate_user(utilizator);
	this->users_repository.remove_user(utilizator);
	this->friendship_repository.remove_friend_where_id(idUser); //delete the friendships of user
	this->messages_repository.remove_message_id_user(idUser); //delete messages of user
	this->event_repository.remove_subsscription_where_id_user(idUser);
}

void EntityService::add_user(int idUser, const std::string& nume, const std::string& prenume,const int varsta){
	User utilizator = User(idUser, nume, prenume, varsta);
	this->validate_user(utilizator);
	this->users_repository.add_user(utilizator);
}

void EntityService::add_event(int id_event, const std::string& title, const std::string& description){
	Event ev = Event(id_event, title, description);
	this->validate_event(ev);
	this->event_repository.add_event(ev);
}

List<Event> EntityService::get_all_events(){
	return this->event_repository.get_all_events();
}

void EntityService::modify_user(int id_user, const std::string& new_name, const std::string& new_first_name, const int new_age){
	std::string errors;
	if (new_name == "")
		errors += "Invalid Name!\n";
	if (new_first_name == "")
		errors += "Invalid First Name!\n";
	if (new_age <= 0)
		errors += "Invalid Age!\n";
	if (errors.length() > 0)
		throw(std::exception(errors.c_str()));
	this->users_repository.modify_user(id_user, new_name, new_first_name, new_age);
}

void EntityService::delete_message(int idExpeditor, int idReceptor, const std::string& mesaj){
	Message msg = Message(idExpeditor, idReceptor, mesaj);
	this->validate_message(msg);
	this->messages_repository.remove_message(msg);
}

void EntityService::remove_event(int id_event){
	Event ev = Event(id_event,"", "");
	if (id_event <= 0)
		throw(std::exception("Invalid event ID!\n"));
	this->event_repository.remove_event(ev);
}

OrderdSet<User> EntityService::get_all_users(){
	return this->users_repository.get_all_users();
}

List<User> EntityService::get_friends(int idUser){
	if (this->users_repository.get_user_with_id(idUser).get_user_id()==-1)
		throw(std::exception("Utilizator cu id inexistent\n"));
	List<Friendship> toatePrieteniile = this->friendship_repository.get_all_friends();
	List<User>listaPrieteni;
	for (int i = 0; i < toatePrieteniile.get_size(); i++){
		if (toatePrieteniile.at(i).get_user1_id() == idUser){
			User prieten = this->users_repository.get_user_with_id(toatePrieteniile.at(i).get_user2_id());
			listaPrieteni.add(prieten);
			//std::cout << prieten.getId() << std::endl;
		}
		else if (toatePrieteniile.at(i).get_user2_id() == idUser){
			User prieten = this->users_repository.get_user_with_id(toatePrieteniile.at(i).get_user1_id());
			listaPrieteni.add(prieten);
			//std::cout << prieten.getId() << std::endl;

		}
	}
	return listaPrieteni;
}

List<int> EntityService::get_subscribers_id_for_event(int id_event){
	if (this->event_repository.find_event(id_event) == false)
		throw(std::exception("No event with this id!\n"));
	List<Subscription> all_subscriptions = this->event_repository.get_all_subscriptions();
	List<int>result;
	for (int i = 0; i < all_subscriptions.get_size(); i++){
		if (all_subscriptions[i].get_id_event() == id_event)
			result.add(all_subscriptions[i].get_id_subscriber());
	}
	return result;
}

void EntityService::add_subscription(int id_event, int id_user){
	Subscription subscription = Subscription(id_event, id_user);
	this->validate_subscription(subscription);
	this->event_repository.add_subscription(subscription);
}

void EntityService::remove_subscription(int id_event, int id_user){
	Subscription subscription = Subscription(id_event, id_user);
	this->validate_subscription(subscription);
	this->event_repository.remove_subscription(subscription);
}

List<Message> EntityService::get_chat(int idSolicitant, int idUser2){
	if (this->users_repository.get_user_with_id(idSolicitant).get_user_id()==-1 || this->users_repository.get_user_with_id(idUser2).get_user_id() == -1)
		throw(std::exception("Users with inexistent ID!\n"));
	List<Message> allMessages = this->messages_repository.get_all_messages();
	List<Message>mesajeSolicitate;
	Message mesaj;
	for (int i = 0; i < allMessages.get_size(); i++){
		mesaj = allMessages.at(i);
		if ((mesaj.get_id_user_sender() == idSolicitant && mesaj.get_id_user_receiver() == idUser2)
			|| (mesaj.get_id_user_sender() == idUser2 && mesaj.get_id_user_receiver() == idSolicitant))
			mesajeSolicitate.add(mesaj);
	}
	return mesajeSolicitate;
}

User EntityService::get_user_with_id(int id){
	return this->users_repository.get_user_with_id(id);
}