# ROS101
- ROS101 class - from basic to advanced 
- 강의명: ROS와 Carmaker 기반 자율주행의 인지,판단,제어 구현(이론, 실습, 프로젝트 10일)​
- 강의일시: 2월 10일(4일차), 09:00-13:00, 14:00-18:00
- 강의장소: 충북대학교
- 수강대상: 학부생 및 대학원생, 재직자 (자율주행관련) 
- 강의주제: ROS 활용 및 예제

## Pre-requirement
- Ubuntu 16.04
- ROS kinetic
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