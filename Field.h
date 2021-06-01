#pragma once
#include <vector>
using namespace std;

/*typedefs*/
typedef int heuristic_t;
typedef uint64_t hash_t;


class Field {
	vector<vector<int>> f;
public:
    Field();//ctor
    int& at(int i, int j);//getter for element [i, j]
    hash_t getHash();//to get hash
    bool isAssembled();//to get is combination assembled
    heuristic_t getHeuristic();//to get heuristic
    pair<int, int> getBlankPosition();//to get where is blank position
    friend int whatBlockToClick(Field beforeTheStepCondition, Field afterOneStepCondition);//difference between 2 combinations(before and after step)
    bool canBeAssembled();//is combination can be assembled?
    bool changeMap(int i, int j);//to make a step
    friend ostream& operator<<(ostream& fileStream, Field f);//to print info into file easier
};

Field::Field() {
    f = vector<vector<int>>(6);
    for (int i = 0; i < 6; i++)
        f[i] = vector<int>(6, -1);
}

int& Field::at(int i, int j) {
    return f[i][j];
}

hash_t Field::getHash() {
    hash_t sum = 0;
    int cnt = 15;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            sum += f[i][j] * (1LLU << (((i - 1) * 4 + j - 1) * 4));
        }
    }
    return sum;
}

bool Field::isAssembled() {
    vector<vector<int>> ideal(6, vector<int>(6, -1));
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++)
            ideal[i][j] = (i - 1) * 4 + j;
    }

    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++)
            if (ideal[i][j] != f[i][j])return false;
    }
    return true;
}

heuristic_t Field::getHeuristic() {
    int sum = 0;

    /*math_distance*/
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            sum += abs(i - (f[i][j] / 4 + 1)) + abs(j - (f[i][j] % 4 + 1));
        }
    }
    /*not on their positions*/
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            sum += (i - 1) * 4 + j != f[i][j];
    /*Last move*/
    sum += (f[4][4] == 15 || f[4][4] == 12) ? 2 : 0;
    /*Corner Tiles*/
    int conflictCount = 0;
    //upper left corner
    if (f[1][1] != 1) {
        if (f[1][2] == 2 || f[2][1] == 5)conflictCount++;
    }
    //upper right corner
    if (f[1][4] != 4) {
        if (f[1][3] == 3 || f[2][3] == 8)conflictCount++;
    }
    //lower lefft corner
    if (f[4][1] != 13) {
        if (f[3][1] == 9 || f[4][2] == 14)conflictCount++;
    }

    sum += 2 * conflictCount;
    return sum;
}

pair<int, int> Field::getBlankPosition() {
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (f[i][j] == 16)return make_pair(i, j);
        }
    }
}

int whatBlockToClick(Field beforeTheStepCondition, Field afterOneStepCondition) {
    pair<int, int> beforeStep;
    pair<int, int> afterStep;
    beforeStep = beforeTheStepCondition.getBlankPosition();
    afterStep = afterOneStepCondition.getBlankPosition();
    pair<int, int> shiftVector = make_pair(afterStep.first - beforeStep.first, afterStep.second - beforeStep.second);
    return beforeTheStepCondition.at(beforeStep.first + shiftVector.first, beforeStep.second + shiftVector.second);
}

bool Field::changeMap(int i, int j) {
    if (f[i + 1][j] == 16) {
        swap(f[i][j], f[i + 1][j]);
        return true;
    }

    if (f[i - 1][j] == 16) {
        swap(f[i][j], f[i - 1][j]);
        return true;
    }

    if (f[i][j + 1] == 16) {
        swap(f[i][j], f[i][j + 1]);
        return true;
    }

    if (f[i][j - 1] == 16) {
        swap(f[i][j], f[i][j - 1]);
        return true;
    }
    return false;
}

bool Field::canBeAssembled() {
    /*заглушка на неправильный ввод*/
    /*в матрице должны встречатьс€ “ќЋ№ ќ числа от 1 до 16,
    причем “ќЋ№ ќ по одному разу
    */
    int cnt[17] = {};
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (f[i][j] >= 1 && f[i][j] <= 16) {
                cnt[f[i][j]]++;
            }
        }
    }
    for (int i = 1; i <= 16; i++) {
        if (cnt[i] != 1)return false;
    }


    /*если ввод был совершен в правильном формате*/
    vector<int> snake;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (f[i][j] != 16)snake.push_back(f[i][j]);
        }
    }
    int e = 0;
    int N = 0;

    //on which line blank is
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            if (f[i][j] == 16)e = i;
    //how many inversions
    for (int i = 0; i < snake.size() - 1; i++) {
        for (int j = i + 1; j < snake.size(); j++) {
            N += (int)(snake[j] < snake[i]);
        }
    }
    return !((N + e) % 2);
}

ostream& operator<<(ostream& fileStream, Field f) {
    fileStream << "Start combination: " << endl;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            fileStream << setw(3) << (f.at(i, j) == 16 ? 0 : f.at(i, j));
        }
        fileStream << endl;
    }
    return fileStream;
}