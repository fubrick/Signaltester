#
# make file to compile signaltest and buddy program
#jdskfjsl
default: create

create:
	gcc fileOpener.c -o opener.out

clean:
	$(RM) *.out
	$(RM) *.txt
