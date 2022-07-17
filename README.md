 Filtrovanie tovarov, cien v sklade, workflow a prepinace v PNG
# 1 - chybove situacie 1 2 3 4
# 2 - filter skladov
     " " zahrnu sa vsetky sklady
     "-w name" filter na iba sklad s menom "name"
     "-i item_name" filter na sklady s iba tovarmi s menom "item_name"
     "-n lat -e lon" najdenie skladu ktory je najblizsie k lat lon
# 3 - filter tovaru
     " " zahrnutie vsetkych tovarov
     "-t item_name" filter podla nazvu tovaru
     "-p max_price" vsetky tovary pod max_price sa neukazu
# 4 - vystup v cmd
     " " tovaro-centricky vypis (tovar_meno \n vsetky sklady\n)
     "-w" sklado-centricky vypis (sklad_meno \n vsekty itemy ktore tam patria \n)
