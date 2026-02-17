#include<bits/stdc++.h>

using namespace std;

struct Size {
    const long long maxRowWidth;
    const long long height;

    Size(const long long maxRowWidth, const long long height) : maxRowWidth(maxRowWidth), height(height) {}
};

long long nStars;

Size *getSize(long long firstRowWidth, long long widthDiff) {
    const auto secondRowWidth = firstRowWidth + widthDiff;
    if (firstRowWidth < 1 || secondRowWidth < 1 || abs(widthDiff) > 1) {
        return nullptr;
    }
    if (firstRowWidth == nStars) {
        return new Size(firstRowWidth, 1);
    }
    const auto maxRowWidth = max(firstRowWidth, secondRowWidth);
    const auto pairTotalWidth = firstRowWidth + secondRowWidth;
    const auto nPairs = nStars / pairTotalWidth;
    return nPairs * pairTotalWidth == nStars ? new Size(maxRowWidth, nPairs * 2) :
           nPairs * pairTotalWidth + firstRowWidth == nStars ? new Size(maxRowWidth, nPairs * 2 + 1) :
           nullptr;
}

long long answer = LLONG_MAX;

void maybeUpdateAnswer(const Size *size) {
    if (size != nullptr) {
        answer = min(answer, abs(size->maxRowWidth - size->height));
    }
}

int main() {
    cin >> nStars;
    answer = nStars - 1;
    const auto upperBound = (long long) sqrt(nStars) + 10;
    for (long long firstRowWidth = 1; firstRowWidth <= upperBound; firstRowWidth++) {
        for (long long widthDiff = -1; widthDiff <= 1; widthDiff++) {
            maybeUpdateAnswer(getSize(firstRowWidth, widthDiff));
        }
    }
    for (long long height = 1; height <= upperBound; height++) {
        for (long long widthDiff = -1; widthDiff <= 1; widthDiff++) {
            const auto firstRowWidth = height % 2 == 0 ?
                                       (nStars / (height / 2) - widthDiff) / 2 :
                                       (nStars - widthDiff * height / 2) / height;
            maybeUpdateAnswer(getSize(firstRowWidth, widthDiff));
        }
    }
    cout << answer << endl;
}
