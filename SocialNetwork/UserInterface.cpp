#include "UserInterface.h"
#include "EntityService.h"
#include <iostream>

void UI::print_commands() {
	//std::cout << std::endl;
	std::cout << "1. Add user. \n";
	std::cout << "2. Remove user. \n";
	std::cout << "3. Modify user. \n";
	std::cout << "4. Print all users. \n";
	std::cout << std::endl;
	std::cout << "5. Add event. \n";
	std::cout << "6. Delete event. \n";
	std::cout << "7. View events. \n";
	std::cout << std::endl;
	std::cout << "8. Add subscription. \n";
	std::cout << "9. Remove subscription.\n";
	std::cout << "10. View subscriptions.\n";
	std::cout << std::endl;
	std::cout << "11. Add friendship.\n";
	std::cout << "12. Remove friendship.\n";
	std::cout << "13. Print user friends.\n";
	std::cout << std::endl;
	std::cout << "14. Add message.\n";
	std::cout << "15. Remove message.\n";
	std::cout << "16. Print chat.\n";
	std::cout << std::endl;
	std::cout << "x. Close aplication. \n";
	std::cout << std::endl;
}

void UI::read_data_about_user(int& id_user, std::string& name, std::string& first_name, int& age){
	std::string name_string, first_name_string, user_id_string, age_string;
	std::cout << std::endl;
	std::cout << "User ID: "; std::getline(std::cin, user_id_string);
	std::cout << "Name: "; std::getline(std::cin, name_string);
	std::cout << "First Name: "; std::getline(std::cin, first_name_string);
	std::cout << "Age: "; std::getline(std::cin, age_string);
	try{
		id_user = std::stoi(user_id_string);
	}
	catch (std::exception error ){
		throw(std::exception("ID must be a number!\n"));
		std::cout << std::endl;
	}
	try{
		age = std::stoi(age_string);
	}
	catch (std::exception error){
		throw(std::exception("Age must be a number!\n"));
		std::cout << std::endl;
	}
	name = name_string;
	first_name = first_name_string;
	//std::cout << std::endl;
}

void UI::read_data_about_friendship(int& id_user1, int& id_user2){
	std::string id_string_1, id_string_2;
	std::cout << std::endl;
	std::cout << "Id user 1: "; std::getline(std::cin, id_string_1);
	std::cout << "Id user 2: "; std::getline(std::cin, id_string_2);
	try{
		id_user1 = std::stoi(id_string_1);
		id_user2 = std::stoi(id_string_2);
	}
	catch (std::exception error){
		throw(std::exception("Id must be a number!\n"));
		std::cout << std::endl;
	}
}

void UI::print_all_users(){
	OrderdSet<User> users =entity_service.get_all_users();
	SetIterator<User> iterator = users.iterator();
	while (iterator.valid()){
		std::cout << iterator.get_element() << "\n";
		iterator.next();
	}
	std::cout << std::endl;
}

void UI::add_user(){
	int id_user, age;
	std::string name, first_name;
	try{
		this->read_data_about_user(id_user, name, first_name, age);
	}
	catch (std::exception& error){
		std::cout << error.what() << std::endl;
		return;
	}
	try{
		this->entity_service.add_user(id_user, name, first_name, age);
		std::cout << "User added successfully!\n";
		std::cout << std::endl;
	}
	catch (std::exception err){
		std::cout << err.what() << std::endl;
	}
}

void UI::delete_user(){
	int id_user, age;
	std::string name, first_name;
	try{
		this->read_data_about_user(id_user, name, first_name, age);
	}
	catch (std::exception& error){
		std::cout << error.what() << std::endl;
		return;
	}
	try{
		this->entity_service.remove_user(id_user, name, first_name, age);
		std::cout << "User deleted successfully!\n";
		std::cout << std::endl;
	}
	catch (std::exception err){
		std::cout << err.what() << std::endl;
	}
}

void UI::add_friendship(){
	int id_user1, id_user_2;
	try{
		this->read_data_about_friendship(id_user1, id_user_2);
	}
	catch (std::exception error){
		std::cout << error.what() << std::endl;
		return;
	}
	try{
		this->entity_service.add_friend(id_user1, id_user_2);
		std::cout << "Friendship added successfully!\n";
		std::cout << std::endl;
	}
	catch (std::exception error){
		std::cout << error.what() << std::endl;
	}
}

