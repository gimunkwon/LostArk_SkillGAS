# 🛡️ Unreal Engine 5: Top-Down Multi-RPG
**GAS(Gameplay Ability System)**를 활용한 로스트아크 스타일의 멀티플레이 RPG 프로젝트입니다.

---

## 🚀 프로젝트 개요
* **개발 기간**: 2026.01.25 ~ 진행 중
* **핵심 목표**: 전용 서버(Dedicated Server) 환경에서 안정적인 스킬 시스템 및 파티 시스템 구현
* **개발 환경**: UE 5.4, C++, JetBrains Rider

---

## 🛠️ 주요 기술 스택
* **GAS (Gameplay Ability System)**: 캐릭터 스탯, 스킬 로직 및 상태 이상 관리
* **Network**: PlayerController 기반 ServerRPC 이동 및 동기화
* **Data-Driven**: TSoftObjectPtr를 활용한 DataAsset 기반 직업(Job) 관리 시스템 (메모리 최적화)
* **System**: GameState를 통한 GUID 기반 파티 관리
