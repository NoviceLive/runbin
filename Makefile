install:
	sudo install bin/hex /usr/bin/hex
	sudo install bin/unhex /usr/bin/unhex
	sudo install bin/runbin /usr/bin/runbin
	sudo install bin/runbin32 /usr/bin/runbin32

	sudo install scripts/disbin32.sh /usr/bin/disbin32
	sudo install scripts/disbin64.sh /usr/bin/disbin64
	sudo ln -sf /usr/bin/disbin64 /usr/bin/disbin
	sudo install scripts/dishex32.sh /usr/bin/dishex32
	sudo install scripts/dishex64.sh /usr/bin/dishex64
	sudo ln -sf /usr/bin/dishex64 /usr/bin/dishex
