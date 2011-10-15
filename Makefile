# Stworzone przez MICHAL WCISLO 15.10.2011
#
#			Nie zmianiajcie tego!!! 
#
# Wszystko powinno dzialac bez zadnych zmian.
# Makefile sam odczytuje pliki cpp i ogarnia wszystkie zaleznosci.
# W razie klopotow dajcie znac wcisk88@gmail.com, 163111@student.pwr.wroc.pl


MOB_AG_SYS = Mobile_agent_system
all: $(MOB_AG_SYS)

CXX = g++
CPPFLAGS=-Wall -g -pedantic

OBJDIR = obj/
SRCDIR = src/
INCDIR = src/
BINDIR = bin/
DEPDIR = dep/
#Binarka
BINARY := $(BINDIR)$(MOB_AG_SYS)

#Zrodla
SRCS := $(patsubst $(SRCDIR)%,%,$(shell ls $(SRCDIR)*.cpp))

#Obiekty
OBJS = $(SRCS:.cpp=.o)
P_OBJS = $(addprefix $(OBJDIR),$(OBJS))

#Glowny program
$(MOB_AG_SYS): $(P_OBJS)
	$(CXX) ${LDFLAGS} -o $(BINARY) $(P_OBJS)
#Poszczegolne klasy
$(OBJDIR)%.o: $(SRCDIR)%.cpp $(DEPDIR)%.d $(INCDIR)%.hh
	$(CXX) -c ${CPPFLAGS} $< -o $@

#Zaleznosci
$(DEPDIR)%.d: $(SRCDIR)%.cpp
	$(CXX) $(CPPFLAGS) -MM -MT '$(patsubst $(SRCDIR)%,$(OBJDIR)%,$(patsubst %.cpp,%.o,$<))' $< > $@



clean:
	\rm -f $(OBJDIR)*.o $(SRCDIR)*~ $(INCDIR)*~ $(BINARY)
doc: __start_doxygen__

__start_doxygen__:
	doxygen zamp2.doxy
help:
	@echo
	@echo " make,make all       - budowanie aplikacji"
	@echo " make clean          - usuniecie produktow kompilacji i konsolidacji"
	@echo " make doc            - tworzenie dokumentacji w doxy"
	@echo
