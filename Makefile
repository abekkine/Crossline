e1:
	g++ -o e1.bin example.c

e2:
	g++ -o e2.bin example2.c

esql:
	g++ -o esql.bin example_sql.c

clean:
	$(RM) e1.bin e2.bin esql.bin
