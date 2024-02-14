#ifndef MATCH_H
#define MATCH_H

#include <string>
#include <sstream>
#include <iostream>

#include "List.h"
#include "TextFileHandler.h"

using namespace std;

struct Match {
    string localTeam;
    int scoreLocalTeam;
    string visitingTeam;
    int scoreVisitingTeam;

    int getPointsForLocalTeam() {

        if(scoreLocalTeam > scoreVisitingTeam){
            return 5;
        }
        if(scoreLocalTeam < scoreVisitingTeam){
            return 0;
        }
        if(scoreLocalTeam == 0 && scoreVisitingTeam == 0){
            return 1;
        }
        return 3;
    }

    int getPointsForVisitingTeam() {

        if(scoreLocalTeam > scoreVisitingTeam){
            return 0;
        }
        if(scoreLocalTeam < scoreVisitingTeam){
            return 5;
        }
        if(scoreLocalTeam == 0 && scoreVisitingTeam == 0){
            return 1;
        }

        return 3;
    }
};

Match getMatchFromLine(string line, char delimiter) {
        Match match;
        
        List<string> tokens = split(line, delimiter);

        cout << tokens.get(0) << endl;
        cout << tokens.get(1) << endl;
        cout << tokens.get(2) << endl;
        cout << tokens.get(3) << endl;
        match.localTeam = tokens.get(0);

        match.scoreLocalTeam = stoi(tokens.get(1));
        
        match.visitingTeam = tokens.get(2);
        
        match.scoreVisitingTeam = stoi(tokens.get(3));
            
        return match;
}

string getLineFromMatch(Match match, char delimiter) {
    string line = match.localTeam + delimiter + to_string(match.scoreLocalTeam) + delimiter + match.visitingTeam + delimiter + to_string(match.scoreVisitingTeam);
    return line;
}

List<string> getLinesListFromMatchList(List<Match> matchList, char delimiter) {
    List<string> lineList;
    for (int i = 0; i < matchList.size; i++) {
        lineList.add(getLineFromMatch(matchList.get(i), delimiter));
    }
    return lineList;
}

string printMatches(List<Match> matchList) {
    stringstream ss;
    for (int i = 0; i < matchList.size; i++) {
        ss << "["<<i<<"]"<<matchList.elements[i].localTeam << " " << matchList.elements[i].scoreLocalTeam << " - " << matchList.elements[i].scoreVisitingTeam << " " << matchList.elements[i].visitingTeam << endl;
    }
    return ss.str();
}

     

#endif /* MATCH_H */