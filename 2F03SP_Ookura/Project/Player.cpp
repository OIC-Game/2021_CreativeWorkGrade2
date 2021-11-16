#include	"Player.h"
#include"Game.h"
/**
 * �R���X�g���N�^
 *
 */
CPlayer::CPlayer() :
m_Texture() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_bDead(false) ,
m_ShotTexture() ,
m_ShotArray() ,
m_ShotWait() {
}

/**
 * �f�X�g���N�^
 *
 */
CPlayer::~CPlayer(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CPlayer::Load(void){
	//�e�N�X�`���̓ǂݍ���
	if(!m_Texture.Load("Player.png"))
	{
		return false;
	}
	//�e�̃e�N�X�`���i�ǂݍ��݂͈�ł��ׂĂ̒e�Ƀ|�C���^��ݒ�j
	if(!m_ShotTexture.Load("P_missile.png"))
	{
		return false;
	}
	for(int i = 0;i < PLAYERSHOT_COUNT;i++)
	{
		m_ShotArray[i].SetTexture(&m_ShotTexture);
	}
	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * �v���C���[�̈ʒu�ȂǏ�Ԃ��������������Ƃ��Ɏ��s����B
 */
void CPlayer::Initialize(void){
	m_PosX = g_pGraphics->GetTargetWidth() * 0.5f - m_Texture.GetWidth() * 0.5f;
	m_PosY = g_pGraphics->GetTargetHeight() - m_Texture.GetHeight();
	m_bDead = false;
	for(int i = 0;i < PLAYERSHOT_COUNT;i++)
	{
		m_ShotArray[i].Initialize();
	}
}
//void CPlayer::GetGamePadCount(void) {
	

/**
 * �X�V
 *
 */
void CPlayer::Update(void) {
	if (m_bDead)
	{
		return;
	}
	//�L�[�{�[�h�ł̈ړ�
	if(g_pInput->IsKeyHold(MOFKEY_A))
	{
		m_PosX -= PLAYER_SPEED;
	}
	else if(g_pInput->IsKeyHold(MOFKEY_D))
	{
		m_PosX += PLAYER_SPEED;
	}
	if(g_pInput->IsKeyHold(MOFKEY_W))
	{
		m_PosY -= PLAYER_SPEED;
	}
	else if(g_pInput->IsKeyHold(MOFKEY_S))
	{
		m_PosY += PLAYER_SPEED;
	}
	//void CPlayer::GetGamePadCount(void) {
	if (g_pInput->GetGamePadCount())
	{
		LPGamePad pPad = g_pInput->GetGamePad(0);
		pPad->GetPadState();

		if (pPad != nullptr)
		{
			if (m_ShotWait <= 0) {
				if (pPad->IsKeyHold(2))
				{
					for (int i = 0; i < PLAYERSHOT_COUNT; i++)
					{
						if (m_ShotArray[i].GetShow())
						{
							continue;
						}
						m_ShotWait = PLAYERSHOT_WAIT;
						m_ShotArray[i].Fire(m_PosX + m_Texture.GetWidth() * 0.5f, m_PosY);
						break;
					}
				}
			}
		}
		else
		{
			m_ShotWait--;
		}
		//�e�̍X�V
		for (int i = 0; i < PLAYERSHOT_COUNT; i++)
		{
			m_ShotArray[i].Update();
		}

		m_PosX += pPad->GetStickHorizontal() * 10;
		m_PosY += pPad->GetStickVertical() * 10;

	}
	
	//�e�̔���
	if(m_ShotWait <= 0)
	{
		if(g_pInput->IsKeyHold(MOFKEY_RETURN))
		{
			for(int i = 0;i < PLAYERSHOT_COUNT;i++)
			{
				if(m_ShotArray[i].GetShow())
				{
					continue;
				}
				m_ShotWait = PLAYERSHOT_WAIT;
				m_ShotArray[i].Fire(m_PosX + m_Texture.GetWidth() * 0.5f,m_PosY);
				break;
			}
		}
	}
	else
	{
		m_ShotWait--;
	}
	//�e�̍X�V
	for(int i = 0;i < PLAYERSHOT_COUNT;i++)
	{
		m_ShotArray[i].Update();
	}
	if (m_PosX + m_Texture.GetWidth() > g_pGraphics->GetTargetWidth())
	{
		m_PosX = 1/*g_pGraphics->GetTargetWidth() - m_Texture.GetWidth()*/;
	}
	else if (m_PosX < 0)
	{
		m_PosX = g_pGraphics->GetTargetWidth() - m_Texture.GetWidth();
	}
}

/**
 * �����蔻��
 * �����̓G�ɑ΂��ċ�`���m�̓����蔻������s����B
 * �������Ă����ꍇ�̓v���C���[�̏�Ԃ�ύX����
 *
 * ����
 * [in]			ene				������s���G
 *
 * �߂�l
 * �������Ă���ꍇ��true�A�������Ă��Ȃ����false��Ԃ�
 */
bool CPlayer::Collision(CEnemy& ene){
	CRectangle prec = GetRect();
	//�G�̒e�Ǝ����̔���
	for(int i = 0;i < ENEMYSHOT_COUNT;i++)
	{
		if(!ene.GetShot(i).GetShow())
		{
			continue;
		}
		CRectangle srec = ene.GetShot(i).GetRect();
		if(srec.CollisionRect(prec))
		{
			m_bDead = true;
			ene.GetShot(i).SetShow(false);
			break;
		}
	}
	if(!ene.GetShow())
	{
		return false;
	}
	CRectangle erec = ene.GetRect();
	if(prec.CollisionRect(erec))
	{
		m_bDead = true;
	}
	//�e�Ƃ̔���
	for(int i = 0;i < PLAYERSHOT_COUNT;i++)
	{
		if(!m_ShotArray[i].GetShow())
		{
			continue;
		}
		CRectangle srec = m_ShotArray[i].GetRect();
		if(srec.CollisionRect(erec))
		{
			ene.Damage(1);
			m_ShotArray[i].SetShow(false);
			break;
		}
	}
	return false;
}

/**
 * �`��
 *
 */
void CPlayer::Render(void){
	if(m_bDead)
	{
		return;
	}
	//�e�N�X�`���̕`��
	m_Texture.Render(m_PosX,m_PosY);
	//�e�̕`��
	for(int i = 0;i < PLAYERSHOT_COUNT;i++)
	{
		m_ShotArray[i].Render();
	}
}

/**
 * �f�o�b�O�`��
 *
 */
void CPlayer::RenderDebug(void){
	//�ʒu�̕`��
	CGraphicsUtilities::RenderString(10,40,MOF_XRGB(0,0,0),"�v���C���[�ʒu X : %.0f , Y : %.0f",m_PosX,m_PosY);
	//�����蔻��̕\��
	CGraphicsUtilities::RenderRect(m_PosX,m_PosY,m_PosX + m_Texture.GetWidth(),m_PosY + m_Texture.GetHeight(),MOF_XRGB(0,255,0));
	//�e�̕`��
	for(int i = 0;i < PLAYERSHOT_COUNT;i++)
	{
		m_ShotArray[i].RenderDebug();
	}
}

/**
 * ���
 *
 */
void CPlayer::Release(void){
	m_Texture.Release();
	m_ShotTexture.Release();
}