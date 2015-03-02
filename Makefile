#
# make file to compile signaltest and buddy program
#
default: create

create:
	gcc signaltest.c -o test.out
	gcc buddy.c -o slap.out

clean:
	$(RM) *.out
