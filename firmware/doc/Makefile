##-*- makefile -*-############################################################
#
#  System        : 
#  Module        : 
#  Object Name   : $RCSfile$
#  Revision      : $Revision$
#  Date          : $Date$
#  Author        : $Author$
#  Created By    : Robert Heller
#  Created       : Tue Apr 4 16:29:59 2023
#  Last Modified : <251121.0914>
#
#  Description	
#
#  Notes
#
#  History
#	
#  $Log$
#
##############################################################################
#
#    Copyright (C) 2023  Robert Heller D/B/A Deepwoods Software
#			51 Locke Hill Road
#			Wendell, MA 01379-9728
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
# 
#
##############################################################################

SRCS = $(wildcard ../*.hxx) $(wildcard ../*.cxx) $(wildcard ../Azatrax/*.hxx) \
	$(wildcard ../Azatrax/*.cxx) \
	$(wildcard ../targets/freertos.armv7m.st-stm32f303re-nucleo-1shield/*.hxx) \
	$(wildcard ../targets/freertos.armv7m.st-stm32f303re-nucleo-1shield/*.cxx) \
	Revision.dox KitBooklet.dox ServoConfig.dox AzatraxConfig.dox
	
all: docs


Revision.dox: ../targets/freertos.armv7m.st-stm32f303re-nucleo-1shield/Revision.hxxout
	echo '/** @page Revision Build Revisions' > $@
	grep '^[[:space:]]*"[^"]*",$$' $< |sed 's/^[[:space:]]*"/ * - /g'|sed 's/",$$//g' >> $@
	echo '*/' >> $@
	                                
.PHONY:
docs: html/index.html kitbooklet.pdf UserManual.pdf

html/index.html UserManual.pdf : $(SRCS) Makefile Doxyfile header.tex
	rm -rf html latex
	doxygen Doxyfile
	$(MAKE) -C latex
	mv latex/refman.pdf ./UserManual.pdf
	

latex2/refman.tex : ../main.cxx KitBooklet.dox \
	../AzatraxRIR4Crossing.hxx AzatraxConfig.dox \
	../BlinkingConsumerConfig.hxx ../SSRConsumerConfig.hxx \
	../StallConsumerConfig.hxx ServoConfig.dox \
	Makefile Doxyfile.kit $(wildcard images/*) header.tex
	rm -rf latex2
	doxygen Doxyfile.kit
	

kitbooklet.pdf: latex2/refman.tex
	$(MAKE) -C latex2
	pdfbook2 --paper=letter latex2/refman.pdf
	mv latex2/refman-book.pdf kitbooklet.pdf

header.tex: Doxyfile.kit Doxyfile Makefile header.sed
	doxygen -w latex new_header.tex /dev/null /dev/null
	sed <new_header.tex >header.tex -f header.sed 
	-rm new_header.tex

clean::
	rm -rf latex latex2 html warnings 
                
veryclean:: clean
	rm -f UserManual.pdf  kitbooklet.pdf


