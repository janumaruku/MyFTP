CXX		=	g++

BUILD_DIR	=	build

CXXFLAGS	=	-std=c++20				\
			-Wall					\
			-Wextra					\
			-Werror

CPPFLAGS	=	-Isrc/DesignPattern/include					\
			-Isrc/Network/include						\
			-Isrc/Utils/include						\
			-Isrc/Server/include						\
			-Isrc/Server/FtpException/include				\
			-Isrc/Server/FtpProtocol/include				\
			-Isrc/ServerEntryPoint/include					\
			-Isrc/ServerEntryPoint/OptionHandlers/include

LDFLAGS		=

RM		=	rm -f