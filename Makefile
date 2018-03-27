#
# OMNeT++/OMNEST Makefile for rina
#
# This file was generated with the command:
#  opp_makemake -f --deep --nolink -O out -d policies -d src -X. -L./out/$$\(CONFIGNAME\)/policies -L./out/$$\(CONFIGNAME\)/src
#

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target when "Build Project" is invoked
all:
# TODO: atrocious, rewrite
#	$(Q)test -f src/Makefile -a -f policies/Makefile || make makefiles
	$(qecho) Creating library librinasimcore ...
#	$(Q)if [ -d $(PROJECT_OUTPUT_DIR) ]; then \
		find $(PROJECT_OUTPUT_DIR) -type f -name "librinasim.*" -exec rm -rf {} \;; fi
	$(Q)cd src && $(MAKE) all
	$(qecho) Creating library librinasim ...
	$(Q)cd policies && $(MAKE) all

submakedirs:  src_dir policies_dir

makefiles:
	$(qecho) Generating makefiles...

	$(Q)cd src && \
	opp_makemake -f --deep --make-lib -o rinasimcore -O out -I../src -I../policies -L../out/$$\(CONFIGNAME\)/policies
	
	$(Q)cd policies && \
	opp_makemake -f --deep --make-so -o rinasim -O out -I../src -I../policies -L../out/$$\(CONFIGNAME\)/src -lrinasimcore
	

.PHONY: all clean cleanall depend msgheaders src policies
policies: policies_dir
src: src_dir

policies_dir:
	cd policies && $(MAKE) all

src_dir:
	cd src && $(MAKE) all

msgheaders:
	$(Q)cd src && $(MAKE) msgheaders
	$(Q)cd policies && $(MAKE) msgheaders

# When "Clean Local/Project" is invoked
clean: cleansrc cleanpolicies
	$(qecho) Cleaning project ...
	$(Q)rm -rf $(O)
	$(Q)rm -f ./policies/librinasim.so ./policies/librinasim.dll ./src/librinasimcore.a ./src/librinasimcore.lib

cleanall: clean
	$(Q)rm -rf $(PROJECT_OUTPUT_DIR)

cleanlibs:
	$(qecho) Cleaning libraries ...
	$(Q)find $(PROJECT_OUTPUT_DIR) -type f -name "librinasimcore.*" -exec rm -rf {} \;
	$(Q)find $(PROJECT_OUTPUT_DIR) -type f -name "librinasim.*" -exec rm -rf {} \;

cleansrc:
	$(Q)cd src && $(MAKE) clean && rm -f .tmp* sta*

cleanpolicies:
	$(Q)cd policies && $(MAKE) clean && rm -f .tmp* sta*

depend:
	$(qecho) Creating dependencies...
	$(Q)cd src && if [ -f Makefile ]; then $(MAKE) depend; fi
	$(Q)cd policies && if [ -f Makefile ]; then $(MAKE) depend; fi

