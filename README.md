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

![obrazek klonu Arduino Micro][arduino-img] ![obrazek mikrofonu][mic-img] ![obrazek brzęczyka][buzzer-img] ![obrazek płytki stykowej][breadboard-img] ![obrazek przycisku][button-img] ![obrazek przewodów][wires-img]

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

## Plan działania
Aby ułatwić sobie pracę, przygotowałem listę czynności, które należy wykonać.
- [x] Zakup potrzebnych elementów.

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
