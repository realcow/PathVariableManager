# 개요
PathVariableManager는 커맨드 라인 인터페이스(CLI) 기반 쉘에서 간편하게 패쓰 변수를 설정하는 유틸리티이다. 개발 언어는 C++ 이며 크로스 플랫폼을 지원한다.

# 사용법
pvm.bat가 있는 디렉토리를 PATH환경변수에 등록하고 pvm을 호출하여 사용한다. 하기 예시를 참고하시오.

### Windows 

```
:: 현재 패쓰 변수에 python2 경로 추가
> pvm --set python2

:: 현재 패쓰 변수에 python2 경로 제거
> pvm --reset python2

:: python3 디렉토리를 등록
> pvm --reg python3 "C:\Program Files\Python3"

:: 현재 패쓰 변수에 python3 경로 추가
> pvm --set python3

:: python3 디렉토리를 등록 해지
> pvm --dereg python3
```

# 빌드
pvm은 크로스 플랫폼을 지원하기 위해 CMake를 기반으로 만들어졌다. <br>
또한 boost와 yamlcpp를 이용한다.

```
cmake (pvm-source-directory)
```

# 라이선스
MIT License