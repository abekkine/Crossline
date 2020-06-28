e1:
	g++ -std=c++11 -Wfatal-errors -o e1.exe example.c

e2:
	g++ -std=c++11 -o e2.exe example2.c

clean:
	$(RM) e1.exe e2.exe
