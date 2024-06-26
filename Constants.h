#pragma once

constexpr auto MAX_ALPHA = 255;	// 이미지 최대 알파값

constexpr auto DEFAULT_ANIM_DURATION = 0.08f;			// 애니메이션 프레임당 재생시간 기본값
constexpr auto INTERVAL_CHANGE_BOSS_DEAD_ANIMATION = 3.f;	// 보스 Dead 애니메이션으로 전환하기 위한 대기시간
constexpr auto MAX_GAUGE_MOONLIGHT = 100;				// 달빛게이지 최대 게이지값

#define NO_LIMIT_DURATION (float)INT_MAX				// 지속시간 제한이 없음