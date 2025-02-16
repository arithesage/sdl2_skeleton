include Project.mk


EXEC							:= ${PROJECT_NAME}

ifneq (${WINDIR},)
	SYSTEM						:= windows
	EXEC						:= ${EXEC}.exe
else
	UNAME						:= $(shell uname)

	ifeq (${UNAME},Darwin)
		SYSTEM					:= macos
	else ifeq (${UNAME},Linux)
		SYSTEM					:= linux
	else
		SYSTEM					:= other
	endif
endif

SRC								:= src
BUILD							:= build
OBJ								:= obj

OBJ_PATH						:= ${OBJ}/${SYSTEM}
BUILD_PATH						:= ${BUILD}/${SYSTEM}

EXEC							:= ${BUILD}/${SYSTEM}/${EXEC}


include Commands.mk
include Functions.mk

C_MAIN							:= $(shell find ${SRC}/** -type f -name "main.c")
CPP_MAIN						:= $(shell find ${SRC}/** -type f -name "main.cpp")

ifneq (${C_MAIN},)
	MAIN						:= ${C_MAIN}
else
	MAIN						:= ${CPP_MAIN}
endif

MAIN_FILE						:= $(notdir ${MAIN})
MAIN_OBJ						:= ${OBJ_PATH}/$(call SRC2OBJ,${MAIN_FILE})

C_SRCS							:= $(shell find ${SRC}/** -type f -name "*.c" -not -name "main.c")
CPP_SRCS						:= $(shell find ${SRC}/** -type f -name "*.cpp" -not -name "main.cpp")

C_HEADERS						:= $(shell find ${SRC}/** -type f -name "*.h")
CPP_HEADERS						:= $(shell find ${SRC}/** -type f -name "*.hpp")

SRCS							:= $(strip ${C_SRCS} ${CPP_SRCS})
HEADERS							:= $(strip $(C_HEADERS) ${CPP_HEADERS})
OBJS							:= $(foreach src,${SRCS},$(call SRC2OBJ,${src}))

INCLUDE_PATHS					:= $(sort $(foreach file,${HEADERS},$(dir ${file})))

INCLUDE							:= $(strip $(foreach inc,${INCLUDE_PATHS},-I ${inc}))
LIBS							:= $(foreach lib,${LIBS},-l${lib})

DEPS_LIBS						:= $(shell find deps/* -type f -name "*.hpp")
DEPS_SRCS						:= $(shell find deps/* -type f -name "*.cpp")
DEPS_INCLUDE_PATHS				:= $(sort $(foreach lib,${DEPS_LIBS},$(dir ${lib})))
DEPS_INCLUDE					:= $(strip $(foreach lib,${DEPS_INCLUDE_PATHS},-I ${lib}))
DEPS_OBJS						:= $(foreach src,${DEPS_SRCS},deps/obj/$(notdir $(call SRC2OBJ,${src})))

ifeq (${C},)
	C							:= clang
endif

ifeq (${CXX},)
	CXX							:= clang++
endif




.PHONY: all clean_deps deps clean info run


all: ${OBJ_PATH} ${BUILD_PATH} ${EXEC}


clean:
	$(shell ${RMTREE} ${OBJ})
	$(shell ${RMTREE} ${BUILD})


clean_deps:
	$(shell ${RMTREE} deps/obj)


${BUILD_PATH}:
	$(shell ${MKTREE} ${BUILD_PATH})


${OBJ_PATH}:
	$(shell ${MKTREE} ${OBJ_PATH})


# Builds the executable
${EXEC}: ${OBJS} ${MAIN_OBJ}
ifeq (${MAIN_FILE},main.c)
	${C} ${DEPS_OBJS} ${OBJS} ${MAIN_OBJ} -o ${EXEC} ${LIBS} ${LDFLAGS}
else
	${CXX} ${DEPS_OBJS} ${OBJS} ${MAIN_OBJ} -o ${EXEC} ${LIBS} ${LDFLAGS}
endif


# Builds the main object
${MAIN_OBJ}: ${MAIN}
ifeq (${MAIN_FILE},main.c)
	${C} -c ${MAIN} -o ${MAIN_OBJ} ${DEPS_INCLUDE} ${INCLUDE} ${CFLAGS}
else
	${CXX} -c ${MAIN} -o ${MAIN_OBJ} ${DEPS_INCLUDE} ${INCLUDE} ${CXXFLAGS}
endif


# Builds all C files mirroring their folder tree
${OBJ_PATH}/%.o: ${SRC}/%.c
	$(shell ${MKTREE} $(dir $@))
	${C} -c $< -o $@ ${DEPS_INCLUDE} ${INCLUDE} ${CFLAGS}


# Builds all CPP files mirroring their folder tree
${OBJ_PATH}/%.o: ${SRC}/%.cpp
	$(shell ${MKTREE} $(dir $@))
	${CXX} -c $< -o $@ ${DEPS_INCLUDE} ${INCLUDE} ${CXXFLAGS}


# Old recipe for creating custom recipes for compiling all file exept main.
# Did not work then because 'eval' was missing, but can be useful.
#$(foreach src,${SRCS},$(eval $(call COMPILE,${src},$(call SRC2OBJ,${src}))))


libs:
	/bin/bash -c libs/build


info:
	$(info PROJECT_NAME: ${PROJECT_NAME})
	$(info EXEC: ${EXEC})
	$(info SYSTEM: ${SYSTEM})
	$(info MAIN: ${MAIN})
	$(info MAIN_FILE: ${MAIN_FILE})
	$(info MAIN_OBJ: ${MAIN_OBJ})
	$(info C_SRCS: ${C_SRCS})
	$(info CPP_SRCS: ${CPP_SRCS})
	$(info C_HEADERS: ${C_HEADERS})
	$(info CPP_HEADERS: ${CPP_HEADERS})
	$(info SRCS: ${SRCS})
	$(info OBJS: ${OBJS})
	$(info INCLUDED_PATHS: ${INCLUDE})
	$(info LIBS: ${LIBS})
	$(info EXTRA_LIBS: ${EXTRA_LIBS})
	$(info EXTRA_INCLUDE_PATHS: ${EXTRA_INCLUDE_PATHS})
	$(info EXTRA_INCLUDE: ${EXTRA_INCLUDE})
	$(info EXTRA_OBJS: ${EXTRA_OBJS})


run:
ifeq (${SYSTEM},windows)
	${EXEC}
else
	./${EXEC}
endif
