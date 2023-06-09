# 3조 IoT project
## 주제 : 아두이노 IoT를 이용한 V2I 기술의 구현
![ezgif com-optimize (1)](https://user-images.githubusercontent.com/69943723/236184807-8f8c688b-9a9c-4681-bb74-1a98d6f7164c.gif)
## 팀원 : 
  - 송승훈 : Infra 코드 담당
  - 백준형 : 통신 코드 담당
  - 김세연 : 라인트레이싱 코드 담당

## 코드 설명 :
  - jellibi.ino : jellibi 차량 라인트레이싱 아두이노 NANO 코드
  - Vehicle.ino : 좌회전 우회전 등 통신에 대한 반응을 추가한 jellibi 차량 아두이노 NANO 코드
  - ProjectSignal.ino : infra 1 신호등의 코드
  - infra.ino : infra 2 표지판의 코드

## 프로젝트 설명
![image](https://user-images.githubusercontent.com/69943723/230870538-cf770b61-b54c-445b-8c43-85582013a1a1.png)  
![image](https://user-images.githubusercontent.com/69943723/230870587-9c21d172-51ac-4f94-9b58-3948439cdbe2.png)  
![image](https://user-images.githubusercontent.com/69943723/230870614-7283c1a7-488e-4ecd-9aaa-b209607c77f5.png)  
![image](https://user-images.githubusercontent.com/69943723/230870656-f603f9e0-041d-40cd-bcd8-6529a72b8b40.png)  
![image](https://user-images.githubusercontent.com/69943723/230870700-99b5c3af-6eea-480b-921e-c15ed5a8bf55.png)  
![ezgif-2-e7bb8c07c9](https://user-images.githubusercontent.com/69943723/236182902-edda38ef-0864-481d-9193-cc16c43fd4fb.gif)  
![image](https://user-images.githubusercontent.com/69943723/230870731-3a252861-cd56-4fdd-9141-1980c6ca8235.png)  
![ezgif com-optimize](https://user-images.githubusercontent.com/69943723/236180990-f547fff0-046f-4270-890b-10335d2a7fbe.gif)  

아두이노 IoT를 통해 자율주행 기술인 V2I 기술을 모사하고자 하였다  
단순한 라인트레이싱 알고리즘을 통해 동작하는 기본 차량에 교통인프라에서 보내준 신호로 여러 자세한 제어가 가능할 것이라 판단하였다.
  
교통 인프라 각각은 ESP 블루투스 통신을 통해 차량의 ESP 보드에게 자신의 신호를 전달하게 되고  
차량 ESP는 그렇게 받아들인 신호를 차량에게 전송하여 상황에 맞는 동작을 수행할 수 있게 하였다.

## 배운 것들
  - 회로에 정격 전압보다 적거나 많은 전원을 인가하였을 경우, 매우 빠르게 움직이거나 통신이 되지 않는 등의 이슈가 있었다.  
  하드웨어와 소프트웨어 문제 양면의 중요성을 배울 수 있었다.
  - 같은 코드라도 하드웨어의 특성에 따라 다르게 동작하게 된다는 점을 배웠다.  
  일례로 라인트레이싱 코드의 경우 기기의 양 센서의 민감도가 다르다던가 기종별 양쪽 모터 출력이 다르다는 점에 신경쓰지 않으면 제대로 동작하지 않았다.
  - 블루투스 직렬 통신, RFID 센서를 다루며 통신에 대한 고민을 해볼 수 있었다.  
  통신이 정상작동하지 않을 경우 원인을 파악하는 데 많은 시간을 투자했다.
  
---
[발표용 ppt](https://docs.google.com/presentation/d/19YS5kTOKq8n68Tw-wl9UC9dEZpB6E_nViElo82Xve74/edit?usp=sharing)
