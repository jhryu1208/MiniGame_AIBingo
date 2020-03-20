#include <iostream>
#include <time.h>

using namespace std;

enum AI_MODE
{
	AM_EASY = 1,
	AM_HARD
};

enum LINE_NUMBER
{
	LN_H1,
	LN_H2,
	LN_H3,
	LN_H4,
	LN_H5,

	LN_V1,
	LN_V2,
	LN_V3,
	LN_V4,
	LN_V5,

	LN_LT,
	LN_RT
};
int main()
{
	srand((unsigned int)time(0));

	// 5X5 빙고판
	int iNumber[25] = {};
	int iAINumber[25] = {};

	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
		iAINumber[i] = i + 1;
	}

	int idx1, idx2, iTemp;

	// 숫자를 섞어준다.
	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;

		idx1 = rand() % 25;
		idx2 = rand() % 25;
		iTemp = iAINumber[idx1];
		iAINumber[idx1] = iAINumber[idx2];
		iAINumber[idx2] = iTemp;
	}


	int iBingo = 0, iAIBingo = 0;
	int iAIMode;

	// AI 난이도를 선택한다.
	while (1)
	{
		system("cls");
		cout << "1.EASY" << endl;
		cout << "2.HARD" << endl;
		cout << "AI 모드를 선택하세요 :" << endl;
		cin >> iAIMode;

		if (iAIMode >= AM_EASY && iAIMode <= AM_HARD)
			break;
	}
	/*
	AI EASY 모드는 현재 AI의 숫자목록중 *로 바뀌지 않은 숫자 목록을 만들어서
	그 목록중 하나를 선택하게 한다. (랜덤하게)
	*/
	// 선택안된 목록 배열을 만들어준다.
	int iNoneSelect[25] = {};
	// 선택 안된 숫자 개수를 저장한다.
	int iNoneSelectCount = 0;

	while (1)
	{
		// *이 생긴
		// 빙고판을 즉각적으로 업데이트하기위해서 결과화면을 지워주고 새로만든다.
		system("cls");

		// 숫자 5X5로 출력한다.
		cout << "===================== Player =====================" << endl;
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				// 숫자를 *로 업데이트
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				// 그대로 출력
				else
					cout << iNumber[i * 5 + j] << "\t";
			}
			cout << endl;
		}

		cout << "Bingo Line :" << iBingo << endl << endl;

		// AI 빙고 판을 출력한다.
		cout << "======================= AI =======================" << endl;

		switch (iAIMode)
		{
		case AM_EASY:
			cout << "AIMODE : EASY " << endl;
			break;
		case AM_HARD:
			cout << "AIMODE:HARD" << endl;
			break;
		}

		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (iAINumber[i * 5 + j] == INT_MAX)
					cout << "*\t";

				else
					cout << iAINumber[i * 5 + j] << "\t";
			}
			cout << endl;
		}

		// AI 빙고 줄 수를 출력한다.
		cout << "AIBingo Line :" << iAIBingo << endl;


		// 줄수가 5 이상일 경우 게임을 종료한다.
		// 똑같은 5줄이라도 플레이어에게 승리 우선권을 부여한다.
		if (iBingo >= 5)
		{
			cout << "Player 승리" << endl;
			break;
		}

		else if (iAIBingo >= 5)
		{
			cout << "AI 승리" << endl;
			break;
		}

		cout << "숫자를 입력하세요 (0: 종료)";

		int iInput;
		cin >> iInput;

		if (iInput == 0)
			break;

		else if (iInput < 1 || iInput>25)
			continue;

		// 중복입력을 체크하기 위한 변수이다. 기본적으로 중복되었다라고 하기위해 true로 잡았다.
		bool bAcc = true;

		// 모든 숫자를 차례대로 검사해서 입력한 숫자와 같은 숫자가 있는지를 찾아낸다.
		for (int i = 0; i < 25; ++i)
		{
			// 같은 숫자가 있을 경우
			if (iInput == iNumber[i])
			{
				// 숫자를 찾았을 경우 중복된 숫자가 아니므로
				// bAcc 변수를 false로 만들어준다.
				bAcc = false;

				// 숫자를 *로 변경하기 위해 특수한 값인 INT_MAX로 해준다.
				// INT_MAX에는 특수값(2147483647)이 들어있다.
				iNumber[i] = INT_MAX;

				// 더이상 다른 숫자를 찾아볼 필요가 없으므로
				// for문을 빠져나간다.
				break;
			}
		}

		// bAcc 변수가 true일 경우 중복된 숫자를 입력해서 숫자를 *로
		// 바꾸지 못했으므로 다시 입력받게  continue 해준다.
		if (bAcc)
			continue;

		// 중복이 아니라면 AI의 숫자도 찾아서 *로 바꿔준다.
		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] == iInput)
			{
				iAINumber[i] = INT_MAX;

				break;
			}
		}

		// AI가 선택을 한다. AI가 선택하는 것은 AI 모드에 따라서 달라진다.
		switch (iAIMode)
		{
		case AM_EASY:
			// 선택안된 숫자목록을 만들어준다.
			// 선택안된 숫자 개수는 목록을 만들어 카운팅해준다.
			iNoneSelectCount = 0;
			for (int i = 0; i < 25; ++i)
			{
				if (iAINumber[i] != INT_MAX)
				{
					// *이 아닌 숫자일 경우 iNoneSelectCount를 인덱스로 활요한다.
					// 선택 안된 목록에 추가할때마다 개수를 1씩증가 시켜서
					// 총 선택안된 개수를 구해준다.
					// 그런데 0부터 카운트가 시작이므로 0번에 넣고 ++해서 1개
					// 추가되었다라고 명시한다.
					iNoneSelect[iNoneSelectCount] = iAINumber[i];
					++iNoneSelectCount;
				}
			}

			// for문을 빠져나오게 되면 선택안된 목록이 만들어지고
			// 선택안된 목록의 개수가 만들어지게 된다.
			// 선택안된 목록의 숫자중 랜덤한 하나의 숫자를 얻어오기 위해
			// 인덱스를 랜덤하게 구해준다.
			iInput = iNoneSelect[rand() % iNoneSelectCount];
			break;

		case AM_HARD:
			// 하드모드는 현재 숫자중 빙고줄 완성 가능성이 가장 높은 줄을
			// 찾아서 그 줄에 있는 숫자중 하나를 *로 만들어준다.

			int iLine = 0;
			int iStarCount = 0;
			int iSaveCount = 0;

			// 가로 라인 중 가장 *이 많은 라인을 찾아낸다.
			for (int i = 0; i < 5; ++i)
			{
				iStarCount = 0;
				for (int j = 0; j < 5; ++j)
				{
					if (iAINumber[i * 5 + j] == INT_MAX)
						++iStarCount;
				}

				// 카운트가 5이면 빙고완성 줄이기때문에, 5보다 작은경우에서 고려해야함
				// 기존에 가장 많은 라인의 별보다 커야 가장 별이 많은 라인이므로
				// 라인을 교체해주고 저장된 별 수를 교체한다.
				if (iStarCount < 5 && iSaveCount < iStarCount)
				{
					// i는 가로줄번호
					// 여기는 가로 라인중 가장 별이 많은 라인을 체크하는 곳이다.
					// 가로라인은 0 ~ 4 로 의미를 부여했다.
					iLine = i;
					iSaveCount = iStarCount;
				}
			}

			// 가로 라인중 가장 별이 많은 라인은 이미 위에서 구했다.
			// 이 값과 세로 라인들을 비교하여 별이 가장 많은 라인을 구한다.
			for (int i = 0; i < 5; ++i)
			{
				iStarCount = 0;
				for (int j = 0; j < 5; ++j)
				{
					if (iAINumber[j * 5 + i] == INT_MAX)
						++iStarCount;
				}

				if (iStarCount < 5 && iSaveCount < iStarCount)
				{
					// 세로라인은 5 ~ 9로 의미를 부여한다.
					// ex 0열은 5, 1열은 6, ..., 4열은 9
					iLine = i + 5;
					iSaveCount = iStarCount;
				}
			}

			// 왼쪽 -> 오른쪽 대각선 체크
			iStarCount = 0;
			for (int i = 0; i < 25; i += 6)
			{
				if (iAINumber[i] == INT_MAX)
					++iStarCount;
			}

			if (iStarCount < 5 && iSaveCount < iStarCount)
			{
				// LN_LT는 열거체에 의해서 10을 의미한다.
				iLine = LN_LT;
				iSaveCount == iStarCount;
			}


			// 오른쪽 -> 왼쪽 대각선 체크
			iStarCount = 0;
			for (int i = 4; i < 25; i += 4)
			{
				if (iAINumber[i] == INT_MAX)
					++iStarCount;
			}

			if (iStarCount < 5 && iSaveCount < iStarCount)
			{
				// LN_RT는 열거체에 의해서 11을 의미한다.
				iLine = LN_RT;
				iSaveCount == iStarCount;
			}

			// 모든 라인을 조사했으면 iLine에 가능성이 가장 높은 줄 번호가 저장되었다.
			// 그 줄에 있는 *이 아닌 숫자중 하나를 선택하게 한다.
			// 1. 가로줄일 경우
			if (iLine <= LN_H5)
			{
				// 가로줄일 경우 iLine이 0 ~ 4 사이의 값이다.
				for (int i = 0; i < 5; ++i)
				{
					if (iAINumber[iLine * 5 + i] != INT_MAX)
					{
						iInput = iAINumber[iLine * 5 + i];
						break;
					}
				}
			}

			// 2. 세로줄일 경우
			else if (iLine <= LN_V5)
			{
				for (int i = 0; i < 5; ++i)
				{
					if (iAINumber[i * 5 + (iLine - 5)] != INT_MAX)
					{
						iInput = iAINumber[i * 5 + (iLine - 5)];
						break;
					}
				}
			}

			// 3. 가로줄 (왼쪽상단에서 오른쪽하단)일 경우
			else if (iLine <= LN_LT)
			{
				for (int i = 0; i < 25; i += 6)
				{
					if (iAINumber[i] != INT_MAX)
					{
						iInput = iAINumber[i];
						break;
					}
				}
			}

			// 4. 가로줄 (오른쪽상단에서 왼쪽하단)일 경우
			else if (iLine <= LN_RT)
			{
				for (int i = 4; i < 20; i += 4)
				{
					if (iAINumber[i] != INT_MAX)
					{
						iInput = iAINumber[i];
						break;
					}
				}
			}
			break;
		}

		// AI가 숫자를 선택했으므로 플레이어와 AI의 숫자를 *로 바꿔준다.
		// Player의 숫자 교체
		for (int i = 0; i < 25; ++i)
		{
			if (iNumber[i] == iInput)
			{
				iNumber[i] = INT_MAX;
				break;
			}
		}
		// AI의 숫자 교체
		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] == iInput)
			{
				iAINumber[i] = INT_MAX;
				break;
			}
		}

		// 빙고 줄 수를 체크하는 것은 매번 숫자를 입력할때마다 처음부터
		// 새로 카운트 할것이다. 그러므로 iBingo 변수를 0으로 매번
		// 초기화하고 새롭게 줄 수를 구해주도록 한다.
		iBingo = 0;
		iAIBingo = 0;

		// 가로,세로 줄 수를 구해준다.
		int iStar1 = 0, iStar2 = 0;
		int iAIStar1 = 0, iAIStar2 = 0;

		for (int i = 0; i < 5; ++i)
		{
			// 한줄을 체크하기 전에 먼저 0으로 별 개수를 초기화한다.
			iStar1 = iStar2 = 0;
			iAIStar1 = iAIStar2 = 0;
			for (int j = 0; j < 5; ++j)
			{
				// 가로 별 개수를 구해준다.
				if (iNumber[i * 5 + j] == INT_MAX)
					++iStar1;

				// 세로 별 개수를 구해준다.
				if (iNumber[i + 5 * j] == INT_MAX)
					++iStar2;

				if (iAINumber[i * 5 + j] == INT_MAX)
					++iAIStar1;

				if (iAINumber[i + 5 * j] == INT_MAX)
					++iAIStar2;
			}

			// j for문을 빠져나오고 나면 현재 줄의 가로 별 개수가 몇개인지
			// iStar1 변수에 들어가게 된다.
			// iStar1 값이 5이면 한줄이 모두 *이라는 의미이므로 빙고 줄 카운트를 추가한다.
			if (iStar1 == 5 || iStar2 == 5)
				++iBingo;

			if (iAIStar1 == 5 || iAIStar2 == 5)
				++iAIBingo;
		}

		// 왼쪽 상단 -> 오른쪽 하단 대각선 체크
		iStar1 = 0;
		iAIStar1 = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;

			if (iAINumber[i] == INT_MAX)
				++iAIStar1;
		}

		if (iStar1 == 5)
			++iBingo;

		// 오른쪽 상단 -> 왼쪽 하단 대각선 체크
		iStar1 = 0;
		iAIStar1 = 0;
		for (int i = 4; i < 25; i += 4)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;

			if (iAINumber[i] == INT_MAX)
				++iAIStar1;
		}

		if (iStar1 == 5)
			++iBingo;

		if (iAIStar1 == 5)
			++iAIBingo;
	}
	return 0;
}