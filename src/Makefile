make:
	g++ -std=c++11  client.cpp -o peerclient -I/usr/include/python2.7 -lpython2.7

gen:
	g++ -std=c++11  coins.cpp -o gen -I/usr/include/python2.7 -lpython2.7

all:
	g++ -std=c++11  coins.cpp -o gen -I/usr/include/python2.7 -lpython2.7
	g++ -std=c++11  client.cpp -o peerclient -I/usr/include/python2.7 -lpython2.7

test:
	g++ -std=c++11  test.cpp -o test -I/usr/include/python2.7 -lpython2.7


clean:
	rm gen peerclient blocks.chain peercoin.config