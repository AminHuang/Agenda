#include "AgendaService.h"

AgendaService::AgendaService() {
    userManage_ = UserManage::getInstance();
    meetingManage_ = MeetingManage::getInstance();
    fileManage_ = FileManage::getInstance();
}

AgendaService::~AgendaService() {
    delete userManage_;
    delete meetingManage_;
    delete fileManage_;
}

User* AgendaService::userLogIn(std::string userName, std::string password) {
    User* user = userManage_->findUserByName(userName);
    if (user != NULL && (password == user->getPassword())) {
      return user;
    } else {
      return NULL;
      }
}

bool AgendaService::userRegister(std::string userName, std::string password,
                  std::string email, std::string phone) {
    bool succeed = userManage_->createUser(userName, password, email, phone);
    return succeed;
}

bool AgendaService::deleteUser(User user) {
    bool succeed = userManage_->deleteUser(user);
    return succeed;
}

std::list<User> AgendaService::listAllUsers(void) {
    return userManage_->listAllUsers();
}

bool AgendaService::createMeeting(std::string userName, std::string title,
                   std::string participator, std::string startDate,
                   std::string endDate) {
    bool succeed = false;

    if (userManage_->findUserByName(userName) != NULL &&
       userManage_->findUserByName(participator) != NULL)
    succeed = meetingManage_->addMeeting(userName, participator,
           Date::stringToDate(startDate), Date::stringToDate(endDate), title);
    return succeed;
}

Meeting* AgendaService::meetingQuery(std::string title) {
    return meetingManage_->queryMeetingByTitle(title);
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName,
                                std::string startDate, std::string endDate) {
    return meetingManage_->queryMeetingsByTime(userName,
         Date::stringToDate(startDate), Date::stringToDate(endDate));
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
    return meetingManage_->listAllMeetings(userName);
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
    return meetingManage_->listAllSponsorMeetings(userName);
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(
                                                   std::string userName) {
    return meetingManage_->listAllParticipateMeetings(userName);
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
    bool succeed = false;
    if (userManage_->findUserByName(userName) != NULL &&
        meetingManage_->queryMeetingByTitle(title) != NULL) {
    succeed = meetingManage_->deleteMeeting(userName, title);
    }
    return succeed;
}

bool AgendaService::deleteAllMeetings(std::string userName) {
    bool succeed = meetingManage_->deleteAllMeetings(userName);
    return succeed;
}

void AgendaService::startAgenda(void) {
    userManage_->initUsersList(fileManage_->readUsersFromFile());
    meetingManage_->initMeetingsList(fileManage_->readMeetingsFromFile());
}

void AgendaService::quitAgenda(void) {
    fileManage_->writeUsersToFile(userManage_->listAllUsers());
    fileManage_->writeMeetingsToFile(meetingManage_->acquireMeetingsList());
}

bool AgendaService::updateUserPassword(User user, std::string newPassword) {
    return userManage_->updateUserPassword(user, newPassword);
}

User* AgendaService::findUserByName(std::string userName) {
    return userManage_->findUserByName(userName);
}
