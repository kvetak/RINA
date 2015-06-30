#!/bin/bash
echo "This script counts SLOCs of RINASim project"
echo "C++ code (*.cc, *.h)"
git ls-files .. | grep -E '*.cc|*.h'| xargs cat | wc -l
echo "OMNeT++ code (*.msg, *.ned)"
git ls-files .. | grep -E '*.msg|*.ned'| xargs cat | wc -l
echo "Simulation code (*.ini, *.xml)"
git ls-files .. | grep -E '*.ini|*.xml'| xargs cat | wc -l
echo "Whole project code (*.cc, *.h, *.msg, *.ned, *.ini, *.xml)"
git ls-files .. | grep -E '*.cc|*.h|*.msg|*.ned|*.xml|*.ini'| xargs cat | wc -l
echo "All files watched by GIT"
git ls-files .. | xargs cat | wc -l 