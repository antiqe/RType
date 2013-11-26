SERVER_NAME	=	server
CLIENT_NAME	=	client

SRV_DIR		=	Server/
ULT_DIR		=	Ultra/
NET_DIR		=	Network/
CLIENT_DIR	=	Client/
ENGINE_DIR	=	Engine/
SFML_DIR	=	./lib/SFML-2.1/
LIB_CRPT	=	./lib/cryptopp/

SRC_SRV		=	$(SRV_DIR)main.cpp \
			$(SRV_DIR)Core.cpp \
			$(SRV_DIR)AccountManager.cpp \
			$(SRV_DIR)ServiceManager.cpp \
			$(SRV_DIR)RoomManager.cpp \
			$(SRV_DIR)Room.cpp \
			$(SRV_DIR)Player.cpp \
			$(SRV_DIR)Account.cpp \
			$(SRV_DIR)MySQLDatabase.cpp \
			$(SRV_DIR)MySQLResultDatabase.cpp \
			$(SRV_DIR)LogMessage.cpp \
			$(SRV_DIR)ChannelConsole.cpp \
			$(SRV_DIR)AuthService.cpp \
			$(SRV_DIR)DispatchService.cpp \
			$(SRV_DIR)RoomService.cpp \
			$(SRV_DIR)ListenerTCP.cpp \
			$(SRV_DIR)ListenerUDP.cpp \
			$(SRV_DIR)Configuration.cpp \
			$(SRV_DIR)TCPPacket.cpp \
			$(SRV_DIR)UDPPacket.cpp

SRC_ULTRA	=	$(ULT_DIR)Value.cpp \
			$(ULT_DIR)AFramer.cpp \
			$(ULT_DIR)Color.cpp \
			$(ULT_DIR)DecoratorThread.cpp \
			$(ULT_DIR)Exception.cpp \
			$(ULT_DIR)INIReader.cpp \
			$(ULT_DIR)INISection.cpp \
			$(ULT_DIR)ScopeLock.cpp \
			$(ULT_DIR)LThread.cpp \
			$(ULT_DIR)LFramer.cpp \
			$(ULT_DIR)LTimer.cpp \
			$(ULT_DIR)LMutex.cpp \
			$(ULT_DIR)Attr.cpp \
			$(ULT_DIR)Sleep.cpp

SRC_NETWORK	=	$(NET_DIR)Aggregator.cpp \
			$(NET_DIR)APacket.cpp \
			$(NET_DIR)ASocket.cpp \
			$(NET_DIR)BinaryStream.cpp \
			$(NET_DIR)Client.cpp \
			$(NET_DIR)Server.cpp \
			$(NET_DIR)Message.cpp \
			$(NET_DIR)MessageFactory.cpp \
			$(NET_DIR)LSocket.cpp \
			$(NET_DIR)InternalMessage.cpp

SRC_CLIENT	=	$(CLIENT_DIR)Animation.cpp \
			$(CLIENT_DIR)AParallax.cpp \
			$(CLIENT_DIR)ASlider.cpp \
			$(CLIENT_DIR)Background.cpp \
			$(CLIENT_DIR)ButtonCallback.cpp \
			$(CLIENT_DIR)Button.cpp \
			$(CLIENT_DIR)CheckBoxCallBack.cpp \
			$(CLIENT_DIR)CheckBox.cpp \
			$(CLIENT_DIR)Configuration.cpp \
			$(CLIENT_DIR)ConnectionState.cpp \
			$(CLIENT_DIR)ConnectionCallback.cpp \
			$(CLIENT_DIR)DataModule.cpp \
			$(CLIENT_DIR)EventModule.cpp \
			$(CLIENT_DIR)FactoryModule.cpp \
			$(CLIENT_DIR)GameState.cpp \
			$(CLIENT_DIR)GlobalCallback.cpp \
			$(CLIENT_DIR)HParallax.cpp \
			$(CLIENT_DIR)HSliderCallback.cpp \
			$(CLIENT_DIR)HSlider.cpp \
			$(CLIENT_DIR)Image.cpp \
			$(CLIENT_DIR)ListenerTCP.cpp \
			$(CLIENT_DIR)ListBoxCallback.cpp \
			$(CLIENT_DIR)ListBox.cpp \
			$(CLIENT_DIR)main.cpp \
			$(CLIENT_DIR)MD5encode.cpp \
			$(CLIENT_DIR)NetworkModule.cpp \
			$(CLIENT_DIR)PlayCreateCallback.cpp \
			$(CLIENT_DIR)PlayCreateState.cpp \
			$(CLIENT_DIR)PlayJoinState.cpp \
			$(CLIENT_DIR)PlayState.cpp \
			$(CLIENT_DIR)PlayStateCallback.cpp \
			$(CLIENT_DIR)RenderModule.cpp \
			$(CLIENT_DIR)SFMLInput.cpp \
			$(CLIENT_DIR)SFMLRender.cpp \
			$(CLIENT_DIR)SliderCursorCallback.cpp \
			$(CLIENT_DIR)SliderCursor.cpp \
			$(CLIENT_DIR)SourceModule.cpp \
			$(CLIENT_DIR)State.cpp \
			$(CLIENT_DIR)StateModule.cpp \
			$(CLIENT_DIR)TCPPacket.cpp \
			$(CLIENT_DIR)TextBoxCallback.cpp \
			$(CLIENT_DIR)TextBox.cpp \
			$(CLIENT_DIR)Text.cpp \
			$(CLIENT_DIR)UDPPacket.cpp \
			$(CLIENT_DIR)VParallax.cpp \
			$(CLIENT_DIR)VSliderCallback.cpp \
			$(CLIENT_DIR)VSlider.cpp

