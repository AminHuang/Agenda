#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include "AgendaController.h"

AgendaController::AgendaController():agendaService_() {
    agendaService_.startAgenda();
    currentUser_ = NULL;
    startAgenda();
}

void AgendaController::getOperation(void) {
    std::cout << std::endl;
    std::cout << "------------------------------------------------------"
              << std::endl;
    std::cout << "Action :" << std::endl;
    std::cout << "l   - log in Agenda by user name and password" << std::endl;
    std::cout << "r   - register an Agenda account" << std::endl;
    std::cout << "q   - quit Agenda" << std::endl;
    std::cout << "------------------------------------------------------"
              << std::endl;
    std::cout << std::endl;

    std::string op;
    while (1) {
      std::cout << std::endl << "Agenda";
      if (currentUser_ == NULL)
        std::cout << " : ~$ ";
      else
        std::cout << "@" << currentUser_->getName() << " : # ";

      std::cin >> op;
      if (!executeOperation(op))
         break;
    }
}

void AgendaController::startAgenda(void) {
    agendaService_.startAgenda();
}

bool AgendaController::executeOperation(std::string op) {
    if (currentUser_ == NULL) {
      if (op == "l") userLogIn();
      else if (op == "r") userRegister();
      else if (op == "q") {
        quitAgenda();
        return false;
        } else {
          std::cout << "[error] No commond found!" << std::endl;
        }
    } else {
        if (op == "o") userLogOut();
        else if (op == "dc") deleteUser();
        else if (op == "lu") listAllUsers();
        else if (op == "cm") createMeeting();
        else if (op == "la") listAllMeetings();
        else if ( op == "las" ) listAllSponsorMeetings();
        else if ( op == "lap" ) listAllParticipateMeetings();
        else if ( op == "qm" ) queryMeetingByTitle();
        else if ( op == "qt" ) queryMeetingByTimeInterval();
        else if ( op == "dm" ) deleteMeetingByTitle();
        else if ( op == "da" ) deleteAllMeetings();
        else if ( op == "up" ) updatePassword();
        else std::cout << "[error] No commond found!" << std::endl; 
      }
     return true;
}

void AgendaController::userLogIn(void) {
    std::string userName, Password;
    std::cout << std::endl;
    std::cout << "[log in] [user name] [password]" << std::endl;
    std::cout << "[log in] ";
    std::cin >> userName >> Password;
    currentUser_ = agendaService_.userLogIn(userName, Password);
    if (currentUser_ == NULL) {
      std::cout << "[error] log in fail!" << std::endl;
      std::cout << "[log in] Want to modify your password?[Y/N]";
      std::string yor;
      std::cin >> yor;
      if (yor == "Y" || yor == "y") {
         std:: string email, phone, newPassword;
         User* user = agendaService_.findUserByName(userName);
         std::cout << "[log in] Your email: ";
         std::cin >> email;
         std::cout << "[log in] Your phone: ";
         std::cin >> phone;
         if (email == user->getEmail() && phone == user->getPhone()) {
           std::cout << "[log in] Input new password: ";
           std::cin >> newPassword;
            if (agendaService_.updateUserPassword(*user, newPassword))
               std::cout << "[log in] change password succeed!" << std::endl;
            else
               std::cout << "[log in] change password fail!" << std::endl;
         } else {
             std::cout << "[log in] email or phone wrong!" << std::endl;
           }
      }
    } else {
    std::cout << "[log in] succeed!" << std::endl;
    std::cout << std::endl;
    std::cout << "------------------------------------------------------"
              << std::endl;
    std::cout << "Action :" << std::endl;
    std::cout << "o   - log out Agenda" << std::endl;
    std::cout << "dc  - delete Agenda account" << std::endl;
    std::cout << "lu  - list all Agenda account" << std::endl;
    std::cout << "cm  - create a meeting" << std::endl;
    std::cout << "la  - list all meetings" << std::endl;
    std::cout << "las - list all sponsor meetings" << std::endl;
    std::cout << "lap - list all participate meetings" << std::endl;
    std::cout << "qm  - query meeting by title" << std::endl;
    std::cout << "qt  - query meeting by time interval" << std::endl;
    std::cout << "dm  - delete meeting by title" << std::endl;
    std::cout << "da  - delete all meetings" << std::endl;
    std::cout << "up  - update password" << std::endl;
    std::cout << "------------------------------------------------------"
              << std::endl;
    std::cout << std::endl;
    }
}

