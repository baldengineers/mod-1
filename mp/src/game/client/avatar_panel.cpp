#include "cbase.h"
#include "Iavatar_panel.h"
#include "vgui_avatarimage.h"
using namespace vgui;
#include <vgui/IVGui.h>
#include <vgui_controls/Frame.h>

class CAvatarPanel : public vgui::Frame
{
	DECLARE_CLASS_SIMPLE(CAvatarPanel, vgui::Frame);

	CAvatarPanel(vgui::VPANEL parent);
	~CAvatarPanel(){};
protected:
	virtual void OnTick();
	virtual void OnCommand(const char* pcCommand);
private:
	//etc
};

CAvatarPanel::CAvatarPanel(vgui::VPANEL parent) : BaseClass(NULL, "AvatarPanel")
{
	SetParent(parent);

	SetKeyBoardInputEnabled(false);
	SetMouseInputEnabled(false);

	SetProportional(false);
	SetTitleBarVisible(false);
	SetMinimizeButtonVisible(false);
	SetMaximizeButtonVisible(false);
	SetCloseButtonVisible(false);
	SetSizeable(false);
	SetMoveable(false);
	SetVisible(true);

	SetScheme(vgui::scheme()->LoadSchemeFromFile("resource/SourceScheme.res", "SourceScheme"));

	LoadControlSettings("resource/UI/avatarpanel.res");
	vgui::ivgui()->AddTickSignal(GetVPanel(), 100);
	DevMsg("Avatar panel created.\n");

	
}