EXEC=diffeq-project

${EXEC}: ${EXEC}.cpp Makefile
	g++ -g ${EXEC}.cpp -o ${EXEC} -Wall

run: ${EXEC}
	 ./${EXEC}

debug: ${EXEC}
	gdb ${EXEC}

clean:
	rm ${EXEC}