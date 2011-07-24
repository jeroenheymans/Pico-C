all:	
	$(MAKE) -C ../Pico
	$(MAKE) tpico
	
tpico: configure.libs tpico.o ../Pico/*.o
	gcc -m32 -o tpico tpico.o ../Pico/*.o -lm -lncurses -lreadline

configure.libs:
	./configure

install: all
	install tpico /usr/local/bin/tpico-1
	strip /usr/local/bin/tpico-1
	ln -sf /usr/local/bin/tpico-1 /usr/local/bin/tpico
	install -m 0644 tpico.1 /usr/local/man/man1/tpico.1

clean:
	rm -f tpico *.o core tags configure.libs configure.opts

tpico.o: tpico.c ../Pico/Pico.h ../Pico/PicoMai.h
	gcc  -m32 -c tpico.c
