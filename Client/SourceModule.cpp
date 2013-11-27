#include "SourceModule.hpp"
#include "SFMLAnimation.hpp"
#include "SFMLImage.hpp"
#include "SFMLText.hpp"

SourceModule::SourceModule()
{

}

SourceModule::~SourceModule()
{

}

void	SourceModule::initialize()
{
	// Put all animations objects
	this->_images.add(SFMLAnimation::EXPLOSION1, new SFMLAnimation("Assets/Animation/explosion1.png", 64, 64, 0.02f));
	this->_images.add(SFMLAnimation::EXPLOSION2, new SFMLAnimation("Assets/Animation/explosion2.png", 256, 128, 0.035f));
	this->_images.add(SFMLAnimation::EXPLOSION3, new SFMLAnimation("Assets/Animation/explosion3.png", 64, 90, 0.03f));
	this->_images.add(SFMLAnimation::ASTEROID1, new SFMLAnimation("Assets/Animation/asteroid1.png", 64, 64, 0.05f));
	this->_images.add(SFMLAnimation::ASTEROID2, new SFMLAnimation("Assets/Animation/asteroid2.png", 64, 64, 0.05f));
	this->_images.add(SFMLAnimation::LOADING, new SFMLAnimation("Assets/Animation/loading.png", 46, 46, 0.05f));

	this->_images.add(SFMLAnimation::STARSHIP2, new SFMLAnimation("Assets/Game/Starship/starship2.png", 32, 28, 0.15f));
	this->_images.add(SFMLAnimation::STARSHIP3, new SFMLAnimation("Assets/Game/Starship/starship3.png", 63, 44, 0.15f));
	this->_images.add(SFMLAnimation::STARSHIP4, new SFMLAnimation("Assets/Game/Starship/starship4.png", 49, 48, 0.05f));
	// Put all images objects
	this->_images.add(SFMLImage::BACKGROUND, new SFMLImage("Assets/Menu/background.png"));
	this->_images.add(SFMLImage::TEXTBOX, new SFMLImage("Assets/Menu/TextBox.png"));
	this->_images.add(SFMLImage::TEXTBOX_HOVER, new SFMLImage("Assets/Menu/TextBoxHover.png"));
	this->_images.add(SFMLImage::TEXTBOX_SELECTED, new SFMLImage("Assets/Menu/TextBox.png"));
	this->_images.add(SFMLImage::BUTTON_BACK, new SFMLImage("Assets/Menu/buttonBackNormal.png"));
	this->_images.add(SFMLImage::BUTTON_HOVER_BACK, new SFMLImage("Assets/Menu/buttonBackHover.png"));
	this->_images.add(SFMLImage::BUTTON_CLICKED_BACK, new SFMLImage("Assets/Menu/buttonBackClicked.png"));
	this->_images.add(SFMLImage::BUTTON_QUIT, new SFMLImage("Assets/Menu/buttonQuitNormal.png"));
	this->_images.add(SFMLImage::BUTTON_HOVER_QUIT, new SFMLImage("Assets/Menu/buttonQuitHover.png"));
	this->_images.add(SFMLImage::BUTTON_CLICKED_QUIT, new SFMLImage("Assets/Menu/buttonQuitClicked.png"));
	this->_images.add(SFMLImage::BUTTON_LOGIN, new SFMLImage("Assets/Menu/buttonLoginNormal.png"));
	this->_images.add(SFMLImage::BUTTON_HOVER_LOGIN, new SFMLImage("Assets/Menu/buttonLoginHover.png"));
	this->_images.add(SFMLImage::BUTTON_CLICKED_LOGIN, new SFMLImage("Assets/Menu/buttonLoginClicked.png"));
	this->_images.add(SFMLImage::BUTTON_SETTINGS, new SFMLImage("Assets/Menu/buttonSettingsNormal.png"));
	this->_images.add(SFMLImage::BUTTON_HOVER_SETTINGS, new SFMLImage("Assets/Menu/buttonSettingsHover.png"));
	this->_images.add(SFMLImage::BUTTON_CLICKED_SETTINGS, new SFMLImage("Assets/Menu/buttonSettingsClicked.png"));
	this->_images.add(SFMLImage::BUTTON_CREATE, new SFMLImage("Assets/Menu/buttonCreateNormal.png"));
	this->_images.add(SFMLImage::BUTTON_HOVER_CREATE, new SFMLImage("Assets/Menu/buttonCreateHover.png"));
	this->_images.add(SFMLImage::BUTTON_CLICKED_CREATE, new SFMLImage("Assets/Menu/buttonCreateClicked.png"));
	this->_images.add(SFMLImage::BUTTON_JOIN, new SFMLImage("Assets/Menu/buttonJoinNormal.png"));
	this->_images.add(SFMLImage::BUTTON_HOVER_JOIN, new SFMLImage("Assets/Menu/buttonJoinHover.png"));
	this->_images.add(SFMLImage::BUTTON_CLICKED_JOIN, new SFMLImage("Assets/Menu/buttonJoinClicked.png"));
	this->_images.add(SFMLImage::BUTTON_OK, new SFMLImage("Assets/Menu/buttonOkNormal.png"));
	this->_images.add(SFMLImage::BUTTON_HOVER_OK, new SFMLImage("Assets/Menu/buttonOkHover.png"));
	this->_images.add(SFMLImage::BUTTON_CLICKED_OK, new SFMLImage("Assets/Menu/buttonOkClicked.png"));
	this->_images.add(SFMLImage::BUTTON_SELECT, new SFMLImage("Assets/Menu/buttonSelectNormal.png"));
	this->_images.add(SFMLImage::BUTTON_HOVER_SELECT, new SFMLImage("Assets/Menu/buttonSelectHover.png"));
	this->_images.add(SFMLImage::BUTTON_CLICKED_SELECT, new SFMLImage("Assets/Menu/buttonSelectClicked.png"));
	this->_images.add(SFMLImage::BUTTON_REFRESH, new SFMLImage("Assets/Menu/buttonRefreshNormal.png"));
	this->_images.add(SFMLImage::BUTTON_HOVER_REFRESH, new SFMLImage("Assets/Menu/buttonRefreshHover.png"));
	this->_images.add(SFMLImage::BUTTON_CLICKED_REFRESH, new SFMLImage("Assets/Menu/buttonRefreshClicked.png"));
	this->_images.add(SFMLImage::BUTTON_GO, new SFMLImage("Assets/Menu/buttonGoNormal.png"));
	this->_images.add(SFMLImage::BUTTON_HOVER_GO, new SFMLImage("Assets/Menu/buttonGoHover.png"));
	this->_images.add(SFMLImage::BUTTON_CLICKED_GO, new SFMLImage("Assets/Menu/buttonGoClicked.png"));
	this->_images.add(SFMLImage::BUTTON_NEXT, new SFMLImage("Assets/Menu/ArrowRightNormal.png"));
	this->_images.add(SFMLImage::BUTTON_HOVER_NEXT, new SFMLImage("Assets/Menu/ArrowRightHover.png"));
	this->_images.add(SFMLImage::BUTTON_CLICKED_NEXT, new SFMLImage("Assets/Menu/ArrowRightClicked.png"));
	this->_images.add(SFMLImage::BUTTON_PREV, new SFMLImage("Assets/Menu/ArrowLeftNormal.png"));
	this->_images.add(SFMLImage::BUTTON_HOVER_PREV, new SFMLImage("Assets/Menu/ArrowLeftHover.png"));
	this->_images.add(SFMLImage::BUTTON_CLICKED_PREV, new SFMLImage("Assets/Menu/ArrowLeftClicked.png"));
	this->_images.add(SFMLImage::BUTTON_SEND, new SFMLImage("Assets/Menu/buttonSendNormal.png"));
	this->_images.add(SFMLImage::BUTTON_HOVER_SEND, new SFMLImage("Assets/Menu/buttonSendHover.png"));
	this->_images.add(SFMLImage::BUTTON_CLICKED_SEND, new SFMLImage("Assets/Menu/buttonSendClicked.png"));

	this->_images.add(SFMLImage::CHECKBOX_CHECKED_NORMAL_READY, new SFMLImage("Assets/Menu/checkBoxReadyCheckedNormal.png"));
	this->_images.add(SFMLImage::CHECKBOX_CHECKED_CLICKED_READY, new SFMLImage("Assets/Menu/checkBoxReadyCheckedClicked.png"));
	this->_images.add(SFMLImage::CHECKBOX_CHECKED_HOVER_READY, new SFMLImage("Assets/Menu/checkBoxReadyCheckedHover.png"));
	this->_images.add(SFMLImage::CHECKBOX_UNCHECKED_NORMAL_READY, new SFMLImage("Assets/Menu/checkBoxReadyUncheckedNormal.png"));
	this->_images.add(SFMLImage::CHECKBOX_UNCHECKED_CLICKED_READY, new SFMLImage("Assets/Menu/checkBoxReadyUncheckedClicked.png"));
	this->_images.add(SFMLImage::CHECKBOX_UNCHECKED_HOVER_READY, new SFMLImage("Assets/Menu/checkBoxReadyUncheckedHover.png"));
	this->_images.add(SFMLImage::CHECKBOX_CHECKED_NORMAL_PRIVATE, new SFMLImage("Assets/Menu/checkBoxPrivateCheckedNormal.png"));
	this->_images.add(SFMLImage::CHECKBOX_CHECKED_CLICKED_PRIVATE, new SFMLImage("Assets/Menu/checkBoxPrivateCheckedClicked.png"));
	this->_images.add(SFMLImage::CHECKBOX_CHECKED_HOVER_PRIVATE, new SFMLImage("Assets/Menu/checkBoxPrivateCheckedHover.png"));
	this->_images.add(SFMLImage::CHECKBOX_UNCHECKED_NORMAL_PRIVATE, new SFMLImage("Assets/Menu/checkBoxPrivateUncheckedNormal.png"));
	this->_images.add(SFMLImage::CHECKBOX_UNCHECKED_CLICKED_PRIVATE, new SFMLImage("Assets/Menu/checkBoxPrivateUncheckedClicked.png"));
	this->_images.add(SFMLImage::CHECKBOX_UNCHECKED_HOVER_PRIVATE, new SFMLImage("Assets/Menu/checkBoxPrivateUncheckedHover.png"));
	this->_images.add(SFMLImage::CHECKBOX_CHECKED_NORMAL, new SFMLImage("Assets/Menu/checkBoxCheckedNormal.png"));
	this->_images.add(SFMLImage::CHECKBOX_CHECKED_CLICKED, new SFMLImage("Assets/Menu/checkBoxCheckedClicked.png"));
	this->_images.add(SFMLImage::CHECKBOX_CHECKED_HOVER, new SFMLImage("Assets/Menu/checkBoxCheckedHover.png"));
	this->_images.add(SFMLImage::CHECKBOX_UNCHECKED_NORMAL, new SFMLImage("Assets/Menu/checkBoxUncheckedNormal.png"));
	this->_images.add(SFMLImage::CHECKBOX_UNCHECKED_CLICKED, new SFMLImage("Assets/Menu/checkBoxUncheckedClicked.png"));
	this->_images.add(SFMLImage::CHECKBOX_UNCHECKED_HOVER, new SFMLImage("Assets/Menu/checkBoxUncheckedHover.png"));

	this->_images.add(SFMLImage::SLIDER, new SFMLImage("Assets/Menu/slidebar.png"));
	this->_images.add(SFMLImage::HSLIDER, new SFMLImage("Assets/Menu/Hslidebar.png"));
	this->_images.add(SFMLImage::SLIDER_CURSOR_NORMAL, new SFMLImage("Assets/Menu/CursorNormal.png"));
	this->_images.add(SFMLImage::SLIDER_CURSOR_CLICKED, new SFMLImage("Assets/Menu/CursorClicked.png"));
	this->_images.add(SFMLImage::SLIDER_CURSOR_HOVER, new SFMLImage("Assets/Menu/CursorHover.png"));
	this->_images.add(SFMLImage::TERRE, new SFMLImage("Assets/Menu/terre.png"));
	this->_images.add(SFMLImage::LISTBOX_EVEN, new SFMLImage("Assets/Menu/gridBarre1.png"));
	this->_images.add(SFMLImage::LISTBOX_ODD, new SFMLImage("Assets/Menu/gridBarre2.png"));
	this->_images.add(SFMLImage::LISTBOX_FOCUS, new SFMLImage("Assets/Menu/gridBarreSelected.png"));
	this->_images.add(SFMLImage::GAUGE_BACKGROUND, new SFMLImage("Assets/Menu/GaugeBackground.png"));
	this->_images.add(SFMLImage::GAUGE_FILLED, new SFMLImage("Assets/Menu/GaugeFilled.png"));
	this->_images.add(SFMLImage::CONNECTION_BACKGROUND, new SFMLImage("Assets/Menu/ConnectionBackground.png"));
	this->_images.add(SFMLImage::PLAY_BACKGROUND, new SFMLImage("Assets/Menu/PlayBackground.png"));
	this->_images.add(SFMLImage::JOIN_BACKGROUND, new SFMLImage("Assets/Menu/JoinBackground.png"));
	this->_images.add(SFMLImage::ROOM_BACKGROUND, new SFMLImage("Assets/Menu/RoomBackground.png"));
	this->_images.add(SFMLImage::SETTINGS_BACKGROUND, new SFMLImage("Assets/Menu/SettingsBackground.png"));
	this->_images.add(SFMLImage::POWER, new SFMLImage("Assets/Menu/power.png"));
	this->_images.add(SFMLImage::ARMOR, new SFMLImage("Assets/Menu/armor.png"));
	this->_images.add(SFMLImage::SPEED, new SFMLImage("Assets/Menu/speed.png"));

	this->_images.add(SFMLImage::STARSHIP1NORMAL, new SFMLImage("Assets/Game/Starship/starship1Normal.png"));
	this->_images.add(SFMLImage::STARSHIP1UP, new SFMLImage("Assets/Game/Starship/starship1Up.png"));
	this->_images.add(SFMLImage::STARSHIP1DOWN, new SFMLImage("Assets/Game/Starship/starship1Down.png"));
	// Put all texts objects
	this->_texts.add(SFMLText::TEXTBOX, new SFMLText(SFMLText::TEXTBOX, "Assets/Font/prototype.ttf"));
}

void	SourceModule::update()
{
	this->_images.randomInitialize();
	this->_texts.randomInitialize();
}

void	SourceModule::unload()
{

}

Engine::IImage*	SourceModule::getImage(std::string const& id)
{
	return (this->_images.get(id));
}

Engine::IText*	SourceModule::getText(std::string const& id)
{
	return (this->_texts.get(id));
}