void UI::remove_event(){
	int id_event;
	std::string description,id_event_string;
	std::cout << "ID event: "; std::getline(std::cin, id_event_string);
	try{
		id_event = std::stoi(id_event_string);
	}
	catch (std::exception error){
		std::cout << "ID must be a number!\n";
		std::cout << std::endl;
		return;
	}
	try{
		this->entity_service.remove_event(id_event);
		std::cout << "Event removed successfully!\n";
		std::cout << std::endl;
	}
	catch (std::exception error){
		std::cout << error.what() << std::endl;
		return;
	}
}

void UI::view_events(){
	List<Event> all_events = this->entity_service.get_all_events();
	std::cout << std::endl;
	for (int i = 0; i < all_events.get_size(); i++)
		std::cout << all_events[i] << std::endl;
}

void UI::delete_friendship(){
	int id_user1, id_user_2;
	this->read_data_about_friendship(id_user1, id_user_2);
	try{
		this->entity_service.remove_friend(id_user1, id_user_2);
		std::cout << "Friendship deleted successfully!\n";
		std::cout << std::endl;
	}
	catch (std::exception error){
		std::cout << error.what() << std::endl;
	}
}

void UI::view_subscribers_for_event(){
	int id_event;
	std::cout << std::endl;
	std::string id_event_string;
	List<int>subscribers;
	std::cout << "ID event: "; std::getline(std::cin, id_event_string);
	try{
		id_event = std::stoi(id_event_string);
	}
	catch (std::exception error){
		std::cout << "ID must be a number!\n";
		std::cout << std::endl;
		return;
	}
	try{
		subscribers = this->entity_service.get_subscribers_id_for_event(id_event);
	}
	catch (std::exception error){
		std::cout << "ID must be a number!\n";
		std::cout << std::endl;
		return;
	}
	std::cout << "For event with id: " << id_event << std::endl;
	std::cout << "Users enrolled are: ";
	for (int i = 0; i < subscribers.get_size(); i++)
		std::cout << subscribers[i] << " ";
	std::cout << std::endl;
	std::cout << std::endl;
}

void UI::print_user_friends() {
	std::string id_string;
	int id_user;
	std::cout << std::endl;
	std::cout << "Id user: "; std::getline(std::cin, id_string);
	try{
		id_user = std::stoi(id_string);
	}
	catch (std::exception error){
		std::cout << "Id must be a number!\n";
		std::cout << std::endl;
		return;
	}
	try{
		List<User> friends = entity_service.get_friends(id_user);
		this->print_all_users(friends);
	}
	catch (std::exception error){
		std::cout << error.what() << std::endl;
		return;
	}
}

void UI::modify_user(){
	std::string id_string;
	int id_user;
	std::cout << "Id user: "; std::getline(std::cin, id_string);
	try{
		id_user = std::stoi(id_string);
	}
	catch (std::exception error){
		std::cout << "Id must be a number!\n";
		std::cout << std::endl;
		return;
	}
	std::string new_name, new_first_name;
	int new_age;
	std::string new_age_string;
	std::cout << "New name: "; std::getline(std::cin, new_name);
	std::cout << "New first name: "; std::getline(std::cin, new_first_name);
	std::cout << "New age: "; std::getline(std::cin, new_age_string);
	try{
		new_age = std::stoi(new_age_string);
	}
	catch (std::exception error){
		std::cout << "Age must be a number!\n";
		std::cout << std::endl;
		return;
	}
	try{
		this->entity_service.modify_user(id_user, new_name, new_first_name, new_age);
		std::cout << "Modification made successfully!\n";
		std::cout << std::endl;
	}
	catch (std::exception error){
		std::cout << error.what();
		return;
	}
}

void UI::print_all_users(const List<User>& users) {
	if (users.get_size() == 0) {
		std::cout << "No users!!!\n";
		std::cout << std::endl;
		return;
	}
	for (int i = 0; i < users.get_size(); i++)
		std::cout << users.at(i) << std::endl;
	std::cout << std::endl;
}

