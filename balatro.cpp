// 함수/변수/클래스 등 모든 이름은 대문자로 시작
// 단어별로 대문자로 표기
// 띄어쓰기는 언더바 이용

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

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

// 스트레이트 확인 함수
bool HasStraight(const vector<int> &countNumberOnHand)
{
  // A-5-4-3-2 스트레이트 확인 (A는 1로도 사용 가능)
  if (countNumberOnHand[1] > 0 && countNumberOnHand[2] > 0 &&
      countNumberOnHand[3] > 0 && countNumberOnHand[4] > 0 &&
      countNumberOnHand[14] > 0)
  {
    return true;
  }

  // 일반 스트레이트 확인 (5장 연속)
  for (int i = 1; i <= 10; i++)
  {
    if (countNumberOnHand[i] > 0 && countNumberOnHand[i + 1] > 0 &&
        countNumberOnHand[i + 2] > 0 && countNumberOnHand[i + 3] > 0 &&
        countNumberOnHand[i + 4] > 0)
    {
      return true;
    }
  }

  return false;
}

// 플러시 확인 함수
bool HasFlush(const vector<string> &MyCards)
{
  map<char, int> suitCount;

  for (const auto &card : MyCards)
  {
    suitCount[card[0]]++;
  }

  // 같은 무늬가 5장 이상인지 확인
  for (const auto &suit : suitCount)
  {
    if (suit.second >= 5)
    {
      return true;
    }
  }

  return false;
}

// 스트레이트 플러시 확인 함수
bool HasStraightFlush(const vector<string> &MyCards)
{
  map<char, vector<int>> suitCards;

  // 무늬별로 카드 분류
  for (const auto &card : MyCards)
  {
    char suit = card[0];
    char rank = card[1];
    int rankValue;

    if (rank == 'A')
    {
      rankValue = 14;
      suitCards[suit].push_back(1); // A는 1과 14 둘 다 가능
    }
    else if (rank == 'K')
    {
      rankValue = 13;
    }
    else if (rank == 'Q')
    {
      rankValue = 12;
    }
    else if (rank == 'J')
    {
      rankValue = 11;
    }
    else if (rank == '0')
    {
      rankValue = 10;
    }
    else
    {
      rankValue = rank - '0';
    }

    suitCards[suit].push_back(rankValue);
  }

  // 각 무늬별로 스트레이트 여부 확인
  for (auto &suit : suitCards)
  {
    if (suit.second.size() >= 5)
    {
      // 중복 제거 및 정렬
      sort(suit.second.begin(), suit.second.end());
      suit.second.erase(unique(suit.second.begin(), suit.second.end()), suit.second.end());

      // 스트레이트 확인
      for (size_t i = 0; i <= suit.second.size() - 5; i++)
      {
        if (suit.second[i + 4] - suit.second[i] == 4)
        {
          return true;
        }
      }

      // A-5-4-3-2 스트레이트 확인
      if (find(suit.second.begin(), suit.second.end(), 14) != suit.second.end() &&
          find(suit.second.begin(), suit.second.end(), 2) != suit.second.end() &&
          find(suit.second.begin(), suit.second.end(), 3) != suit.second.end() &&
          find(suit.second.begin(), suit.second.end(), 4) != suit.second.end() &&
          find(suit.second.begin(), suit.second.end(), 5) != suit.second.end())
      {
        return true;
      }
    }
  }

  return false;
}

