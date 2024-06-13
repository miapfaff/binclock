INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense -lm

all: clockdisplay

clockdisplay: main.o display.o
	cc -o clockdisplay main.o display.o $(LDFLAGS)

clean:
	rm -f *.o clockdisplay

main.o: main.c display.h
	cc -c main.c -I ~/include

display.o: display.c display.h
	cc -c display.c -I ~/include
run: 
	./clock.sh | ./clockdisplay
