<div>
  <h2>모작 참고 자료</h2>
</div>
<div>
  https://www.youtube.com/watch?v=JyigqW3hDsw</div>
<div>
  <h2>포트폴리오 개발 내용</h2>
  <ul>
    <li><a href="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/edit/main/README.md#%ED%94%8C%EB%A0%88%EC%9D%B4%EC%96%B4-%EA%B8%B0%EB%B3%B8-%EC%9D%B4%EB%8F%99-%EA%B5%AC%ED%98%84">플레이어 기본 이동 구현</a></li>
    <li><a href="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/edit/main/README.md#%EB%A9%94%EC%9D%B4%ED%94%8C%EC%8A%A4%ED%86%A0%EB%A6%AC-%EB%B3%B4%EC%8A%A4%EB%AA%AC%EC%8A%A4%ED%84%B0-%EC%9C%8C-%EA%B5%AC%ED%98%84">메이플스토리 보스몬스터 윌 구현</a></li>
    <li><a href="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/edit/main/README.md#%ED%94%8C%EB%A0%88%EC%9D%B4%EC%96%B4-%EC%8A%A4%ED%82%AC-%EC%84%B8%EB%B6%80-%EA%B5%AC%ED%98%84">플레이어 스킬 세부 구현</a></li>
  </ul>
</div>
<div>
  <h2>개발 기간</h2>
  <ul>
    <li>2024.3.25 ~ 2024.4.22</li>
    <li>
      <b>[1주차]</b>
      게임엔진, 각종 매니저클래스, 컴포넌트 생성, 플레이어 움직임, 점프, 기본공격, 더미몬스터, 카메라 구현
    </li>
    <li>
      <b>[2주차]</b>
      보스몬스터 기본골격, 기본 UI, 윌 입장맵, 윌 1페이즈 구현
    </li>
    <li>
      <b>[3주차]</b>
      윌 2페이즈, 3페이즈 구현
    </li>
    <li>
      <b>[4주차]</b>
      플레이어 스킬 다양화 (메이플스토리 직업 썬콜 일부 스킬 구현)
    </li>
  </ul>
</div>
<div>
  <h2>플레이어 기본 이동 구현</h2>
  <div>
    상하좌우 방향키를 입력하면 플레이어가 해당 방향으로 이동<br>
    왼쪽 Alt키를 입력하면 점프<br>
    점프 상태에서 왼쪽 Alt키를 한번 더 누르면 더블 점프<br>
    이동 방향으로 점프 가능
  </div>
