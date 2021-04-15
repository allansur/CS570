
CC = gcc
CCFLAGS= -Wall -lpthread -lrt

# factory_controller.cpp producers.cpp consumers.cpp

default: main.cpp producer.o consumer.o belt.o
	${CC} -o mizzo main.cpp producer.o consumer.o belt.o ${CCFLAGS}

producer.o: producer.cpp producer.h
	${CC} -c producer.cpp ${CCFLAGS}
	
consumer.o: consumer.cpp consumer.h
	${CC} -c consumer.cpp ${CCFLAGS}
	
belt.o: belt.cpp belt.h
	${CC} -c belt.cpp ${CCFLAGS}

# run command works on linux only
run:
	./mizzo -E 1000 -L 3000 -f 600 -e 400

clean:
	rm *.o
	rm *.stackdump
