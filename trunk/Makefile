__start__: Mobile_agent_system

CPPFLAGS=-Wall -g -pedantic -Iinc

OBJDIR = obj/
SRCDIR = src/
INCDIR = src/
#Tutaj dopisujemy zrodla z .cpp, koniec wiersza -> \

SRCS = \
main.cpp 

#Obiekty i naglowki
HDRS = $(SRCS:.cpp=.hh)
OBJS = $(SRCS:.cpp=.o)

P_SRCS = $(addprefix src/,SRCS)
P_HDRS = $(addprefix src/,HDRS)
P_OBJS = $(addprefix obj/,$(OBJS))

Mobile_agent_system: $(P_OBJS)
	g++ ${LDFLAGS} -o $@ $(P_OBJS)

$(P_OBJS): %.cpp %.hh
	g++ -c ${CPPFLAGS} $< -o *@


clean:
	\rm -f obj/*.o src/*~ inc/*~ lib/*.so zamp2 
tar:
	tar -czf ../zad2.tar.gz ./
wtyczka: lib/turn90.so
	@echo "Biblioteka utworzona"
lib/turn90.so: src/command4turn90.cpp inc/command4turn90.hh 
	g++ ${LIBFLAGS}  -o lib/turn90.so src/command4turn90.cpp -lm 
doc: __start_doxygen__

__start_doxygen__:
	doxygen zamp2.doxy
help:
	@echo
	@echo " make        - tworzenie i uruchomienie aplikacji"
	@echo " make clean  - usuniecie produktow kompilacji i konsolidacji"
	@echo " make tar  - utworzenie archiwum zawierajacego projekt"
	@echo " make wtyczka  - kompilacja wtyczki turn90"
	@echo
