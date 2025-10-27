# Simulacija poštanske službe za dostavu paketa
Program simulira rad poštanske službe koja dostavlja pakete unutar jednog grada. Cilj je efikasno rasporediti i dostaviti pakete koristeći jedno dostavno vozilo ograničenog kapaciteta.
Grad je predstavljen kao neusmjeren težinski graf, gdje:
* čvorovi predstavljaju adrese (mjesta)
* grane predstavljaju ulice
* vrijednosti u matrici susjednosti predstavljaju udaljenosti između adresa (mjesta).

Ulazni podaci uključuju:
* tekstualni fajl (grad1.txt, grad2.txt, grad3.txt) sa matricom susjednosti grada
* CSV fajl (posta1.csv, posta2.csv) sa spiskom paketa koje je potrebno dostaviti.

## Paket - struktura podataka
Svaki paket sadrži:
* naziv,
* opis,
* adresu (broj čvora na koju ga je potrebno isporučiti)
* masu
* prioritet (0 - 100).

Paketi se prvo obrađuju po prioritetu, a zatim po masi - do maksimalne težine koju vozilo može da prihvati.
Paketi koji ne mogu da stanu u vozilo zapisuju se u izlazni fajl (*visak_paketa.txt*).

## Tok simulacije
1. Učitava se matrica susjednosti grada
2. Iz CSV fajla se učitavaju paketi i smještaju se u **prioritetni red**
3. Paketi se raspoređuju u dostavno vozilo do maksimalne dozvoljene mase
4. Vozilo kreće iz pošte i obilazi adrese redoslijedom najkraćih ruta koristeći _Floyd-Warshall_-ov algoritam
5. Nakon svake dostave ispisuje se trenutno stanje - trenutni i naredni čvor na putanji, te koji paketi su dostavljeni
6. Na kraju se prikazuje:
   * broj ukupnih, dostavljenih i neisporučenih paketa
   * procenat uspješno dostavljenih paketa.

## Rezultati simulacije
Na konzoli se prikazuju:
* matrica susjedstva,
* matrica najkraćih rastojanja (po _Floyd-Warshall_-ovom algoritmu)
* paketi koji čekaju na dostavljanje (u pošti)
* paketi koji su uspješno ubačeni u vozilo (i koji će biti isporučeni)
* redoslijed dostava
* ukupna putanja koju je vozilo prešlo prilikom dostavljanja paketa
* procenat uspješno dostavljenih paketa.

Dodatno, kao rezultat dobija se i fajl sa paketima koji nisu uspješno isporučeni (nisu ubačeni u vozilo zbog prekoračenja maksimalne dozvoljene težine).

## Primjer izvršavanja

