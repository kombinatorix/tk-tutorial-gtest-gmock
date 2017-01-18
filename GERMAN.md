# Das deutsche Tutorial #

Damit wir uns Tipparbeit sparen, wird die Variable `${GTEST_DIR}` mit dem Pfad zum googletest-Ordner gesetzt. Dazu füge in der `~/.bashrc` folgende Zeile hinzu.

	export GTEST_DIR = Pfad/zum/Ordner/googletest/googletest/

Danach musst du in der Kommandozeile einmal `source ~/.bashrc` ausführen, damit der Befehl geladen wird.

Da Google Mock auf Google Test aufbaut, werden wir uns zuerst mit Google Test beschäftigen.

## Google Test ##

Google Test ist eine Modultest(Unittest)-Bibliothek für C++. Die grundlegende Struktur basiert auf der xUnit-Architektur.
Für Google Test ist die Struktur in der folgenden Tabelle aufgeführt.

| Komponente   | Erklärung                                                                                      |
|--------------|------------------------------------------------------------------------------------------------|
| Assertion    | Prüft, ob eine Bedingung wahr ist.                                                        |
| Test         | Nutzt Assertions, um das Verhalten des Codes zu prüfen.                                       |
| Test case    | Besteht aus mindestens einem Test. Es soll die Struktur des zu testenden Codes widerspiegeln. |
| Test fixture | Setzt die Umgebung(svariablen), so dass Tests dies nicht immer selbst machen müssen.           |
| Test program | Besteht aus mindestens einem Testcase. Lässt diese durchlaufen.                                |

Wie man der Tabelle entnehmen kann, sieht die Struktur eines Minimalbeispiels wie folgt aus:

	Test program( Test case ( Test ( Assertion ( ... ) ) ) )

Wir arbeiten uns nun von der kleinsten Einheiten, den Assertions, zu dem großen Ganzen - dem Testprogramm - vor.

### Assertions ###

Allgemein gesprochen ist eine Assertion eine Bedingungsüberprüfung, die eine von drei Zuständen zurückmeldet: **success**, **nonfatal failure** oder **fatal failure**.

Es ist zwar einfach, einen Erfolg festzustellen, aber Google Test hat keine Möglichkeit, abzuleiten, ob ein Fehler fatal ist oder nicht.
Dies muss der Benutzer selbst festlegen. Deshalb gibt es **2** Typen von Assertions:

|Typ     |Erfolg|Fehler          |
|:-------|:-----|:---------------|
| ASSERT |success|fatal failure   |
| EXPECT |success|nonfatal failure|

Mehr Informationen brauchen wir nicht für unseren ersten Test. Hierzu nutzen wir ein erstes Beispielprogramm:

<table align="center">
<tr>
<td>
	prog1.hpp
</td>
<td>
	prog1.cpp
</td>
</tr>
<tr>
<td valign="top">
	<pre lang = "C++">
	#ifndef __prog1__hpp__
	#define __prog1__hpp__

	int add(short a, short b);


	#endif
	</pre>
</td>
<td valign="top">
<pre lang = "C++">
	#include "include/prog1.hpp"
	#include <iostream>

	int add(short a, short b){
	    return static_cast< int >(a+b);
	}
</pre>
</td>
</tr>
</table>

Das Programm macht nichts anderes, als zwei shorts zu addieren und die Summe als Integer zurückzuliefern.
Für das Programm, dass unsere Addition testet, müssen wir noch eine statische Bibliothek erzeugen. Zuerst
erstellen wir dafür eine Objektdatei *.o*:

```bash
g++ -isystem ${GTEST_DIR}/include -pthread -c prog1.cpp
```

Auch wer schon mal mit g++ ein Programm kompiliert hat, kennt nicht umbedingt das Flag `-isystem`. Mit diesem
Flag können Pfade für Systemheader angegeben werden. Und in unserem Fall möchten wir die Google Test Header
nutzen.
Außerdem nutzen wir das Flag `-pthread`, da Google Test Gebrauch von Threads macht.

Nun haben wir eine Objektdatei. Jetzt möchten wir eine statische Bibliothek haben. Diese können wir mit `ar` erzeugen:

