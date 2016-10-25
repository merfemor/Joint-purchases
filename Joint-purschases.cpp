#include <iostream>
#include <string>
#include <map>
using namespace std;

map <string, map <string, double> > give; // здесь в итоге хранится кто сколько кому должен
map <string, double> buyers; // здесь промежуточно хранятся задолженнности каждого человека
// если second > 0, то человеку кто-то должен, если second < 0 человек кому-то должен

int main()
{
	// формат ввода: название стоимость количество_человек имя_первого_человека сколько_заплатил_первый_человек имя_второго_человека сколько_заплатил_второй...
	freopen("input.in", "r", stdin);
	while (true)
	{
		string name;
		cin >> name;
		if (name == "") // если нечего не введено, то файл кончился
			break;
		double cost;
		cin >> cost;
		int buyersNum;
		cin >> buyersNum;
		double sumPaid = 0, evereonePaid = cost / buyersNum;
		for (int i = 0; i < buyersNum; i++)
		{
			string s;
			double paid;
			cin >> s >> paid;
			buyers[s] += (paid - evereonePaid); // добавляем в буфер долгов этого человека долг (сколько_заплатил - сколько_должен_запалить)
			sumPaid += paid; // для расчета того, сколько суммарно заплатили
		}
		if (abs(sumPaid - cost) > 0.001) // если суммарно заплатили не столько же, сколько и стоимость
		{
			cout << "Error! Code 1: sum of paid must be = price!";
			system("pause >> void");
			
			return 0;
		}
	}
	auto it = buyers.begin(); // для хождения по буферу и поиску кредитора
	while (buyers.size() > 0)
	{
		double debt1 = it->second; // задолженность текущего человека
		if (abs(debt1) < 0.01) // округление до копеек
		{
			auto it1 = it;
			it++;
			buyers.erase(it1);
			continue;
		}
		if (debt1 > 0) // если ему должны (это кредитор)
		{
			for (auto debtor = buyers.begin(); debtor != buyers.end(); debtor++) // ищем дебитора, который вернет часть своего долга
			{
				double debt2 = debtor->second; // задолженность текущего человека
				if (debt2 > 0) // таких же кредиторов пропускаем
					continue;
				if (-debt2 < debt1) // если долг дебитора меньше займа кредитора
				{
					give[it->first][debtor->first] += (-debt2); // добавляем в итог
					debt1 += debt2; // изменяем займ кредитора  
					it->second += debt2; // изменяем займ кредитора в буфере
					auto _debtor = debtor++; // создаем копию итератора на дебитора, а оригинал переводим на следующего человека
					buyers.erase(_debtor); // дебитор полностью вернул долги, убираем его
				}
				else if (abs(debt1 + debt2) < 0.01) // debt1 == debt2
				{
					give[it->first][debtor->first] += (-debt2);
					debt1 += debt2;
					it->second += debt2;
					auto _debtor = debtor;
					debtor++;
					buyers.erase(_debtor); // дебитор полностью погасил долги
					auto _it = it++;
					buyers.erase(_it); // кредитору вернули все необходимые деньги
					break;
				}
				else
				{
					give[it->first][debtor->first] += debt1;
					debtor->second += debt1; // дебитор отдал часть денег, записываем это
					auto _it = it++;
					buyers.erase(_it); // кредитор получил все деньги, убираем его из буфера
					break;
				}
			}
			it = buyers.begin(); // иначе начинаем поиск кредитора с начала
			continue;
		}
		it++; // переходим к следующей персоне
	}
	for (auto it1 = give.begin(); it1 != give.end(); it1++)
	{
		for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
		{
			cout << it1->first << " <- " << it2->first << " | ";
			printf("%.2f\n", it2->second);
		}
	}
	system("pause >> void");
	return 0;
}