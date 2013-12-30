################################################################
#
# R�gles pour France T�l�com
# Appels locaux
#
# Fichier original par
# $Id: Local.rst,v 1.1.4.1 1999/05/25 01:29:28 porten Exp $
# (C) 1997 Czo <sirol@asim.lip6.fr>
#
# Modifi� par Fabrice Eudes <eudes@gat.univ-lille1.fr>
# le 21 Decembre 1997.
#
# Modifi� par Laurent Montel <montell@club-internet.fr>
# le 8 mai 1999
################################################################

# Les nouveaux tarifs de France T�l�com sont en vigueur
# depuis le 1er Octobre 1997.
#
# Pour les appels locaux, France T�l�com indique qu'une minute
# de communication devrait co�ter:
# ( A mon avis, ceci ne tient pas compte des arrondis )
#
# 0.14 F TTC en tarif r�duit
# 0.28 F TTC in tarif normal
#

name=France_Local_Area
currency_symbol=F
currency_position=right
currency_digits=2


################################################################
# Param�tres de connection
################################################################

# NOTE: les r�gles sont parcourues du d�but vers la fin du fichier
#       donc seulement la derni�re r�gle appropri�e est prise en
#       consid�ration. Placez donc les r�gles les plus g�n�rales
#       avant les plus sp�cifiques.

# Ceci est un co�t suppl�mentaire �ventuel par appel. Si vous
# n'�tes pas concern�, posez le �gal � z�ro ou commentez-le.
per_connection=0.0

# Frais minimum par appel. Si le co�t d'un appel est inf�rieur
# � cette valeur, alors cette derni�re est le co�t retenu.
minimum_costs=0.0

# C'est ce que vous payez pour les trois premi�res minutes de
# connexion, peu importe si l'appel dure 1 ou 179 secondes.
flat_init_costs=(0.74,180)

# Ceci est la r�gle utilis�e par d�faut lorsqu'aucune autre ne
# s'applique. Le premier nombre est le prix correspondant � la
# dur�e en secondes qui est le second nombre.
default=(0.28, 60)
# Ceci n'engage que moi, mais si toutes les heures de la semaine
# sont incluses dans les r�gles ci-dessous; quelle est l'utilit�
# de ce param�tre ?!?!

on (monday..saturday) between (00:00..08:00) use (0.14, 60)
on (monday..friday)   between (08:00..19:00) use (0.28, 60)
on (monday..friday)   between (19:00..23:59) use (0.14, 60)
# changement le 1er mars 1999 le samedi de 8 Heures � 12 Heures ca coute 0.14 francs par minute
on (saturday)         between (08:00..12:00) use (0.14, 60)
on (saturday)         between (12:00..23:59) use (0.14, 60)
on (sunday)           between (00:00..23:59) use (0.14, 60)

# Jours f�ri�s :-))
on (01/01, easter+1, 05/01, 05/08, easter+38, easter+50, 07/14, 08/15, 11/01, 11/11, 12/25) between (00:00..23:59) use (0.14, 60)

