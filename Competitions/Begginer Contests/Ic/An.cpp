#include <bits/stdc++.h>



using namespace std;



string magic() {

    map<char,unsigned>  dp;



    dp['A'] = 2;

    dp['B'] = 2;

    dp['C'] = 2;

    dp['D'] = 3;

    dp['E'] = 3;

    dp['F'] = 3;

    dp['G'] = 4;

    dp['H'] = 4;

    dp['I'] = 4;

    dp['J'] = 5;

    dp['K'] = 5;

    dp['L'] = 5;

    dp['M'] = 6;

    dp['N'] = 6;

    dp['O'] = 6;

    dp['P'] = 7;

    dp['R'] = 7;

    dp['S'] = 7;

    dp['T'] = 8;

    dp['U'] = 8;

    dp['V'] = 8;

    dp['W'] = 9;

    dp['X'] = 9;

    dp['Y'] = 9;



    string str;

    getline(cin, str);

    // remoção de espaços em branco e -

    str.erase(std::remove(str.begin(), str.end(), '-'),str.end());

    str.erase(std::remove(str.begin(), str.end(), ' '),str.end());

    // convertendo não difitos em digitos

    for(int i = 0; i < str.size();i++)

        if(!isdigit(str[i]))

            str[i] = '0' +  dp[str[i]];

    str.insert(3, "-");

    return str;

}



void simulation() {

    int n;

    cin >> n;

    cin.ignore(256, '\n');

    vector<string> str(n);

    for(int i = 0; i < n; i++)

        str[i] = magic();

    sort(str.begin(), str.end());

    int p = 0;

    int result = false;

    // como ordenei consigo contar a ocorrencia dessa forma

    for(int i = 0;i < n - 1; i++){

        if(str[i] == str[i + 1]) {

            p++;

            result = true;

        }

        else {

            if(p > 0) cout << str[i] << " " << p + 1 << endl;

            p = 0;

        }

    }

    if(!result) cout << "No duplicates." <<endl;



}



int main() {

    int n;

    cin>>n;

    while(n--){

        simulation();

        if(n) cout << endl;

    }



}
