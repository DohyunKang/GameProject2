#ifndef _GAME_H_
#define _GAME_H_
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#define BUFFER_W 400            // 게임 화면의 내부 가로 너비 (해상도)
#define BUFFER_H 300            // 게임 화면의 내부 세로 높이
#define DISP_SCALE 2.5          // 화면 확대 비율 (창 크기 조절용)
#define MAX_ENEMIES 200         // 화면에 동시에 존재할 수 있는 최대 적 수
#define MAX_ITEMS 8             // 화면에 동시에 존재할 수 있는 최대 아이템 수
#define MAX_RANK 10             // 랭킹 시스템에 저장될 최대 순위 개수

#define PLAYER_W 30             // 플레이어 가로 크기
#define PLAYER_H 30             // 플레이어 세로 크기

#define HP_W 24                 // 체력 아이템 가로 크기
#define HP_H 24                 // 체력 아이템 세로 크기
#define BARRIER_W 24            // 배리어 아이템 가로 크기
#define BARRIER_H 24            // 배리어 아이템 세로 크기
#define CHEST_W 24              // 보물상자 아이템 가로 크기
#define CHEST_H 24              // 보물상자 아이템 세로 크기

#define ENEMY1_W 20              // 기본 표창 가로 크기
#define ENEMY1_H 20              // 기본 표창 세로 크기
#define ENEMY2_W 20              // 집속탄 가로 크기
#define ENEMY2_H 20              // 집속탄 세로 크기
#define ENEMY3_W 20              // 유도 표창 가로 크기
#define ENEMY3_H 20              // 유도 표창 세로 크기


// 게임의 현재 흐름을 제어하는 상태 (메뉴, 게임 중, 결과창 등)
typedef enum {
    STATE_MENU, STATE_MODE_SELECT, STATE_GENDER_SELECT,
    STATE_PLAYING, STATE_INPUT_NAME, STATE_RANKING,
    STATE_GAMEOVER, STATE_VICTORY
} GAME_STATE;

// 게임 모드 설정
typedef enum {
    MODE_STORY,      // 스토리 모드
    MODE_CHALLENGE,  // 무한/도전 모드
    MODE_BOSS_ONLY   // 보스전만 진행하는 모드
} GAME_MODE;

// 적의 종류
typedef enum {
    ENEMY_SPEAR,     // 창병 (직선 공격 등)
    ENEMY_BOMB,      // 폭탄병 (범위 공격)
    ENEMY_FIREBALL,  // 화염구
    ENEMY_HOMING,    // 추적탄 (플레이어를 쫓아옴)
    ENEMY_TYPE_N      // 적의 수
    //ENEMY_BOSS_SHOT  // 보스가 발사하는 탄환
} ENEMY_TYPE;

// 아이템의 종류
typedef enum {
    ITEM_HEART,                 // 체력 회복
    ITEM_BARRIER,               // 방어막 생성
    ITEM_TREASURE_CHEST_TIME    // 보물상자 혹은 시간 관련 아이템
} ITEM_TYPE;

// 랭킹 정보 (이름과 클리어 타임)
typedef struct { char name[16]; float time; } Rank;

// 플레이어 정보
typedef struct {
    float x, y;          // 위치 좌표
    int hp, gender;      // 체력 및 캐릭터 성별
    int inv_timer;       // 무적 시간 타이머 (피격 후 깜빡임 등)
    bool barrier;        // 방어막 보유 여부
    int barrier_timer;   // 방어막 지속 시간
} Player;

// 적 정보
typedef struct {
    float x, y;          // 위치 좌표
    float dx, dy;        // 이동 속도 및 방향 (델타 값)
    ENEMY_TYPE type;     // 적 종류
    int timer;           // 패턴용 타이머
    bool active;         // 현재 화면 존재 여부 (활성화 상태)
} Enemy;

// 아이템 정보
typedef struct {
    float x, y;          // 위치 좌표
    ITEM_TYPE type;      // 아이템 종류
    int timer;           // 소멸 전 지속 시간 등
    bool active;         // 활성화 상태
} Item;

GAME_STATE state = STATE_MENU;  // 초기 상태는 메뉴 화면
GAME_MODE mode = MODE_STORY;    // 기본 모드는 스토리 모드

Player p;                       // 플레이어 객체 생성
Enemy en[MAX_ENEMIES];          // 적 배열 선언
Item it[MAX_ITEMS];             // 아이템 배열 선언
Rank ranks[MAX_RANK];           // 랭킹 배열 선언

int rank_count = 0;             // 현재 등록된 랭킹 개수
char input_name[16] = "";       // 플레이어가 입력 중인 이름
int stage = 1;                  // 현재 스테이지 번호
long frames = 0;                // 게임 시작 후 흐른 총 프레임 수
float boss_time = 0;            // 보스전 진행 시간 (미정 부분 0으로 처리)

// 키보드 입력 상태 저장 (ALLEGRO 라이브러리용)
bool key[ALLEGRO_KEY_MAX] = { 0 };

// 효과음 자원
ALLEGRO_SAMPLE* snd_hit = NULL; // 피격 시 효과음
ALLEGRO_SAMPLE* snd_die = NULL; // 사망 시 효과음


// 메뉴 함수 선언
void store_filed();
void cal_score();
void background(int);

// player & item 함수 선언
void pi_init();
void player_update();
void item_update();
void player_draw();
void item_draw();

// enemy 함수 선언
void enemy_init();
void enemy_update();
void enemy_draw();

// hud 함수 선언
void hud_init();
void hud_update();
void hud_draw();

// 공용체 함수
void must_init(bool test, const char* description);
int between(int lo, int hi);
float between_f(float lo, float hi);
bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);

void disp_init();
void disp_deinit();
void disp_pre_draw();
void disp_post_draw();

void keyboard_init();
void keyboard_update(ALLEGRO_EVENT* event);

ALLEGRO_BITMAP* sprite_grab(int x, int y, int w, int h);
void sprites_init();
void sprites_deinit();

void audio_init();
void audio_deinit();

void fx_init();
void fx_add(bool spark, int x, int y);
void fx_update();
void fx_draw();

#endif