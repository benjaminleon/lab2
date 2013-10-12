#
# Makefile för kalkylatorn, nivå G, GNU GCC (g++)
#
# Filkataloger där andra delar av programet finns.
EXPRESSION = ../Expression

# Diagnosmeddelanden från kompilatorn (g++) filtreras av gccfilter.
CCC = gccfilter -c -a g++

# Kompilatorflaggor, lägg till '-g' om kompilering för avlusning ska göras.
CCFLAGS += -std=c++11 -Wpedantic -Wall -Wextra -Werror

# Preprocessorflaggor, -I lägger till en filkatalog i inkluderingssökvägen.
CPPFLAGS += -I$(EXPRESSION)

# Länkflaggor - Fix för att lösa lokala problem med C++ länkbibliotek.
LDFLAGS  += -L/sw/gcc-$(GCC4_V)/lib -static-libstdc++

# Objektkodsmoduler som ingår i den kompletta kalkylatorn.
OBJECTS = Expression_Tree.o

# Huvudmål - skapas med kommandot 'make' eller 'make kalkylator'.
expression_tree-test: $(OBJECTS) makefile
	$(CCC) $(CPPFLAGS) $(CCFLAGS) $(LDFLAGS) -o test $(OBJECTS)

# Delmål (flaggan -c avbryter innan länkning, objektkodsfil erhålls)
expression_tree-test.o: expression_tree-test.cc
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c expression_tree-test.cc

#Calculator.o: Calculator.h Calculator.cc
#	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c Calculator.cc

#Expression.o: $(EXPRESSION)/Expression.h $(EXPRESSION)/Expression.cc
#	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c $(EXPRESSION)/Expression.cc

Expression_Tree.o: Expression_Tree.h Expression_Tree.cc
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c Expression_Tree.cc

# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).
clean:
	@ \rm -rf *.o *.gch core

# 'make zap' tar även bort det körbara programmet och reservkopior (filer
# som slutar med tecknet '~').
zap: clean
	@ \rm -rf test *~

# Se upp vid eventuell ändring, '*' får absolut inte finnas för sig!!!
#
# '@' medför att kommandot inte skrivs ut på skärmen då det utförs av make.
# 'rm' är ett alias för 'rm -i' på IDA:s system, '\rm' innebär att "original-
# versionen", utan flaggan '-i', används. 
