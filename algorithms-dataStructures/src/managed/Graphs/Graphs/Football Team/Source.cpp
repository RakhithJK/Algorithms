#define _CRT_SECURE_NO_WARNINGS
#include<array>
#include<numeric>
using namespace std;

#define banksN 1001

array<int, banksN>	money_in;
array<int, banksN>	money_out;
array<int, banksN>	money_diff;
int					banks, money, initialMoney = 0;

auto accumulateOnlyPositiveMoney = [](int accumulator, int current) {
	return current >= 0 ? accumulator + current : accumulator;
};

int main() {
	int tests = 0;
	scanf("%d", &banks);
	while (banks) {
		tests++;
		fill(money_in.begin(), money_in.end(), 0);
		fill(money_out.begin(), money_out.end(), 0);
		fill(money_diff.begin(), money_diff.end(), 0);
		initialMoney = 0;
		for (int bank = 1; bank <= banks; bank++)
		{
			for (int outBank = 1; outBank <= banks; outBank++) {
				scanf("%d", &money);
				money_out[bank]	  -= money;
				money_in[outBank] += money;
				initialMoney	  += money;
			}
		}
		for (int bank = 1; bank <= banks; bank++)
			money_diff[bank] = money_out[bank] + money_in[bank];
		auto reducedMoney = accumulate(money_diff.begin(), money_diff.end(), 0, accumulateOnlyPositiveMoney);
		printf("%d. %d %d\n", tests, initialMoney, reducedMoney);
		scanf("%d", &banks);
	}
	return 0;
}