void AgendaController::userRegister(void) {
    std::string userName, password, email, phone;
    std::cout << std::endl;
    std::cout << "[register] [user name] [password] [email] [phone]"
              << std::endl;
    std::cout << "[register] ";
    std::cin >> userName >> password >> email >> phone;
    if (!checkName(userName))
      std::cout << "[error] User name only use numbers or letters!"
                << std::endl;
    else if (!checkEmail(email))
      std::cout << "[error] email wrong!" << std::endl;
    else if (!checkPhone(phone))
      std::cout << "[error] phone wrong!" << std::endl;
    else if (agendaService_.userRegister(userName, password, email, phone))
      std::cout << "[register] succeed!" << std::endl;
    else
      std::cout << "[error] register fail!" << std::endl;
}

void AgendaController::quitAgenda(void) {
    agendaService_.quitAgenda();
}

void AgendaController::userLogOut(void) {
    currentUser_ = NULL;
    std::cout << std::endl;
    std::cout << "------------------------------------------------------"
              << std::endl;
    std::cout << "Action :" << std::endl;
    std::cout << "l   - log in Agenda by user name and password" << std::endl;
    std::cout << "r   - register an Agenda account" << std::endl;
    std::cout << "q   - quit Agenda" << std::endl;
    std::cout << "------------------------------------------------------"
              << std::endl;
    std::cout << std::endl;
}

void AgendaController::deleteUser(void) {
    std::cout << std::endl;
    if (agendaService_.deleteUser(*currentUser_)) {
      std::cout << "[delete agenda account] succeed!" << std::endl;
      currentUser_ = NULL;
    } else {
      std::cout << "[error] delete agenda account fail!" << std::endl;
      }
}

void AgendaController::listAllUsers(void) {
    std::cout << std::endl;
    std::cout << "[list all users]" << std::endl;
    std::cout << std::endl;
    printf("%-8s%-16s%-12s\n", "name", "email", "phone");
    std::list<User> listUser = agendaService_.listAllUsers();
    std::list<User>::iterator iter = listUser.begin();
    for (iter; iter != listUser.end(); iter++) {
      printf("%-8s%-16s%-12s\n", (iter->getName()).c_str(),
                                 (iter->getEmail()).c_str(),
                                 (iter->getPhone()).c_str());
    }
}

void AgendaController::createMeeting(void) {
    std::cout << std::endl;
    std::string title, participator, stime, etime;
    std::cout << "[create meeting] [title] [participator] " <<
            "[start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" <<
            std::endl;
    std::cout << "[create meeting] ";
    std::cin >> title >> participator >> stime >> etime;
    bool succeed = agendaService_.createMeeting(currentUser_->getName(),
                                         title, participator, stime, etime);
    if (succeed)
      std::cout << "[create meeting] succeed!" << std::endl;
    else
      std::cout << "[error] create meeting fail!" << std::endl;
}

void AgendaController::listAllMeetings(void) {
    std::cout << std::endl;
    std::cout << "[list all meetings]" << std::endl;
    std::cout << std::endl;
    printf("%-15s%-12s%-15s%-20s%-20s\n", "title", "sponsor", "participator",
                                           "start time", "end time");
    std::list<Meeting> listMeeting = agendaService_.listAllMeetings(
                                                     currentUser_->getName());
    std::list<Meeting>::iterator iter = listMeeting.begin();
    if (currentUser_ != NULL) {
    for (iter; iter != listMeeting.end(); iter++) {
      printf("%-15s%-12s%-15s%-20s%-20s\n", (iter->getTitle()).c_str(),
                                          (iter->getSponsor()).c_str(),
                                     (iter->getParticipator()).c_str(),
                    (Date::dateToString(iter->getStartDate())).c_str(),
                      (Date::dateToString(iter->getEndDate())).c_str());
    }
    }
}

