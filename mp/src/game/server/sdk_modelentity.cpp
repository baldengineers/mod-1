#include "cbase.h"

class CMyModelEntity : public CBaseAnimating
{
public:
	DECLARE_CLASS(CMyModelEntity, CBaseAnimating);
	DECLARE_DATADESC();

	CMyModelEntity()
	{
		m_bActive = false;
	}

	void Spawn(void);
	void Precache(void);

	void MoveThink(void);

	//Input func
	void InputToggle(inputdata_t &inputData);

private:
	bool m_bActive;
	float m_flNextChangeTime;
};

LINK_ENTITY_TO_CLASS(my_model_entity, CMyModelEntity);

BEGIN_DATADESC(CMyModelEntity)

	DEFINE_FIELD(m_bActive, FIELD_BOOLEAN),
	DEFINE_FIELD(m_flNextChangeTime, FIELD_TIME),

	DEFINE_INPUTFUNC(FIELD_VOID, "Toggle", InputToggle),

	DEFINE_THINKFUNC(MoveThink),

END_DATADESC()

#define ENTITY_MODEL "models/alyx.mdl"

void CMyModelEntity::Precache(void)
{
	PrecacheModel(ENTITY_MODEL);
	BaseClass::Precache();
}

void CMyModelEntity::Spawn(void)
{
	Precache();

	SetModel(ENTITY_MODEL);
	SetSolid(SOLID_BBOX);
	UTIL_SetSize(this, -Vector(20, 20, 20), Vector(20, 20, 20));

	SetSequence(LookupSequence("cheer1"));
	SetPlaybackRate(2.0f);
	UseClientSideAnimation();
}

void CMyModelEntity::MoveThink(void)
{
	if (m_flNextChangeTime < gpGlobals->curtime)
	{
		//randomly take new dir and spd
		Vector vecNewVelocity = RandomVector(-64.0f, 64.0f);
		SetAbsVelocity(vecNewVelocity);

		//randomly change again within 1-3 secs
		m_flNextChangeTime = gpGlobals->curtime + random->RandomFloat(1.0f, 3.0f);
	}
	
	//face where heading
	Vector velFacing = GetAbsVelocity();
	QAngle angFacing;
	VectorAngles(velFacing, angFacing);
	SetAbsAngles(angFacing);

	//think at 20hz
	SetNextThink(gpGlobals->curtime + 0.05f);
}

void CMyModelEntity::InputToggle(inputdata_t &inputData)
{
	//toggle active
	if (!m_bActive)
	{
		//starting thinking
		SetThink(&CMyModelEntity::MoveThink);

		SetNextThink(gpGlobals->curtime + 0.05f);

		//start moving
		SetMoveType(MOVETYPE_FLY);

		//force movethink() to choose new speed and dir immediately
		m_flNextChangeTime = gpGlobals->curtime;

		//update m_bActive to new state
		m_bActive = true;
	}
	else
	{
		//stop thinking
		SetThink(NULL);

		//stop moving
		SetAbsVelocity(vec3_origin);
		SetMoveType(MOVETYPE_NONE);

		m_bActive = false;
	}

}

CON_COMMAND(create_sdk_modelentity, "Creates an instance of the sdk model entity in front of the player.")
{
	Vector vecForward;
	CBasePlayer *pPlayer = UTIL_GetCommandClient();
	if (!pPlayer)
	{
		Warning("Could not determine calling player!\n");
		return;
	}

	AngleVectors(pPlayer->EyeAngles(), &vecForward);
	CBaseEntity *pEnt = CreateEntityByName("my_model_entity");
	if (pEnt)
	{
		Vector vecOrigin = pPlayer->GetAbsOrigin() + vecForward * 256 + Vector(0, 0, 64);
		QAngle vecAngles(0, pPlayer->GetAbsAngles().y - 90, 0);
		pEnt->SetAbsOrigin(vecOrigin);
		pEnt->SetAbsAngles(vecAngles);
		DispatchSpawn(pEnt);
	}
}