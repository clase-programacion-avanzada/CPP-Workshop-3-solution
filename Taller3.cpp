#include "libs/List.h"
#include "libs/TextFileHandler.h"
#include "libs/Match.h"
#include "libs/MatchPoint.h"

#include <iostream>
#include <string>


using namespace std;

List<Match> readMatchListFromFile(string path, char delimiter);
void printMatchList(List<Match> matchList);
List<Match> addMatchAndUpdateFile(List<Match> matchList, string path, char delimiter);
List<Match> removeMatchAndUpdateFile(List<Match> matchList, string path, char delimiter);

void printMenu();
void printLineList(List<string> lineList);
bool writeMatchListToFile(List<Match> matchList, string path, char delimiter);
void writeReportOfWinnersAndTiesToFile(List<Match> matchList);
void writeReport(string fileName, List<string> lineList, string type, int totalMatches);

int main() {
    
    int option = 0;

    List<Match> matchList;

    do {
        printMenu();
        cin >> option;
        string inputFileName = "resultados.txt";
        const char delimiter = ',';
        switch (option) {
            case 1:
                matchList = readMatchListFromFile(inputFileName, delimiter);
                break;
            case 2:
                if (matchList.size == 0) {
                    cout << "Debe leer el archivo de texto primero" << endl;
                    break;
                }
                printMatchList(matchList);
                break;
            case 3:
                matchList = addMatchAndUpdateFile(matchList, inputFileName, delimiter);
                break;
            case 4:
                if (matchList.size == 0) {
                    cout << "La lista no puede estar vacía" << endl;
                    break;
                }
                matchList = removeMatchAndUpdateFile(matchList, inputFileName, delimiter);
                break;
            case 5:
                if (matchList.size == 0) {
                    cout << "Debe leer el archivo de texto primero" << endl;
                    break;
                }
                writeReportOfWinnersAndTiesToFile(matchList);
                break;
            case 6:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción inválida" << endl;
                break;
        }
    } while (option != 6);
    
    return 0;


}

void printMenu() {
    cout << "1. Leer archivo de texto" << endl;
    cout << "2. Mostrar lista de partidos" << endl;
    cout << "3. Agregar partido" << endl;
    cout << "4. Eliminar partido" << endl;
    cout << "5. Generar reportes" << endl;
    cout << "6. Salir" << endl;
    cout << "Ingrese una opción: ";
}

List<Match> readMatchListFromFile(string path, char delimiter) {
    List<Match> matchList;
    TextFileHandler textFileHandler(path);
    List<string> lineList = textFileHandler.readLines();
    
    for (int i = 0; i < lineList.size; i++) {
        Match match = getMatchFromLine(lineList.get(i), delimiter);
        matchList.add(match);
    }

    return matchList;
}

void printMatchList(List<Match> matchList) {
    
    cout << "Lista de partidos: " << endl;
    cout << printMatches(matchList);
}

List<Match> addMatchAndUpdateFile(List<Match> matchList, string path, char delimiter) {
    Match match;
    cout << "Ingrese el nombre del equipo local: ";
    cin >> match.localTeam;
    cout << "Ingrese el nombre del equipo visitante: ";
    cin >> match.visitingTeam;
    cout << "Ingrese el puntaje del equipo local: ";
    cin >> match.scoreLocalTeam;
    cout << "Ingrese el puntaje del equipo visitante: ";
    cin >> match.scoreVisitingTeam;

    List<Match> newMatchList = matchList.copy();
    newMatchList.add(match);

    writeMatchListToFile(newMatchList, path, delimiter);

    return newMatchList;
}

void printLineList(List<string> lineList) {
    for (int i = 0; i < lineList.size; i++) {
        cout << lineList.get(i) << endl;
    }
}

List<Match> removeMatchAndUpdateFile(List<Match> matchList, string path, char delimiter) {
    
    cout << "Lista de partidos: " << endl;
    printMatchList(matchList);
    int index;
    cout << "Ingrese el índice del partido que desea eliminar: ";
    cin >> index;

    List<Match> newMatchList = matchList.copy();
    newMatchList.remove(index);
    
    writeMatchListToFile(newMatchList, path, delimiter);

    return newMatchList;
}

bool writeMatchListToFile(List<Match> matchList, string path, char delimiter) {
    TextFileHandler textFileHandler(path);
    List<string> lineList = getLinesListFromMatchList(matchList, delimiter);
    return textFileHandler.writeLines(lineList);
}

void writeReportOfWinnersAndTiesToFile(List<Match> matchList) {

    string winnerLocalTeamFileName = "reporte_ganador_local.txt";
    string winnerVisitingTeamFileName = "reporte_ganador_visitante.txt";
    string tiesFileName = "reporte_empates.txt";
    string tiesWithoutScoreFileName = "reporte_empates_sin_marcador.txt";

    List<string> winnerLocalTeamLineList;
    List<string> winnerVisitingTeamLineList;
    List<string> tiesLineList;
    List<string> tiesWithoutScoreLineList;

    char delimiter = ' ';

    for (int i = 0; i < matchList.size; i++) {
        Match match = matchList.get(i);
        string lineFromMatch = getLineFromMatch(match, delimiter);
        
        if (match.getPointsForLocalTeam() == 5) {
            winnerLocalTeamLineList.add(lineFromMatch);
        }

        if (match.getPointsForVisitingTeam() == 5) {
            winnerVisitingTeamLineList.add(lineFromMatch);
        }

        if (match.getPointsForLocalTeam() == 3 && match.getPointsForVisitingTeam() == 3) {
            tiesLineList.add(lineFromMatch);
        }

        if (match.getPointsForLocalTeam() == 1 && match.getPointsForVisitingTeam() == 1) {
            tiesWithoutScoreLineList.add(lineFromMatch);
        }
    }

    writeReport(winnerLocalTeamFileName, winnerLocalTeamLineList, "ganados por el equipo local", matchList.size);
    writeReport(winnerVisitingTeamFileName, winnerVisitingTeamLineList, "ganados por el equipo visitante", matchList.size);
    writeReport(tiesFileName, tiesLineList, "empatados", matchList.size);
    writeReport(tiesWithoutScoreFileName, tiesWithoutScoreLineList, "empatados sin goles", matchList.size);


}

void writeReport(string fileName, List<string> lineList, string type, int totalMatches) {
    TextFileHandler textFileHandler(fileName);

    unsigned int appendMode = ios::out | ios::app;

    string header = "Reporte de partidos " + type; 
    
    textFileHandler.writeSingleLine(header, ios::out);
    textFileHandler.writeSingleLine("\n\n===================================\n\n", appendMode);
    textFileHandler.writeLines(lineList, appendMode);
    
    textFileHandler.writeSingleLine("\n\n---------------------------------\n\n", appendMode);

    string totalMatchesOfReport = "Cantidad de partidos " + type + ": " + to_string(lineList.size);
    textFileHandler.writeSingleLine(totalMatchesOfReport, appendMode);

    string totalMatchesOfAll = "\nCantidad de partidos totales: " + to_string(totalMatches);
    textFileHandler.writeSingleLine(totalMatchesOfAll, appendMode);

    float percentageOfMatches = ((float)lineList.size / totalMatches) * 100;
    cout << percentageOfMatches << endl;
    string percentage = "\nPorcentaje de partidos " + type + ": " + to_string(percentageOfMatches) + "%";
    textFileHandler.writeSingleLine(percentage, appendMode);
    

}
