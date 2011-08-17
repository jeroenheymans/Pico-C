all: PicoMai.o PicoMem.o PicoNat.o PicoPri.o PicoEva.o PicoRea.o \
 PicoSca.o PicoEnv.o PicoSch.o

configure.opts:
	./configure

clean:
	rm -f tpico *.o core tags configure.opts .[a-z]*

colours:
	vim-green PicoMai.h
	vim-cyan PicoEnv.h
	vim-magenta PicoMem.h
	vim-globals *.h

PicoEnv.o: PicoEnv.c Pico.h PicoMai.h PicoMem.h PicoNat.h PicoEnv.h \
 configure.opts
	gcc -O3 `cat configure.opts` -c PicoEnv.c

PicoEva.o: PicoEva.c Pico.h PicoMai.h PicoEnv.h PicoMem.h PicoNat.h \
 PicoEva.h configure.opts
	gcc -O3 `cat configure.opts` -c PicoEva.c

PicoMai.o: PicoMai.c Pico.h PicoMai.h PicoMem.h PicoRea.h PicoEnv.h \
 PicoNat.h PicoEva.h PicoPri.h configure.opts
	gcc -O3 `cat configure.opts` -c PicoMai.c

PicoMem.o: PicoMem.c Pico.h PicoMai.h PicoMem.h configure.opts
	gcc -O3 `cat configure.opts` -c PicoMem.c

PicoNat.o: PicoNat.c Pico.h PicoMai.h PicoMem.h PicoEnv.h PicoRea.h \
 PicoPri.h PicoEva.h PicoNat.h configure.opts
	gcc -O3 `cat configure.opts` -c PicoNat.c

PicoPri.o: PicoPri.c Pico.h PicoMai.h PicoMem.h PicoEnv.h PicoNat.h \
 PicoPri.h configure.opts
	gcc -O3 `cat configure.opts` -c PicoPri.c

PicoRea.o: PicoRea.c Pico.h PicoMai.h PicoMem.h PicoEnv.h PicoNat.h \
 PicoSca.h PicoRea.h configure.opts
	gcc -O3 `cat configure.opts` -c PicoRea.c

PicoSca.o: PicoSca.c Pico.h PicoMai.h PicoSca.h configure.opts
	gcc -O3 `cat configure.opts` -c PicoSca.c

PicoSch.o: PicoSch.c Pico.h PicoMai.h PicoMem.h PicoSch.h configure.opts
	gcc -O3 `cat configure.opts` -c PicoSch.c
