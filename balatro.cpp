// 함수/변수/클래스 등 모든 이름은 대문자로 시작
// 단어별로 대문자로 표기
// 띄어쓰기는 언더바 이용

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Poker_Hands
{ // 조커도 넣고, 스톤도 넣을 예정
public:
  map<string, vector<int>> Poker_Ranks; // 조합 이름, 레벨, 칩, 배수 순서.

  void Initialize_PokerRank()
  {                                              // 레벨, 칩, 배수 순서
    Poker_Ranks["High_Card"] = {1, 5, 1};        // 아래 족보에 없는 카드
    Poker_Ranks["Pair"] = {1, 10, 2};            // 같은 숫자 2장 * 1쌍
    Poker_Ranks["Two_Pair"] = {1, 20, 2};        // 같은 숫자 2장 * 2쌍
    Poker_Ranks["Triple"] = {1, 30, 3};          // 같은 숫자 3장 * 1쌍
    Poker_Ranks["Straight"] = {1, 30, 4};        // 문양 상관 없이 연속 숫자 5장
    Poker_Ranks["Flush"] = {1, 35, 4};           // 숫자 상관 없이 같은 문양 5장
    Poker_Ranks["Full_House"] = {1, 40, 4};      // 트리플 + 페어
    Poker_Ranks["Four_Card"] = {1, 60, 7};       // 같은 숫자 4장 * 1쌍
    Poker_Ranks["Straight_Flush"] = {1, 100, 8}; // 같은 문양 연속 숫자 5장
  }
  // 족보의 레벨을 올리는 함수, [0]은 레벨, [1]은 칩, [2]는 배수
  void LvUp_High_Card()
  {
    Poker_Ranks["High_Card"][0] += 1;
    Poker_Ranks["High_Card"][1] += 10;
    Poker_Ranks["High_Card"][2] += 1;
  }
  void LvUp_Pair()
  {
    Poker_Ranks["Pair"][0] += 1;
    Poker_Ranks["Pair"][1] += 15;
    Poker_Ranks["High_Card"][2] += 1;
  }
  void LvUp_Two_Pair()
  {
    Poker_Ranks["Two_Pair"][0] += 1;
    Poker_Ranks["Two_Pair"][1] += 20;
    Poker_Ranks["Two_Pair"][2] += 1;
  }
  void LvUp_Triple()
  {
    Poker_Ranks["Triple"][0] += 1;
    Poker_Ranks["Triple"][1] += 20;
    Poker_Ranks["Triple"][2] += 2;
  }
  void LvUp_Straight()
  {
    Poker_Ranks["Straight"][0] += 1;
    Poker_Ranks["Straight"][1] += 30;
    Poker_Ranks["Straight"][2] += 3;
  }
  void LvUp_Flush()
  {
    Poker_Ranks["Flush"][0] += 1;
    Poker_Ranks["Flush"][1] += 15;
    Poker_Ranks["Flush"][2] += 2;
  }
  void LvUp_Full_House()
  {
    Poker_Ranks["Full_House"][0] += 1;
    Poker_Ranks["Full_House"][1] += 25;
    Poker_Ranks["Full_House"][2] += 2;
  }
  void LvUp_Four_Card()
  {
    Poker_Ranks["Four_Card"][0] += 1;
    Poker_Ranks["Four_Card"][1] += 30;
    Poker_Ranks["Four_Card"][2] += 3;
  }
  void LvUp_Straight_Flush()
  {
    Poker_Ranks["Straight_Flush"][0] += 1;
    Poker_Ranks["Straight_Flush"][1] += 40;
    Poker_Ranks["Straight_Flush"][2] += 4;
  }
};

class Trump
{
public:
  map<string, map<string, int>> Cards; // 스다하클, 숫자(AKQJ포함), 칩 순
  vector<string> MyCards;
  void Initialize_Trump()
  { // S0, D0, H0, C0은 각각 숫자 10을 의미.
    Cards["Spade"] = {{"SA", 11}, {"SK", 10}, {"SQ", 10}, {"SJ", 10}, {"S0", 10}, {"S9", 9}, {"S8", 8}, {"S7", 7}, {"S6", 6}, {"S5", 5}, {"S4", 4}, {"S3", 3}, {"S2", 2}, {"S1", 1}};
    Cards["Diamond"] = {{"DA", 11}, {"DK", 10}, {"DQ", 10}, {"DJ", 10}, {"D0", 10}, {"D9", 9}, {"D8", 8}, {"D7", 7}, {"D6", 6}, {"D5", 5}, {"D4", 4}, {"D3", 3}, {"D2", 2}, {"D1", 1}};
    Cards["Heart"] = {{"HA", 11}, {"HK", 10}, {"HQ", 10}, {"HJ", 10}, {"H0", 10}, {"H9", 9}, {"H8", 8}, {"H7", 7}, {"H6", 6}, {"H5", 5}, {"H4", 4}, {"H3", 3}, {"H2", 2}, {"H1", 1}};
    Cards["Clover"] = {{"CA", 11}, {"CK", 10}, {"CQ", 10}, {"CJ", 10}, {"C0", 10}, {"C9", 9}, {"C8", 8}, {"C7", 7}, {"C6", 6}, {"C5", 5}, {"C4", 4}, {"C3", 3}, {"C2", 2}, {"C1", 1}};
  }
};

void FindHighestScoreOnNumber(
    map<string, vector<int>> &Poker_Ranks, map<string, map<string, int>> &Cards,
    vector<string> &MyCards)
{ // 숫자 중 가장 큰 조합을 뽑는 함수
  vector<int> countNumberOnHand = {
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0}; // 이 벡터에다가 {0, ... A}까지의 숫자 카운트
  // countNumberOnHand의 index는 [1]부터 시작.

  for (const auto &card : MyCards)
  {
    char rank = card[1];
    int RankNumber;

    if (card[1] == 'A')
    {
      countNumberOnHand[14]++;
    }
    else if (card[1] == 'K')
    {
      countNumberOnHand[13]++;
    }
    else if (card[1] == 'Q')
    {
      countNumberOnHand[12]++;
    }
    else if (card[1] == 'J')
    {
      countNumberOnHand[11]++;
    }
    else if (card[1] == '0')
    {
      countNumberOnHand[10]++;
    }
    else
    {
      RankNumber = rank - '0';
      // char to int 변환. foo = (int)bar 하면 안됨.
      // ASCII로 바꾸는거라서 인덱스를 벗어날 수 있음.
      countNumberOnHand[RankNumber]++;
    }
  }
  // 이제 Poker_Rank와 countNumberOnHand를 이용해 각각의 족보가 가능한지 확인.
  // 확인하는 족보: 하이카드, 페어, 투페어, 트리플, 포카드
  // 맨 마지막에 High_Card를 넣어야 함.
  vector<int> NumberScore = {0, 0, 0, 0, 0};

  // condition => NumberScore[i] = Rank * 칩의 개수
}

int main()
{
  Poker_Hands pokerhands;
  Trump trump;
  pokerhands.Initialize_PokerRank();
  trump.Initialize_Trump();

  while (true)
  { // 카드 입력받고, MyCards에 push_back
    string card;
    cin >> card;
    if (card == "0")
    {
      break;
    }
    else
    {
      trump.MyCards.push_back(card);
    }
  }

  FindHighestScoreOnNumber(pokerhands.Poker_Ranks, trump.Cards, trump.MyCards);
  return 0;
}