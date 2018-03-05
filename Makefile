.PHONY : runmake runlein

all: runmake runlein
#all: runlein
#all: runmake

runmake:
	echo "Building native resources."
	$(MAKE) -C $(PWD)/test/native
	echo "Finished building native resources."

runlein:
	echo "Running lein tests."
	lein test
	echo "Finished lein tests."
