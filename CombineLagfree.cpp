#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <bitset>
#include <windows.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>
#include <thread>
using namespace std;
void dianzi(vector<int> initVals, int maxLimit, int &maxVal, vector<int> &usedVals, vector<int> &order) {
    int n = initVals.size();
    maxVal = 0;
    sort(initVals.begin(), initVals.end());
    vector<vector<int>> orders = {initVals, vector<int>(initVals.rbegin(), initVals.rend())};
    vector<int> oddEvenOrder;
    for (auto initVals : orders) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                vector<int> tempInitVals = {initVals[i], initVals[j]};
                vector<int> tempOrder = {i + 1, j + 1};
                int newVal = initVals[i] + floor(initVals[j] / 2);
                if (newVal <= maxLimit && (newVal > maxVal || (newVal == maxVal && tempInitVals.size() < usedVals.size()))) {
                    maxVal = newVal;
                    usedVals = {initVals[i], initVals[j]};
                    order = tempOrder;
                }
                for (int k = 0; k < n; k++) {
                    if (k != i && k != j) {
                        tempInitVals.push_back(initVals[k]);
                        tempOrder.push_back(k + 1);
                        newVal = initVals[i] + floor(initVals[j] / 2);
                        newVal += floor(initVals[k] / 2);
                        if (newVal <= maxLimit && (newVal > maxVal || (newVal == maxVal && tempInitVals.size() < usedVals.size()))) {
                            maxVal = newVal;
                            usedVals = {initVals[i], initVals[j], initVals[k]};
                            order = tempOrder;
                        }
                        for (int l = 0; l < n; l++) {
                            if (l != i && l != j && l != k) {
                                tempInitVals.push_back(initVals[l]);
                                tempOrder.push_back(l + 1);
                                newVal = initVals[i] + floor(initVals[j] / 2);
                                newVal += floor(initVals[k] / 2) + floor(initVals[l] / 2);
                                if (newVal <= maxLimit && (newVal > maxVal || (newVal == maxVal && tempInitVals.size() < usedVals.size()))) {
                                    maxVal = newVal;
                                    usedVals = {initVals[i], initVals[j], initVals[k], initVals[l]};
                                    order = tempOrder;
                                }
                                for (int m = 0; m < n; m++) {
                                    if (m != i && m != j && m != k && m != l) {
                                        tempInitVals.push_back(initVals[m]);
                                        tempOrder.push_back(m + 1);
                                        newVal = initVals[i] + floor(initVals[j] / 2);
                                        newVal += floor(initVals[k] / 2) + floor(initVals[l] / 2);
                                        newVal += floor(initVals[m] / 2);
                                        if (newVal <= maxLimit && (newVal > maxVal || (newVal == maxVal && tempInitVals.size() < usedVals.size()))) {
                                            maxVal = newVal;
                                            usedVals = {initVals[i], initVals[j], initVals[k], initVals[l], initVals[m]};
                                            order = tempOrder;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void dizi(vector<int> initVals, int maxLimit, int &maxVal, vector<int> &usedVals, vector<int> &halfVals) {
    int n = initVals.size();
    maxVal = 0;
    int minCount = n + 1;
    for (int i = 1; i < pow(2, n); i++) {
        bitset<32> binaryVec(i);
        int tempSum = 0;
        for (int j = 0; j < n; j++) {
            if (binaryVec[j]) {
                tempSum += initVals[j];
            }
        }
        if (tempSum <= maxLimit && tempSum > maxVal) {
            maxVal = tempSum;
            usedVals.clear();
            halfVals.clear();
            for (int j = 0; j < n; j++) {
                if (binaryVec[j]) {
                    usedVals.push_back(initVals[j]);
                }
            }
            minCount = usedVals.size();
        } else if (tempSum <= maxLimit && tempSum == maxVal) {
            int count = 0;
            for (int j = 0; j < n; j++) {
                if (binaryVec[j]) {
                    count++;
                }
            }
            if (count < minCount) {
                usedVals.clear();
                halfVals.clear();
                for (int j = 0; j < n; j++) {
                    if (binaryVec[j]) {
                        usedVals.push_back(initVals[j]);
                    }
                }
                minCount = count;
            }
        }
        for (int j = 0; j < n; j++) {
            if (!binaryVec[j]) {
                int tempSum2 = tempSum + floor(initVals[j] / 2);
                if (tempSum2 <= maxLimit && tempSum2 > maxVal) {
                    maxVal = tempSum2;
                    usedVals.clear();
                    halfVals.clear();
                    for (int k = 0; k < n; k++) {
                        if (binaryVec[k]) {
                            usedVals.push_back(initVals[k]);
                        }
                    }
                    usedVals.push_back(initVals[j]);
                    halfVals.push_back(initVals[j]);
                    minCount = usedVals.size() + halfVals.size();
                } else if (tempSum2 <= maxLimit && tempSum2 == maxVal) {
                    int count = 0;
                    for (int k = 0; k < n; k++) {
                        if (binaryVec[k]) {
                            count++;
                        }
                    }
                    count++;
                    if (count < minCount) {
                        usedVals.clear();
                        halfVals.clear();
                        for (int k = 0; k < n; k++) {
                            if (binaryVec[k]) {
                                usedVals.push_back(initVals[k]);
                            }
                        }
                        usedVals.push_back(initVals[j]);
                        halfVals.push_back(initVals[j]);
                        minCount = count;
                    }
                }
            }
        }
    }
}
int main() {
    SetConsoleOutputCP(65001);
    printf("伊洛纳手游装备计算器\n功能整合版 version3.0\n个人开发，免费开源，欢迎使用！\n禁止任何转手销售行为，否则后果自负！\n程序及源代码详见B站UP：双流壮汉 uid:61204526\n");
        cout << endl;
        for (int i = 0; i < 120; i++) { 
            cout << '-';
        }
        cout << endl << endl;
    int choice;
    cout << "输入1算垫子，输入2算底子\n\n所有数值输完按回车键输入下一项\n\n选择: ";
    cin >> choice;
    cout << endl << endl;
    for (int i = 0; i < 120; i++) { 
            cout << '-';
        }
        cout << endl;
    if (choice == 1) {
        cout << "当前为垫子计算器模式\n\n";
    } else if (choice == 2) {
        cout << "当前为底子计算器模式\n\n";
    } else {
        cout << "输入错误，程序退出" << endl;
        return 0;
    }
    cout << "如需切换模式，请重启程序\n\n";
    for (int i = 0; i < 120; i++) { 
            cout << '-';
        }
        cout << endl;
    if (choice == 1) {
        while (true) {
            vector<int> initVals;
        // 让用户选择要读取的文件
        cout <<"选择装备库\n\n";
         for (int i = 0; i < 120; i++) { 
            cout << '-';
        }
        cout << endl << endl;
        cout <<"1-魔免，2-物免，3-小免，4-格挡，5-法术格挡，6-追打，7-追射，8-暗影追伤，9-精神追伤，10-地狱追伤，\n\n11-元素引导，12-魔法修行，13-战术，14-射术，15-枪械专精，16-速度，17-魔力，18-感知，19-体质，20-力量，\n\n21-栽培，22-采掘，23-探知，24-木工，25-铁匠，26-宝石加工，27-信仰，28-自定义A,29-自定义B,30-自定义C\n\n";
        int fileChoice;
         for (int i = 0; i < 120; i++) { 
            cout << '-';
        }
        cout <<"选择:";
        std::wcin >> fileChoice;
    std::filesystem::path fileName;
if (fileChoice == 1) {
    fileName = L"魔免.txt";
} 
else if (fileChoice == 2) {
    fileName = L"物免.txt";
}
else if (fileChoice == 3) {

    fileName = L"小免.txt";
}
else if (fileChoice == 4) {

    fileName = L"格挡.txt";
}
else if (fileChoice == 5) {

    fileName = L"法术格挡.txt";
}
else if (fileChoice == 6) {
    
    fileName = L"追打.txt";
}
else if (fileChoice == 7) {

    fileName = L"追射.txt";
}
else if (fileChoice == 8) {

    fileName = L"暗影追伤.txt";
}
else if (fileChoice == 9) {

    fileName = L"精神追伤.txt";
}
else if (fileChoice == 10) {

    fileName = L"地狱追伤.txt";
}
else if (fileChoice == 11) {

    fileName = L"元素引导.txt";
}
else if (fileChoice == 12) {

    fileName = L"魔法修行.txt";
}
else if (fileChoice == 13) {

    fileName = L"战术.txt";
}
else if (fileChoice == 14) {

    fileName = L"射术.txt";
}
else if (fileChoice == 15) {

    fileName = L"枪械专精.txt";
}
else if (fileChoice == 16) {

    fileName = L"速度.txt";
}
else if (fileChoice == 17) {

    fileName = L"魔力.txt";
}
else if (fileChoice == 18) {

    fileName = L"感知.txt";
}
else if (fileChoice == 19) {

    fileName = L"体质.txt";
}
else if (fileChoice == 20) {

    fileName = L"力量.txt";
}
else if (fileChoice == 21) {

    fileName = L"栽培.txt";
}
else if (fileChoice == 22) {

    fileName = L"采掘.txt";
}
else if (fileChoice == 23) {

    fileName = L"探知.txt";
}
else if (fileChoice == 24) {

    fileName = L"木工.txt";
}
else if (fileChoice == 25) {

    fileName = L"铁匠.txt";
}
else if (fileChoice == 26) {

    fileName = L"宝石加工.txt";
}
else if (fileChoice == 27) {

    fileName = L"信仰.txt";
}
else if (fileChoice == 28) {

    fileName = L"自定义A.txt";
}
else if (fileChoice == 29) {

    fileName = L"自定义B.txt";
}
else if (fileChoice == 30) {

    fileName = L"自定义C.txt";
}
else {
    cout << "无效的选择，请重新输入。" << endl;
}
std::wifstream file(fileName);
ifstream inputFile(fileName);
        if (!file.is_open()) {
            cout << "无法打开文件，请检查文件是否存在。" << endl;
        }
        int val;
         for (int i = 0; i < 120; i++) { 
            cout << '-';
        }
        cout << endl  << endl;
        cout << "装备库已载入,当前装备库为："<< (fileName) << endl;
        cout << endl << endl;
         for (int i = 0; i < 120; i++) { 
            cout << '-';
        }
        while (inputFile >> val) {
            initVals.push_back(val);
        }
        inputFile.close();
        
        int maxLimit;
        cout << "请输入最大数值限制:";
        cin >> maxLimit;
        int maxVal;
        vector<int> usedVals;
        vector<int> order;
        dianzi(initVals, maxLimit, maxVal, usedVals, order);
        cout << "最接近的值: " << maxVal << endl;
        cout << "使用过的装备对应的数值（按合成顺序排列，第一个为底）: ";
        for (int val : usedVals) {
            cout << val << ' ';
        }
        cout<<"最少消耗能力卷轴数："<<usedVals.size()<<endl;
        cout << endl;
        cout << "是否采用并保存该方案？（Y/N）";
        char decide;
        cin >> decide;
        if (decide == 'Y' || decide == 'y') {
        cout << endl << endl;
        cout <<"方案已保存。";
        
      std::vector<std::string> data; // 用于存储.txt文件中的数据
    std::vector<std::string> newData; // 用于存储删除后的数据

    // 读取.txt文件中的所有数据
    std::ifstream inFile(fileName);
    std::string line;
    while (std::getline(inFile, line)) {
        data.push_back(line);
    }
    inFile.close();

    // 遍历data向量，对于每个元素，首先检查它是否以“#”开头。
    // 如果是，则直接将其存储在newData向量中；
    // 否则，使用std::stringstream类来处理该元素。
    // 对于每个子元素，尝试将其转换为整数。
    // 如果转换成功且该整数不在usedVals向量中，则将该子元素存储在一个新的字符串中；
    // 如果转换失败，则直接将该子元素存储在新的字符串中。
    // 最后，将新的字符串存储在newData向量中。
    for (std::string val : data) {
        if (val[0] == '#') {
            newData.push_back(val);
        } else {
            std::stringstream ss(val);
            std::string subVal;
            std::string newLine;
            while (ss >> subVal) {
                try {
                    int intVal = std::stoi(subVal);
                    if (std::find(usedVals.begin(), usedVals.end(), intVal) == usedVals.end()) {
                        newLine += subVal + ' ';
                    }
                } catch (std::invalid_argument&) {
                    newLine += subVal + ' ';
                }
            }
            newData.push_back(newLine);
        }
    }
    std::string newString = "---------------------------------------------------------------\n\n";
    newString +="已采用的垫子方案: ";
    for (int val : usedVals) {
    newString += "#" + std::to_string(val) + ' ';
    newString +="消耗能力卷轴数：" + std::to_string(usedVals.size()) + "\n\n";
    
}
    newData.push_back(newString);
    // 使用newData向量覆盖原来的.txt文件
    std::ofstream outFile(fileName);
    for (std::string val : newData) {
        std::stringstream ss(val);
        std::string subVal;
        while (ss >> subVal) {
            try {
                outFile << subVal << std::endl;
            } catch (std::invalid_argument&) {
                outFile << subVal << ' ';
            }
        }
    }
    outFile.close();
    cout<< endl << endl;
}
        
        else {

            cout << endl << endl;
            cout << "方案未保存。";
        }
    std::vector<int> data; // 用于存储.txt文件中的数据
    std::vector<int> newData; // 用于存储删除后的数据
        cout<< endl << endl;
         for (int i = 0; i < 120; i++) { 
            cout << '-';
        }
        cout << endl;
    }
    } else if (choice == 2) {
       while (true) {
        vector<int> initVals;
        // 让用户选择要读取的文件
       cout <<"选择装备库\n\n";
         for (int i = 0; i < 120; i++) { 
            cout << '-';
        }
        cout << endl << endl;
        cout <<"1-魔免，2-物免，3-小免，4-格挡，5-法术格挡，6-追打，7-追射，8-暗影追伤，9-精神追伤，10-地狱追伤，\n\n11-元素引导，12-魔法修行，13-战术，14-射术，15-枪械专精，16-速度，17-魔力，18-感知，19-体质，20-力量，\n\n21-栽培，22-采掘，23-探知，24-木工，25-铁匠，26-宝石加工，27-信仰，28-自定义A,29-自定义B,30-自定义C\n\n";
        int fileChoice;
         for (int i = 0; i < 120; i++) { 
            cout << '-';
        }
        cout <<"选择:";
        std::wcin >> fileChoice;
    std::filesystem::path fileName;
if (fileChoice == 1) {
    fileName = L"魔免.txt";
} 
else if (fileChoice == 2) {
    fileName = L"物免.txt";
}
else if (fileChoice == 3) {

    fileName = L"小免.txt";
}
else if (fileChoice == 4) {

    fileName = L"格挡.txt";
}
else if (fileChoice == 5) {

    fileName = L"法术格挡.txt";
}
else if (fileChoice == 6) {
    
    fileName = L"追打.txt";
}
else if (fileChoice == 7) {

    fileName = L"追射.txt";
}
else if (fileChoice == 8) {

    fileName = L"暗影追伤.txt";
}
else if (fileChoice == 9) {

    fileName = L"精神追伤.txt";
}
else if (fileChoice == 10) {

    fileName = L"地狱追伤.txt";
}
else if (fileChoice == 11) {

    fileName = L"元素引导.txt";
}
else if (fileChoice == 12) {

    fileName = L"魔法修行.txt";
}
else if (fileChoice == 13) {

    fileName = L"战术.txt";
}
else if (fileChoice == 14) {

    fileName = L"射术.txt";
}
else if (fileChoice == 15) {

    fileName = L"枪械专精.txt";
}
else if (fileChoice == 16) {

    fileName = L"速度.txt";
}
else if (fileChoice == 17) {

    fileName = L"魔力.txt";
}
else if (fileChoice == 18) {

    fileName = L"感知.txt";
}
else if (fileChoice == 19) {

    fileName = L"体质.txt";
}
else if (fileChoice == 20) {

    fileName = L"力量.txt";
}
else if (fileChoice == 21) {

    fileName = L"栽培.txt";
}
else if (fileChoice == 22) {

    fileName = L"采掘.txt";
}
else if (fileChoice == 23) {

    fileName = L"探知.txt";
}
else if (fileChoice == 24) {

    fileName = L"木工.txt";
}
else if (fileChoice == 25) {

    fileName = L"铁匠.txt";
}
else if (fileChoice == 26) {

    fileName = L"宝石加工.txt";
}
else if (fileChoice == 27) {

    fileName = L"信仰.txt";
}
else if (fileChoice == 28) {

    fileName = L"自定义A.txt";
}
else if (fileChoice == 29) {

    fileName = L"自定义B.txt";
}
else if (fileChoice == 30) {

    fileName = L"自定义C.txt";
}
else {
    cout << "无效的选择，请重新输入。" << endl;
}
std::wifstream file(fileName);
ifstream inputFile(fileName);
        if (!file.is_open()) {
            cout << "无法打开文件，请检查文件是否存在。" << endl;
        }
        int val;
         for (int i = 0; i < 120; i++) { 
            cout << '-';
        }
        cout << endl  << endl;
        cout << "装备库已载入,当前装备库为："<< (fileName) << endl;
        cout << endl << endl;
         for (int i = 0; i < 120; i++) { 
            cout << '-';
        }
        while (inputFile >> val) {
            initVals.push_back(val);
        }
        inputFile.close();
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int maxLimit;
        int currentVal;
        int currentLimit;
        int bestVal;
        cout << "输入用作底子的装备的当前数值: ";
        cin >> currentVal;
        cout << "输入当前词条的可改造上限: ";
        cin >> currentLimit;
        maxLimit = 2*(currentLimit - currentVal);
       // cout<<maxLimit<<endl;
        int maxVal;
        vector<int> usedVals;
        vector<int> halfVals;
        dizi(initVals, maxLimit, maxVal, usedVals, halfVals);
        bestVal=currentVal+(maxVal*0.5);
        cout << "最接近的值: " << bestVal << endl;
        cout << "使用过的装备数值: ";
        for (int val : usedVals) {
            cout << val << ' ';
        }
        cout << endl;
        cout << "需要先合到其他素材装备上的装备数值: ";
        for (int val : halfVals) {
            cout << val << ' ';
        }
        cout << endl;
        cout << "消耗能力获得卷轴数: " << usedVals.size()  << endl;
        for (int i = 0; i < 120; i++) { 
            cout << '-';
        }
        cout << endl;
        cout << "是否采用并保存该方案？（Y/N）";
        char decide;
        cin >> decide;
        if (decide == 'Y' || decide == 'y') {
            cout << endl << endl;
             cout <<"方案已保存。";
      std::vector<std::string> data; // 用于存储.txt文件中的数据
    std::vector<std::string> newData; // 用于存储删除后的数据

    // 读取.txt文件中的所有数据
    std::ifstream inFile(fileName);
    std::string line;
    while (std::getline(inFile, line)) {
        data.push_back(line);
    }
    inFile.close();

    // 遍历data向量，对于每个元素，首先检查它是否以“#”开头。
    // 如果是，则直接将其存储在newData向量中；
    // 否则，使用std::stringstream类来处理该元素。
    // 对于每个子元素，尝试将其转换为整数。
    // 如果转换成功且该整数不在usedVals向量中，则将该子元素存储在一个新的字符串中；
    // 如果转换失败，则直接将该子元素存储在新的字符串中。
    // 最后，将新的字符串存储在newData向量中。
    for (std::string val : data) {
        if (val[0] == '#') {
            newData.push_back(val);
        } else {
            std::stringstream ss(val);
            std::string subVal;
            std::string newLine;
            while (ss >> subVal) {
                try {
                    int intVal = std::stoi(subVal);
                    if (std::find(usedVals.begin(), usedVals.end(), intVal) == usedVals.end()) {
                        newLine += subVal + ' ';
                    }
                } catch (std::invalid_argument&) {
                    newLine += subVal + ' ';
                }
            }
            newData.push_back(newLine);
        }
    }
    std::string newString = "---------------------------------------------------------------\n\n";
    newString +="已采用的底子方案: ";
    for (int val : usedVals) {
    newString += "#" + std::to_string(val) + ' ';     
}
    newString += "\n此方案中需要减半的数值：";
    for (int val : halfVals) {
    newString += "#" + std::to_string(val) + ' ';     
}
    newString += "\n此方案所用底子的数值#"+std::to_string(currentVal);
    newData.push_back(newString);
    // 使用newData向量覆盖原来的.txt文件
    std::ofstream outFile(fileName);
    for (std::string val : newData) {
        std::stringstream ss(val);
        std::string subVal;
        while (ss >> subVal) {
            try {
                outFile << subVal << std::endl;
            } catch (std::invalid_argument&) {
                outFile << subVal << ' ';
            }
        }
    }
    outFile.close();
    cout<< endl << endl;
}
        
        else {
           cout << endl << endl;
            cout << "方案未保存。";
        }
    std::vector<int> data; // 用于存储.txt文件中的数据
    std::vector<int> newData; // 用于存储删除后的数据
        cout<< endl << endl;
         for (int i = 0; i < 120; i++) { 
            cout << '-';
        }
    }
    } else {
        cout << "没有这个选项！" << endl;
    }
    return 0;
}