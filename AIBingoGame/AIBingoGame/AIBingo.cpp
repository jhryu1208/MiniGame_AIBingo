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

	// 5X5 ������
	int iNumber[25] = {};
	int iAINumber[25] = {};

	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
		iAINumber[i] = i + 1;
	}

	int idx1, idx2, iTemp;

	// ���ڸ� �����ش�.
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

	// AI ���̵��� �����Ѵ�.
	while (1)
	{
		system("cls");
		cout << "1.EASY" << endl;
		cout << "2.HARD" << endl;
		cout << "AI ��带 �����ϼ��� :" << endl;
		cin >> iAIMode;

		if (iAIMode >= AM_EASY && iAIMode <= AM_HARD)
			break;
	}
	/*
	AI EASY ���� ���� AI�� ���ڸ���� *�� �ٲ��� ���� ���� ����� ����
	�� ����� �ϳ��� �����ϰ� �Ѵ�. (�����ϰ�)
	*/
	// ���þȵ� ��� �迭�� ������ش�.
	int iNoneSelect[25] = {};
	// ���� �ȵ� ���� ������ �����Ѵ�.
	int iNoneSelectCount = 0;

	while (1)
	{
		// *�� ����
		// �������� �ﰢ������ ������Ʈ�ϱ����ؼ� ���ȭ���� �����ְ� ���θ����.
		system("cls");

		// ���� 5X5�� ����Ѵ�.
		cout << "===================== Player =====================" << endl;
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				// ���ڸ� *�� ������Ʈ
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				// �״�� ���
				else
					cout << iNumber[i * 5 + j] << "\t";
			}
			cout << endl;
		}

		cout << "Bingo Line :" << iBingo << endl << endl;

		// AI ���� ���� ����Ѵ�.
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

		// AI ���� �� ���� ����Ѵ�.
		cout << "AIBingo Line :" << iAIBingo << endl;


		// �ټ��� 5 �̻��� ��� ������ �����Ѵ�.
		// �Ȱ��� 5���̶� �÷��̾�� �¸� �켱���� �ο��Ѵ�.
		if (iBingo >= 5)
		{
			cout << "Player �¸�" << endl;
			break;
		}

		else if (iAIBingo >= 5)
		{
			cout << "AI �¸�" << endl;
			break;
		}

		cout << "���ڸ� �Է��ϼ��� (0: ����)";

		int iInput;
		cin >> iInput;

		if (iInput == 0)
			break;

		else if (iInput < 1 || iInput>25)
			continue;

		// �ߺ��Է��� üũ�ϱ� ���� �����̴�. �⺻������ �ߺ��Ǿ��ٶ�� �ϱ����� true�� ��Ҵ�.
		bool bAcc = true;

		// ��� ���ڸ� ���ʴ�� �˻��ؼ� �Է��� ���ڿ� ���� ���ڰ� �ִ����� ã�Ƴ���.
		for (int i = 0; i < 25; ++i)
		{
			// ���� ���ڰ� ���� ���
			if (iInput == iNumber[i])
			{
				// ���ڸ� ã���� ��� �ߺ��� ���ڰ� �ƴϹǷ�
				// bAcc ������ false�� ������ش�.
				bAcc = false;

				// ���ڸ� *�� �����ϱ� ���� Ư���� ���� INT_MAX�� ���ش�.
				// INT_MAX���� Ư����(2147483647)�� ����ִ�.
				iNumber[i] = INT_MAX;

				// ���̻� �ٸ� ���ڸ� ã�ƺ� �ʿ䰡 �����Ƿ�
				// for���� ����������.
				break;
			}
		}

		// bAcc ������ true�� ��� �ߺ��� ���ڸ� �Է��ؼ� ���ڸ� *��
		// �ٲ��� �������Ƿ� �ٽ� �Է¹ް�  continue ���ش�.
		if (bAcc)
			continue;

		// �ߺ��� �ƴ϶�� AI�� ���ڵ� ã�Ƽ� *�� �ٲ��ش�.
		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] == iInput)
			{
				iAINumber[i] = INT_MAX;

				break;
			}
		}

		// AI�� ������ �Ѵ�. AI�� �����ϴ� ���� AI ��忡 ���� �޶�����.
		switch (iAIMode)
		{
		case AM_EASY:
			// ���þȵ� ���ڸ���� ������ش�.
			// ���þȵ� ���� ������ ����� ����� ī�������ش�.
			iNoneSelectCount = 0;
			for (int i = 0; i < 25; ++i)
			{
				if (iAINumber[i] != INT_MAX)
				{
					// *�� �ƴ� ������ ��� iNoneSelectCount�� �ε����� Ȱ���Ѵ�.
					// ���� �ȵ� ��Ͽ� �߰��Ҷ����� ������ 1������ ���Ѽ�
					// �� ���þȵ� ������ �����ش�.
					// �׷��� 0���� ī��Ʈ�� �����̹Ƿ� 0���� �ְ� ++�ؼ� 1��
					// �߰��Ǿ��ٶ�� ����Ѵ�.
					iNoneSelect[iNoneSelectCount] = iAINumber[i];
					++iNoneSelectCount;
				}
			}

			// for���� ���������� �Ǹ� ���þȵ� ����� ���������
			// ���þȵ� ����� ������ ��������� �ȴ�.
			// ���þȵ� ����� ������ ������ �ϳ��� ���ڸ� ������ ����
			// �ε����� �����ϰ� �����ش�.
			iInput = iNoneSelect[rand() % iNoneSelectCount];
			break;

		case AM_HARD:
			// �ϵ���� ���� ������ ������ �ϼ� ���ɼ��� ���� ���� ����
			// ã�Ƽ� �� �ٿ� �ִ� ������ �ϳ��� *�� ������ش�.

			int iLine = 0;
			int iStarCount = 0;
			int iSaveCount = 0;

			// ���� ���� �� ���� *�� ���� ������ ã�Ƴ���.
			for (int i = 0; i < 5; ++i)
			{
				iStarCount = 0;
				for (int j = 0; j < 5; ++j)
				{
					if (iAINumber[i * 5 + j] == INT_MAX)
						++iStarCount;
				}

				// ī��Ʈ�� 5�̸� ����ϼ� ���̱⶧����, 5���� ������쿡�� ����ؾ���
				// ������ ���� ���� ������ ������ Ŀ�� ���� ���� ���� �����̹Ƿ�
				// ������ ��ü���ְ� ����� �� ���� ��ü�Ѵ�.
				if (iStarCount < 5 && iSaveCount < iStarCount)
				{
					// i�� �����ٹ�ȣ
					// ����� ���� ������ ���� ���� ���� ������ üũ�ϴ� ���̴�.
					// ���ζ����� 0 ~ 4 �� �ǹ̸� �ο��ߴ�.
					iLine = i;
					iSaveCount = iStarCount;
				}
			}

			// ���� ������ ���� ���� ���� ������ �̹� ������ ���ߴ�.
			// �� ���� ���� ���ε��� ���Ͽ� ���� ���� ���� ������ ���Ѵ�.
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
					// ���ζ����� 5 ~ 9�� �ǹ̸� �ο��Ѵ�.
					// ex 0���� 5, 1���� 6, ..., 4���� 9
					iLine = i + 5;
					iSaveCount = iStarCount;
				}
			}

			// ���� -> ������ �밢�� üũ
			iStarCount = 0;
			for (int i = 0; i < 25; i += 6)
			{
				if (iAINumber[i] == INT_MAX)
					++iStarCount;
			}

			if (iStarCount < 5 && iSaveCount < iStarCount)
			{
				// LN_LT�� ����ü�� ���ؼ� 10�� �ǹ��Ѵ�.
				iLine = LN_LT;
				iSaveCount == iStarCount;
			}


			// ������ -> ���� �밢�� üũ
			iStarCount = 0;
			for (int i = 4; i < 25; i += 4)
			{
				if (iAINumber[i] == INT_MAX)
					++iStarCount;
			}

			if (iStarCount < 5 && iSaveCount < iStarCount)
			{
				// LN_RT�� ����ü�� ���ؼ� 11�� �ǹ��Ѵ�.
				iLine = LN_RT;
				iSaveCount == iStarCount;
			}

			// ��� ������ ���������� iLine�� ���ɼ��� ���� ���� �� ��ȣ�� ����Ǿ���.
			// �� �ٿ� �ִ� *�� �ƴ� ������ �ϳ��� �����ϰ� �Ѵ�.
			// 1. �������� ���
			if (iLine <= LN_H5)
			{
				// �������� ��� iLine�� 0 ~ 4 ������ ���̴�.
				for (int i = 0; i < 5; ++i)
				{
					if (iAINumber[iLine * 5 + i] != INT_MAX)
					{
						iInput = iAINumber[iLine * 5 + i];
						break;
					}
				}
			}

			// 2. �������� ���
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

			// 3. ������ (���ʻ�ܿ��� �������ϴ�)�� ���
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

			// 4. ������ (�����ʻ�ܿ��� �����ϴ�)�� ���
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

		// AI�� ���ڸ� ���������Ƿ� �÷��̾�� AI�� ���ڸ� *�� �ٲ��ش�.
		// Player�� ���� ��ü
		for (int i = 0; i < 25; ++i)
		{
			if (iNumber[i] == iInput)
			{
				iNumber[i] = INT_MAX;
				break;
			}
		}
		// AI�� ���� ��ü
		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] == iInput)
			{
				iAINumber[i] = INT_MAX;
				break;
			}
		}

		// ���� �� ���� üũ�ϴ� ���� �Ź� ���ڸ� �Է��Ҷ����� ó������
		// ���� ī��Ʈ �Ұ��̴�. �׷��Ƿ� iBingo ������ 0���� �Ź�
		// �ʱ�ȭ�ϰ� ���Ӱ� �� ���� �����ֵ��� �Ѵ�.
		iBingo = 0;
		iAIBingo = 0;

		// ����,���� �� ���� �����ش�.
		int iStar1 = 0, iStar2 = 0;
		int iAIStar1 = 0, iAIStar2 = 0;

		for (int i = 0; i < 5; ++i)
		{
			// ������ üũ�ϱ� ���� ���� 0���� �� ������ �ʱ�ȭ�Ѵ�.
			iStar1 = iStar2 = 0;
			iAIStar1 = iAIStar2 = 0;
			for (int j = 0; j < 5; ++j)
			{
				// ���� �� ������ �����ش�.
				if (iNumber[i * 5 + j] == INT_MAX)
					++iStar1;

				// ���� �� ������ �����ش�.
				if (iNumber[i + 5 * j] == INT_MAX)
					++iStar2;

				if (iAINumber[i * 5 + j] == INT_MAX)
					++iAIStar1;

				if (iAINumber[i + 5 * j] == INT_MAX)
					++iAIStar2;
			}

			// j for���� ���������� ���� ���� ���� ���� �� ������ �����
			// iStar1 ������ ���� �ȴ�.
			// iStar1 ���� 5�̸� ������ ��� *�̶�� �ǹ��̹Ƿ� ���� �� ī��Ʈ�� �߰��Ѵ�.
			if (iStar1 == 5 || iStar2 == 5)
				++iBingo;

			if (iAIStar1 == 5 || iAIStar2 == 5)
				++iAIBingo;
		}

		// ���� ��� -> ������ �ϴ� �밢�� üũ
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

		// ������ ��� -> ���� �ϴ� �밢�� üũ
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