all:
	cd engine && $(MAKE)
	cd game && $(MAKE)

clean:
	cd engine && $(MAKE) clean
	cd game && $(MAKE) clean