```
Broj mjesta u gradu na koje treba dostaviti paket: 6
Lokacije: 2 3 4 5 6 7 
Udaljenosti:
    0     3     4     5     6     8    12 
    3     0     9    17    19    22    16 
    4     9     0    14    18    27    37 
    5    17    14     0    38    39    65 
    6    19    18    38     0    40    42 
    8    22    27    39    40     0    77 
   12    16    37    65    42    77     0 
-------------------------------------------
NAJKRACA RASTOJANJA(FLOYD):
    0     3     4     5     6     8    12 
    3     0     7     8     9    11    15 
    4     7     0     9    10    12    16 
    5     8     9     0    11    13    17 
    6     9    10    11     0    14    18 
    8    11    12    13    14     0    20 
   12    15    16    17    18    20     0 
-------------------------------------------

U posti sljedeci paketi cekaju na isporuku:
1.) Sage [sit amet cursus id turpis integer aliquet massa id lobortis] (masa: 64.02) - na adresu 2, sa prioritetom 99
2.) Riverside Spineflower [velit vivamus vel nulla eget eros elementum] (masa: 89.23) - na adresu 6, sa prioritetom 97
3.) Skeletongrass [integer ac leo pellentesque ultrices] (masa: 96.06) - na adresu 6, sa prioritetom 97
4.) Cypress Graphina Lichen [et tempus semper est quam pharetra magna ac consequat] (masa: 99.72) - na adresu 5, sa prioritetom 94
5.) Hybrid Willow [posuere cubilia curae duis faucibus accumsan odio] (masa: 46.09) - na adresu 4, sa prioritetom 88
6.) Climbing Bedstraw [cum sociis natoque penatibus et magnis dis parturient] (masa: 82.73) - na adresu 7, sa prioritetom 88
7.) Shinyleaf Spirea [amet erat nulla tempus vivamus in felis eu] (masa: 89.11) - na adresu 5, sa prioritetom 85
8.) Neolloydia [sagittis sapien cum sociis natoque] (masa: 37.94) - na adresu 4, sa prioritetom 77
9.) Arkansas Alumroot [rhoncus sed vestibulum sit amet cursus] (masa: 63.50) - na adresu 3, sa prioritetom 74
10.) Field Pumpkin [in magna bibendum imperdiet nullam] (masa: 39.06) - na adresu 7, sa prioritetom 67
11.) Leatherweed [faucibus orci luctus et ultrices] (masa: 45.20) - na adresu 2, sa prioritetom 67
12.) Bigseed Alfalfa Dodder [viverra pede ac diam cras] (masa: 63.19) - na adresu 5, sa prioritetom 65
13.) Island Babyboot Orchid [ante ipsum primis in faucibus] (masa: 5.58) - na adresu 2, sa prioritetom 50
14.) Common Hop [nulla nunc purus phasellus in felis donec] (masa: 90.44) - na adresu 5, sa prioritetom 46
15.) Pale Sage [porttitor id consequat in consequat ut nulla] (masa: 81.53) - na adresu 2, sa prioritetom 41
16.) West Virginia Blackberry [semper sapien a libero nam dui proin leo odio] (masa: 37.01) - na adresu 7, sa prioritetom 34
17.) Winged Sandpuffs [lorem integer tincidunt ante vel] (masa: 87.60) - na adresu 4, sa prioritetom 32
18.) Rattlebox [malesuada in imperdiet et commodo] (masa: 6.73) - na adresu 6, sa prioritetom 23
19.) Columbian Onion [lorem id ligula suspendisse ornare consequat] (masa: 81.65) - na adresu 4, sa prioritetom 23
20.) Smooth Azalea [vestibulum rutrum rutrum neque aenean auctor gravida] (masa: 92.60) - na adresu 2, sa prioritetom 17
21.) Clove [phasellus in felis donec semper sapien a libero] (masa: 56.94) - na adresu 6, sa prioritetom 15
22.) Blackish Oxytrope [ut at dolor quis odio] (masa: 95.90) - na adresu 5, sa prioritetom 13
23.) Knotted Hedgeparsley [commodo vulputate justo in blandit ultrices enim] (masa: 43.46) - na adresu 3, sa prioritetom 13
24.) Thickleaf Yerba Santa [lacus curabitur at ipsum ac tellus semper] (masa: 67.58) - na adresu 7, sa prioritetom 7
25.) Sierra Skullcap [enim sit amet nunc viverra dapibus] (masa: 63.00) - na adresu 7, sa prioritetom 3
26.) Wild Sweetwilliam [suscipit ligula in lacus curabitur at ipsum ac tellus] (masa: 97.69) - na adresu 7, sa prioritetom 2
27.) Wright's Goldenrod [et ultrices posuere cubilia curae donec pharetra magna] (masa: 53.44) - na adresu 7, sa prioritetom 2
28.) Rough Dubautia [ante ipsum primis in faucibus orci luctus et ultrices] (masa: 76.24) - na adresu 6, sa prioritetom 2

U vozilo su ubačeni sljedeći paketi:
1.) Sage [sit amet cursus id turpis integer aliquet massa id lobortis] (masa: 64.02) - na adresu 2, sa prioritetom 99
2.) Riverside Spineflower [velit vivamus vel nulla eget eros elementum] (masa: 89.23) - na adresu 6, sa prioritetom 97
3.) Skeletongrass [integer ac leo pellentesque ultrices] (masa: 96.06) - na adresu 6, sa prioritetom 97

Kretanje vozila:
----------------
1.)Pocetni cvor: 1
 Ciljni cvor: 2
 Tezina putanje: 3
Iz vozila se istovaraju sljedeci paketi:
1.) Sage (masa: 64.02, prioritet: 99)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
2.)Pocetni cvor: 2
 Ciljni cvor: 3
 Tezina putanje: 7
Iz vozila se istovaraju sljedeci paketi:
~NEMA PAKETA ZA ISPORUKU NA OVOJ ADRESI!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
3.)Pocetni cvor: 3
 Ciljni cvor: 4
 Tezina putanje: 9
Iz vozila se istovaraju sljedeci paketi:
~NEMA PAKETA ZA ISPORUKU NA OVOJ ADRESI!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
4.)Pocetni cvor: 4
 Ciljni cvor: 5
 Tezina putanje: 11
Iz vozila se istovaraju sljedeci paketi:
~NEMA PAKETA ZA ISPORUKU NA OVOJ ADRESI!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
5.)Pocetni cvor: 5
 Ciljni cvor: 6
 Tezina putanje: 14
Iz vozila se istovaraju sljedeci paketi:
1.) Riverside Spineflower (masa: 89.23, prioritet: 97)
2.) Skeletongrass (masa: 96.06, prioritet: 97)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
6.)Pocetni cvor: 6
 Ciljni cvor: 7
 Tezina putanje: 20
Iz vozila se istovaraju sljedeci paketi:
~NEMA PAKETA ZA ISPORUKU NA OVOJ ADRESI!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

=>Putanja kretanja vozila: 1->2->3->4->5->6


Ukupan broj paketa koji su se nalazili u posti: 28
Broj uspjesno dostavljenih paketa: 3
Broj neisporucenih paketa: 25

=>Procenat dostavljenih paketa: 10.71[%]
```

## Upotrebljeni algoritmi i strukture
* Floyd-Warshall algoritam - za pronalaženje najkraćih putanja između svih adresa
* Prioritetni red (heap) - za sortiranje paketa po prioritetu i masi
* Strukture grafa i reda - za modelovanje mreže grada i poštanskog sistema

# Autorska prava 
© 2025 Aleksandra Vučićević
