Inlämningsuppgift 0 (Treveckorsupprop), 'Hello world'
=====================================================

Denna inlämning gäller som treveckorsupprop. Lämnar du in den här uppgiften
visar du att du är aktiv i kursen vilket är ett krav. D.v.s, lämnar du inte in
den här uppgiften blir du struken.

Vad ska du göra?
----------------
Du ska ändra i filen `src/hello.cpp` så att den skriver ut det namn användaren
matat in istället för `Börje`. Du ska alltså ändra rad 14 så att det istället
för:
```cpp
  return std::string("Hello ") + myFavouritePersonInTheWorld + "!";
```
står:
```cpp
  return std::string("Hello ") + name + "!";
```

Du ska sedan zippa projeketet och lämna in på canvas. Instruktioner för detta
finns nedan.

Hur kompilerar jag och kör mitt program?
----------------------------------------
I mappen du fått finns det en makefil för att bygga och testa ditt program.
Bygg ditt program genom att köra `make clean all`.

Om du vill köra ditt program, skriv då `./app` på linux/macOS. Använder du WSL
på windows är det en liten linuxmaskin du jobbar i och då gör du som på linux.

Tester
------
Ett test som finns i katalogen `tests` kommer provköra din lösning för att se
att inlämningens regler är uppfyllda

För att testa ditt program med testet finns det ett make-mål (eng. make
target). Kör det genom skriva `make clean test` i terminalen när du står i
samma katalog som makefilen.

***Testerna används för att verifiera att din inlämning faktiskt fungerar.
Ändra därför inte i test-main.cpp utan skapa istället en egen .cpp om du vill
testa din inlämning***.

Hur man testar med `Catch` ligger utanför scopet för denna kurs. För den
nyfikne som vill prova kan man dock titta på Catchs dokumentation:
https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md

Inlämning
---------
När du är redo att lämna in kör du kommandot `make zip`. Du kommer då få en
zipfil i projektmappen. Det är den du ska lämna in på Canvas.

Felmeddelanden
--------------
Får du felmeddelanden i stil med>
```bash
make: tjorven: Command not found
make: *** [makefile:57: zip] Error 127
```

Betyder det att du saknar något program/verktyg, vilket program ser du av
felmeddelandet, i det här fallet är det programmet `tjorven` (det finns inget
sådant program, det är bara ett exempel).
