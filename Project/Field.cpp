#include "Field.h"
#include "time.h"

void CField::Initialize(void) 
{
	CUtilities::SetCurrentDirectory("Resource");
	gSound[0].Load("PuyoMove.mp3");
	gSound[1].Load("PuyoRotate.mp3");
	gSound[2].Load("PuyoDrop.mp3");
	gSound[3].Load("Change.mp3");
	gSound[4].Load("PuyoDelete.mp3");

	random.SetSeed(time(NULL));

	nowState = eDrop;
	score = 0;

	dropTime = 2.0f;
	accelNum = 1500;
	obstacleTime = 10.0f;
	obstacleAmount = 2;
	stopCnt = 0;
	waitTime = 0;


	stock[0] = 0;
	stock[1] = 0;

	for (int y = 0; y < 13; y++)
	{
		for (int x = 0; x < 6; x++)
		{
			//field[x][y] = 0;
			//altField[x][y] = 0;

			mainField[x][y].SetIsHide(true);
			//alterField[x][y].SetIsHide(true);
		}
	}

	for (int i = 0; i < 3; i++) AddPuyo();

	//デバッグ用
	for (int i = 0; i < 3; i++) {
		mainField[0][12 - i].SetColor(5);
		mainField[0][12 - i].SetIsHide(false);
	}
	/*
	score = 15000;
	mainField[0][12].SetIsHide(false);
	*/

}

void CField::Render(void) 
{
	if (isInv) invCnt++;

	//落下ぷよ描写
	for (int i = 0; i < 2; i++) {
		if (drop[i][1] > 0) CGraphicsUtilities::RenderFillCircle(125 + 50 * drop[i][0], 50 + 50 * (drop[i][1] - 1), 25, color[drop[i][2] - 1]);
	}
	//場面ぷよ描写
	for (int y = 0; y < 13; y++) {
		for (int x = 0; x < 6; x++) {
			//if (field[x][y] != 0 && y != 0) CGraphicsUtilities::RenderFillCircle(125 + 50 * x, 50 + 50 * (y - 1), 25, color[field[x][y] - 1]);
			if(invCnt > 5)
			{
				mainField[x][y].Render(x, y, true);
			}
			else
			{
				mainField[x][y].Render(x, y, false);
			}
		}
	}

	if (invCnt == 6) invCnt = 0;

	//１個先ぷよ予測
	for (int i = 0; i < 2; i++) CGraphicsUtilities::RenderFillCircle(450, 185 - 50 * i, 25, color[next[0][i] - 1]);
	
	//２個先ぷよ予測
	for (int i = 0; i < 2; i++) CGraphicsUtilities::RenderFillCircle(495, 235 - 30 * i, 15, color[next[1][i] - 1]);
	
	//ストック
	for (int i = 0; i < 2; i++) CGraphicsUtilities::RenderFillCircle(55, 165 - 30 * i, 15, color[stock[i] - 1]);

	//連鎖表記
	if (combo >= 2) CGraphicsUtilities::RenderString(250, 400, "%dChain!", combo);

	if (GetNowState() == eGameover) {
		CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2, g_pGraphics->GetTargetHeight() / 2, "GameOver");
		CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2, g_pGraphics->GetTargetHeight() / 2 + 25, "Press Enter");
	}
}

void CField::Release(void) 
{
	for (int i = 0; i < 5; i++) {
		gSound[i].Release();
	}
}

void CField::Right(void) {
	if (drop[0][0] != 5 && drop[1][0] != 5 &&
		//field[drop[0][0] + 1][drop[0][1]] == 0 && (drop[1][1] == -1 || field[drop[1][0] + 1][drop[1][1]] == 0))
		mainField[drop[0][0] + 1][drop[0][1]].GetIsHide() && mainField[drop[1][0] + 1][drop[1][1]].GetIsHide())
	{
		drop[0][0]++;
		drop[1][0]++;
		//gSound[0].Play();
	}
}

void CField::Left(void) {
	if (drop[0][0] != 0 && drop[1][0] != 0 &&
		//field[drop[0][0] - 1][drop[0][1]] == 0 && (drop[1][1] == -1 || field[drop[1][0] - 1][drop[1][1]] == 0))
		mainField[drop[0][0] - 1][drop[0][1]].GetIsHide() && mainField[drop[1][0] - 1][drop[1][1]].GetIsHide())
	{
		drop[0][0]--;
		drop[1][0]--;
		gSound[0].Play();
	}
}