```bash
ar -rv libgtest.a prog1.o
```

Für weitere Informationen über `ar` führe `man ar` in der Konsole aus.

Kommen wir nun zu unserem ersten Testprogram (*prog1_test1.cpp*):
```cpp
#include "include/prog1.hpp"
#include "gtest/gtest.h"

TEST(Addition, boring){

	ASSERT_EQ(2, add(1,1));

}

int main(int argc,char **argv){
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
```

Zuerst müssen wir den Header einbinden, der die zu testenden Funktionen enthält:

```cpp
	#include "include/prog1.hpp"
```

Außerdem muss in jedem Fall der Google Test-Header eingebunden werden:

```cpp
	#include "gtest/gtest.h"
```

Nun definieren wir unseren ersten Test. Ein Test hat immer folgende Struktur:

```cpp
TEST(NameDesTestCases, NameDiesesSpeziellenTest){

	//Hier steht der Testcode

}
```

Mit `NameDesTestCases` registriert man den folgenden Test beim Test case. Danach gibt man den Namen des Tests an.
Man sollte am besten auf Unterstriche `_` verzichten ([Erklärung](https://github.com/google/googletest/blob/master/googletest/docs/FAQ.md#why-should-not-test-case-names-and-test-names-contain-underscore)).  
Erst dann kommt der eigentliche Code zu testen. In unserem einfachen Fall hatten wir:

```cpp
	ASSERT_EQ(2, add(1,1));
```

Der Befehl `ASSERT_EQ( ... , ... )` prüft, ob das erste Argument mit dem zweiten übereinstimmt. Dabei ist die Reihenfolge
egal.

Der Code, der in der main-Funktion steht, ist ziemlich selbsterklärend. Bis auf wenige Zusätze bleibt dieser Code immer der selbe. Später
wird noch einmal darauf eingegangen.

Als nächstes muss das Testprogramm kompiliert werden. Dies geschieht mit:

```bash
g++ -isystem ${GTEST_DIR}/include -pthread prog1_test1.cpp libgtest.a -o prog1_test1 -lgtest
```

Hier ist wichtig, dass man das Flag `-lgtest` nicht vergisst. In der offiziellen README des Google Test Projekts fehlt dies.
Ohne das Flag gibt es jedoch einige Linkerfehler. Ansonsten muss man nur die Namen jeweils anpassen. Das betrifft die .cpp und die .a Datei, sowie
den Namen der Binary.

Gab es keine Probleme beim Kompilieren, kann das Testprogramm mit `./prog1_test1` ausgeführt werden. Es sollte dann folgenden Output geben:

```
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from Addition
[ RUN      ] Addition.boring
[       OK ] Addition.boring (0 ms)
[----------] 1 test from Addition (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 1 test.
```

Damit lief unser Test ohne Probleme durch. Das ist schön, aber wir haben noch nicht alle Fälle abgedeckt. So haben wir unseren
Input nicht überprüft. Dies kann zu Überläufen führen. Dies wird in *prog1_test2.cpp* überprüft:

```cpp
#include "include/prog1.hpp"
#include "gtest/gtest.h"

TEST(Addition, fail){

	ASSERT_EQ(120000, add(60000,60000));

}

int main(int argc,char **argv){
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
```

Jetzt müssen wir das Programm wieder kompilieren:

```bash
g++ -isystem ${GTEST_DIR}/include -pthread prog1_test2.cpp libgtest.a -o prog1_test2 -lgtest
```

Ausgeführt sollte es dann diesen Output geben:

```
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from Addition
[ RUN      ] Addition.fail
prog1_test2.cpp:6: Failure
      Expected: 120000
To be equal to: add(60000,60000)
      Which is: -11072
[  FAILED  ] Addition.fail (0 ms)
[----------] 1 test from Addition (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 0 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] Addition.fail

 1 FAILED TEST
```

Unser Test schlägt hier fehl. Aber Google Test versorgt uns mit mehr Informationen. So sehen an welcher Stelle (`prog1_test2.cpp:6: Failure`) das Programm fehlschlug. Außerdem wird uns gezeigt, welche Wert erwartet wurde und welchen Wert wir tatsächlich bekommen.

Ein weiteres nützliches Feature ist, dass man bei einer Assertion eine eigene Fehlermeldung mit dem Streamoperator anhängen kann. Siehe dazu das Beispielprogramm *prog1_test3.cpp*:

```cpp
// ...

TEST(Addition, fail){

	ASSERT_EQ(120000, add(60000,60000)) << "Hier gab es einen Bufferüberlauf und damit
											ein falsches Ergebnis von: " << add(60000,60000);

}

// ...
```

Oben haben wir schon davon gesprochen, dass es `ASSERT` und `EXPECT` gibt. Der Unterschied besteht darin, dass `ASSERT` sofort den Test beendet.
Bei einem Fehler in `EXPECT` können noch weitere Fehler zurückgemeldet werden. Um das zu demonstrieren, kann *prog1_test4.cpp* genutzt werden.


```cpp
#include "include/prog1.hpp"
#include "gtest/gtest.h"

TEST(Addition, failOne){
	ASSERT_EQ(120000, add(60000,60000));
	ASSERT_EQ(120000, add(60000,60000));
}
TEST(Addition, failTwo){
	EXPECT_EQ(120000, add(60000,60000));
	EXPECT_EQ(120000, add(60000,60000));
}
TEST(Addition, failThree){
	ASSERT_EQ(120000, add(60000,60000));
	EXPECT_EQ(120000, add(60000,60000));
}
TEST(Addition, failFour){
	EXPECT_EQ(120000, add(60000,60000));
	ASSERT_EQ(120000, add(60000,60000));
}

int main(int argc,char **argv){
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
```

Nach Kompilierung und Ausführung sehen wir, dass failOne und failThree nur einen Fehler zurückmelden, wobei failTwo und failFour 2 Fehler zurückmelden.

Da wir jetzt ein Gefühl dafür bekommen haben, was eine Assertion ist und wie sie benutzt wird, sollen im Folgenden die möglichen Ausprägungen vorgestellt werden.

#### Wahrheitswertige Assertions ####

Hier wird nur darauf geprüft, ob die Bedingung den richtigen Wahrheitswert hat.

| **Fatal assertion** | **Nonfatal assertion** | **Prüft** |
|:--------------------|:-----------------------|:----------|
| `ASSERT_TRUE(`_Bedingung_`)`;  | `EXPECT_TRUE(`_Bedingung_`)`;   | _Bedingung_ is wahr |
| `ASSERT_FALSE(`_Bedingung_`)`; | `EXPECT_FALSE(`_Bedingung_`)`;  | _Bedingung_ is falsch |

#### Binäre Vergleiche ####

Hier geht es um den binären Vergleich von zwei Werten.

| **Fatal assertion** | **Nonfatal assertion** | **Prüft** |
|:--------------------|:-----------------------|:----------|
|`ASSERT_EQ(`_Wert1_`, `_Wert2_`);`|`EXPECT_EQ(`_Wert1_`, `_Wert2_`);`| _Wert1_ `==` _Wert2_ |
|`ASSERT_NE(`_Wert1_`, `_Wert2_`);`|`EXPECT_NE(`_Wert1_`, `_Wert2_`);`| _Wert1_ `!=` _Wert2_ |
|`ASSERT_LT(`_Wert1_`, `_Wert2_`);`|`EXPECT_LT(`_Wert1_`, `_Wert2_`);`| _Wert1_ `<` _Wert2_ |
|`ASSERT_LE(`_Wert1_`, `_Wert2_`);`|`EXPECT_LE(`_Wert1_`, `_Wert2_`);`| _Wert1_ `<=` _Wert2_ |
|`ASSERT_GT(`_Wert1_`, `_Wert2_`);`|`EXPECT_GT(`_Wert1_`, `_Wert2_`);`| _Wert1_ `>` _Wert2_ |
|`ASSERT_GE(`_Wert1_`, `_Wert2_`);`|`EXPECT_GE(`_Wert1_`, `_Wert2_`);`| _Wert1_ `>=` _Wert2_ |

#### C-String Vergleiche ####

Hier geht es explizit um C-Strings, da normale Strings mit den binären Vergleichen abgedeckt werden.

| **Fatal assertion** | **Nonfatal assertion** | **Prüft** |
|:--------------------|:-----------------------|:----------|
| `ASSERT_STREQ(`_str1_`, `_str2_`);`    | `EXPECT_STREQ(`_str1_`, `_str_2`);`     | Beide C-Strings haben den gleichen Inhalt |
| `ASSERT_STRNE(`_str1_`, `_str2_`);`    | `EXPECT_STRNE(`_str1_`, `_str2_`);`     | Beide C-Strings haben unterschiedliche Inhalte |
| `ASSERT_STRCASEEQ(`_str1_`, `_str2_`);`| `EXPECT_STRCASEEQ(`_str1_`, `_str2_`);` | Beide C-Strings haben den gleichen Inhalte bei ignorierter Groß- und Kleinschreibung  |
| `ASSERT_STRCASENE(`_str1_`, `_str2_`);`| `EXPECT_STRCASENE(`_str1_`, `_str2_`);` | Beide C-Strings unterschiedliche Inhalte bei ignorierter Groß- und Kleinschreibung |

#### Explizite Rückgaben ####

|Assertion|Ergebnis|
|:--------|:-------|
|SUCCEED();|success|
|FAIL();|fatal failure|
|ADD_FAILURE();|nonfatal failure|
|ADD_FAILURE_AT(" Pfad_zur_Datei ", Zeilennummer );| nonfatal failure|

#### Exception Assertions ####

| **Fatal assertion** | **Nonfatal assertion** | **Verifies** |
|:--------------------|:-----------------------|:-------------|
| `ASSERT_THROW(`_Anweisung_, _exception\_type_`);`  | `EXPECT_THROW(`_Anweisung_, _exception\_type_`);`  | _Anweisung_ wirft eine Exception des gegebenen Typs  |
| `ASSERT_ANY_THROW(`_Anweisung_`);`                | `EXPECT_ANY_THROW(`_Anweisung_`);`                | _Anweisung_ wirft eine Exception irgendeines Typs        |
| `ASSERT_NO_THROW(`_Anweisung_`);`                 | `EXPECT_NO_THROW(`_Anweisung_`);`                 | _Anweisung_ wirft keine Exception            |

Für weitere Assertions gucke [hier](https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md#using-an-existing-boolean-function).

#### Assertions in Subroutinen ####

#### Death Tests ####

#### Übungen zu Assertions ####

Nun sollen einfache Tests mit Assertions geschrieben werden.

##### Übung 1 #####
Die erste Übung soll überprüfen, ob das Sortieren eines Vektors klappt.

<table align="center">
<tr>
<td>
	exercise1.hpp
</td>
<td>
	exercise1.cpp
</td>
</tr>
<tr>
<td valign="top">
	<pre lang = "C++">
#ifndef __example1__hpp__
#define __example1__hpp__

#include < vector >
#include < stdlib.h >
#include < time.h >

class goodandbadsort{
private:
	std::vector<int> randomNumbers;
public:
	goodandbadsort(int n);





	~goodandbadsort();

	std::vector<int> goodSort();





	std::vector<int> badSort();


};

#endif
	</pre>
</td>
<td valign="top">
<pre lang = "C++">



#include "include/exercise1.hpp"
#include < algorithm >






goodandbadsort::goodandbadsort(int n){
		srand(time(NULL));
		for(int i=0; i<n; ++i){
			this->randomNumbers.push_back(rand() % 100);
		}
}

goodandbadsort::~goodandbadsort(){}

std::vector<int> goodandbadsort::goodSort(){
	std::vector<int> tempVec = this->randomNumbers;
	 std::sort(tempVec.begin(),tempVec.end());
	return tempVec;
}

std::vector<int> goodandbadsort::badSort(){
	return this->randomNumbers;
}

</pre>
</td>
</tr>
</table>

Es sollen 3 Tests für einen 10 Elemente großen Vektor geschrieben werden:

1.	Sortiert **goodSort** aufsteigend?
2.	Sortiert **badSort** aufsteigen?
3.	Überprüfe **badSort** durch **goodSort**.

Für den Test kann folgende Vorlage (*exercise1_test.cpp*) genutzt werden:

```cpp
#include "include/exercise1.hpp"
#include "gtest/gtest.h"

TEST(Sortierung, guteSortierung){
	// ausfuellen
}

TEST(Sortierung, schlechteSortierung){
	// ausfuellen
}

TEST(Sortierung, Vergleich){
	// ausfuellen
}

int main(int argc,char **argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
```

Eine Beispiellösung stellt die *exercise1_test_solution.cpp* zur Verfügung.

##### Übung 2 #####

Einen wichtigen Bereich, den Tests immer abdecken sollen, ist die Überprüfung der Eingangsdaten.
So will man grundsätzlich, dass eine Funktion, falls sie **NULL** bzw einen **nullptr** übergeben bekommt, eine Exception schmeißt.

<table align="center">
<tr>
<td>
	exercise2.hpp
</td>
<td>
	exercise2.cpp
</td>
</tr>
<tr>
<td valign="top">
<pre lang = "C++">
#ifndef __exercise2__hpp__
#define __exercise2__hpp__

#include < exception >
struct NULLException : public std::exception {
	const char * what () const throw () {
		return "NULL Exception";
	}
};

void throws(int* a);





void throwsNot(int* a);

#endif
</pre>
</td>
<td valign="top">
<pre lang = "C++">



#include "include/exercise2.hpp"






void throws(int* a){
	if(!a){
		throw NULLException();
	}
}

void throwsNot(int* a){}


</pre>
</td>
</tr>
</table>

Schreibe 2 Tests:

1. Überprüfe, ob throws eine NULLException wirft.
2. Überprüfe, ob throwsNot eine NULLException wirft.

Nutze dazu die Vorlage (*excercise2_test.cpp*):

```cpp
#include "include/exercise2.hpp"
#include "gtest/gtest.h"

TEST(NULLException, throwsException){
	int* ptr = nullptr;
	// ausfuellen
}

TEST(Sortierung, throwsNoException){
	int* ptr = nullptr;
	// ausfuellen
}


int main(int argc,char **argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
```

### Test Fixtures ###

Je mehr Tests man schreibt, desto häufiger kommt es vor, dass man auf gleiche oder ähnliche Daten zugreift. Damit man diese
nicht für jeden Test neu definieren muss, kann man ein *Test Fixture* nutzen. Dies erlaubt die einfach Mehrfachnutzung.

Um ein Test Fixture zu erzeugen, sind 5 Punkte zu beachten:

1.	Leite das Fixture von `::testing::Test` ab.
	*	Der Body muss mit `public:` oder `protected:` starten, da wir auf auf Member von Subklassen zugreifen werden.
2.	In der Klasse müssen alle Objekte, die verwendet werden sollen, deklariert werden.
3.	Wenn benötigt, dann muss man einen Default-Konstruktor oder `SetUp()` schreiben, damit die Objekte richtig initialisiert werden.
	*	**C++ ist case-sensitive!** Achte darauf, dass du nicht `setup()` oder `Setup()` schreibst.
4.	Wenn benötigt, dann muss man einen Default-Destruktor oder `TearDown()` schreiben, damit die Objekte richtig gelöscht werden.
	*	Wann man Konstruktoren/Destruktoren nutzt und wann `SetUp()`/`TearDown()` kann [hier](https://github.com/google/googletest/blob/master/googletest/docs/FAQ.md#should-i-use-the-constructordestructor-of-the-test-fixture-or-the-set-uptear-down-function) nachgelesen werden.
5.	Wenn benötigt, schreibe Subroutinen.

Wie sieht also die Struktur einer Fixture-Klasse aus?

```cpp
class KlasseTest : public ::testing::Test{
	protected: // kann auch public sein
		virtual void SetUp(){

			// Code

		}

		virtual void TearDown(){

			// Code

		}

		// Deklarierung der Variablen
}
```

Jetzt muss das Google Test auch wissen, dass wir das Test Fixture für einen Test nutzen wollen, deshalb ersetzen wir `TEST` durch `TEST_F`, das führt dan zu:

```cpp
TEST_F(KlasseTest, Testname){

	// Code

}
```

Beachte, dass `KlasseTest` dem Namen der Fixture-Klasse entspricht.

##### Übung 3 #####

### Ergänzende Möglichkeiten Tests laufen zu lassen ###

Google Test lässt grundsätzlich alle Tests durchlaufen. Das ist aber gerade für größere Projekte nicht immer sinnvoll. Um das Verhalten des Testprogramms zu ändern, gibt es es Flags, die man im Quellcode setzen kann. Zusätzlich lassen sich alle Flags auch über die Kommandozeile überschreiben.

Die zur Verfügung stehenden Flag erhält man, indem man an das ausführbare Testprogramm das Flag `--help`, `-h`, `-?` oder `/?` anhängt.

Will man das Flag `--gtest_foo` in der main-Funktion lesen oder setzen, geschieht dies über `::testing::GTEST_FLAG(foo)`.
Prototypisch sieht es so aus:

```cpp
int main(int argc, char** argv) {

  // Schaltet das foo-Flag aus
  ::testing::GTEST_FLAG(foo) = false;

  // Hier können die gesetzten Flags über die Kommandozeile überschrieben werden.
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
```

Für die [Testauswahl](#testauswahl) sind folgende Flags verfügbar:

1.	`--gtest_list_tests`
2.	`--gtest_filter=POSTIVE_PATTERNS[-NEGATIVE_PATTERNS]`
3.  `--gtest_also_run_disabled_tests`

Für die [Testausführung](#testausführung) sind folgende Flags verfügbar:

1.	`--gtest_repeat=[COUNT]`
2.	`--gtest_shuffle`
3.	`--gtest_random_seed=[NUMBER]`

Für den Testoutput sind folgende Flags verfügbar:

1.	`--gtest_color=(yes|no|auto)`
2.	`--gtest_print_time=0`
3.	`--gtest_output=xml[:DIRECTORY_PATH/|:FILE_PATH]`
4.	`--gtest_stream_result_to=HOST:PORT`

Für Assertionverhalten sind folgende Flags verfügbar:

1.	`--gtest_death_test_style=(fast|threadsafe)`
2.	`--gtest_break_on_failure`
3.	`--gtest_throw_on_failure`
4.	`--gtest_catch_exceptions=0`



#### Testauswahl ####

Das Flag `--gtest_list_tests` überschreibt alle anderen Flags und der Output sieht dann wie folgt aus:

```
TestCase1.
	TestName1
	TestName2
	TestName3
	...
	TestNameL
...
TestCaseM.
	TestName1
	TestName2
	...
	TestNameN
```

Mit dem Flag `--gtest_filter` kann gesteuert werden, welche Test ausgeführt werden sollen. Zur besseren Kontrolle gibt es reservierte Zeichen:

| Zeichen | Effekt |
|:--------|:-------|
|`?`| Entspricht einem beliebigen Zeichen |
|`*`| Entspricht einem beliebigen String |
|`-`| Schließt das nachfolgende Muster vom Test aus |
|`:`| Teilt Wildcard-Muster. Kann auch von einem `-` und einem `:` gefolgt werden (Negative Muster-Liste) |

Im folgenden gibt es ein paar Beispiele mit Effekt:

| Kommandozeile | Auswirkung |
|:--------------|:-----------|
|`./test` | Führt alle Tests aus. |
|`./test --gtest_filter=*` | Führt alle Tests aus. |
|`./test --gtest_filter=TestCase.*` | Führt alle Tests aus dem Test Case *TestCase* aus. |
|`./test --gtest_filter=*Foo*:*Bar*` | Führt alle Tests aus, die entweder *Foo* oder *Bar* enthalten. |
|`./test --gtest_filter=-*Foo*` | Führt alle Tests aus, die kein *Foo* beinhalten. |
|`./test --gtest_filter=TestCase.*-TestCase.Foo` | Führt alle Tests aus dem Test Case *TestCase* bis auf *Foo* aus. |

Mit dem Flag `--gtest_also_run_disabled_tests` werden auch ausgeschaltete Test ausgeführt. Manchmal ist ein Test in sich kaputt und soll ausgeschaltet werden.
Dies geht mit dem Präfix `DISABLED`:

```cpp
TEST(FooTest, DISABLED_Test) { ... }

class DISABLED_BarTest : public ::testing::Test { ... };

TEST_F(DISABLED_BarTest, Test) { ... }
```

**HINWEIS**: Ein `-` negiert **alles** was dahinter steht, auch was durch `:` abgetrennt wird! Das ist ein Fehler in den ich gelaufen bin.

##### Übung 4 #####

Ergänze das folgende Testprogramm (*exercise4_test.cpp*) so, dass es die Test wegfiltert, die fehlschlagen.

```cpp
#include "gtest/gtest.h"

TEST(Case1, Test1){
	SUCCEED();
}
TEST(Case1, Test2){
	SUCCEED();
}
TEST(Case1, Test3){
	FAIL();
}
TEST(Case1, Test4){
	SUCCEED();
}

TEST(Case2, Test1FAIL){
	FAIL();
}
TEST(Case2, Test2SUCCEED){
	SUCCEED();
}
TEST(Case2, Test3FAIL){
	FAIL();
}
TEST(Case2, Test4FAIL){
	FAIL();
}
TEST(Case2, Test5SUCCEED){
	SUCCEED();
}

TEST(TOTALFAIL, Test1){
	FAIL();
}
TEST(TOTALFAIL, Test2){
	FAIL();
}
TEST(TOTALFAIL, Test3){
	FAIL();
}

int main(int argc,char **argv){

	// Hier den Filter einfügen.

	::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
```

#### Testausführung ####

Manchmal muss man einen Test öfters ausführen. Z.B. hat man mehrere Threads und es könnten Raceconditions auftreten. Diese treten nicht immer auf, deshalb testet man öfter.
Dies kann mit `--gtest_repeat=Anzahl` realisiert werden. Ist `Anzahl` negativ, dann wird der Test ewig wiederholt.

Es kann auch angehen, dass Tests Abhängigkeiten aufweisen. Um diese aufzudecken, kann man die Tests zufällig durchführen. Dies wird mit `--gtest_shuffle` bewerkstelligt.
Möchte man immer die gleiche zufällige Reihenfolge haben, so kann man das Flag `--gtest_random_seed=SEED` nutzen. Dabei muss `SEED` eine natürliche Zahl zwischen 0 un 99999 sein. Die 0 ist besonders. Sie sagt, dass das Default-Verhalten durchgeführt werden soll. In diesem Verhalten wird der `SEED` aus der aktuellen Zeit berechnet.

In Kombination mit `--gtest_repeat=N` wird in jeder Durchführung ein zufälliger oder der gewählte `SEED` um 1 inkrementiert..  

##### Übung 5 #####

Als kleine Übung soll der das nächste Testprogramm (*exercise5_test.cpp*) 3 mal ausgeführt werden, startend mit einem `SEED` von 3.

```cpp
#include "gtest/gtest.h"

TEST(Case1, Test1){
	SUCCEED();
}
TEST(Case1, Test2){
	SUCCEED();
}
TEST(Case1, Test3){
	SUCCEED();
}
TEST(Case1, Test4){
	SUCCEED();
}

int main(int argc,char **argv){

	// Hier die Flags setzen

	::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
```


### Wert-parametrisierte Test ###

[Fürs erste hier](https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md#value-parameterized-tests)

##### Übung 6 #####

### Typisierte Tests ###

[Fürs erste hier](https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md#typed-tests)

##### Übung 7 #####

### Typ-parametrisierte Tests ###

[Fürs erste hier](https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md#type-parameterized-tests)

##### Übung 8 #####

### Testen von privatem Code ###

[Fürs erste hier](https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md#testing-private-code)

##### Übung 9 #####

### Nette zusätzliche Features ###


#### Fangen von Failures ####

[Fürs erste hier](https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md#catching-failures)


#### Der aktuelle Testname ####

[Fürs erste hier](https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md#getting-the-current-tests-name)


#### Erweitern von Google Test durch Handling Test Events ####

[Fürs erste hier](https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md#extending-google-test-by-handling-test-events)


## Google Mock ##
