카메라로부터 영상을 받아 그레이스케일영상과 이진영상으로 변환하여 원본영상, 그레이영상, 이진영상을 모두 PC로 전송하여 출력하는 main 코드

main 코드를 실행시키는 makefile
#### CSI 카메라를 초기화

src

#### Videocapture 객체생성

source

#### gstreamer를 이용하여 네트워크로 전송하는 명령어 저장, 전달 : 

dst1, writer1 컬러영상

dst2, writer2 그레이

dst3, writer3 이진화

#### 영상처리

cvtcolor gray

threshold 이진화

---

## 실행결과

![jetson_camera](https://github.com/user-attachments/assets/a80f03ef-7e31-462c-9f86-f6898758a9a6)
