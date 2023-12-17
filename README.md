# CatRat

CatRat är mer eller mindre en klon av PacMan, skrivet i C++ med SFML för de visuella delarna. Du spelar som en råtta med målet att äta upp alla ostar som finns på spelplanen, utan att bli uppäten av de katter som cirkulerar. Det finns även råttfällor utplacerade. Dessa kan du passera genom, men var medveten om att du tar skada av dem. Passerar du genom tre stycken... du kan lista ut vad som händer då.

## Kontroller
Under spelets gång är det dessa kontroller som gäller:

|  Knapp |     Händelse     |
|:------:|:----------------:|
| W \| ↑ |  Riktning uppåt  |
| S \| ↓ |  Riktning nedåt  |
| A \| ← | Riktning vänster |
| D \| → |  Riktning höger  |
|   ESC  |   Avsluta spel   |

## Banor
Alla banor finns sparade under mappen ```map``` i filer med ändelsen ```catrat```. Dessa filer innehåller en rad olika tecken i den formen som den aktuella banan kommer vara. Se tabellen nedan för en förklaring. 

| Tecken |    Betydelse   |
|:------:|:--------------:|
|    #   |      Vägg      |
|    _   |      Golv      |
|    !   |      Katt      |
|    *   |    Råttfälla   |
|    @   | Råtta(Spelare) |
|    $   |       Ost      |

