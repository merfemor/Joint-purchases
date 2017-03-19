#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

map <string, map <string, double> > result; // здесь в итоге хранится кто сколько кому должен
map <string, double> debts; // здесь  хранится состояние счета человека
// если second > 0, то человеку кто-то должен, если second < 0 человек кому-то должен

void calculateResult(); // ходит по debts и считает в reesult, кто кому сколько должен
void printResult();
void getPurchase(); // ввод очередной покупки

int main()
{
	//freopen("input.in", "r", stdin);
	while (true)
	{
		string s;
		cin >> s;
		if (s == "") // если ничего не введено, то ввод кончился
			break;
		getPurchase();
	}
	calculateResult();
	printResult();
	system("pause > NUL");
	return 0;
}

void getPurchase()
{
	double cost = 0;
	int buyersNum, consumersNum; // покупатели и потребители
	string name;
	cin >> buyersNum;
	for (int i = 0; i < buyersNum; i++)
	{
		double paid;
		cin >> name >> paid; // вводим имя и сколько заплатил
		debts[name] += paid;
		cost += paid; // для расчета того, сколько суммарно заплатили
	}
	cin >> consumersNum;
	double everyoneMustPay = cost / consumersNum; // сумма, которую каждый потребитель должен отдать
	for (int i = 0; i < consumersNum; i++)
	{
		cin >> name;
		debts[name] -= everyoneMustPay;
	}
}

void calculateResult()
{
	auto it = debts.begin(); // для хождения по буферу и поиску кредитора
	while (debts.size() > 0)
	{
		double debt1 = it->second; // задолженность текущего человека
		if (abs(debt1) < 0.01) // округление до копеек
		{
			auto it1 = it;
			it++;
			debts.erase(it1);
			continue;
		}
		if (debt1 > 0) // если ему должны (это кредитор)
		{
			for (auto debtor = debts.begin(); debtor != debts.end(); debtor++) // ищем дебитора, который вернет часть своего долга
			{
				double debt2 = debtor->second; // задолженность текущего человека
				if (debt2 > 0) // таких же кредиторов пропускаем
					continue;
				if (-debt2 < debt1) // если долг дебитора меньше займа кредитора
				{
					result[it->first][debtor->first] += (-debt2); // добавляем в итог
					debt1 += debt2; // изменяем займ кредитора  
					it->second += debt2; // изменяем займ кредитора в буфере
					auto _debtor = debtor++; // создаем копию итератора на дебитора, а оригинал переводим на следующего человека
					debts.erase(_debtor); // дебитор полностью вернул долги, убираем его
				}
				else if (abs(debt1 + debt2) < 0.01) // debt1 == debt2
				{
					result[it->first][debtor->first] += (-debt2);
					debt1 += debt2;
					it->second += debt2;
					auto _debtor = debtor;
					debtor++;
					debts.erase(_debtor); // дебитор полностью погасил долги
					auto _it = it++;
					debts.erase(_it); // кредитору вернули все необходимые деньги
					break;
				}
				else
				{
					result[it->first][debtor->first] += debt1;
					debtor->second += debt1; // дебитор отдал часть денег, записываем это
					auto _it = it++;
					debts.erase(_it); // кредитор получил все деньги, убираем его из буфера
					break;
				}
			}
			it = debts.begin(); // иначе начинаем поиск кредитора с начала
			continue;
		}
		it++; // переходим к следующей персоне
	}
}

void printResult()
{
	for (auto it1 = result.begin(); it1 != result.end(); it1++)
		for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
		{
			cout << it1->first << " <- " << it2->first << " | ";
			printf("%.1f\n", it2->second);
		}
}
