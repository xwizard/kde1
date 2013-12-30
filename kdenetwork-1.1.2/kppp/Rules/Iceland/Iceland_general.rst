################################################################
#                                                              #
# Phone cost rules for Landsimi Islands  (Iceland Telecom)     #
#                                                              #
# Authors: Thorarinn R. Einarsson (thori@mindspring.com)       #
#          Bjarni R. Einarsson (bre@netverjar.is)              #
#                                                              #
# Created on February 2, 1999                                  #
# Last updated on 5. September, 1999                           #
#                                                              #
# Ath. H�fundar bera EKKI �byrg� � r�ngum �treikningum !       #
#                                                              #
# Vita� er a� �treikningar eru �n�kv�mir, �v� Landss�minn      #
# rukkar fyrir skrefi�, ekki m�n�tuna.  �essi gjaldskr� mi�ast #
# hinsvegar vi� m�n�tur, og byggir � uppl�singum �r s�ma-      #
# skr�nni fr� 1999.                                            #
#                                                              #
################################################################

###  Name of ruleset ###
name=Island_almennur_taxti

###  Currency symbol  ### (ekki �a� al�j��lega heldur �a� sem birtist)
currency_symbol=kr.

# Define the position of the currency symbol.
currency_position=right 

# Define the number of significant digits.
currency_digits=2

################################################################
# connection settings
################################################################

# NOTE: rules are applied from top to bottom - the
#       LAST matching rule is the one used for the
#       cost computations.

#
# Kostna�ur vi� tengingu  (1 skref)
#
 
per_connection=3.32

#
# L�gmarkskostna�ur (�arf ekki a� nota �v� 3.32 kemur � hverja tengingu)
#

minimum_costs=0.0

#
# Sl�ttur kostna�ur er ekki nota�ur � �slandi
#

flat_init_costs=(0.0,0.0)

#
# Sj�lfgefinn kostna�ur - Alla virka daga � daginn.
# Virka daga b�tast 1.56 kr. vi� � hverjum 60 sek�ndum
# (e�a 128 sek. � skrefi)
#
default=(1.56, 60)


###################
# Aukareglurnar:  #################################
###################

#
# Kv�ld og n�turtaxti alla virka daga
#
# 0.78 kr. � m�n. (e�a 256 sek. � skrefi)
#

on (monday..friday) between (19:00..07:59) use (0.78, 60)

#
# Helgartaxti
#
# Sama og K&N taxti e�a 0.78 kr. � m�n.
#

on (saturday..sunday) between () use (0.78, 60)


#
# H�t��isdagar:  Nota kv�ld- og n�turtaxta
#
# J�ladagur
#

on (12/25) between () use (0.78, 60)

#
# H�t��isdagar nota kv�ld- og n�turtaxta
#
# H�r eru nokkrir...

on (12/1, 12/24..12/26, 12/31, 01/01, 05/01, 06/17) between () use (0.78, 60)

#
# og a�rir tengdir p�skum
#

# Sk�rdagur
on (easter-3) between() use (0.78, 60)

# F�studagurinn langi
on (easter-2) between() use (0.78, 60)

# Annar � P�skum
on (easter+1) between () use (0.78, 60)

# Hv�tasunnudagur
on (easter+50) between () use (0.78, 60)
