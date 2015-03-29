# Eclipse SVN - mały tutorial #

# Instalacja #
  1. Instalujemy Eclipsa (to jest jasne)
  1. Instalacja plugin'u Google
    * Trzeba wejść na http://code.google.com/intl/pl/eclipse/docs/getting_started.html   i skopiować link pod wersją która zainstalowaliśmy.
    * W Eclipse z górnego panelu Help>Install new software... > work with: i tutaj     wklejamy adres i enter
    * Zaznaczamy Google plugin for eclipse i Next/Ok/I agree/Finnish itp.
  1. Instalacja plugin'u SVN
    * W Eclipse z górnego panelu Help>Install new software... > work with: i tutaj wybieramy z rozwijanej listy download.eclipse.org/releases/(Galileo,Helios,Indigo)
    * Następnie poniżej rozwijamy Collaboration i zaznaczamy Subversive SVN Team provider i Subversive revision graph.
    * Next/Ok/I agree/Finnish itp.
  1. Dodawanie repozytorium
    * **WAŻNE!** W którymś momencie wyskoczy okienko eclipsa z zapytaniem o użytkownika i hasło, uzytkownik: login z gmail, hasło generujemy ze stronki projektu http://code.google.com/p/distributed-system-for-mobile-agents-coordination/ > Source > i tam gdzies jest "When prompted, enter your generated googlecode.com password." klikamy i generowane jest hasło, które kopiujemy do eclipsa.
    * Po restartach związanych z nowymi pluginami pojawia nam się w górnych panelach ikonka Google klikamy > Import Google hosted project > logowanie na Google
    * Tutaj powinien być dostępny projekt distributed-system-for-mobile-agents-coordination Next > Next > !!Cancel!!
    * Jeżeli jeszcze nie jesteśmy w widoku SVN Repository browser to z panelu górnego Window > Show view > SVN Repository browser i tam jest nasze repo
    * rozwijamy repo, branches i każda cześc projektu ma swojego brancha, klikamy na swoim prawym i wybieramy Find/Checkout as, później Finnish i mamy projekt w eclipsie. Starałem się wszystko ułatwić, więc nazwa projektu, ikonki do make'owania są dodane. Jedyne co trzeba zrobić to dodać w Run/Debug configuration uruchamianie binarek. Oprócz normalnych ustawień w zakładce Arguments trzeba zmienić working directory na twoj/projekt/...!/bin! bo binarki są w tym katalogu


# ABC Eclipse SVN #
Nie wiem czy to jest potrzebne, nikt nie protestował kiedy zaproponowałem Eclipsa, więc pewnie zbędne, aaaale...:
  * ogólnie wszystko związane z SVN jest pod w części team (po kliknięciu prawym przyciskiem na pliku)
  * **Dodawanie nowego pliku/katalogu**: prawy > Team > Add to version control i prawy > Team > Commit + dodanie komentarza
  * **Zatwierdzanie zmian**: prawy > Team > Commit + dodanie komentarza
  * **Ściągnięcie zmian innych**: prawy > Team > Update
  * **Łączenie zmian (mergowanie)**: prawy > Team > Synchronize with repository, nie zawsze jest to wygodne, ja raczej ściągam najnowaszą wersję i robie merga z poziomu eclipsa a potem tylko commit.
  * **Ściąganie całego projektu**: prawy > Team > Find/Checkout as