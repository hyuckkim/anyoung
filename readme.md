# 안녕 : 약한 문법의 약한 프로그래밍 언어
안녕은 어순에 구애받지 않고 문법을 쓸 수 있는 프로그래밍 언어입니다.

## 우리말
 * 철수가 밥을 먹는다.
 * 밥을 철수가 먹는다.  

이 두 문장은 같은 뜻을 가지고 있습니다. 한글에는 조사가 있기 때문이죠.

 * Chulsoo eat rice.
 * Rice eat Chulsoo.  

이 두 문장은 같은 뜻을 가지고 있지 않습니다. 영어에는 조사가 없기 때문이죠.

```창조
문자창보여("hello, world!");
("hello, world!")문자창보여";
```

이게 되겠습니까? 
분명 창조 언어는 한글로 만들어져 있습니다. 하지만 C언어 스타일 문법을 따라갑니다.

그래서 '안녕' 언어를 만들었습니다.

```안녕
"hello, world!"를 말하기
말하기 "hello, world!"를
```

안녕에서는 됩니다.

## 문법

#### Case 1:
```"문자열"을 5번 표시하기 ```라는 함수로 설명하겠습니다.

우선 함수 이름을 읽습니다.  
여기서는 _표시하기_ 라는 이름의 함수입니다.

표시하기의 인수를 검색합니다.  
표시하기의 인수는 _을/를_ 하나와 _번_ 입니다.

이제 읽은 인수 목록으로 전체 줄을 읽습니다.

전체 줄을 읽으면서 인수가 등장하면 그 앞까지를 인수에 포함되는 데이터로 정합니다.  
전체 줄을 읽으면서 함수 이름이 등장하면 그 부분은 건너뜁니다.

__"문자열"__ 을 __5__ 번 표시하기 가 됩니다.

_을/를_ 에 포함된 "문자열"과 _번_ 에 포함된 5를 사용해 *표시하기* 함수가 동작합니다.

#### Case 2:

그렇다면 ```표시하기 5번 "문자열" 을``` 은 어떨까요?

우선 함수 이름을 읽습니다.  
_표시하기_ 를 바로 찾았습니다.

표시하기의 인수는 _을/를_ 과 _번_ 이므로  
표시하기 __5__ 번 __"문자열"__ 을 이 됩니다.

_을/를_ 에 포함된 "문자열"과 _번_ 에 포함된 5를 사용해 *표시하기* 함수가 동작합니다.

결과를 보면 알 수 있듯이 같은 동작을 합니다.

## 함수


흐름  
+ 여기까지  
흐름 함수를 어디까지 실행할지의 조건이 됩니다.  

+ [ㅁ 로/으로] ㅇ 번 되풀이  
'여기까지' 까지의 함수를 ㅇ번 실행합니다. ㅁ에 동작 횟수를 0부터 기록합니다.  
+ ㅁ 면/이면 조건  
ㅁ가 숫자고 1이라면 '여기까지' 까지의 함수를 실행합니다.  
  + 아니면  
조건과 여기까지 사이에 넣어 함수를 실행할지를 반전합니다.  

+ ㅁ 이라는/라는 동작  
ㅁ 라는 문자열로 함수를 정의합니다.  
  + ㅁ 을/를 [ㅇ 로/으로] 인수  
함수의 인수를 설정합니다. 'ㅂ 와/나' 로 여러 조사를 받게 할 수 있습니다.  
  + ㅁ 이 있는지  
인수로 ㅁ이 있으면 1, 없으면 0을 출력합니다.  

+ ㅁ 을/를 읽어오기  
ㅁ이라는 이름의 안녕 파일을 읽어 실행합니다.  

데이터  
+ ㅁ 을/를 ㅇ으로/로 정하기  
변수 ㅁ의 값을 ㅇ로 지정합니다. ㅁ이 없다면 새로 만듭니다.  
+ ㅁ 을/를 ㅇ 만큼 더하기  
변수 ㅁ의 값에 ㅇ를 더합니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.  
+ ㅁ 을/를 ㅇ 만큼 빼기  
변수 ㅁ의 값에 ㅇ를 뺍니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.  
+ ㅁ 을/를 ㅇ 만큼 곱하기  
변수 ㅁ의 값에 ㅇ를 곱합니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.  
+ ㅁ 을/를 ㅇ 만큼 나누기  
변수 ㅁ의  값에 ㅇ를 나눕니다. ㅁ이 문자열이 아니어야 하고 없다면 새로 만듭니다.  

화면 입출력  
+ ㅁ 에 듣기  
화면에서 입력을 받아 변수 ㅁ에 전달합니다.  
+ ㅁ 을/를 [조용히] 말하기  
ㅁ을 개행문자와 함께 출력합니다. '조용히' 와 사용되면 개행문자 없이 출력합니다.  
+ ㅁ 을/를 [ㅇ 번] 표시하기  
ㅁ을 ㅇ번 출력합니다. ㅇ는 숫자여야 합니다.  
+ 도움  
함수에 대한 도움말을 봅니다.  
    