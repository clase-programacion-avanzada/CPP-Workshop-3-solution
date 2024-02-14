#ifndef MATCHPOINT_H
#define MATCHPOINT_H

#include <string>
#include "List.h"
#include "Match.h"

using namespace std;

struct MatchPoint {
    string team;
    int points;

    MatchPoint() {
        team = "";
        points = 0;
    }
};


#endif /* MATCHPOINT_H */