#include	"EnemyShot.h"

/**
 * �R���X�g���N�^
 *
 */
CEnemyShot::CEnemyShot() :
	m_pTexture(NULL),
	enemyShot_Position(0.0f,0.0f),
	enemyShot_Speed(0.0f,0.0f),
	m_bShow(false),
	tmpEnemy_Reverse(false),
	enemyShot_AddSpeed(false),
	enemyShot_Type(0),
	enemyShot_FireBound(false)
{
}

/**
 * �f�X�g���N�^
 *
 */
CEnemyShot::~CEnemyShot() {
}

/**
 * ������
 */
void CEnemyShot::Initialize(int type) {
	enemyShot_Position = Vector2(0, 0);
	enemyShot_Speed = Vector2(0, 0);
	m_bShow = false;
	tmpEnemy_Reverse = false;
	enemyShot_Type = type;
	enemyShot_FireBound = false;
	switch (enemyShot_Type)
	{
		case ENEMYSHOT_BONE:
		{
			SpriteAnimationCreate anime[] = {
			{
				"��]",
				0,0,
				32,32,
				TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}},
			},
			};
			enemyShot_Motion.Create(anime, 1);
			break;
		}
		case ENEMYSHOT_FIRE:
		{
			SpriteAnimationCreate anime[] = {
			{
				"��]",
				0,0,
				16,16,
				TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}},
			},
			};
			enemyShot_Motion.Create(anime, 1);
			break;
		}
		case ENEMYSHOT_KURIBO:
		{
			SpriteAnimationCreate anime[] = {
			{
				"�ړ�",
				0,0,
				32,32,
				TRUE,{{5,0,0},{5,1,0},{5,2,0}},
			},
			};
			enemyShot_Motion.Create(anime, 1);
			break;
		}
		case ENEMYSHOT_MUSH:
		{
			SpriteAnimationCreate anime[] = {
			{
				"�ړ�",
				0,0,
				32,32,
				TRUE,{{5,0,0}},
			},
			};
			enemyShot_Motion.Create(anime, 1);
			break;
		}

		default:
			break;
	}
	
	enemyShot_AddSpeed = false;
}
/**
 * ����
 */
void CEnemyShot::Fire(float px, float py,float sx,float sy,bool Reverse) {
	enemyShot_Position.x = px;
	enemyShot_Position.y = py;
	tmpEnemy_Reverse = Reverse;
	switch (enemyShot_Type)
	{
	case ENEMYSHOT_BONE:
	{
		if (!enemyShot_AddSpeed)
		{
			enemyShot_AddSpeed = true;
		}
		if (tmpEnemy_Reverse)
		{
			enemyShot_Speed.x = -sx;
		}
		else
		{
			enemyShot_Speed.x = sx;
		}
		enemyShot_Speed.y = -sy;

		m_bShow = true;
		
		break;
	}
	case ENEMYSHOT_FIRE:
	{
		if (tmpEnemy_Reverse)
		{
			enemyShot_Speed.x = -sx;
		}
		else
		{
			enemyShot_Speed.x = sx;
		}
		enemyShot_Speed.y = sy;

		m_bShow = true;
	}
	default:
		break;
	}
	if (enemyShot_Motion.GetMotionNo() != 0)
		enemyShot_Motion.ChangeMotion(0);


	
}

/**
 * �X�V
 *
 */
void CEnemyShot::Update(void) {
	//��\��
	if (!m_bShow)
	{
		if(enemyShot_AddSpeed)
		enemyShot_AddSpeed = false;
		return;
	}
	//�A�j���[�V�����̍X�V
	enemyShot_Motion.AddTimer(CUtilities::GetFrameSecond());
	enemyShot_RectTexture = enemyShot_Motion.GetSrcRect();
	
	//�d�͏���
	enemyShot_Speed.y += ENEMY_GRAVITY;
	if (enemyShot_Speed.y >= 20.0f)
	{
		enemyShot_Speed.y = 20.0f;
	}
	//���x�𗘗p�����ړ�
	enemyShot_Position += enemyShot_Speed;
	//��ʊO�ŏ���
	if (enemyShot_Position.y < 0 || enemyShot_Position.y > 900)
	{
		m_bShow = false;
	}
}

/**
 * �`��
 *
 */
void CEnemyShot::Render(float wx, float wy) {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	CRectangle dr = enemyShot_RectTexture;
	if (tmpEnemy_Reverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//�e�N�X�`���̕`��
	m_pTexture->Render(enemyShot_Position.x - wx, enemyShot_Position.y - wy,dr);
}

/**
 * �f�o�b�O�`��
 *
 */
void CEnemyShot::RenderDebug(float wx, float wy) {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx,hr.Top - wy,hr.Right - wx,hr.Bottom - wy, MOF_XRGB(0, 255, 0));
	CGraphicsUtilities::RenderString(300, 600, "�V���b�g��%f", enemyShot_Speed);
}

void CEnemyShot::Release(void)
{
	enemyShot_Motion.Release();
}