</div>
<div>
  <h2>메이플스토리 보스몬스터 윌 구현</h2>
  <div>
    <div>
      <b>[모든 페이즈 공통]</b>
    </div>
    <ul>
      <li>
        <div>달빛 게이지 : 사용 시, 각 페이즈마다 다른 효과 발동</div>
        <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/1e959dfb-d621-4613-8a7b-e8ccdf393531">
      </li>
      <li>
        <div>주시하는 눈동자 : 탄막 발사 형식의 공격 패턴</div>
          <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/d05afd48-d2a6-4431-9404-5359e206c99f">
      </li>
      <li>
        <div>거미다리 내려찍기</div>
          <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/66bf762c-5bdb-4198-b155-6f2e1fcafe22">
      </li>
      <li>
        <div>어둠의 집행자 : 소환형 몬스터</div>
          <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/73f3aa56-468d-40f7-b15e-88df5026e950">
      </li>
      <li>
        <div>근거리 공격 : 전방의 플레이어 공격</div>
      </li>
      <li>
        <div>원거리 공격 : 비교적 넓은 범위에 있는 플레이어 공격(윌이 향하는 방향으로 전방 8 : 후방 2 정도의 피격 판정 범위)</div>
      </li>
      <li>
        <div>밀쳐내기 : 전방의 플레이어를 밀쳐내 데미지를 입히고 5초동안 상태이상에 걸리게 함</div>
        => 상태이상 : 방향키 입력이 반대로 적용됨
      </li>
    </ul>
  </div>
  <div>
      <b>[1 페이즈]</b>
    </div>
    <ul>
      <li>
        <div>거울 차원 이동 : 두 공간에 있는 윌의 체력을 모두 깎아야 함</div>
          <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/f8ab1ec3-84e9-4859-b1e7-653a0e9be772"><br>
          이미지 출처 : https://m.blog.naver.com/44alice/221195757597
      </li>
      <li>
        <div>달빛 게이지 : 사용 시, 다른 공간으로 이동 가능</div>
      </li>
      <li>
        <div>장풍 날리기 : 윌이 향한 방향으로 움직이는 장풍 소환</div>
        <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/97bb4f76-6e29-47e4-b481-b73f0eee8fb2">
      </li>
      <li>
        <div>텔레포트 : 윌이 사라졌다가 플레이어가 있는 위치에 다시 나타남</div>
      </li>
      <li>
        <div>공간붕괴 : 조건부 즉사스킬</div>
        <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/fe25af74-1934-4480-8739-52406699d345"><br>
        <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/27acf825-805a-4ee4-a3d9-28b9b671211e">
        <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/4d7ee867-f4ec-4d8a-b8e1-749b2b03d133">
      </li>
      <li>
        <div>주시하는 눈동자 : 조건부 즉사스킬, 패턴 파훼시 윌 행동불가</div>
        <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/dd791d0e-403d-4433-a610-765f5554330c">
      </li>
      <li>
        <div>혼란의 눈동자 : 플레이어를 다른 공간에 강제 이동시킴</div>
        <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/e4d3a571-ba00-484d-a9e8-2538495a89a2">
      </li>
    </ul>
  </div>
  <div>
      <b>[2 페이즈]</b>
    </div>
    <ul>
      <li>
        <div>치유 불가 저주 : 아이템, 스킬을 통한 플레이어 체력 회복 불가능</div>
      </li>
      <li>
        <div>달빛 게이지 : 사용 시, 체력 회복</div>
      </li>
      <li>
        <div>돌진 : 전방의 플레이어에게 돌진해 피해를 입힘</div>
      </li>
      <li>
        <div>페이크 공격 : 모션을 취하는 방향과 반대 방향으로 지면에 반사된 윌이 공격 시전</div>
      </li>
      <li>
        <div>심연의 장벽 : 설치형 스킬 오브젝트. 플레이어의 위치를 제한시키는 효과</div>
        <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/798e77dc-48da-46d3-b0cf-82bff2d2280b">
      </li>
      <li>
        <div>거미 소환 : 소환형 몬스터</div>
        <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/4e3f9cdb-9c7d-44c9-8778-b554f6692b69">
      </li>
      <li>
        <div>거짓의 거울 : 패턴 파훼 실패시, 윌 공략 불가능</div>
        <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/4b41c655-a06e-498a-a51e-955a2241b8a6">
        <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/ed5826b6-4033-4ebd-adec-49d46f24c990">
      </li>
    </ul>
  </div>
  <div>
      <b>[3 페이즈]</b>
    </div>
    <ul>
      <li>
        <div>달빛 게이지 : 사용 시, 맵에 소환되는 거미줄을 지울 수 있음</div>
      </li>
      <li>
        <div>거미줄 소환 : 플레이어에게 닿으면, 5초간 스킬봉인. 달빛게이지를 적절히 사용하게 강제하는 패턴</div>
        <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/4e2e78df-334f-4f5d-b80b-8c5c83d696aa" width="1000px" height="500px"><br>
        이미지 출처 : https://arca.live/b/maplestory/81937463?category=%EC%A0%95%EB%B3%B4&p=1
      </li>
      <li>
        <div>감염 : 조건부 즉사기, 플레이어에게 도트데미지, 플레이어 버프</div>
        <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/960cda72-1944-4c48-83ac-92b125e0a382">
      </li>
      <li>
        <div>내려찍기 : 규칙성이 있는 공격 패턴</div>
        <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/2f20ecfc-37f3-4c45-a04d-b40eea729538">
        <img src="https://github.com/yaewon94/Portfolio-WinAPI-MapleStory/assets/84373511/9e3156f4-f21f-46c3-9fff-e8f6b5cfb8ee">
      </li>
    </ul>
  </div>
</div>
<div>
  <h2>플레이어 스킬 세부 구현</h2>
  <div>플레이어 스킬을 일반 공격스킬, 전역 공격스킬, 바인드 스킬, 상태이상 해제 스킬 등으로 다양하게 구성함</div>
  <div>중요 스킬의 경우 재사용 대기시간을 설정해, 적절한 타이밍에 스킬을 사용하도록 생각하게 함</div>
  <ul>
    <li>
      용사의 의지 : 상태이상 해제, 면역
    </li>
    <li>
      텔레포트 : 상하좌우 방향 순간이동기
    </li>
    <li>
      체인 라이트닝 : 다른 몬스터들에게도 전이가 가능한 공격스킬. 일반 공격기
    </li>
    <li>
      프리징 브레스 : 몬스터 행동불가 만들기, 시전 시 플레이어 무적
    </li>
    <li>
      라이트닝 스피어 : 키다운 공격 스킬. 극딜기
    </li>
    <li>
      썬더 브레이크 : 자체 이동 소환형 스킬, 이동/고정 여부를 플레이어가 선택할 수 있음. 극딜기
    </li>
    <li>
      스피릿 오브 스노우 : 일정 시간동안 소환 가능한 설치형 공격 스킬
    </li>
    <li>
      주피터 썬더 : 자체 이동 소환형 스킬, 특정 조건에 따라 재이동 또는 재사용 대기시간 감소. 극딜기
    </li>
    <li>
      프로즌 라이트닝 : 시전 시 플레이어 무적, 현재 맵의 모든 몬스터에게 타격 가능한 전역범위 스킬. 극딜기
    </li>
  </ul>
</div>
