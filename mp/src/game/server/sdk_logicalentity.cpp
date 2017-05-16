#include "cbase.h"
class CTestLogicalEntity : public CLogicalEntity
{
public:
	DECLARE_CLASS(CTestLogicalEntity, CLogicalEntity);
	DECLARE_DATADESC();

	//Constructor 
	CTestLogicalEntity()
	{
		m_nCounter = 0;
	}

	//Input Function
	void InputTick(inputdata_t &inputData);
private:
	int m_nThreshold;	//Count at which to fire output
	int m_nCounter;		//Internal Counter

	COutputEvent m_OnThreshold; //Output event when counter reaches threshold
};

LINK_ENTITY_TO_CLASS(test_logical_entity, CTestLogicalEntity);

//Start of Data description
BEGIN_DATADESC(CTestLogicalEntity)

	//Save/Load
	DEFINE_FIELD(m_nCounter, FIELD_INTEGER),

	//links to hammer keyvalue
	DEFINE_KEYFIELD(m_nThreshold, FIELD_INTEGER, "threshold"),

	//links input name from hammer to input member function
	DEFINE_INPUTFUNC(FIELD_VOID, "Tick", InputTick),

	//Links output member variable to output name used by hammer
	DEFINE_OUTPUT(m_OnThreshold, "OnThreshold"),

END_DATADESC()

void CTestLogicalEntity::InputTick(inputdata_t &inputData)
{
	//Increment Counter
	m_nCounter++;

	//Met threshold value?
	if (m_nCounter >= m_nThreshold)
	{
		//fire output event
		m_OnThreshold.FireOutput(inputData.pActivator, this);

		//reset counter
		m_nCounter = 0;
	}
}