# Requirement

# NEED TO DO

-  Knowing Shell
	- waht is "shell"? - [posix shell manual translation for minishell](https://80000coding.oopy.io/9e88ba5f-4c38-44b2-9ddd-c1626c6b4dc4)

- What can we implement first without knowing shell
	1. 프롬프팅을 계속받는 루프문
		1.1. 주어진 시그널에 따라 프롬프트 종료 시키기(Ctrl-C, Ctrl-D, Ctrl-\ )
			- Ctrl-C : new line + no update signal
			- Ctrl-D : exit shell
			- Ctrl-\ : no action
		1.2. 입력 받기 
			히스토리를 저장해야한다
			add_history 메소드 사용

2. 명령어를 받아야한다.
	2-1. 입력 받은 히스토리 저장
	2-2. 올바른 실행 파일을 찾기
	2-3. 닫히지 않은 따옴표나 특정되지 않은 특수 문자를 해석하지 않아야 한다. ex) \, ;, etc...
3. 명령어를 실행해야한다.