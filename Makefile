
# CS3377
# Makefile for Program 6
# Luke Corley lcc160130 4.23.18

CXX = g++
CXXFLAGS = -Wall -g 
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses 


#PROJECTNAME is the name for the backup folder
PROJECTNAME = prog6backup
EXECFILE = program6
OBJS =  prog6.cc

all: $(EXECFILE)

#remove the objects files and  emacs backup files, but retain the executable (unusual requirement of program 5)
clean:
	@rm -f $(OBJS) $(EXECFILE) *~ \#*
	@echo Removed unneeded files.

#rule for creating the executable
$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)


backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
