#include <iostream>
#include "UserInterface.h"
#include "FriendShipRepository.h"
#include "UserRepository.h"
#include "MessageRepository.h"
#include "Tests.h"
#include "EventsRepository.h"

int main(){
    User_repository_file usr("Users.cvs");
    Friendship_repository pr;
    Message_repository ms;
    Event_repository evr;
    EntityService se(pr, usr, ms,evr);
    //Teste tests;
    //tests.runTeste();
    UI ui(se);
    ui.start();
}