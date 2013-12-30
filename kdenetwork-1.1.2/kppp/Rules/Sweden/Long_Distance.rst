################################################################
# Swedish rate ruleset for long distance calls (sverigesamtal) #
# Created 1997-11-26 by Anders Widell  <d95-awi@nada.kth.se>   #
# Updated 1999-02-02 by Anders Widell  <d95-awi@nada.kth.se>   #
# May be distributed freely. I take no responsibility for      #
# the correctness of the information in this file.             #
################################################################

name=Swedish_Long_Distance
currency_symbol=SEK
currency_position=right 
currency_digits=2

# S� h�r ber�knar Telia samtalskostnaden (enligt vad jag f�rst�r...)
#
# * en �ppningsavgift debiteras f�r alla samtal s� fort man f�tt svar
# * d�refter ber�knas kostnaden per sekund
#
# Kostnaden per sekund beror av tiden:
# * h�g taxa vardagar kl 08:00-18:00
# * l�g taxa �vrig tid
#
# Som vardagar r�knas m�ndag till fredag. Dock ej:
# * r�da dagar i almanackan
# * Vissa �vriga dagar. Vilka dessa �r verkar n�got oklart, och kan kanske
#   variera fr�n �r till �r efter Telias tycke och smak. Men en tumregel �r
#   att "aftnar" typ julafton och ny�rsafton inte r�knas som vardagar.


# �ppningsavgift: 40 �re
per_connection=0.40
minimum_costs=0.0

# L�g taxa: 20 �re/min (r�knat per sekund)
default=(0.01, 3)

# H�g taxa: 38 �re/min m�ndag-fredag 8-18
on (monday..friday) between (8:00..17:59) use (0.019, 3)

# R�da helgdagar (de som infaller p� en l�rdag/s�ndag utel�mnade)
# ny�rsdagen
on (01/01) between () use (0.01, 3)
# trettondag jul
on (01/06) between () use (0.01, 3)
# l�ngfredagen
on (easter-2) between () use (0.01, 3)
# annandag p�sk
on (easter+1) between () use (0.01, 3)
# f�rsta maj
on (05/01) between () use (0.01, 3)
# kristi himmelf�rds dag
on (easter+39) between () use (0.01, 3)
# annandag pingst
on (easter+50) between () use (0.01, 3)
# juldagen
on (12/25) between () use (0.01, 3)
# annandag jul
on (12/26) between () use (0.01, 3)

# "aftnar" (os�kert om f�ljande �r korrekt & fullst�ndigt)
# trettondagsafton
on (01/05) between () use (0.01, 3)
# julafton
on (12/24) between () use (0.01, 3)
# ny�rsafton
on (12/31) between () use (0.01, 3)
