## insert와 update를 동시에 하는 쿼리에 대하여
###### insert into {TABLE_NAME} ( {COLUMN} ) values ( {VALUES} ) in duplicate key update 로 사용
###### 입력받은 데이터가 중복이 없다면 insert로 처리, 중복(primary key 기준)이 있다면 update 처리를 하는 쿼리이다
###### 기존의 목록이 재편성되는 치사한 상황에 사용
###### 보통 이런 상황에선 기존 데이터 목록과 새 데이터 목록을 비교하여 새거에만 있으면 추가, 둘다 있으면 수정, 기존에만 있으면 삭제하는 식으로 처리
###### 기존 데이터 목록과 새 데이터 목록을 비교하기 위해선 우선 기존 데이터 목록을 select 해서 어딘가 저장해두고 쓴다 -> 이게 귀찮을때 on duplicate 쓴다
###### ※다만 on duplicate 쓸때는 기존 목록을 select 해와서 비교하는것과 원리가 같기 때문에 느리다고 한다
