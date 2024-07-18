simple command
/bin/ls
/bin/echo
/bin/cat

touch tmpfile
./nofile : bash: ./nofile: No such file or directory, 127
./tmpfile: bash: ./tmpfile: Permission denied, 126
/bin/ls/nofile : bash: /bin/ls/nofile: Not a directory, 126 //TODO execve errno 관련
/bin/nofile : bash: /bin/nofile: No such file or directory 127 // TODO execve errno 관련

/bin : Permission denied, 126 -> zsh 기반으로 명령이 동작하기 때문에 배쉬랑 다를 수 밖에 없음 // TODO execve errno 관련

<< eof nocmd
nocmd

---

Arguments
/bin/ls -l
/bin/echo Hello
/bin/cat main.c
Syntax error
<<<<<<<< // TODO leak heredoc file name with space "<<< "

> > > > > > > > // TODO leak heredoc file name with space "<<< "
> > > > > > > > <<
> > > > > > > > < <
> > > > > > > > ||
> > > > > > > > <>
> > > > > > > > < // TODO leak heredoc file name with space "<<< "
> > > > > > > > Heredoc
> > > > > > > > << out | cat
> > > > > > > > << eof | nocmd | nocmd | nocmd
> > > > > > > > << eof cat >> infile
> > > > > > > > << eof > a.txt | cat a.txt
> > > > > > > > echo test > ls >> ls >> ls
> > > > > > > > << eof > out1 | << eof > out2 | << eof > out3
> > > > > > > > cat << eof > out1 | cat << eof > out2 | cat << eof > out3
> > > > > > > > Heredoc append
> > > > > > > > echo Hello > tmp (새로 만들어)
> > > > > > > > echo World >> tmp (추가모드)
> > > > > > > > --- 이까지 테스트 완료
> > > > > > > > Builtin
> > > > > > > > Env | grep PWD
> > > > > > > > export
> > > > > > > > export
> > > > > > > > export test
> > > > > > > > export test= //TODO export test = -> leak + '='등록되면 안됨!
> > > > > > > > export test=ls

export test="ls -l" //TODO export "ls -l"이 커맨드로 들어감
export test='ls -al' //TODO same

export 1=100
export test1=100
export test1='200'
export TEST="ls -l - a" // TODO same
export a=100 a
env
unset PATH
ls
clear
..
exit
exit
exit 99
exit -1
exit 012
exit a1
exit a1 asdf
cat
cat | cat | ls
Cat | cat | ls // TODO->sig pipe
echo
echo
echo -n hi
echo -n -n -n hi
echo -nnnn hi
echo -nnn -nnn hi
echo -n123 hi
echo - hi
echo -n hi -n
echo -n -n -n hi -n
echo -nnnn hi -nnn
echo -nnn -nnn hi -nnn
echo -n123 hi -nn
echo - hi -nn
echo "hello $USER"
 echo 'hello $USER'
 echo "hello $USER | ls"
 echo 'hello $USER | ls'
 echo "hello $USER > out"
 echo 'hello $USER > out'
 echo "hello $USER < out"
 echo 'hello $USER < out'
 echo "hello $USER > out < out | ls"
 echo 'hello $USER > out < out | ls'
 echo "fuck you donalds" | cat > no | cat << out
 "echo" "-n-n-n-n-n-n-n-n" "hello"
 echo test "" test "" test
 echo > <
 echo | |
 echo "Hello" | cat -e
 echo " Hello ; echo 123    " | cat -e
 echo "'$HOME'
echo ' $HOME ; ; ; echo $PATH $ '

> tmp4 echo ABC
> long cmd
> ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls
> ls -al | awk '{ print $1, $2, $3 }'
> grep int < main.c
> cat /etc/passwd | grep ':' | more
> ls -l | grep d > tmp5
> cd
> cd ../../../../../../../../../
> cd nodir
> mkdir test
> cd test
> rm -rf ../test
> pwd
> cd .. // TODO OLDPWD, PWD를 이용한 경로갱신 사용할지 결정 필요
> ETC
> ls | sleep 3
> ls -l | grep d > tmp5
> < infile cat | grep a | wc -l
> << eof cat >> infile
> cat << eof > a.txt | cat a.txt -> 자식 프로세스 생성과 실행의 시점을 운영체제가 스케줄링 하기 때문에 우리가 그것을 보증할 수는 없다. 만약 똑같이 만드려면 배쉬 코드를 뜯어봐야된다.
> ls -al | cat
> signal
> sleep 3
> ctrl + c 130
> ctrl + \ 131
> echo $?
> ctrl + \ -> do nothing
