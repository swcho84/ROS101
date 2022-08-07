# ROS101
- ROS101 class - from basic to advanced

## 충북대학교
- 강의일시: 2022년 1월 24일-26일(3일), 10:00-17:00
- 강의명: ROS 기반 프로그래밍 이론 및 실습​ with MoraiSimulator
- 강의장소: 청주대학교
- 수강대상: 학부생 및 대학원생 
- 강의주제: ROS1 Noetic C/C++ and Python3, ROS2 Galactic C/C++ and Python3 활용 및 예제, 실습위주

## 인천대학교
- 강의일시: 2021년 4월 26일(1일), 10:00-18:00
- 강의명: ROS 기반 프로그래밍 이론 및 실습​
- 강의장소: 인천대학교
- 수강대상: 학부생 및 대학원생 
- 강의주제: ROS 활용 및 예제, 실습위주

## 국민대학교 (코로나로 인해 취소)
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

### Install Pre-requisites
``` Bash
sudo apt-get install build-essential git
sudo apt-get install clang-format
```

### Install cmake
- go to https://cmake.org/download/ and download the latest release
``` Bash
tar -xvzf (file.tar)
cd (target folder)
./bootstrap --prefix=/usr/local
make
sudo make install
```

### Install serial
``` Bash
git clone https://github.com/wjwwood/serial
cd ~/serial
mkdir -p build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make
sudo make install
```

### Install Xbox360 wired joystick driver
``` Bash
sudo apt-get install xboxdrv jstest-gtk
```

### Build
``` Bash
catkin build custom_msg_srv_param_ros
catkin build
```
with alias
``` Bash
cb
```

### For using Xbox360 wired joystick before ROScore
``` Bash
sudo xboxdrv --detach-kernel-driver
```
- 실행 후 /dev/input/js(번호) 확인하기 (ROS에서 joynode사용 시 필요)

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
- "rosparam set /mission_num (임무번호)"로 임무설정
- "rosparam set /mission_perf_status true"로 임무완료 상황 발생하여 새로운 임무설정 서비스를 자동으로 실행
- 서비스로 임무 받고 "rosparam set /mission_perf_status false"로 변경하여 임무 수행상황으로 설정

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
- rqt의 topic monitor를 활용하여 feedback과 result 를 통해 결과 확인
- /node 폴더의 gen_number.py를 실행하여 랜덤한 숫자 생성하여 publish하고 이를 action client가 action server에 요청하면 100개의 mean과 standard deviation을 계산

## synced subscribe
- 서로 다른 topic들을 sync하여 한 번에 subscribe하는 방법 제시
- 파일만 참고할 수 있도록 코드 제공

## turtlesim_joy_ctrl_cmd_adv
- turtlesim에 등장하는 거북이를 xbox360 wired joystick으로 조종하는 pkg
- subscriber(joy), publisher(geometry/Twist), service client(clear) 실습에 사용
- Xbox360 joystic driver installagion
``` Bash
sudo apt-get install xboxdrv
```
- ros-noetic-joy installation (for using Xbox360 in ROS environment)
``` Bash
sudo apt-get install ros-noetic-joy
```
- run xboxdrv
``` Bash
sudo xboxdrv --detach-kernel-driver --silent
```
- get the /dev/input/jsX (X is number)
- set the launch file in turtlesim_joy_ctrl_cmd_adv
- run the node using the launch file (turtlesim_joy_cmd_example.launch)111