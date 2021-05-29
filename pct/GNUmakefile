-include GNUmakefile.std

PGMS		:= pct

SRCS            := ${wildcard *.cc}
HDRS            := ${wildcard *.hh}
OBJS		:= ${SRCS:%.cc=%.o}
INST		:= ${PGMS:%=${TOPBIN}%}
LOGS		:= ${PGMS:%=%.log}

IMPORTLIBS	:= roll

# -- ================================================================ --
#    Compile C++ to Objects

build::			objs
objs::			${OBJS}
clean::		; $C $R ${OBJS} *.d

# -- ================================================================ --
#    Link Objects into Programs

build::			pgms
pgms::			${PGMS}
${PGMS}:		${LIBA}
${PGMS}:        %:              ${OBJS}
	$P '[ld] %s\n' '$(REL)$*'
	$Q $(LINK.cc) ${OBJS} $(LOADLIBES) $(LDLIBS) -o $@
clean::		; $C $R ${PGMS}

build::			install
${TOPBIN}%:		%
	@ test -d ${TOPBIN} || mkdir -p ${TOPBIN}
	$P '[*bin*] %s\n' '$*'
	$Q cp '$*' ${TOPBIN}'$*'
install::		${INST}
uninstall::	; $C $R ${INST}
clean::			uninstall

# -- ================================================================ --
#    Collect outputs of programs

execs::			logs
logs::			${LOGS}
${LOGS}:        %.log:           ${TOPBIN}%
	$P '[go] %s\n' '$(REL)$*'
	$Q '${TOPBIN}$*' 2>&1 | tee '$@'
clean::		; $C $R ${LOGS}
