BEGIN {
S["am__EXEEXT_FALSE"]=""
S["am__EXEEXT_TRUE"]="#"
S["LTLIBOBJS"]=""
S["LIBOBJS"]=""
S["ac_ct_AR"]="ar"
S["AR"]="ar"
S["DEBUG_FALSE"]=""
S["DEBUG_TRUE"]="true"
S["RANLIB"]="ranlib"
S["am__fastdepCC_FALSE"]="#"
S["am__fastdepCC_TRUE"]=""
S["CCDEPMODE"]="depmode=gcc3"
S["am__nodep"]="_no"
S["AMDEPBACKSLASH"]="\\"
S["AMDEP_FALSE"]="#"
S["AMDEP_TRUE"]=""
S["am__quote"]=""
S["am__include"]="include"
S["DEPDIR"]=".deps"
S["OBJEXT"]="o"
S["EXEEXT"]=""
S["ac_ct_CC"]="gcc"
S["CPPFLAGS"]=""
S["LDFLAGS"]=""
S["CFLAGS"]="-O3"
S["CC"]="gcc"
S["AM_BACKSLASH"]="\\"
S["AM_DEFAULT_VERBOSITY"]="1"
S["AM_DEFAULT_V"]="$(AM_DEFAULT_VERBOSITY)"
S["AM_V"]="$(V)"
S["am__untar"]="$${TAR-tar} xf -"
S["am__tar"]="$${TAR-tar} chof - \"$$tardir\""
S["AMTAR"]="$${TAR-tar}"
S["am__leading_dot"]="."
S["SET_MAKE"]=""
S["AWK"]="mawk"
S["mkdir_p"]="$(MKDIR_P)"
S["MKDIR_P"]="/usr/bin/mkdir -p"
S["INSTALL_STRIP_PROGRAM"]="$(install_sh) -c -s"
S["STRIP"]=""
S["install_sh"]="${SHELL} /paraminer/paraminer-1.0/install-sh"
S["MAKEINFO"]="makeinfo"
S["AUTOHEADER"]="autoheader"
S["AUTOMAKE"]="automake-1.13"
S["AUTOCONF"]="autoconf"
S["ACLOCAL"]="aclocal-1.13"
S["VERSION"]="1.0"
S["PACKAGE"]="melinda"
S["CYGPATH_W"]="echo"
S["am__isrc"]=""
S["INSTALL_DATA"]="${INSTALL} -m 644"
S["INSTALL_SCRIPT"]="${INSTALL}"
S["INSTALL_PROGRAM"]="${INSTALL}"
S["target_alias"]=""
S["host_alias"]=""
S["build_alias"]=""
S["LIBS"]=""
S["ECHO_T"]=""
S["ECHO_N"]="-n"
S["ECHO_C"]=""
S["DEFS"]="-DHAVE_CONFIG_H"
S["mandir"]="${datarootdir}/man"
S["localedir"]="${datarootdir}/locale"
S["libdir"]="${exec_prefix}/lib"
S["psdir"]="${docdir}"
S["pdfdir"]="${docdir}"
S["dvidir"]="${docdir}"
S["htmldir"]="${docdir}"
S["infodir"]="${datarootdir}/info"
S["docdir"]="${datarootdir}/doc/${PACKAGE_TARNAME}"
S["oldincludedir"]="/usr/include"
S["includedir"]="${prefix}/include"
S["localstatedir"]="${prefix}/var"
S["sharedstatedir"]="${prefix}/com"
S["sysconfdir"]="${prefix}/etc"
S["datadir"]="${datarootdir}"
S["datarootdir"]="${prefix}/share"
S["libexecdir"]="${exec_prefix}/libexec"
S["sbindir"]="${exec_prefix}/sbin"
S["bindir"]="${exec_prefix}/bin"
S["program_transform_name"]="s,x,x,"
S["prefix"]="/usr/local"
S["exec_prefix"]="${prefix}"
S["PACKAGE_URL"]=""
S["PACKAGE_BUGREPORT"]="Benjamin.Negrevergne@imag.fr"
S["PACKAGE_STRING"]="Melinda 1.0"
S["PACKAGE_VERSION"]="1.0"
S["PACKAGE_TARNAME"]="melinda"
S["PACKAGE_NAME"]="Melinda"
S["PATH_SEPARATOR"]=":"
S["SHELL"]="/bin/bash"
  for (key in S) S_is_set[key] = 1
  FS = ""

}
{
  line = $ 0
  nfields = split(line, field, "@")
  substed = 0
  len = length(field[1])
  for (i = 2; i < nfields; i++) {
    key = field[i]
    keylen = length(key)
    if (S_is_set[key]) {
      value = S[key]
      line = substr(line, 1, len) "" value "" substr(line, len + keylen + 3)
      len += length(value) + length(field[++i])
      substed = 1
    } else
      len += 1 + keylen
  }

  print line
}

