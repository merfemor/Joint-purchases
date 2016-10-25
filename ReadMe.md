## Формат ввода
* каждая новая покупка пишется на новой строке (необязательно, лишь для удобства)
* каждая покупка содержит:
  * наименование покупки (никак не участвует в расчёте)
  * число заплативших, допустим N
  * N пар из имени заплатившего и суммы, которую он заплатил
  * число потребителей, допустим M
  * M имен потребителей
* все имена, суммы, могут быть отделены любыми разделителями (пробелы, переносы строки)
* все имена должны быть в ASCII, N, M - натуральными числами, прочие суммы - рациональными положительными числами

### *Пример:*
    Supermarket-16october     2 Gena 300.50 Petr 100        3 Gena Leha Petr

Это значит, что была совершена покупка на общую сумму 400.50, 300.50 из которых заплатил Gena, и 100 заплатил Petr
Покупка была предназначена 3-м людям - Gena, Leha, Petr.

#### *Примечание:*
Если нужно ввести долг, а не покупку, то ввести его можно следующим способом:

    Dolg                   1 Gena 500         1 Petr

Т.е. как покупка, которую купил один для другого. В данном случае Petr оказывается должен Gena 500:

    Gena <- Petr | 500

## Вывод
* каждая новая задолженность выводится в новой строке
* формат вывода: *человек-которому-должен-заплатить <- человек-который-должен-заплатить | сумма*

### *Пример(вывод для примера ввода выше):*
    Gena <- Leha | 133.50
    Gena <- Petr | 33.50

Это значит, что Leha должен отдать Gena 133.50 и Petr должен Gena 33.50
