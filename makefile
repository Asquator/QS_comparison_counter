CC = g++
CFLAGS = -Wall
OBJS = driver.o generator.o quicksort.o select.o aux.o counter.o
PROG = QS_comparison_counter
$(PROG):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o : %.c
	$(CC) -c $(CFLAGS) $< -g -c -o $@

clean:
	rm -rf $(PROG) *.o
	
debug:
	$(CC) $(CFLAGS) $(OBJS) -g -o $@ 

#Dependency chains:
driver.o: driver.cpp quicksort.h counter.h
quicksort.o: quicksort.cpp quicksort.h
select.o: select.cpp select.h
generator.o: generator.cpp
aux.o: aux.cpp aux.h
counter.cpp: counter.h aux.h quicksort.h select.h
