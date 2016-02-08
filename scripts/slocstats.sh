#!/bin/bash
printf "This script counts SLOCs of RINASim project\n"
printf "===============================================================\n"
printf "language   extension\tall\texcl.comments\texcl.pattern\n"
printf "===============================================================\n"

#C++
cppall=`git ls-files .. | grep -E '\.cc|\.h' | xargs cat | wc -l`
cppexc=`git ls-files .. | grep -E '\.cc|\.h' | xargs cat | sed '/\/\//d' | sed '/^\s*$/d' | sed '/\/\*/,/*\//d' | wc -l`
printf "C++        *.cc  *.h\t$cppall\t$cppexc\t\tempty // /**/\n"

#OMNeT
omnall=`git ls-files .. | grep -E '\.msg|\.ned' | xargs cat | wc -l`
omnexc=`git ls-files .. | grep -E '\.msg|\.ned' | xargs cat | sed '/\/\//d' | sed '/^\s*$/d' | wc -l`
printf "NED        *.msg *.ned\t$omnall\t$omnexc\t\tempty //\n"

#Simul
simall=`git ls-files .. | grep -E '\.ini|\.xml' | xargs cat 2>/dev/null | wc -l`
simexc=`git ls-files .. | grep -E '\.ini|\.xml' | xargs cat 2>/dev/null | sed '/\s*#.*$/d' | sed '/^\s*$/d' | wc -l`
printf "OMNeT++    *.ini *.xml\t$simall\t$simexc\t\tempty #\n"
printf "===============================================================\n"

#All
sumall=`expr $cppall + $omnall + $simall`
sumexc=`expr $cppexc + $omnexc + $simexc`
printf "Summary    \t\t$sumall\t$sumexc\n"

printf "===============================================================\n"
gitall=`git ls-files .. | xargs cat 2>/dev/null | wc -l`
gitexc=`git ls-files .. | xargs cat 2>/dev/null | sed '/^\s*$/d' | wc -l`
printf "GIT        *.*\t\t$gitall\t$gitexc\t\tempty\n"
