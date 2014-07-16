#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "UserManage.h"
#include "MeetingManage.h"

UserManage::UserManage() {
}

UserManage::~UserManage() {
    instanceFlag_ = false;
    instance_ = NULL;
}

bool UserManage::instanceFlag_ = false;
UserManage* UserManage::instance_ = NULL;

UserManage* UserManage::getInstance(void) {
    if (!instanceFlag_) {
     instance_ = new UserManage();
     instanceFlag_ = true;
     return instance_;
    } else {
     return instance_;
    }
}

void UserManage::initUsersList(std::list<User> users) {
    users_ = users;
}

User* UserManage::findUserByName(std::string userName) {
    std::list<User>::iterator iter = users_.begin();
    for (iter; iter != users_.end(); iter++) {
      if (userName == (*iter).getName()) {
        return &(*iter);
       }
    }

    return NULL;
}

bool UserManage::createUser(std::string userName, std::string userPassword,
                std::string userEmail, std::string userPhone) {
    if (findUserByName(userName) != NULL) {
     return false;
    } else {
     User user(userName, userPassword, userEmail, userPhone);
     users_.push_back(user);
     return true;
    }
}

bool UserManage::deleteUser(User user) {
    std::list<User>::iterator iter = users_.begin();
    if (iter == users_.end())
      return false;
    MeetingManage* mM = MeetingManage::getInstance();
    if (!(mM->listAllMeetings(user.getName())).empty())
      return false;
    for ( iter; iter != users_.end(); iter++ ) {
      if ( user.getName() == (*iter).getName() ) {
          users_.erase(iter);
          return true;
      }
    }
    return false;
}

bool UserManage::updateUserPassword(User user, std::string newPassword) {
    std::list<User>::iterator iter = users_.begin();
    if (iter == users_.end())
      return false;
    for ( iter; iter != users_.end(); iter++ ) {
      if (user.getName() == (*iter).getName()) {
           (*iter).setPassword(newPassword);
          return true;
      }
    }
    return false;
}

bool UserManage::updateUserEmail(User user, std::string newEmail) {
    std::list<User>::iterator iter = users_.begin();
    if (iter == users_.end())
      return false;
    for (iter; iter != users_.end(); iter++) {
      if (user.getName() == (*iter).getName()) {
          (*iter).setEmail(newEmail);
          return true;
      }
    }
    return false;
}

bool UserManage::updateUserPhone(User user, std::string newPhone) {
    std::list<User>::iterator iter = users_.begin();
    if (iter == users_.end())
      return false;
    for (iter; iter != users_.end(); iter++) {
      if (user.getName() == (*iter).getName()) {
          (*iter).setPhone(newPhone);
          return true;
      }
    }
    return false;
}

std::list<User> UserManage::listAllUsers(void) {
    return users_;
}