void UI::print_chat() {
	int id_user1, id_user2;
	List<Message>chat;
	this->read_data_about_friendship(id_user1, id_user2);
	try{
		chat = this->entity_service.get_chat(id_user1, id_user2);

	}
	catch (std::exception err){
		std::cout << err.what() << std::endl;
		return;
	}
	if (chat.get_size() == 0){
		std::cout << "No messages!!!\n";
		std::cout << std::endl;
		return;
	}
	User user1 = this->entity_service.get_user_with_id(id_user1);
	User user2 = this->entity_service.get_user_with_id(id_user2);
	std::cout << user1.get_user_name() << " " << user1.get_user_first_name() << "                              ";
	std::cout << user2.get_user_name() << " " << user2.get_user_first_name() << std::endl;
	std::cout << "-----------------------------------------------------------------------" << std::endl;
	for (int i = 0; i < chat.get_size(); i++){
		Message message = chat.at(i);
		if (message.get_id_user_sender() == id_user1)
			std::cout << message.get_message() << std::endl;
		else
			std::cout << "                                         " << message.get_message() << std::endl;
		std::cout << std::endl;
	}
}

void UI::add_message(){
	int user1, user2;
	this->read_data_about_friendship(user1, user2);
	std::string message;
	std::cout << "Message: "; std::getline(std::cin, message);
	try{
		this->entity_service.add_message(user1, user2, message);
	}
	catch (std::exception error){
		std::cout << error.what() << std::endl;
		return;
	}
	std::cout << "Message sent successfully!\n";
	std::cout << std::endl;
}

void UI::delete_message(){
	int user1, user2;
	this->read_data_about_friendship(user1, user2);
	std::string message;
	std::cout << "Message: "; std::getline(std::cin, message);
	try{
		this->entity_service.delete_message(user1, user2, message);
		std::cout << "Message deleted successfully!\n";
		std::cout << std::endl;
	}
	catch (std::exception error){
		std::cout << error.what() << std::endl;
	}
}

void UI::add_event(){
	int id_event;
	std::string description,title,id_string;
	std::cout << std::endl;
	std::cout << "ID Event: "; std::getline(std::cin, id_string);
	try{
		id_event = std::stoi(id_string);
	}
	catch (std::exception error){
		std::cout << "ID must be a number!\n";
		std::cout << std::endl;
		return;
	}
	std::cout << "Event title: "; std::getline(std::cin, title);
	std::cout << "Event description: "; std::getline(std::cin, description);
	try{
		this->entity_service.add_event(id_event, title, description);
		std::cout << "Event added successfully!\n";
		std::cout << std::endl;
	}
	catch (std::exception error){
		std::cout << error.what() << std::endl;
		return;
	}
}

void UI::add_subscription(){
	int id_event,  id_user;
	std::string id_ev_str, id_usr_str;
	std::cout << std::endl;
	std::cout << "ID event: "; std::getline(std::cin, id_ev_str);
	std::cout << "ID user: "; std::getline(std::cin, id_usr_str);
	try{
		id_user = std::stoi(id_usr_str);
		id_event = std::stoi(id_ev_str);
	}
	catch (std::exception err){
		std::cout << "Id must be a number!\n";
		std::cout << std::endl;
		return;
	}
	try{
		this->entity_service.add_subscription(id_event, id_user);
		std::cout << "Subscription added successfully!\n";
		std::cout << std::endl;
	}
	catch (std::exception err){
		std::cout << err.what() << std::endl;
		return;
	}
}

void UI::remove_subscription(){
	int id_event, id_user;
	std::cout << std::endl;
	std::string id_ev_str, id_usr_str;
	std::cout << "ID event: "; std::getline(std::cin, id_ev_str);
	std::cout << "ID user: "; std::getline(std::cin, id_usr_str);
	try{
		id_user = std::stoi(id_usr_str);
		id_event = std::stoi(id_ev_str);
	}
	catch (std::exception err){
		std::cout << "Id must be a number!\n";
		std::cout << std::endl;
		return;
	}
	try{
		this->entity_service.remove_subscription(id_event, id_user);
		std::cout << "Subscription removed successfully!\n";
		std::cout << std::endl;
	}
	catch (std::exception err){
		std::cout << err.what() << std::endl;
		return;
	}
}

