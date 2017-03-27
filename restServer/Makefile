CPPFLAGS = -std=c++11 -stdlib=libstdc++ -I /usr/include/libcxxabi -lboost_system -lcurl -I /usr/include/ -I /usr/include/libxml2/ -lxml2 -lcrypto -lssl -lcpprest
RM = rm -rf
.PHONY: all clean
all: Message Lazy
clean:
	$(RM) *.o Message Lazy ../HTMLCrawler.o

Message : Listener.o MessageListener.o MessageMain.o ../HTMLCrawler.o
	clang++ -o Message Listener.o MessageListener.o MessageMain.o ../HTMLCrawler.o $(CPPFLAGS)

Lazy : LazyListener.o Listener.o LazyMain.o
	clang++ -o Lazy LazyListener.o Listener.o LazyMain.o $(CPPFLAGS)

MessageListener.o : MessageListener.cpp
	clang++ -c MessageListener.cpp $(CPPFLAGS)

MessageMain.o : MessageMain.cpp
	clang++ -c MessageMain.cpp $(CPPFLAGS)

Listener.o : Listener.cpp
	clang++ -c Listener.cpp	$(CPPFLAGS)

LazyListener.o : LazyListener.cpp
	clang++ -c LazyListener.cpp $(CPPFLAGS)

LazyMain.o : LazyMain.cpp
	clang++ -c LazyMain.cpp $(CPPFLAGS)

../HTMLCrawler.o : ../HTMLCrawler.cpp
	clang++ -c ../HTMLCrawler.cpp -o ../HTMLCrawler.o $(CPPFLAGS)
