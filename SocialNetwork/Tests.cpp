#include "Tests.h"
#include "EntityService.h"
#include "FriendShipRepository.h"
#include "UserRepository.h"
#include "MessageRepository.h"
#include <fstream>
#include <iostream>
#include <assert.h>
/*
void Teste::initializeaza()
{
	std::ofstream out("testPrietenii.cvs");
	if (!out.is_open())
		throw(std::exception("Erroare deschidere fisier teste"));
	out << "1;2\n1;7\n2;7\n2;10"; //scriem id-urile utilizatorilor care sunt prieteni
	out.close();

	std::ofstream outMsg("testMesaje.cvs");
	if (!outMsg.is_open())
		throw(std::exception("Erroare deschidere fisier teste"));
	outMsg << "1;7;salut, ce mai faci?\n7;1;bine, tu?";

	outMsg.close();

	std::ofstream outUt("testUtilizatori.cvs");
	if (!outUt.is_open())
		throw(std::exception("Erroare deschidere fisier teste"));
	outUt << "1;Maria;Ana;19\n7;Gica;Alexandru; 40\n2;Rusu;Ionel;20\n10;Marian;Grigore;21";
	outUt.close();

}

void Teste::testRepos()
{
	initializeaza();
	Friendship_repository repoPrietenie{ Friendship_repository("testPrietenii.cvs") };
	User_repository_file repoUtilizatori{ User_repository_file("testUtilizatori.cvs") };
	FileRepoMesaje repoMesaje{ FileRepoMesaje("testMesaje.cvs") };

	OrderdSet<User> multime = repoUtilizatori.get_all_users();
	SetIterator<User> it = multime.iterator();
	User ut1{ User(1,"Maria","Ana",19) };
	User ut2{ User(10,"Marian","Grigore",21) };
	User ut3{ User(2,"Rusu","Ionel",20) };
	User ut4{ User(7,"Gica","Alexandru",40) };
	assert(it.get_element() == ut1);
	it.next();
	assert(it.get_element() == ut3);
	it.next();
	assert(it.get_element() == ut4);
	it.next();
	assert(it.get_element() == ut2);

	List<Friendship> lista = repoPrietenie.get_all_friends();
	Friendship pr1{ Friendship(1,2) };
	Friendship pr2{ Friendship(7,1) };
	Friendship pr3{ Friendship(2,7) };
	Friendship pr4{ Friendship(2,10) };
	assert(lista.at(0) == pr1);
	assert(lista.at(1) == pr2);
	assert(lista.at(2) == pr3);
	assert(lista.at(3) == pr4);

	List<Message> listaMesaje = repoMesaje.get_all_messages();
	assert(listaMesaje.get_size() == 2);
	Message msg1 = listaMesaje.at(0);
	assert(msg1.get_id_user_sender() == 1);
	assert(msg1.get_id_user_receiver() == 7);
	assert(msg1.get_message() == "salut, ce mai faci?");

	Message msg2 = listaMesaje.at(1);
	assert(msg2.get_id_user_sender() == 7);
	assert(msg2.get_id_user_receiver() == 1);
	assert(msg2.get_message() == "bine, tu?");


}

void Teste::testAdaugaPrietenie()
{
	initializeaza();
	Friendship_repository repoPrietenie{ Friendship_repository("testPrietenii.cvs") };
	User_repository_file repoUtilizatori{ User_repository_file("testUtilizatori.cvs") };
	FileRepoMesaje repoMesaje{ FileRepoMesaje("testMesaje.cvs") };
	Event_repository evr;
	EntityService service{ EntityService(repoPrietenie,repoUtilizatori,repoMesaje,evr) };
	service.add_friend(1, 10);
	List<Friendship> lista = repoPrietenie.get_all_friends();

	assert(lista[lista.get_size() - 1].get_user1_id() == 10 && lista[lista.get_size() - 1].get_user2_id() == 1);
	try
	{
		service.add_friend(10, 1);//prietenia mai exista deja
		assert(false);
	}
	catch (std::exception err) {
		assert(true);
	}
	try
	{
		service.add_friend(10, 20);//nu exista utilizator cu id 20
		assert(false);
	}
	catch (std::exception err) {
		assert(true);
	}
}

void Teste::testStergePrietenie()
{
	initializeaza();
	Friendship_repository repoPrietenie{ Friendship_repository("testPrietenii.cvs") };
	User_repository_file repoUtilizatori{ User_repository_file("testUtilizatori.cvs") };
	FileRepoMesaje repoMesaje{ FileRepoMesaje("testMesaje.cvs") };
	Event_repository evr;
	EntityService service{ EntityService(repoPrietenie,repoUtilizatori,repoMesaje,evr) };
	service.remove_friend(1, 2);
	assert(repoPrietenie.get_all_friends().get_size() == 3);
	service.remove_friend(7, 2);
	assert(repoPrietenie.get_all_friends().get_size() == 2);
	try
	{
		service.remove_friend(1, 2);
		assert(false);
	}
	catch (std::exception err)
	{
		assert(true);
	}
	try
	{
		service.remove_friend(100, 2);
		assert(false);
	}
	catch (std::exception err)
	{
		assert(true);
	}
	try
	{
		service.remove_friend(-1, 2);
		assert(false);
	}
	catch (std::exception err)
	{
		assert(true);
	}
}

void Teste::testTrimiteMesaj()
{
	initializeaza();
	Friendship_repository repoPrietenie{ Friendship_repository("testPrietenii.cvs") };
	User_repository_file repoUtilizatori{ User_repository_file("testUtilizatori.cvs") };
	FileRepoMesaje repoMesaje{ FileRepoMesaje("testMesaje.cvs") };
	Event_repository evr;
	EntityService service{ EntityService(repoPrietenie,repoUtilizatori,repoMesaje,evr) };
	service.add_message(2, 10, "salut");
	List<Message> toateMesajele = repoMesaje.get_all_messages();
	Message msg = toateMesajele.at(toateMesajele.get_size() - 1);
	assert(msg.get_id_user_sender() == 2);
	assert(msg.get_id_user_receiver() == 10);
	assert(msg.get_message() == "salut");

	try {
		service.add_message(4, 10, "Mai");
		assert(false);
	}
	catch (std::exception error)
	{
		assert(true);
	}

	try {
		service.add_message(1, 10, "Mai");
		assert(false);
	}
	catch (std::exception error)
	{
		assert(true);
	}
	try {
		service.add_message(10, 10, "Mai");
		assert(false);
	}
	catch (std::exception error)
	{
		assert(true);
	}
}

void Teste::testStergeUtilizator()
{
	initializeaza();
	Friendship_repository repoPrietenie{ Friendship_repository("testPrietenii.cvs") };
	User_repository_file repoUtilizatori{ User_repository_file("testUtilizatori.cvs") };
	FileRepoMesaje repoMesaje{ FileRepoMesaje("testMesaje.cvs") };
	Event_repository evr;
	EntityService service{ EntityService(repoPrietenie,repoUtilizatori,repoMesaje,evr) };
	User utilizator = User(2, "Rusu", "Ionel", 20);
	service.remove_user(2, "Rusu", "Ionel", 20);
	assert(repoUtilizatori.get_user_with_id(2).get_user_id()==-1);
	try
	{
		service.remove_user(-2, "", "", 3);
		assert(false);
	}
	catch (std::exception err)
	{
		assert(true);
	}
	try
	{
		service.remove_user(40, "Ioana", "Rusa", 19);
		assert(false);
	}
	catch (std::exception err)
	{
		assert(true);
	}

}

void Teste::testAdaugaUtilizator()
{
	initializeaza();
	Friendship_repository repoPrietenie{ Friendship_repository("testPrietenii.cvs") };
	User_repository_file repoUtilizatori{ User_repository_file("testUtilizatori.cvs") };
	FileRepoMesaje repoMesaje{ FileRepoMesaje("testMesaje.cvs") };
	Event_repository evr;
	EntityService service{ EntityService(repoPrietenie,repoUtilizatori,repoMesaje,evr) };
	service.add_user(99, "Ionica", "Mircea", 40);
	assert(repoUtilizatori.get_all_users().get_size() == 5);
	try
	{
		service.add_user(99, "Ionica", "Mircea", 40); //mai adaugam odata acelasi utilizator
		assert(false);
	}
	catch (std::exception err)
	{
		assert(true);
	}
	try
	{
		service.add_user(0, "", "Mircea", 40);//utilizator invalid
		assert(false);
	}
	catch (std::exception err)
	{
		assert(true);
	}

}

void Teste::testStergeMesaj()
{
	initializeaza();
	Friendship_repository repoPrietenie{ Friendship_repository("testPrietenii.cvs") };
	User_repository_file repoUtilizatori{ User_repository_file("testUtilizatori.cvs") };
	FileRepoMesaje repoMesaje{ FileRepoMesaje("testMesaje.cvs") };
	Event_repository evr;
	EntityService service{ EntityService(repoPrietenie,repoUtilizatori,repoMesaje,evr) };
	service.add_message(1, 7, "Numai bine");
	service.delete_message(7, 1, "bine, tu?");
	assert(repoMesaje.get_all_messages().get_size() == 2);
	try
	{
		service.delete_message(7, 1, "bine, tu?");
		assert(false);
	}
	catch (std::exception err)
	{
		assert(true);
	}
}
void Teste::testPrieteniiUtilizator()
{
	initializeaza();
	Friendship_repository repoPrietenie{ Friendship_repository("testPrietenii.cvs") };
	User_repository_file repoUtilizatori{ User_repository_file("testUtilizatori.cvs") };
	FileRepoMesaje repoMesaje{ FileRepoMesaje("testMesaje.cvs") };
	Event_repository evr;
	EntityService service{ EntityService(repoPrietenie,repoUtilizatori,repoMesaje,evr) };
	List<User> prieteniiUtilizator = service.get_friends(1);
	assert(prieteniiUtilizator.get_size() == 2);
	assert(prieteniiUtilizator.at(0).get_user_id() == 2);
	assert(prieteniiUtilizator.at(1).get_user_id() == 7);
	try
	{
		service.get_friends(4);
		assert(false);
	}
	catch (std::exception err)
	{
		assert(true);
	}

}

void Teste::testGetConversatie()
{
	initializeaza();
	Friendship_repository repoPrietenie{ Friendship_repository("testPrietenii.cvs") };
	User_repository_file repoUtilizatori{ User_repository_file("testUtilizatori.cvs") };
	FileRepoMesaje repoMesaje{ FileRepoMesaje("testMesaje.cvs") };
	Event_repository evr;
	EntityService service{ EntityService(repoPrietenie,repoUtilizatori,repoMesaje,evr) };
	List<Message>conversatie = service.get_chat(1, 7);
	assert(conversatie.get_size() == 2);
	assert(conversatie.at(0).get_message() == "salut, ce mai faci?");
	assert(conversatie.at(1).get_message() == "bine, tu?");
	try
	{
		service.get_chat(1, 100);
		assert(false);
	}
	catch (std::exception err)
	{
		assert(true);
	}
}

void Teste::runTeste()
{
	testRepos();
	testAdaugaPrietenie();
	testStergePrietenie();
	testTrimiteMesaj();
	testStergeUtilizator();
	testAdaugaUtilizator();
	testStergeMesaj();
	testPrieteniiUtilizator();
	testGetConversatie();
}
*/