cc = g++
exe = Agenda
obj = Agenda.o User.o Date.o Meeting.o FileManage.o UserManage.o MeetingManage.o AgendaService.o AgendaController.o

$(exe):$(obj)
	$(cc) -o $(exe) $(obj)

Agenda.o:Agenda.cpp AgendaController.h
	$(cc) -c Agenda.cpp

User.o:User.h User.cpp
	$(cc) -c User.cpp

Date.o:Date.h Date.cpp
	$(cc) -c Date.cpp

Meeting.o:Meeting.h Meeting.cpp Date.h Date.cpp
	$(cc) -c Meeting.cpp

MeetingManage.o:Meeting.h Meeting.cpp MeetingManage.h MeetingManage.cpp
	$(cc) -c MeetingManage.cpp

UserManage.o:User.h User.cpp UserManage.h UserManage.cpp
	$(cc) -c UserManage.cpp

FileManage.o:FileManage.h FileManage.cpp User.cpp Meeting.cpp Date.cpp
	$(cc) -c FileManage.cpp

AgendaService.o:AgendaService.h AgendaService.cpp UserManage.h UserManage.cpp MeetingManage.h MeetingManage.cpp FileManage.h FileManage.cpp User.h User.cpp Meeting.h Meeting.cpp Date.h Date.cpp
	$(cc) -c AgendaService.cpp

AgendaController.o:AgendaController.h AgendaController.cpp AgendaService.cpp UserManage.cpp MeetingManage.cpp FileManage.cpp User.cpp Meeting.cpp Date.cpp
	$(cc) -c AgendaController.cpp

clean:
	rm Agenda  *.o
