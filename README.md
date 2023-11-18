

## 소개
> Wiki : [LS Wiki](https://github.com/chocobubble/LooterShooter/wiki)

언리얼 엔진으로 제작한 개인 프로젝트입니다.
루트 슈터 게임의 각종 로직을 구현했으며, 자세한 내용은 GitHub Wiki에서 확인 가능합니다.

- 게임 장르 : looter shooter(RPG + TPS)  
- 제작 기간 : 2023. 6. ~ 10.
- 제작 인원 : 1인 (개인 프로젝트)
- 사용 엔진 : Unreal Engine v5.2 
- 언어 : C++

### 플레이 영상
- 이미지 클릭 시 유튜브에서 영상이 실행됩니다.

[![play](https://img.youtube.com/vi/KDOwoE6ikm4/0.jpg)](https://youtu.be/KDOwoE6ikm4)

<br>

## 게임 로직 설명
- 프로젝트 각 기능 관련 자세한 내용은 Document Wiki 에서 확인 가능합니다. 
[[Document 링크]](https://github.com/chocobubble/LooterShooter/wiki/Document)

<br><br>

## 주요 내용

### 1. GitHub의 Project, Issue, Wiki 등을 이용한 프로젝트 관리
프로젝트 일정 및 목표 관리, 코드 기록 등의 필요성을 느끼고 GitHub의 Project, Issue, Wiki 등의 기능을 이용해 프로젝트를 제작했습니다. 

- Project
  - GitHub의 Project를 이용하여 프로젝트 일정을 관리 했습니다.

[![project](https://github.com/chocobubble/chocobubble/blob/9ab1c845ef522f4622b6c6cdd25ae4455fdc405f/Images/Project_main.JPG)](https://github.com/users/chocobubble/projects/2)

- Issue
  - GitHub의 Project에 들어가는 Issue들이며, Git Commit 과 연동해 각 Issue에 해당하는 Commit들을 바로 확인할 수 있었습니다.
  - 체크박스를 통해 세부 목표관리를 했습니다.

[![Issue](https://github.com/chocobubble/chocobubble/blob/9ab1c845ef522f4622b6c6cdd25ae4455fdc405f/Images/Project_issue_2.JPG)](https://github.com/chocobubble/chocobubble/Images/Project_issue.JPG) 

- Wiki
  - 프로젝트에서 구현한 기능들을 GitHub의 Wiki를 통해 정리했습니다.
[<img width="523" alt="Wiki" src="https://github.com/chocobubble/chocobubble/assets/100405650/d446a555-e10b-4e17-b134-5bf28ddb5e94">](https://github.com/chocobubble/LS/wiki)


<br>

### 2. 데이터 시스템을 구축을 통한 데이터와 코드의 분리
>  [[Wiki]](https://github.com/chocobubble/LS/wiki/%EB%8D%B0%EC%9D%B4%ED%84%B0-%EC%8B%9C%EC%8A%A4%ED%85%9C)
- 프로젝트 초기에는 무기나 캐릭 스탯 등 수치들을 코드로 설정했고, 프로젝트가 진행 되면서 이런 데이터를 수정할 때마다 코드 수정 과정에서 에러가 생기는 등의 문제가 있었습니다. 
- 해결 방법으로 데이터 시스템을 구축해했고, C++ 코드에 의존적이지 않게 데이터들을 관리할 수 있게 했습니다. 
- 또한 이렇게 구축한 데이터 시스템을 통해 비프로그래머도 프로그래머의 도움 없이 게임 내 데이터 수정이 가능합니다.


<br>

### 3. 클래스의 크기를 줄이고, 다른 객체에 재활용하기 위한 컴포넌트 활용
> [[Wiki]](https://github.com/chocobubble/LS/wiki/%EC%BB%B4%ED%8F%AC%EB%84%8C%ED%8A%B8)
- RPG 게임 특성 상 캐릭터를 구현하는 클래스의 크기가 커져 수정 및 확장이 용이하지 않았습니다. 
- 이런 문제를 해결하기 위해 컴포넌트 기반 설계를 도입했습니다. 
- Defense, Resource, Equipment, Inventory 등의 기능을 컴포넌트로 분리했으며, 이를 몬스터 구현 등에 재사용했습니다. 
- 그리고 컴포넌트 간의 의존성을 줄이기 위해 delegate를 이용했습니다.

<br>


### 4. 유연하고 확장성 있는 기능 구현을 위한 다형성 활용
> [[Wiki]](https://github.com/chocobubble/LS/wiki/%EB%8B%A4%ED%98%95%EC%84%B1)
- 무기 클래스에 다양한 부가 속성을 구현하는 과정에서 무기 클래스가 과도하게 커지는 경향이 있었습니다.
- 그리고 부가 속성을 추가할 때 마다 무기 클래스를 수정해야 했고 그 과정속에서 에러가 발생하는 경우가 있었습니다.
- 해결 방안으로 다형성을 이용하여 유연하고 확장성있게 부가 속성을 구현했습니다.




