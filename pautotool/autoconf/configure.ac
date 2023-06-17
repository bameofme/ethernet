AC_INIT([myproject], [1.0])
AC_CONFIG_SRCDIR([src/main.c])
AC_PROG_CC
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_GREP
AC_PROG_LEX
AC_PROG_YACC
AC_CONFIG_FILES([inc/config.h])
AC_SUBST([VERSION], ['2.0'])

# echo "The value of CC is $CC"
# AC_PROG_CC
# echo "The value of CC is now $CC"
FOO=42
AC_SUBST([FOO])
if ((FOO == 42)); then
    echo "The value of FOO1 is correct!"
fi
AC_CONFIG_FILES([inc/testfile])

# AC_DEFINE([MY_MACRO], ["Hello, World!"], [Mô tả của macro])

# AC_CHECK_FUNCS([printf foobar])
# echo "ac_cv_func_printf: ${ac_cv_func_printf}"
# echo "ac_cv_func_foobar: ${ac_cv_func_foobar}"

# AC_CHECK_HEADERS([spawn.h],
# [echo "Header spawn.h was found"; has_spawn=yes],
# [echo "Header spawn.h was not found"])
# echo ${has_spawn}
# AC_CONFIG_HEADER([config.h])
# AC_MSG_CHECKING([hello])
# AC_SEARCH_LIBS(pthread_create, [pthread])

# AC_ARG_WITH([myfeature], [AS_HELP_STRING([--with-myfeature], [Enable My Feature])], [echo "Action if given, val =  ${withval}"],
# [echo "Action if not given"])

# if test "x$with_myfeature" = "xyes"; then
#     AC_DEFINE([ENABLE_MY_FEATURE], [1], [Define to enable My Feature])
#     AC_MSG_NOTICE([My Feature is enabled])
# else
#     AC_MSG_NOTICE([My Feature is disabled])
# fi

# AC_ARG_ENABLE([test], AS_HELP_STRING([--enable-test], [Enable tests]),
# [echo "Action if given, val = ${enableval}"],
# [echo "Action if not given"])
# echo "enable_test = ${enable_test}"

# AC_LINK_IFELSE([
#     AC_LANG_PROGRAM([[
#         #include <bar.h>
#         int main() {
#             foo();  // Gọi hàm foo
#             return 0;
#         }
#     ]])
# ], [
#     AC_MSG_RESULT([Hàm foo có sẵn trong thư viện bar])
# ], [
#     AC_MSG_RESULT([Hàm foo không có sẵn trong thư viện bar])
#     AC_MSG_ERROR([Không thể liên kết với thư viện bar])
# ])


AC_OUTPUT