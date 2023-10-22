# LooterShooter
> [Wiki](https://github.com/chocobubble/LooterShooter/wiki)
> 
언리얼 엔진으로 제작한 개인 프로젝트입니다.
루트 슈터 게임의 각종 로직을 구현했으며, 자세한 내용은 GitHub Wiki에서 확인 가능합니다.



### 참고
- nullptr 체크 및 디버깅을 아래와 같이 매크로를 사용했습니다.

```cpp
#define LSLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
// 디버깅 매크로
#define LSLOG_S(Verbosity) UE_LOG(LooterShooter, Verbosity, TEXT("%s"), *LSLOG_CALLINFO)
#define LSLOG(Verbosity, Format, ...) UE_LOG(LooterShooter, Verbosity, TEXT("%s %s"), *LSLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
// nullptr 체크 && 디버깅 매크로
#define LSCHECK(Expr, ...) { if(!(Expr)) { LSLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}
```

### 프로젝트 관리
> [Projects](https://github.com/users/chocobubble/projects/2)

GitHub의 Projects, Issues를 활용해 프로젝트 관리를 했습니다.


