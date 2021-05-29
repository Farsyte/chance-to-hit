include GNUmakefile.std

LIBN		:= roll
LIBA		:= ${LIBN:%=lib%.a}
SRCS            := ${wildcard *.cc}
HDRS            := ${wildcard *.hh}
OBJS		:= ${SRCS:%.cc=%.o}
DEPS		:= ${SRCS:%.cc=%.d}
INST		:= ${LIBA:%=${TOPLIB}%}

build::		${INST}
clean::		; $R ${INST} ${OBJS} ${DEPS}
${INST}:	${OBJS:%=${INST}(%)}

