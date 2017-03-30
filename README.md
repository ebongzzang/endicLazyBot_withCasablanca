# endicLazyBot_withCasablanca

카카오톡 자동응답 봇을 만들기 위해 네이버 영어사전 크롤러 / C++ Rest SDK(casablanca)를 사용하여 개발중인 프로젝트 입니다.

@사귀내봇(사전찾기 귀찮아서 내가만든 봇)으로 2017년 3월 27일부터 서비스중입니다.

Development Environment

ubuntu 16.04 with clang++ on Amazon Web Service EC2

실행 방법

/restServer에서 'make all'

Listener.cpp - Rest API base
MessageListener.cpp - /meesage (POST) 요청 처리
LazyListener.cpp - /keyboard (GET) 요청 처리