SRC_ENGINE	=	$(ENGINE_DIR)AComponent.cpp \
			$(ENGINE_DIR)ADataModule.cpp \
			$(ENGINE_DIR)AEventDispatcher.cpp \
			$(ENGINE_DIR)AEventModule.cpp \
			$(ENGINE_DIR)AFactoryModule.cpp \
			$(ENGINE_DIR)AModule.cpp \
			$(ENGINE_DIR)ANetworkModule.cpp \
			$(ENGINE_DIR)ARenderModule.cpp \
			$(ENGINE_DIR)ASoundModule.cpp \
			$(ENGINE_DIR)ASourceModule.cpp \
			$(ENGINE_DIR)AState.cpp \
			$(ENGINE_DIR)AStateModule.cpp \
			$(ENGINE_DIR)Callback.cpp \
			$(ENGINE_DIR)Core.cpp \
			$(ENGINE_DIR)Event.cpp \
			$(ENGINE_DIR)EventListener.cpp \
			$(ENGINE_DIR)GameObject.cpp \
			$(ENGINE_DIR)GameObjectFactory.cpp \
			$(ENGINE_DIR)Governor.cpp \
			$(ENGINE_DIR)KeyboardEvent.cpp \
			$(ENGINE_DIR)MouseEvent.cpp \
			$(ENGINE_DIR)NetworkEvent.cpp \
			$(ENGINE_DIR)Widget.cpp \
			$(ENGINE_DIR)WindowEvent.cpp

OBJ_SRV		=	$(SRC_SRV:.cpp=.o)
OBJ_ULTRA	=	$(SRC_ULTRA:.cpp=.o)
OBJ_NETWORK	=	$(SRC_NETWORK:.cpp=.o)
OBJ_ENGINE	=	$(SRC_ENGINE:.cpp=.o)
OBJ_CLIENT	=	$(SRC_CLIENT:.cpp=.o)

TMP		=	$(SRC:.cpp=.cpp~)

LDFLAGS		=	-L $(SRV_DIR)/lib/mysql -L $(LIB_CRPT)/libcryptopp.a -lmysqlclient -lcryptopp -lpthread -lm -lrt -ldl

CPPFLAGS	=	-Wall -Wno-overflow -Wextra

CPPFLAGS	+=	-I $(SRV_DIR) \
			-I $(ULT_DIR) \
			-I $(NET_DIR) \
			-I $(CLIENT_DIR) \
			-I $(ENGINE_DIR) \
			-I $(SRV_DIR)lib/mysql \
			-I ./lib/glew/include \
			-I $(LIB_CRPT)/include \
			-I $(SFML_DIR)/include

ifeq ($(DEBUG), YES)
	CPPFLAGS += -g
	DEBUGFLAGS = -\033[1;31mDEBUG\033[0m-

endif

ifeq ($(PROFIL), YES)
	CPPFLAGS += -pg
	PROFILFLAGS = -\033[1;31mPROFIL\033[0m-
endif

CPP		=	g++ -g

DEL_FILE	=	rm -f

all:		$(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME):	$(OBJ_ULTRA) $(OBJ_NETWORK) $(OBJ_ENGINE) $(OBJ_SRV)
		@$(CPP) -o $@ $^ $(LDFLAGS)
		@printf "\r[\033[1;33mSERVER\033[0m] $@\n"

$(CLIENT_NAME):	$(OBJ_ULTRA) $(OBJ_NETWORK) $(OBJ_ENGINE) $(OBJ_CLIENT)
		@$(CPP) -o $@ $^ $(LDFLAGS) -L ./lib/glew/lib -Wl,--rpath=./lib/glew/lib -L $(SFML_DIR)/lib64 -Wl,--rpath=$(SFML_DIR)/lib64 -lGLEW -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window

		@printf "\r[\033[1;33mCLIENT\033[0m] $@\n"

%.o:		%.cpp
		@$(CPP) -o $@ -c $< $(CPPFLAGS)
		@printf "\r$(DEBUGFLAGS)$(PROFILFLAGS)[\033[1;32mBUILD\033[0m] $<\n"

clean:
		@$(DEL_FILE) $(OBJ_ULTRA) $(OBJ_NETWORK) $(OBJ_ENGINE) $(OBJ_CLIENT) $(OBJ_SRV)
		@printf "\r[\033[1;31mDELETE\033[0m] *.o\n"
		@$(DEL_FILE) $(TMP)
		@printf "\r[\033[1;31mDELETE\033[0m] *~\n"

fclean:		clean
		@$(DEL_FILE) $(SERVER_NAME) $(CLIENT_NAME)
		@printf "\r[\033[1;31mDELETE\033[0m] $(SERVER_NAME) $(CLIENT_NAME)\n"

re:		fclean all

.PHONY:		all clean fclean re
