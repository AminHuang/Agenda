#include "FileManage.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using std::string;
using std::list;
using std::endl;

FileManage* FileManage::instance_ = NULL;
bool FileManage::instanceFlag_;

FileManage::FileManage() {
    userFileName_ = "user.dat";
    meetingFileName_ = "meeting.dat";
}

FileManage::~FileManage() {
  instance_ = NULL;
  instanceFlag_ = false;
}

FileManage * FileManage::getInstance(void) {
    if (!instanceFlag_) {
        instanceFlag_ = true;
        instance_ = new FileManage;
        return instance_;
    } else {
        return instance_;
    }
}

void FileManage::writeUsersToFile(list<User> users) {
    std::ofstream outFile;
    outFile.open(userFileName_.c_str());
    list<User>::iterator iter = users.begin();
    for (iter; iter != users.end(); iter++) {
      outFile << iter->getName() << ",";
      outFile << iter->getPassword() << ",";
      outFile << iter->getEmail() << ",";
      outFile << iter->getPhone() << " ";
    }
    outFile.close();
}

list<User> FileManage:: readUsersFromFile(void) {
    list<User> userList;
    std::ifstream inFile;
    inFile.open(userFileName_.c_str(), std::ios_base::in);
    string Name, Password, Email, Phone;
    int flag = 0, i;
    string row;
    User user;
    while (!inFile.eof()) {
      getline(inFile, row);
      if (row == "\n" || row == "")
         break;
      for (i = 0; i < row.size(); i++) {
        if (row[i] == ',') {
           flag++;
        } else if (row[i] == ' ') {
            user.setName(Name);
            user.setPassword(Password);
            user.setEmail(Email);
            user.setPhone(Phone);
            userList.push_back(user);
            flag = 0;
            Name = "";
            Password = "";
            Email = "";
            Phone = "";
          } else {
            if (flag == 0)
              Name += row[i];
            else if (flag == 1)
              Password += row[i];
            else if (flag == 2)
              Email += row[i];
            else if (flag == 3)
              Phone += row[i];
           }
        }
     }
     inFile.close();
     return userList;
}

void FileManage::writeMeetingsToFile(list<Meeting> meetings) {
    std::ofstream outFile;
    outFile.open(meetingFileName_.c_str());
    list<Meeting>::iterator iter = meetings.begin();
    for (iter; iter != meetings.end(); iter++) {
      outFile << iter->getSponsor() << ",";
      outFile << iter->getParticipator() << ",";
      outFile << Date::dateToString(iter->getStartDate()) << ",";
      outFile << Date::dateToString(iter->getEndDate()) << ",";
      outFile << iter->getTitle() << " ";
    }
    outFile.close();
}

list<Meeting>  FileManage::readMeetingsFromFile(void) {
    list<Meeting> listMeeting;
    std::ifstream inFile;
    inFile.open(meetingFileName_.c_str(), std::ios_base::in);
    string Spon, Parti, St, En, title;
    int flag = 0;
    string row;
    while (inFile.eof()) {
      getline(inFile, row);
      if (row == "\n" || row == "")
        break;
      for (int i = 0; i < row.size(); i++) {
        if (row[i] == ',') {
          flag++;
        } else if (row[i] == ' ') {
          Meeting c(Spon, Parti, Date::stringToDate(St),
                         Date::stringToDate(En), title);
          listMeeting.push_back(c);
          flag = 0;
          St = "";
          En = "";
          Spon = "";
          Parti = "";
          title = "";
          } else {
            if (flag == 0)
             Spon += row[i];
            else if (flag == 1)
              Parti += row[i];
            else if (flag == 2)
              St += row[i];
            else if (flag == 3)
              En += row[i];
            else if (flag == 4)
              title += row[i];
            }
          }
    }
    inFile.close();
    return listMeeting;
}