void CField::Down(void) {
	if (drop[0][1] != 12 && drop[1][1] != 12 &&
		//field[drop[0][0]][drop[0][1] + 1] == 0 && field[drop[1][0]][drop[1][1] + 1] == 0)
		mainField[drop[0][0]][drop[0][1] + 1].GetIsHide() && mainField[drop[1][0]][drop[1][1] + 1].GetIsHide())
	{
		drop[0][1]++;
		drop[1][1]++;
	}
	else
	{
		isDropOnce = true;
		Set(drop[0][0], drop[0][1], drop[0][2] - 1);
		Set(drop[1][0], drop[1][1], drop[1][2] - 1);
		drop[0][1] = -1;
		drop[1][1] = -1;

		//gSound[2].Play();

		nowState = eFall;
	}
}

void CField::RRotate(void) {
	if (drop[0][0] == drop[1][0])
	{
		if (drop[0][1] > drop[1][1])
		{
			if (drop[1][0] + 1 < 6 && drop[1][1] + 1 < 13 &&
				//field[drop[1][0] + 1][drop[1][1] + 1] == 0)
				mainField[drop[1][0] + 1][drop[1][1] + 1].GetIsHide())
			{
				drop[1][0]++;
				drop[1][1]++;
				gSound[1].Play();
			}

		}
		else if (drop[1][0] - 1 >= 0 &&
			//field[drop[1][0] - 1][drop[1][1] - 1] == 0)
			mainField[drop[1][0]][drop[1][1] - 1].GetIsHide())
		{
			drop[1][0]--;
			drop[1][1]--;
			//gSound[1].Play();
		}
	}
	else if (drop[0][0] > drop[1][0])
	{
		if (drop[1][0] + 1 < 6 &&
			//(drop[1][1] - 1 == -1 || field[drop[1][0] + 1][drop[1][1] - 1] == 0))
			mainField[drop[1][0] + 1][drop[1][1] - 1].GetIsHide())
		{
			drop[1][0]++;
			drop[1][1]--;
			//gSound[1].Play();
		}

	}
	else if (drop[1][0] - 1 >= 0 && drop[1][1] + 1 < 13 &&
		//field[drop[1][0] - 1][drop[1][1] + 1] == 0)
		mainField[drop[1][0] - 1][drop[1][1] + 1].GetIsHide())
	{
		drop[1][0]--;
		drop[1][1]++;
		//gSound[1].Play();
	}
}

void CField::LRotate(void) {
	if (drop[0][0] == drop[1][0])
	{
		if (drop[0][1] > drop[1][1])
		{
			if (drop[1][0] - 1 >= 0 && drop[1][1] + 1 < 13 &&
				//field[drop[1][0] - 1][drop[1][1] + 1] == 0)
				mainField[drop[1][0] - 1][drop[1][1] + 1].GetIsHide())
			{
				drop[1][0]--;
				drop[1][1]++;
				//gSound[1].Play();
			}
		}
		else if (drop[1][0] + 1 < 6 &&
			//field[drop[1][0] + 1][drop[1][1] - 1] == 0)
			mainField[drop[1][0] + 1][drop[1][1] - 1].GetIsHide())
		{
			drop[1][0]++;
			drop[1][1]--;
			//gSound[1].Play();
		}
	}
	else if (drop[0][0] > drop[1][0])
	{
		if (drop[1][0] + 1 < 6 && drop[1][1] + 1 < 13 &&
			//field[drop[1][0] + 1][drop[1][1] + 1] == 0)
			mainField[drop[1][0] + 1][drop[1][1] + 1].GetIsHide())
		{
			drop[1][0]++;
			drop[1][1]++;
			//gSound[1].Play();
		}
	}
	else if (drop[1][0] - 1 >= 0 &&
		//(drop[1][1] - 1 == -1 || field[drop[1][0] - 1][drop[1][1] - 1] == 0))
		mainField[drop[1][0] - 1][drop[1][1] - 1].GetIsHide())
	{
		drop[1][0]--;
		drop[1][1]--;
		//gSound[1].Play();
	}
}

void CField::Stock(void)
{
	if (stock[0] == 0) 
	{
		stock[0] = next[0][0];
		stock[1] = next[0][1];

		next[0][0] = next[1][0];
		next[0][1] = next[1][1];

		next[1][0] = random.Random(1, 6);
		next[1][1] = random.Random(1, 6);

		//gSound[3].Play();
	}
	else
	{
		int a, b = 0;
		a = stock[0];
		b = stock[1];

		stock[0] = next[0][0];
		stock[1] = next[0][1];

		next[0][0] = a;
		next[0][1] = b;

		//gSound[3].Play();
	}
}

