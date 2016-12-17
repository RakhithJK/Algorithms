#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

vector<string> words;

bool rimujuLiSe(const string& kraca, const string& dulja) {
	auto postojiLiZajednickiSufiks1 = dulja.find(kraca);
	auto sameLength = kraca.size() == dulja.size();

	if (postojiLiZajednickiSufiks1 == string::npos && !sameLength)
		return false;

	else if (postojiLiZajednickiSufiks1 != string::npos && !sameLength) {
		auto sufiks = dulja.substr(postojiLiZajednickiSufiks1, kraca.size());
		return sufiks.size() == dulja.size() || sufiks.size() == dulja.size() - 1;
	}


	auto kracaBezPrvog = kraca;
	kracaBezPrvog.erase(0, 1);
	auto postojiLiZajednickiSufiks2 = dulja.find(kracaBezPrvog);

	if(postojiLiZajednickiSufiks2 != string::npos)
	{
		auto sufiks = dulja.substr(postojiLiZajednickiSufiks2, kraca.size());
		return sufiks.size() == dulja.size() || sufiks.size() == dulja.size() - 1;
	}
	
	return false;
}

vector<string> rjesenja;
vector<string> bio; // mozda zatriba
void konstruirajRekurzivno(const string& trenutnaRijec) {
	vector<string> rijeciIsteDuljineKaoTrenutna;
	vector<string> rijeciVeceza1OdTrenutna;

	bool bioPrije = static_cast<int>(count(bio.begin(), bio.end(), trenutnaRijec)) == 1;
	if(bioPrije)
		return;

	rjesenja.push_back(trenutnaRijec);
	bio.push_back(trenutnaRijec);

	for_each(words.begin(), words.end(), [&](string& word)
	{
		if(word.size() == trenutnaRijec.size() && word != trenutnaRijec)
			rijeciIsteDuljineKaoTrenutna.push_back(word);
		if (word.size() == trenutnaRijec.size() + 1)
			rijeciVeceza1OdTrenutna.push_back(word);
	});

	if(rijeciIsteDuljineKaoTrenutna.size() > 0) {
		int brojOstalihRijeci = rijeciIsteDuljineKaoTrenutna.size();
		for (auto rijec : rijeciIsteDuljineKaoTrenutna) {

			bool bioPrijeNaRijeci = static_cast<int>(count(bio.begin(), bio.end(), rijec)) == 1;
			if(!bioPrijeNaRijeci)
			{
				const string& rhs = rijec;
				auto rimuju = rimujuLiSe(trenutnaRijec, rhs);

				bool bioNaProsloj = static_cast<int>(count(bio.begin(), bio.end(), rijec)) == 1;
				if (rimuju && brojOstalihRijeci && !bioNaProsloj)
					konstruirajRekurzivno(rijec);
			}
			brojOstalihRijeci--;
		}
	}

	if(rijeciVeceza1OdTrenutna.size() > 0) {
		int brojOstalihRijeci = rijeciVeceza1OdTrenutna.size();
		for (auto rijec : rijeciVeceza1OdTrenutna) {
			string& rhs = rijec;
			auto rimuju = rimujuLiSe(trenutnaRijec, rhs);

			if (rimuju && brojOstalihRijeci)
				konstruirajRekurzivno(rijec);
			brojOstalihRijeci--;
		}
	}
}

int pronadjiNajduljuRimuRijeci() {
	sort(words.begin(), words.end(), [](const string& lhs, const string& rhs) { return lhs.size() < rhs.size();  });
	vector<vector<string>> svaRjesenja;

	for (int i = 0; i< words.size(); i++)
	{
		konstruirajRekurzivno(words[i]);
		if (rjesenja.size())
		{
			svaRjesenja.push_back(rjesenja);
			rjesenja.clear();
		}
	}

	auto solution = *max_element(svaRjesenja.begin(), svaRjesenja.end(), [](const vector<string>& lhs, const vector<string>& rhs) { return lhs.size() < rhs.size(); });
	return solution.size();
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string temp;
		cin >> temp;
		words.push_back(temp);
	}
	cout << pronadjiNajduljuRimuRijeci() << endl;
}