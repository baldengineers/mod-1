//for playing menu music
#include "cbase.h"
using namespace vgui;
#include <vgui/ISurface.h>
#include "ISoundPanel.h"
#include <vgui/IVGui.h>
#include <vgui_controls/Panel.h>
#include <vgui_controls/Frame.h>

class CSoundPanel : public vgui::Frame
{
	DECLARE_CLASS_SIMPLE(CSoundPanel, vgui::Frame);

	CSoundPanel(vgui::VPANEL parent); 	
	~CSoundPanel(){};				

protected:
	virtual void OnTick();
	virtual void OnCommand(const char* pcCommand);

private:
	

};

CSoundPanel::CSoundPanel(vgui::VPANEL parent)
	: BaseClass(NULL, "SoundPanel")
{
	SetParent(parent);

	SetKeyBoardInputEnabled(false);
	SetMouseInputEnabled(false);

	SetProportional(false);
	SetTitleBarVisible(true);
	SetMinimizeButtonVisible(false);
	SetMaximizeButtonVisible(false);
	SetCloseButtonVisible(false);
	SetSizeable(false);
	SetMoveable(false);
	SetVisible(false);


	SetScheme(vgui::scheme()->LoadSchemeFromFile("resource/SourceScheme.res", "SourceScheme"));

	LoadControlSettings("resource/UI/soundpanel.res");

	vgui::ivgui()->AddTickSignal(GetVPanel(), 100);

	DevMsg("MusicPanel has been constructed\n");

	vgui::surface()->PlaySound("ui/gamestartup.mp3");
}
class CSoundPanelInterface : public ISoundPanel
{
private:
	CSoundPanel *SoundPanel;
public:
	CSoundPanelInterface()
	{
		SoundPanel = NULL;
	}
	void Create(vgui::VPANEL parent)
	{
		SoundPanel = new CSoundPanel(parent);
		vgui::surface()->PlaySound("ui/gamestartup.mp3");
	}
	void Destroy()
	{
		if (SoundPanel)
		{
			SoundPanel->SetParent((vgui::Panel *)NULL);
			delete SoundPanel;
		}
	}
	void Activate(void)
	{
		if (SoundPanel)
		{
			SoundPanel->Activate();
		}
	}
};
static CSoundPanelInterface g_SoundPanel;
ISoundPanel* soundpanel = (ISoundPanel*)&g_SoundPanel;
CON_COMMAND(ToggleMenuSound, "Toggles soundPanel on or off"){
	vgui::surface()->PlaySound("ui/gamestartup.mp3");
}
void CSoundPanel::OnTick()
{
	BaseClass::OnTick();

}

void CSoundPanel::OnCommand(const char* pcCommand)
{
	BaseClass::OnCommand(pcCommand);
}