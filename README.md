# Thread-Safe Priority Queue


학번 마지막 세자리 : 536

이름 : 김민정  

[ 진행 상황 ]

Windows CRITICAL_SECTION을 사용해 스레드 안전한 연결 리스트 기반 큐 구현

Item은 key(int)와 동적 할당된 value(char*)를 포함

기본 함수: 큐 초기화(init), 해제(release), 노드 생성/해제/복제

큐 연산

1. enqueue는 key 오름차순 유지하며 삽입, 중복 key는 value 업데이트

2. equeue는 앞 노드 제거 후 깊은 복사된 아이템 반환

3. range는 특정 key 범위 내 아이템만 복사해 새 큐 생성

4. 메모리 안전성 위해 value를 항상 깊은 복사하고 해제 처리
