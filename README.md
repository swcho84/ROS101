# ROS101
- ROS101 class - from basic to advanced 

## 국민대학교
- 강의일시: 2020년 8월 19일(2일차), 09:00-13:00, 14:00-18:00
- 강의명: ROS 기반 프로그래밍 이론 및 실습​
- 강의장소: 국민대학교
- 수강대상: 학부생 및 대학원생 (자율주행관련) 
- 강의주제: ROS 활용 및 예제

## 충북대학교
- 강의일시: 2020년 2월 10일(4일차), 09:00-13:00, 14:00-18:00
- 강의명: ROS와 Carmaker 기반 자율주행의 인지,판단,제어 구현(이론, 실습, 프로젝트 10일)​
- 강의장소: 충북대학교
- 수강대상: 학부생 및 대학원생, 재직자 (자율주행관련) 
- 강의주제: ROS 활용 및 예제

## Pre-requirement
- Ubuntu 16.04: ROS kinetic
- Ubuntu 18.04: ROS melodic
- Ubuntu 20.04: ROS noetic
- Git pkg: "-" 사용, ROS pkg: "_" 사용

### Install Clang
``` Bash
sudo apt-get install clang, clang-format
```

### Build
``` Bash
catkin build
```
with alias
``` Bash
cb
```

## hello_world_ros
- hello world 를 terminal 또는 ros log file 에서 확인하도록 하는 pkg
- ros pkg 의 기본구조 학습
- custom mavlink msg. 를 이용한 serial modem communication 실습 (msg. generation by using pymavlink)

## pub_test
- ros 의 publisher 예제
- basic: string data 와 float32 multi-array data 를 publish 하는 pkg
- advanced: custom msg 를 publish 하는 pkg

## sub_test
- ros 의 subscriber 예제
- basic: string data 와 float32 multi-array data 를 subscribe 하는 pkg
- advanced: custom msg 를 subscribe 하는 pkg

## srv_test
- ros 의 service server/client 예제
- (basic)calc_add_srv server: 2개의 int number 를 받아서 더하는 연산
- (basic)calc_add_srv client: 2개의 int number 를 param 으로 읽어서 server 호출
- (advanced)set_mission_info_srv server: 1개의 int number 를 받아서 임무를 선택하는 연산 (switch-case)
- (advanced)set_mission_info_srv client: 1개의 int number 를 param 으로 읽어서 server 호출하여 임무를 받아 실행하는 연산

## custom_msg_srv_param_ros
- custom message file 과 custom service file 을 생성하는 pkg (이들 모두를 단일 pkg 하면 관리하기 용이함)
- yaml file 에서 parameter 를 읽어오는 예제 node

## autostart_service
- roscore 와 roslaunch 를 컴퓨터 시작 프로그램에 등록하기 위함
- 각종 시연/대회/상용화/실운용 또는 반복된 실험수행 때 더 이상 디버깅이 필요하지 않은 node 를 실행할 때 용이함
- 해당 폴더의 readme 참고

## act_test
- ros의 action server/client 예제
- http://wiki.ros.org/actionlib/Tutorials 에서 제공하는 코드 기반으로 구성
- Averaging의 경우 class 적용된 cpp style로 변환하는 방법 제시

## synced subscribe
- 서로 다른 topic들을 sync하여 한 번에 subscribe하는 방법 제시
- 파일만 참고할 수 있도록 코드 제공