UI::UI(EntityService& entity_service) :entity_service{ entity_service }{
}

void UI::start(){
	std::string command;

	// at least two friends for each user:
	
	entity_service.add_friend(1, 2);
	entity_service.add_friend(2, 3);
	entity_service.add_friend(4, 10);
	entity_service.add_friend(10, 3);
	entity_service.add_friend(11, 4);
	entity_service.add_friend(5, 8);
	entity_service.add_friend(8, 11);
	entity_service.add_friend(12, 6);
	entity_service.add_friend(6, 13);
	entity_service.add_friend(12, 7);
	entity_service.add_friend(7, 14);
	entity_service.add_friend(13, 14);
	entity_service.add_friend(1, 7);

	// exchanging messages between friends:

	entity_service.add_message(1, 2, "Hello!");
	entity_service.add_message(2, 1, "Hello!");
	entity_service.add_message(1, 2, "Will you come with us to the fotball later?");
	entity_service.add_message(2, 1, "I can not wait!");

	entity_service.add_message(2, 3, "Hi!");
	entity_service.add_message(3, 2, "Hi!");
	entity_service.add_message(2, 3, "Can you help me with some homework please?");
	entity_service.add_message(3, 2, "Of course! ");

	entity_service.add_message(4, 10, "Don't forget you said see you later.! ");
	entity_service.add_message(10, 4, "No, no.");

	entity_service.add_message(3, 10, "I'm coming now! ");
	entity_service.add_message(10, 3, "Hurry up!! ");

	entity_service.add_message(11, 4, "I forgot my headphones at you yesterday =( Can you bring them to me today when you come to school?! ");
	entity_service.add_message(4, 11, "Of course! ");

	entity_service.add_message(5, 8, "I've been waiting for you for 10 minutes ... ");
	entity_service.add_message(8, 5, "Sorry... I'm in a hurry ");

	entity_service.add_message(8, 11, "I have a gift for you!!! ");
	entity_service.add_message(11, 8, "What is the present? ");

	entity_service.add_message(12, 6, "Hello! ");
	entity_service.add_message(6, 12, "Hello! ");
	entity_service.add_message(6, 12, "How are you? ");

	entity_service.add_message(13, 6, "Hi! ");
	entity_service.add_message(6, 13, "Hi! ");

	entity_service.add_message(7, 12, "Ily! ");
	entity_service.add_message(12, 7, "Ily too! ");

	entity_service.add_message(7, 14, "Heloo! ");
	entity_service.add_message(14, 7, "Hello! ");

	entity_service.add_message(13, 14, "Hi! ");
	entity_service.add_message(13, 14, "Hi! ");

	entity_service.add_message(1, 7, "Heloo! ");
	entity_service.add_message(7, 1, "Hello! ");
	

	while (true){
		this->print_commands();
		std::cout << "Input command: ";
		std::getline(std::cin, command);
		if (command == "1"){
			this->add_user();
		}
		else if (command == "2"){
			this->delete_user();
		}
		else if (command == "3"){
			this->modify_user();
		}
		else if (command == "4") {
			this->print_all_users();
		}
		else if (command == "5") {
			this->add_event();
		}
		else if (command == "6") {
			this->remove_event();
		}
		else if (command == "7") {
			this->view_events();
		}
		else if (command == "8") {
			this->add_subscription();
		}
		else if (command == "9") {
			this->remove_subscription();
		}
		else if (command == "10") {
			this->view_subscribers_for_event();
		}
		else if (command == "11") {
			this->add_friendship();
		}
		else if (command == "12") {
			this->delete_friendship();
		}
		else if (command == "13") {
			this->print_user_friends();
		}
		else if (command == "14") {
			this->add_message();
		}
		else if (command == "15") {
			this->delete_message();
		}
		else if (command == "16") {
			this->print_chat();
		}
		else if (command == "x"){
			return;
		}
		else{
			std::cout << "Invalid command! Try again!\n";
			std::cout << std::endl;
		}
	}
}