void AgendaController::listAllSponsorMeetings(void) {
    std::cout << std::endl;
    std::cout << "[list all sponsor meetings]" << std::endl;
    std::cout << std::endl;
    printf("%-15s%-12s%-15s%-20s%-20s\n", "title", "sponsor", "participator",
                                           "start time", "end time");
    std::list<Meeting> listMeeting = agendaService_.listAllSponsorMeetings(
                                                    currentUser_->getName());
    std::list<Meeting>::iterator iter = listMeeting.begin();
    for (iter; iter != listMeeting.end(); iter++) {
      printf("%-15s%-12s%-15s%-20s%-20s\n", (iter->getTitle()).c_str(),
                                          (iter->getSponsor()).c_str(),
                                     (iter->getParticipator()).c_str(),
                    (Date::dateToString(iter->getStartDate())).c_str(),
                      (Date::dateToString(iter->getEndDate())).c_str());
    }
}

void AgendaController::listAllParticipateMeetings(void) {
    std::cout << std::endl;
    std::cout << "[list all participate meetings]" << std::endl;
    std::cout << std::endl;
    printf("%-15s%-12s%-15s%-20s%-20s\n", "title", "sponsor", "participator",
                                           "start time", "end time");
  std::list<Meeting> listMeeting = agendaService_.listAllParticipateMeetings(
                                                    currentUser_->getName());
    std::list<Meeting>::iterator iter = listMeeting.begin();
    for (iter; iter != listMeeting.end(); iter++) {
      printf("%-15s%-12s%-15s%-20s%-20s\n", (iter->getTitle()).c_str(),
                                          (iter->getSponsor()).c_str(),
                                     (iter->getParticipator()).c_str(),
                    (Date::dateToString(iter->getStartDate())).c_str(),
                      (Date::dateToString(iter->getEndDate())).c_str());
    }
}

void AgendaController::queryMeetingByTitle(void) {
    std::cout << std::endl;
    std::cout << "[query meeting] [title]" << std::endl;
    std::cout << "[query meeting] ";
    std::string title;
    std::cin >> title;
    std::cout << std::endl;
    printf("%-12s%-15s%-20s%-20s\n", "sponsor", "participator",
                                       "start time", "end time");
    Meeting* meeting = NULL;
    meeting = agendaService_.meetingQuery(title);
    printf("%-12s%-15s%-20s%-20s\n", (meeting->getSponsor()).c_str(),
                                     (meeting->getParticipator()).c_str(),
                    (Date::dateToString(meeting->getStartDate())).c_str(),
                      (Date::dateToString(meeting->getEndDate())).c_str());
}

void AgendaController::queryMeetingByTimeInterval(void) {
    std::cout << std::endl;
    std::cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)]" <<
            " [end time(yyyy-mm-dd/hh:mm)]" << std::endl;
    std::cout << "[query meetings] ";
    std::string stime, etime;
    std::cin >> stime >> etime;
    std::cout << std::endl;
    printf("%-15s%-12s%-15s%-20s%-20s\n", "title", "sponsor", "participator",
                                           "start time", "end time");
  std::list<Meeting> listMeeting = agendaService_.meetingQuery(
                                       currentUser_->getName(), stime, etime);
    std::list<Meeting>::iterator iter = listMeeting.begin();
    for (iter; iter != listMeeting.end(); iter++) {
      printf("%-15s%-12s%-15s%-20s%-20s\n", (iter->getTitle()).c_str(),
                                          (iter->getSponsor()).c_str(),
                                     (iter->getParticipator()).c_str(),
                    (Date::dateToString(iter->getStartDate())).c_str(),
                      (Date::dateToString(iter->getEndDate())).c_str());
    }
}

