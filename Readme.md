# 개요
 PathVariableManager는 커맨드 라인 인터페이스(CLI) 기반 쉘에서 간편하게 패쓰 변수를 설정하는 유틸리티이다. 개발 언어는 C++ 이며 크로스 플랫폼을 지원한다.

# 사용법

### Windows 

    :: 현재 패쓰 변수에 python2 경로 추가
    > pvm add python2
    
    :: 현재 패쓰 변수에 python2 경로 제거
    > pvm del python2
    
    :: python3 디렉토리를 등록
    > pvm --register python3 "C:\Program Files\Python3"

    :: 현재 패쓰 변수에 python3 경로 추가
    > pvm add python3
    
    :: python3 디렉토리를 등록 해지
    > pvm dereg python3

# 빌드

TODO