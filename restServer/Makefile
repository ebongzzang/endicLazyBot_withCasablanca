CPPFLAGS = -std=c++11 -stdlib=libstdc++ -I /usr/include/libcxxabi -lboost_system -lcurl -I /usr/include/ -I /usr/include/libxml2/ -lxml2 -lcrypto -lssl -lcpprest -pthread
RM = rm -rf
.PHONY: all clean
install: main
clean:
	$(RM) *.o main ../HTMLCrawler.o

main : main.o Listener.o MessageListener.o LazyListener.o ../HTMLCrawler.o
	clang++ -o main main.o Listener.o MessageListener.o LazyListener.o ../HTMLCrawler.o $(CPPFLAGS)

MessageListener.o : MessageListener.cpp
	clang++ -c MessageListener.cpp $(CPPFLAGS)

Listener.o : Listener.cpp
	clang++ -c Listener.cpp	$(CPPFLAGS)

LazyListener.o : LazyListener.cpp
	clang++ -c LazyListener.cpp $(CPPFLAGS)

../HTMLCrawler.o : ../HTMLCrawler.cpp
	clang++ -c ../HTMLCrawler.cpp -o ../HTMLCrawler.o $(CPPFLAGS)

main.o : main.cpp
	clang++ -c main.cpp $(CPPFLAGS) $(TH)
