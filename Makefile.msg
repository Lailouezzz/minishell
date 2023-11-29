#!/usr/bin/make -f
#---
# The make file for print beautiful log
#---

# Define color
BUILD_COLOR = \033[1;32m
RM_COLOR    = \033[1;31m
OK_COLOR    = \033[1;32m
ERR_COLOR   = \033[1;31m
NO_COLOR    = \033[0m

# Newline - comes handy in some situations
define \n


endef


#******************************************************************************#
# General messages
#******************************************************************************#


# Execute a command and display it
# arg1 : printed command
# arg2 : printed arg
# arg3 : executed command
# arg4 : optionnal color of printed command
# display "<arg1> <arg2>"
# execute <arg3>
define cmd
	$(if $(MAKE_FULL_LOG),, \
@printf "$(NO_COLOR)""$4""$1""$(NO_COLOR)"" ""$(NO_COLOR)""$2""$(NO_COLOR)""\n")
	$(if $(MAKE_FULL_LOG),,@)$3
endef

# Quiet command if full log is disabled
# arg1 : executed command
# execute <arg1>
define qcmd
	$(if $(MAKE_FULL_LOG),,@)$1
endef

# Normal message
# arg1 : printed message
# arg2 : optionnal color of printed message
# display : "> <arg1>"
define msg
	$(if $(MAKE_FULL_LOG),, \
@printf "$2""> ""$(NO_COLOR)""$1""$(NO_COLOR)""\n")
endef

# OK message
# arg1 : printed message
# display : "> <arg1>"
define omsg
	$(call msg,$1,$(OK_COLOR))
endef


# Build message
# arg1 : printed command
# arg2 : printed arg
# arg3 : executed command
# display "<arg1> <arg2>"
# execute <arg3>
define bcmd
	$(call cmd,$1,$2,$3,$(BUILD_COLOR))
endef


# Remove message
# arg1 : printed file or dir removed
# display "> <arg1>"
define rmsg
	$(call msg,$1,$(OK_COLOR))
endef


# Error message
# arg1 : printed file or dir removed
# display "> <arg1>"
define emsg
	$(call msg,$1,$(ERR_COLOR))
endef

