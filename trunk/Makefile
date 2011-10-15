MOB_AG_SYS = Mobile_agent_system
__start__: $(MOB_AG_SYS)

CPPFLAGS=-Wall -g -pedantic -Iinc

OBJDIR = obj/
SRCDIR = src/
INCDIR = src/
BINDIR = bin/

BINARY := $(BINDIR)$(MOB_AG_SYS)
#Tutaj dopisujemy zrodla z .cpp, koniec wiersza -> \

SRCS = \
main.cpp 

#Obiekty
OBJS = $(SRCS:.cpp=.o)
P_OBJS = $(addprefix $(OBJDIR),$(OBJS))
#Glowny program
$(MOB_AG_SYS): $(P_OBJS)
	g++ ${LDFLAGS} -o $(BINARY) $(P_OBJS)
#Poszczegolne klasy
$(OBJDIR)%.o: $(SRCDIR)%.cpp $(INCDIR)%.hh
	g++ -c ${CPPFLAGS} $< -o $@


clean:
	\rm -f $(OBJDIR)*.o $(SRCDIR)*~ $(INCDIR)*~ $(BINARY)
doc: __start_doxygen__

__start_doxygen__:
	doxygen zamp2.doxy
help:
	@echo
	@echo " make        - tworzenie i uruchomienie aplikacji"
	@echo " make clean  - usuniecie produktow kompilacji i konsolidacji"
	@echo " make doc    - tworzenie dokumentacji w doxy"
	@echo
