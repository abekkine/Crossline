e1:
	g++ -o e1.exe example.c

e2:
	g++ -o e2.exe example2.c

esql:
	g++ -o esql.exe example_sql.c

clean:
	$(RM) e1.exe e2.exe esql.exe
