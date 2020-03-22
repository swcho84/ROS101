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

## imgproc101
- "자율주행을 위한 영상처리 기초: 캠시스 이윤희 박사님"의 강의용 코드를 ROS 환경으로 통합한 결과 
- 기존 코드는 ROS 환경이 아닌 상태에서만 컴파일 후 사용하도록 되어있었음
- ROS 환경으로 통합하면서 parameter 로 사진파일 관리 가능하도록 하였음
- 핵심 함수는 그대로 사용하였음
- OpenCV 1.x 스타일로 코딩한 결과물이므로 최신 스타일로 변경해둘 필요 있음

## qtros_test
- QtCreator를 이용한 GUI환경개발 기초 코드
- ROS의 catkin_create_qt_pkg로 Qt4 기반 GUI 생성할 수 있지만 현재 sudo apt-get 으로 설치되는 Qt5, QtCreator 최신버전하고는 호환이 잘 되지 않음
- CMakeList를 수정해서 호환되도록 만들었음
- QtCreator에서 ROS의 catkin_ws로 QtCreator 빌드되도록 하려면 아래 세 단계를 거쳐야함
  - Open Project할 때 해당 PKG의 CMakeList선택
  - build folder 경로를 위해 ~/catkin_ws/build/(pkg이름) 으로 설정, pkg이름으로 미리 폴더 만들어두기
  - cmake 실행 전에 다음과 같이 입력(-DCMAKE_INSTALL_PREFIX=../install -DCATKIN_DEVEL_PREFIX=../devel)
  - 설정을 새로 잡아줘야 할 필요 있을 때는 pkg폴더 내에 *.user로 생성된 CMakeList파일 지우기