//着地時処理 引数trueで走査
bool CField::CheckDelete(bool isCheck) {
	bool didDel = false;
	//bool didCheck = false;

	//副配列へ転写
	for (int y = 0; y < 13; y++)
	{
		for (int x = 0; x < 6; x++)
		{
			if(!mainField[x][y].GetIsHide())
			{
				altField[x][y] = mainField[x][y].GetColor() + 1;
			}
			else 
			{
				altField[x][y] = 0;
			}
		}
	}

	for (int y = 12; y >= 0; y--)
	{
		for (int x = 0; x < 6; x++)
		{
			//didCheck = false;

			if (altField[x][y] != 0)
			{
				link = 0;
				//didCheck = true;

				LinkManipulation(x, y, false);
				if (link >= 4)
				{
					if (isCheck) return true;
					
					else
					{
						if (isFirst) combo++;
						isFirst = false;
						didDel = true;

						LinkManipulation(x, y, true);
						//gSound[4].Play();
					}
				}
			}

			//if (!didCheck) break;
		}

		//if (!didCheck) break;
	}

	if (didDel) 
	{
		if (combo >= 2) stopCnt = 0.7f;
		else stopCnt = 1.0f;

		isInv = true;

		nowState = eBanish;
	}
	else if (!isCheck)
	//if (!didDel && !isCheck)
	{
		nowState = eFall;
	}

	return false;
}

//連鎖処理　第三引数で主配列副配列の切り替え
void CField::LinkManipulation(int x,int y,bool isMain) {
	if (isMain)
	{
		//if (field[x][y] != 0 && field[x][y] != 6)
		if(!mainField[x][y].GetIsHide() && mainField[x][y].GetColor() != 5)
		{
			//int c = field[x][y];
			//field[x][y] = 0;
			int c = mainField[x][y].GetColor();
			//mainField[x][y].SetIsHide(true);
			mainField[x][y].SetIsErasing(true);
			
			//score += combo * 100;

			//ObstacleDelete(x, y);

			/*if (x - 1 >= 0 && field[x - 1][y] == c) LinkManipulation(x - 1, y, b);
			if (x + 1 < 6 && field[x + 1][y] == c) LinkManipulation(x + 1, y, b);
			if (y - 1 >= 0 && field[x][y - 1] == c) LinkManipulation(x, y - 1, b);
			if (y + 1 < 13 && field[x][y + 1] == c) LinkManipulation(x, y + 1, b);*/


			bool b = true;
			if (x - 1 >= 0 && mainField[x - 1][y].GetColor() == c && !mainField[x - 1][y].GetIsHide() && !mainField[x - 1][y].GetIsErasing()) LinkManipulation(x - 1, y, b);
			if (x + 1 < 6 && mainField[x + 1][y].GetColor() == c && !mainField[x + 1][y].GetIsHide() && !mainField[x + 1][y].GetIsErasing()) LinkManipulation(x + 1, y, b);
			if (y - 1 >= 0 && mainField[x][y - 1].GetColor() == c && !mainField[x][y - 1].GetIsHide() && !mainField[x][y - 1].GetIsErasing()) LinkManipulation(x, y - 1, b);
			if (y + 1 < 13 && mainField[x][y + 1].GetColor() == c && !mainField[x][y + 1].GetIsHide() && !mainField[x][y + 1].GetIsErasing()) LinkManipulation(x, y + 1, b);
		}
	}
	else if (altField[x][y] != 0 && altField[x][y] != 6)
	{
		int c = altField[x][y];
		altField[x][y] = 0;
		link++;

		bool b = false;
		if (x - 1 >= 0 && altField[x - 1][y] == c) LinkManipulation(x - 1, y, b);
		if (x + 1 < 6 && altField[x + 1][y] == c) LinkManipulation(x + 1, y, b);
		if (y - 1 >= 0 && altField[x][y - 1] == c) LinkManipulation(x, y - 1, b);
		if (y + 1 < 13 && altField[x][y + 1] == c) LinkManipulation(x, y + 1, b);
	}
}

void CField::ObstacleDelete(int x, int y) {
	//if (x - 1 >= 0 && field[x - 1][y] == 6) 
	if(x - 1 >= 0 && mainField[x - 1][y].GetColor() == 5)
	{
		//field[x - 1][y] = 0;
		mainField[x - 1][y].SetIsHide(true);
		score += 50;
	}

	//if (x + 1 < 6 && field[x + 1][y] == 6) 
	if (x + 1 < 6 && mainField[x + 1][y].GetColor() == 5)
	{
		//field[x + 1][y] = 0;
		mainField[x + 1][y].SetIsHide(true);
		score += 50;
	}

	//if (y - 1 >= 0 && field[x][y - 1] == 6) 
	if (y - 1 >= 0 && mainField[x][y - 1].GetColor() == 5)
	{
		//field[x][y - 1] = 0;
		mainField[x][y - 1].SetIsHide(true);
		score += 50;
	}

	//if (y + 1 < 13 && field[x][y + 1] == 6) 
	if (y + 1 < 13 && mainField[x][y + 1].GetColor() == 5)
	{
		//field[x][y + 1] = 0;
		mainField[x][y + 1].SetIsHide(true);
		score += 50;
	}
}