void AgendaController::deleteMeetingByTitle(void) {
    std::cout << std::endl;
    std::cout << "[delete meeting] [title]" << std::endl;
    std::cout << "[delete meeting] ";
    std::string title;
    std::cin >> title;
    std::cout << std::endl;
    bool succeed = agendaService_.deleteMeeting(currentUser_->getName(),
                                                                title);
    if (succeed)
      std::cout << "[delete meeting] succeed!" << std::endl;
    else
      std::cout << "[error] delete meeting fail!" << std::endl;
}

void AgendaController::deleteAllMeetings(void) {
    std::cout << std::endl;
    bool succeed = agendaService_.deleteAllMeetings(currentUser_->getName());
    if (succeed)
      std::cout << "[delete all meetings] succeed!" << std::endl;
    else
      std::cout << "[error] delete all meetings fail!" << std::endl;
}

void AgendaController::printMeetings(std::list<Meeting> meetings) {
    std::cout <<std:: endl;
    printf("%-15s%-12s%-15s%-20s%-20s\n", "title", "sponsor", "participator",
                                           "start time", "end time");
    std::list<Meeting>::iterator iter = meetings.begin();
    for (iter; iter != meetings.end(); iter++) {
      printf("%-15s%-12s%-15s%-20s%-20s\n", (iter->getTitle()).c_str(),
                                          (iter->getSponsor()).c_str(),
                                     (iter->getParticipator()).c_str(),
                    (Date::dateToString(iter->getStartDate())).c_str(),
                      (Date::dateToString(iter->getEndDate())).c_str());
    }
}

bool AgendaController::checkEmail(std::string email) {
    int k = 2;
    for (int i = 0; email[i] != '\0'; i++)
      if (email[i] == '@' || email[i] == '.' || email[i] >= '0' &&
          email[i] <= '9' || email[i] >= 'A' && email[i] <='Z' ||
          email[i] >= 'a' && email[i] <='z') {
         continue;
      } else {
         k=-1;
         break;
        }
     if (k == -1) return false;
    int j = 0;
    while (email[j] != '@' && email[j] != '\0') {
      if (email[j] == '.') {
         k = -1;
         break;
      }
      j++;
     }
    if (!j) return false;
      j++;
    if (email[j] == '\0' || k == -1) return false;
    for (int i = j; email[i] != '\0'; i++) {
      if (email[i] == '.') {
         if (i > j && email[i+1] != '\0') {
           j = i+1;
           k++;
           continue;
         } else {
           k = -1;
           break;
           }
      }
      if (email[i] == '@') {
        k = -1;
        break;
      }
    }
    if (k > 2)
      return true;
    else
      return false;
}

bool AgendaController::checkPhone(std::string phone) {
    if (phone.length() > 11) {
      return false;
    } else {
      for (int i = 0; i < phone.length(); i++) {
       if (phone[i] > '9' || phone[i] < '0')
         return false;
      }
      }
    return true;
}

bool AgendaController::checkName(std::string userName) {
      for (int i = 0; i < userName.length() - 1; i++) {
       if (!((userName[i] <= '9' && userName[i] >= '0') ||
            (userName[i] <= 'z' && userName[i] >= 'a') ||
            (userName[i] <= 'Z' && userName[i] >= 'A')))
         return false;
      }
    return true;
}

void AgendaController::updatePassword(void) {
    std::string oldPassword1, oldPassword2, newPassword;
    for(int i = 0; i < 5; i++) {
    std::cout << "[update password] Input old password: ";
    std::cin >> oldPassword1;
    if (oldPassword1 == currentUser_->getPassword())
      break;
    else
      std::cout << "[error] password wrong!" << std::endl << std::endl;
    }
    std::cout << "[update password] Input old password again: ";
    std::cin >> oldPassword2;
    if (oldPassword2 == currentUser_->getPassword()) {
      std::cout << "[update password] Input new password: ";
      std::cin >> newPassword;
      if (agendaService_.updateUserPassword(*currentUser_, newPassword))
        std::cout << "[update password] succeed!" << std::endl;
      else
        std::cout << "[update password] update password fail!" << std::endl;
    }
}
