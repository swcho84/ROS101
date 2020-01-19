### env 파일 작성
- terminal 에 env 라고 입력
```
env
```
- 해당 정보를 copy 하여 빈 파일에 paste 하고 파일이름 저장
- 확장명 없이 ****_env 로 저장
- 해당 파일을 sudo 권한으로 /etc 로 copy-paste
- 자동시작이 잘 되지 않으면 이 파일의 설정이 이상한 상태이므로 debugging 시 힌트로 사용

### roscore.service
- 컴퓨터 시작 시 시작프로그램에 roscore 를 추가
- sudo 권한으로 실행되므로 주의할 것

### roslaunch_example.service
- 컴퓨터 시작 시 시작프로그램에 원하는 roslaunch file 을 추가
- sudo 권한으로 node 가 실행되므로 주의할 것
- e.g. log 저장용 파일들이 sudo 권한으로 저장됨
- --wait: roscore 가 구동되는 것을 기다림
- 그 외에 순차적으로 구동하는 방법은 AFTER 옵션을 적절히 사용할 것

### 각종 커맨드들
```
sudo systemctl status [service 파일 이름]           // service 상태 파악
sudo systemctl start/stop [service 파일 이름]       // service 시작 및 종료
sudo systemctl enable/disable [service 파일 이름]   // 부팅 시 자동 시작 등록 / 해제
sudo systemctl list-units                         // 등록된 service 목록
sudo systemctl preset [path 파일 이름]              // path 등록
sudo systemctl daemon-reload                      // service 파일 갱신
sudo journalctl -u [service 파일 이름]              // 해당 service log 보기
```