map<string, int> FindHighestScoreOnNumber(
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
  vector<int> NumberScore = {0, 0, 0, 0, 0};
  map<string, int> HandScores = {
      {"High_Card", 0},
      {"Pair", 0},
      {"Two_Pair", 0},
      {"Triple", 0},
      {"Straight", 0},
      {"Flush", 0},
      {"Full_House", 0},
      {"Four_Card", 0},
      {"Straight_Flush", 0}};

  // 스트레이트 플러시 확인
  if (HasStraightFlush(MyCards))
  {
    int level = Poker_Ranks["Straight_Flush"][0];
    int chips = Poker_Ranks["Straight_Flush"][1];
    int multiplier = Poker_Ranks["Straight_Flush"][2];
    HandScores["Straight_Flush"] = level * chips * multiplier;
  }

  // 포카드 확인
  bool hasFourCard = false;
  for (int i = 1; i <= 14; i++)
  {
    if (countNumberOnHand[i] >= 4)
    {
      hasFourCard = true;
      int level = Poker_Ranks["Four_Card"][0];
      int chips = Poker_Ranks["Four_Card"][1];
      int multiplier = Poker_Ranks["Four_Card"][2];
      HandScores["Four_Card"] = level * chips * multiplier;
      break;
    }
  }

  // 풀하우스 확인
  bool hasThreeOfAKind = false;
  int tripleRank = 0;
  bool hasPair = false;
  int pairRank = 0;

  for (int i = 1; i <= 14; i++)
  {
    if (countNumberOnHand[i] >= 3)
    {
      hasThreeOfAKind = true;
      tripleRank = i;
    }
  }

  for (int i = 1; i <= 14; i++)
  {
    if (i != tripleRank && countNumberOnHand[i] >= 2)
    {
      hasPair = true;
      pairRank = i;
      break;
    }
  }

  if (hasThreeOfAKind && hasPair)
  {
    int level = Poker_Ranks["Full_House"][0];
    int chips = Poker_Ranks["Full_House"][1];
    int multiplier = Poker_Ranks["Full_House"][2];
    HandScores["Full_House"] = level * chips * multiplier;
  }

  // 플러시 확인
  if (HasFlush(MyCards))
  {
    int level = Poker_Ranks["Flush"][0];
    int chips = Poker_Ranks["Flush"][1];
    int multiplier = Poker_Ranks["Flush"][2];
    HandScores["Flush"] = level * chips * multiplier;
  }

  // 스트레이트 확인
  if (HasStraight(countNumberOnHand))
  {
    int level = Poker_Ranks["Straight"][0];
    int chips = Poker_Ranks["Straight"][1];
    int multiplier = Poker_Ranks["Straight"][2];
    HandScores["Straight"] = level * chips * multiplier;
  }

  // 트리플 확인 (풀하우스 아닌 경우)
  if (hasThreeOfAKind && !hasPair)
  {
    int level = Poker_Ranks["Triple"][0];
    int chips = Poker_Ranks["Triple"][1];
    int multiplier = Poker_Ranks["Triple"][2];
    HandScores["Triple"] = level * chips * multiplier;
  }

  // 투페어 확인
  int pairCount = 0;
  for (int i = 1; i <= 14; i++)
  {
    if (countNumberOnHand[i] >= 2)
    {
      pairCount++;
    }
  }

  if (pairCount >= 2)
  {
    int level = Poker_Ranks["Two_Pair"][0];
    int chips = Poker_Ranks["Two_Pair"][1];
    int multiplier = Poker_Ranks["Two_Pair"][2];
    HandScores["Two_Pair"] = level * chips * multiplier;
  }

  // 원페어 확인
  if (pairCount == 1)
  {
    int level = Poker_Ranks["Pair"][0];
    int chips = Poker_Ranks["Pair"][1];
    int multiplier = Poker_Ranks["Pair"][2];
    HandScores["Pair"] = level * chips * multiplier;
  }

  // 하이카드 (항상 있음)
  int level = Poker_Ranks["High_Card"][0];
  int chips = Poker_Ranks["High_Card"][1];
  int multiplier = Poker_Ranks["High_Card"][2];
  HandScores["High_Card"] = level * chips * multiplier;

  return HandScores;
}

// 가장 높은 점수의 족보를 찾는 함수
pair<string, int> FindBestHand(const map<string, int> &HandScores)
{
  string bestHand = "High_Card";
  int highestScore = 0;

  for (const auto &hand : HandScores)
  {
    if (hand.second > highestScore)
    {
      highestScore = hand.second;
      bestHand = hand.first;
    }
  }

  return {bestHand, highestScore};
}

int main()
{
  Poker_Hands pokerhands;
  Trump trump;
  pokerhands.Initialize_PokerRank();
  trump.Initialize_Trump();

  cout << "<<카드 표기법>>\n스페이드: S, 다이아: D, 하트: H, 클로버: C\n";
  cout << "킹, 퀸, 잭, 에이스: K, Q, J, A\n";
  cout << "숫자: 숫자\n";
  cout << "예시: 하트 킹인 경우 HK, 클로버 6인 경우 C6으로 입력.\n띄어쓰기로 카드를 구별하며, 입력이 다 된 후 띄어쓴 다음 0을 입력하여 입력을 종료합니다.\n";
  cout << "카드 족보를 입력해주세요.\n\n>>";
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

  map<string, int> handScores = FindHighestScoreOnNumber(pokerhands.Poker_Ranks, trump.Cards, trump.MyCards);
  pair<string, int> bestHand = FindBestHand(handScores);

  cout << "최고점수의 족보: " << bestHand.first << endl;

  return 0;
}