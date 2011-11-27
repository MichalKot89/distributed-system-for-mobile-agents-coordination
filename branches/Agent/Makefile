# Stworzone przez MICHAL WCISLO 15.10.2011
#
#			Nie zmianiajcie tego!!! 
#
# Wszystko powinno dzialac bez zadnych zmian.
# Makefile sam odczytuje pliki cpp i ogarnia wszystkie zaleznosci.
# W razie klopotow dajcie znac wcisk88@gmail.com, 163111@student.pwr.wroc.pl


MOB_AG_SYS = Mobile_agent_system
all: $(MOB_AG_SYS)
		@echo "Koniec make all - stworzono "$(BINARY)

CXX = g++
CPPFLAGS=-Wall -pedantic
DEBUGFLAGS= -g
LDFLAGS=-Wall

OBJDIR = obj/
SRCDIR = src/
INCDIR = src/
BINDIR = bin/
DEPDIR = dep/

debug: CPPFLAGS := $(CPPFLAGS) $(DEBUGFLAGS)
debug: BINARY := $(BINDIR)$(MOB_AG_SYS)_DEBUG
debug: all
		@echo "Koniec make debug - stworzono "$(BINARY)
	

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
	\rm -f $(OBJDIR)*.o $(SRCDIR)*~ $(INCDIR)*~ $(BINARY) $(BINDIR)$(MOB_AG_SYS)_DEBUG
	@echo " Koniec make clean "
doc: __start_doxygen__

__start_doxygen__:
	doxygen GenDoc.doxy
	@echo "Koniec make doc"
help:
	@echo
	@echo " make,make all       - budowanie aplikacji"
	@echo " make clean          - usuniecie produktow kompilacji i konsolidacji"
	@echo " make debug          - budowanie aplikacji pod debugging"
	@echo " make doc            - tworzenie dokumentacji w doxy"
	@echo