//空洞処理 成功時true
void CField::CheckHollow(void) {
	isFirst = true;

	bool falled = false;
	bool isZero = true;
	nowState = eFall;

	for (int x = 0; x < 6; x++)
	{
		falled = false;

		for (int y = 12; y >= 0; y--)
		{
			if (mainField[x][y].GetIsHide())
			{
				for (int i = y - 1; i >= 0; i--) 
				{
					if (!mainField[x][i].GetIsHide()) {
						falled = true;

						mainField[x][i + 1].SetColor(mainField[x][i].GetColor());
						mainField[x][i + 1].SetIsHide(false);
						mainField[x][i].SetIsHide(true);
					}


					//if (CheckBottom(x, i + 1)) gSound[2].Play();
				}
			}
			if (falled)break;
		}

		if (falled)isZero = false;
	}

	if (isZero && CheckDelete(true))
	{
		nowState = eDelete;
	}
	else if (isZero) 
	{
		if (combo >= 2) stopCnt = 0.4f;
		else stopCnt = 0.05f;

		nowState = eSet;
	}
	else stopCnt = 0.1f;

}

bool CField::CheckBottom(int x,int y){
	for (; y < 13; y++) if (mainField[x][y].GetIsHide()) return false;
	return true;
}

void CField::Set(int x,int y,int c) {
	mainField[x][y].SetColor(c);
	mainField[x][y].SetIsHide(false);
}

//キューで予測ぷよを落下ぷよに押し出す処理
//連鎖数もここで初期化する
void CField::AddPuyo(void) 
{
	if (!CheckGameOver()) {
		for (int i = 0; i < 2; i++)
		{
			drop[i][0] = 2;
			drop[i][1] = 1 + i * - 1;
			drop[i][2] = next[0][i];

			next[0][i] = next[1][i];
			next[1][i] = random.Random(1, 6);
		}

		combo = 0;
		//deltaTime = 0;
		SpeedCheck();

		nowState = eDrop;
	}
	else nowState = eGameover;
}

//スコアが一定数値以上なら落下速度、おじゃまぷよ生成周期、生成数を加速させる
void CField::SpeedCheck(void)
{
	if (floor(score / accelNum) != 0 && score <= (accelNum * 10)) {
		dropTime = 2.0f - (floor(score / accelNum) * 0.2f);
	}
	else if (score >= (accelNum * 10)) {
		dropTime = 0.17f;
	}

	if (floor(score / (accelNum * 6)) != 0 && score <= ((accelNum * 6) * 4)) {
		obstacleAmount = floor(score / (accelNum * 6)) + 2;
	}
	else if (score > ((accelNum * 6) * 4)) obstacleAmount = 6;

	if (floor(score / (accelNum * 4) != 0) && score <= ((accelNum * 4) * 15)) {
		obstacleTime = 30.0f - (floor(score / (accelNum * 4)) * 0.5f);
	}
	else if (score > ((accelNum * 4) * 20)) obstacleTime = 20.0f;
}

bool CField::CheckStop(void) 
{
	if (stopCnt > 0 && stopCnt > waitTime) {
		return true;
	}

	return false;
}

void CField::Wait(void) {
	waitTime += CUtilities::GetFrameSecond(); 
	
	if (stopCnt <= waitTime) 
	{
		stopCnt = 0;
		waitTime = 0;
	}
}

void CField::SetObstacle(void) {
	combo = 0;

	for (int i = 0; i < 6; i++) {
		int j = rand() % 6;
		int t = shuffle[i];
		shuffle[i] = shuffle[j];
		shuffle[j] = t;
	}

	for (int i = 0; i < 6 && obstacle > 0; i++) {
		mainField[shuffle[i]][0].SetColor(5);
		mainField[shuffle[i]][0].SetIsHide(false);
		obstacle--;
	}

	if (obstacle > 0) {
		CheckHollow();
		nowState = eSet;
	}
	else nowState = eFall;
}

void CField::Banish()
{
	for (int y = 0; y < 13; y++)
	{
		for (int x = 0; x < 6; x++)
		{
			if (mainField[x][y].GetIsErasing())
			{
				mainField[x][y].SetIsErasing(false);
				mainField[x][y].SetIsHide(true);
				score += combo * 100;

				ObstacleDelete(x, y);
			}
		}
	}

	isInv = false;
	invCnt = 0;

	nowState = eFall;
}
