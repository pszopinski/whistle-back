# Whistle Back
Urządzenie nasłuchujące melodię z otoczenia i odwzorowujące ją za pomocą 
brzęczyka.


## Potrzebne elementy
W projekcie wykorzystuję:
* [klon Arduino Micro][arduino-ali] wyposażony w mikrokontroler [ATmega32U4][atmega] i 2,5&nbsp;kB pamięci SRAM,
* [mikrofon elektretowy ze wzmacniaczem MAX4466][mic-ali] pracujący z napięciem 2.4&nbsp;V &ndash; 5.5&nbsp;V,
* [brzęczyk piezoelektryczny][buzzer-ali] bez wbudowanego generatora sygnału,
* płytkę stykową z 400 otworami,
* przycisk monostabilny,
* przewody połączeniowe.

<a href="https://www.aliexpress.com/item/Micro-ATmega32U4-5V-16MHz-Pins-soldered-Compatible-with-Arduino-Micro-and-Leonardo/32676998690.html">![obrazek klonu Arduino Micro][arduino-img]</a><a href="https://www.aliexpress.com/item/New-Electret-Microphone-Amplifier-MAX4466-With-Adjustable-Gain-For-Arduino/32717091448.html">![obrazek mikrofonu][mic-img]</a><a href="http://www.robitshop.com/passive-buzzer-module">![obrazek brzęczyka][buzzer-img]</a><a href="https://www.aliexpress.com/item/V1NF-Hot-Sale-400-Points-Solderless-Bread-Board-Breadboard-PCB-Test-Board-Free-Shipping/32633859572.html">![obrazek płytki stykowej][breadboard-img]</a><a href="http://minielektro.dk/dip-tryk-knap.html">![obrazek przycisku][button-img]</a><a href="https://kamami.pl/13022-przewody-i-zlacza-do-arduino">![obrazek przewodów][wires-img]</a>

Zdecydowałem się wykorzystać platformę Arduino Micro między innymi dlatego, że pozwala na zasilanie urządzeń peryferyjnych napięciem 3,3&nbsp;V. Mikrofon zasilany takim napięciem charakteryzuje się większą czułością, niż w przypadku zastosowania napięcia 5&nbsp;V.


## Funkcjonalność
Urządzenie pracuje według następującego schematu.

1. Oczekiwanie na naciśnięcie przycisku.
2. Nagrywanie melodii z otoczenia.
3. Zakończenie nagrywania
  - po dwóch sekundach ciszy, lub
  - po 10 sekundach nagrywania.
4. Dla każdej z próbek czasowych:
  1. Przeprowadzenie transformaty Fouriera.
  2. Zapisanie odpowiedniego sygnału wyjściowego.
5. Odtworzenie sygnału wyjściowego.
6. Powrót do punktu 1.

## Lista zadań
Aby ułatwić sobie pracę, przygotowałem listę czynności, które należy wykonać.
- [x] Zakup potrzebnych elementów.
- [x] Implementacja rekurencyjnego algorytmu FFT w języku Python
- [x] Implementacja algorytmu Cooleya-Tukeya w języku C
- [x] Test współpracy klonu Arduino z Arduino IDE.
- [ ] Przylutowanie pinów modułu mikrofonu.
- [ ] Złożenie układu na płytce stykowej.
- [ ] Podstawowa obsługa przycisku.
- [ ] Podstawowa obsługa brzęczyka.
- [ ] Podstawowa obsługa mikrofonu.
- [ ] Obsługa rozpoczęcia i zakończenia nagrywania.
- [ ] Wykonywanie transformat Fouriera.
- [ ] Generowanie adekwatnego sygnału wyjściowego.

## Realizacja

## Źródła
Odnośniki na obrazkach prowadzą do ich źródła.

## Bibliografia
* [Fast Fourier Transforms](http://www.katjaas.nl/FFT/FFT.html) [dostęp: 2016-11-8]  
  obrazowe przedstawienie sposobu działania i implementacji algorytmu Colleya-Turkeya
* [Cooley&ndash;Tukey FFT algorithm](https://en.wikipedia.org/wiki/Cooley–Tukey_FFT_algorithm) [dostęp: 2016-11-8]  
  artykuł w Wikipedii
* [Szeregi i transformaty Fouriera](http://www.icsr.agh.edu.pl/~mownit/output/pdf/fourier.pdf) [dostęp: 2016-11-8]  
  notatki do wykładu z MOwNiT-u dra Bubaka
* R. Burden, J. Faires. Numerical Analysis. Edycja 9. Strony 547&ndash;557.  
  rozdział o szybkiej transformacie Fouriera

***

Paweł Szopiński
    
[arduino-ali]: https://www.aliexpress.com/item/Micro-ATmega32U4-5V-16MHz-Pins-soldered-Compatible-with-Arduino-Micro-and-Leonardo/32676998690.html
[atmega]: http://www.atmel.com/devices/atmega32u4.aspx
[mic-ali]: https://www.aliexpress.com/item/New-Electret-Microphone-Amplifier-MAX4466-With-Adjustable-Gain-For-Arduino/32717091448.html
[buzzer-ali]: https://www.aliexpress.com/item/Passive-Buzzer-Module-for-Arduino-AVR-PIC-Good-New-KY-006/32273623799.html

[arduino-img]: img/arduino.png
[mic-img]: img/mic.png
[buzzer-img]: img/buzzer.png
[breadboard-img]: img/breadboard.png
[button-img]: img/button.png
[wires-img]: img/wires.png
