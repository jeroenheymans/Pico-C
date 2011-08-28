default:
	$(MAKE) -C Pico
	$(MAKE) -C tpico

clean:
	$(MAKE) -C Pico clean
	$(MAKE) -C tpico clean
	
all:
	$(MAKE) clean
	$(MAKE) default
