
proj2: menu.o llist.o
	g++ -Wall -o proj2 llist.o menu.o
llist.o: llist.cpp
	g++ -Wall -c llist.cpp
menu.o: menu.cpp
	g++ -Wall -c menu.cpp  
