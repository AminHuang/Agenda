#include <iostream>
#include <algorithm>
#include "MeetingManage.h"
#include "Meeting.h"

MeetingManage::MeetingManage() {
}

MeetingManage::~MeetingManage() {
    instanceFlag_ = false;
    instance_ = NULL;
}

bool MeetingManage::instanceFlag_ = false;
MeetingManage* MeetingManage::instance_ = NULL;

MeetingManage* MeetingManage::getInstance() {
    if (!instanceFlag_) {
     instance_ = new MeetingManage();
     instanceFlag_ = true;
     return instance_;
    } else {
     return instance_;
    }
}

void MeetingManage::initMeetingsList(std::list<Meeting> meetings) {
    meetings_ = meetings;
}

std::list<Meeting> MeetingManage::acquireMeetingsList(void) {
    return meetings_;
}

Meeting* MeetingManage::queryMeetingByTitle(std::string title) {
    std::list<Meeting>::iterator iter = meetings_.begin();
    for (iter; iter != meetings_.end(); iter++) {
      if ( (*iter).getTitle() == title ) {
         return &(*iter);
      }
    }
    return NULL;
}

bool MeetingManage::addMeeting(std::string sponspor, std::string participator,
                  Date stime, Date etime, std::string title) {
    if (queryMeetingByTitle(title) != NULL)
        return false;
    if (!(stime.isValid(stime) && etime.isValid(etime) || stime > etime))
      return false;
    if (!(queryMeetingsByTime(sponspor, stime, etime).empty() ||
       queryMeetingsByTime(participator, stime, etime).empty()))
      return false;

    Meeting meeting(sponspor, participator, stime, etime, title);
    meetings_.push_back(meeting);
    return true;
}

bool MeetingManage::deleteMeeting(std::string userName, std::string title) {
    std::list<Meeting>::iterator iter = meetings_.begin();
    if (meetings_.empty())
      return false;
    for (iter; iter != meetings_.end(); iter++) {
      if ( userName == (*iter).getSponsor() && (*iter).getTitle() == title ) {
       meetings_.erase(iter);
       return true;
      }
    }
    return false;
}

bool MeetingManage::deleteAllMeetings(std::string userName) {
    bool succeed = false;
    std::list<Meeting>::iterator iter = meetings_.begin();
    if (meetings_.empty())
      return false;
    for (iter; iter != meetings_.end(); iter++) {
     if ( userName == (*iter).getSponsor() ) {
       iter = meetings_.erase(iter++);
       succeed = true;
    }
    }
    return succeed;
}

bool MeetingManage::updateMeetingParticipator(std::string title,
                                              std::string newParticipator) {
    std::list<Meeting>::iterator iter = meetings_.begin();
    for (iter; iter != meetings_.end(); iter++) {
     if (title == (*iter).getTitle()) {
       (*iter).setParticipator(newParticipator);
       return true;
     }
    }
    return false;
}

bool MeetingManage::updateMeetingStartDate(std::string title,
                                           Date newStartDate) {
    std::list<Meeting>::iterator iter = meetings_.begin();
    for (iter; iter != meetings_.end(); iter++) {
     if (title == (*iter).getTitle()) {
       (*iter).setStartDate(newStartDate);
       return true;
     }
    }
    return false;
}

bool MeetingManage::updateMeetingEndDate(std::string title, Date newEndDate) {
    std::list<Meeting>::iterator iter = meetings_.begin();
    for (iter; iter != meetings_.end(); iter++) {
     if (title == (*iter).getTitle()) {
       (*iter).setEndDate(newEndDate);
       return true;
     }
    }
    return false;
}

std::list<Meeting> MeetingManage::queryMeetingsByTime(std::string userName,
                                                   Date stime, Date etime) {
    std::list<Meeting> ameeting, tmp;
    if (!Date::isValid(stime) || !Date::isValid(etime))
        return tmp;
    if (stime > etime)
        return tmp;

    ameeting = listAllMeetings(userName);
    std::list<Meeting>::iterator it;
    for (it = ameeting.begin(); it != ameeting.end(); it++ )
        if ((stime <= it->getEndDate() && it->getEndDate() <= etime) ||
             (stime <= it->getStartDate() && it->getStartDate() <= etime) ||
             (stime <= it->getStartDate() && it->getEndDate() <= etime) ||
             (it->getStartDate() <= stime && etime <= it->getEndDate()))
            tmp.push_back(*it);
    return tmp;
}

std::list<Meeting> MeetingManage::listAllMeetings(std::string userName) {
    std::list<Meeting> meetingsName;
    std::list<Meeting>::iterator iter = meetings_.begin();
    for (iter; iter != meetings_.end(); iter++) {
     if ( userName == (*iter).getSponsor() ||
        userName == (*iter).getParticipator() ) {
     meetingsName.push_back(*iter);
     }
    }
    return meetingsName;
}

std::list<Meeting> MeetingManage::listAllSponsorMeetings(std::string userName) {
    std::list<Meeting> meetingsName;
    std::list<Meeting>::iterator iter = meetings_.begin();
    for (iter; iter != meetings_.end(); iter++) {
     if ( userName == (*iter).getSponsor() ) {
       meetingsName.push_back(*iter);
     }
    }
    return meetingsName;
}

std::list<Meeting> MeetingManage::listAllParticipateMeetings(
                                                   std::string userName) {
    std::list<Meeting> meetingsName;
    std::list<Meeting>::iterator iter = meetings_.begin();
    for (iter; iter != meetings_.end(); iter++) {
     if ( userName == (*iter).getParticipator() ) {
         meetingsName.push_back(*iter);
     }
    }
    return meetingsName;
}
