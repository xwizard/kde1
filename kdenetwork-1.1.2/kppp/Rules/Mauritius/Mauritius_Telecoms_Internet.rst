################################################################
#
# R�gles pour Mauritius Telecoms
# Appels locaux
#
# Fichier original par
# $Id: Mauritius_Telecoms_Internet.rst,v 1.1.2.1 1999/07/03 19:18:46 porten Exp $
# (C) 1997 Czo <sirol@asim.lip6.fr>
#
# Modifi� par Fabrice Eudes <eudes@gat.univ-lille1.fr>
# le 21 Decembre 1997.
#
#
# Modifi� par Alain Bastien <alain_bastien@hotmail.com>
################################################################

# Les nouveaux tarifs de Mauritius Telecoms sont en vigueur
# depuis le 1er Juillet 1999.
#

name=Mauritius_Telecoms_Internet
currency_symbol=Rs
currency_position=left
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
# per_connection=0.0

# Frais minimum par appel. Si le co�t d'un appel est inf�rieur
# � cette valeur, alors cette derni�re est le co�t retenu.
minimum_costs=0.0

# C'est ce que vous payez pour les trois premi�res minutes de
# connexion, peu importe si l'appel dure 1 ou 179 secondes.
# flat_init_costs=(0.74,180)

# Ceci est la r�gle utilis�e par d�faut lorsqu'aucune autre ne
# s'applique. Le premier nombre est le prix correspondant � la
# dur�e en secondes qui est le second nombre.
default=(1.50, 60)
# Ceci n'engage que moi, mais si toutes les heures de la semaine
# sont incluses dans les r�gles ci-dessous; quelle est l'utilit�
# de ce param�tre ?!?!

on (monday..sunday) between (07:00..18:59) use (1.50, 60)
on (monday..sunday)   between (19:00..23:59) use (1.00, 60)
on (monday..sunday)   between (00:00..06:59) use (0.50, 60)

# Jours f�ri�s :-))



