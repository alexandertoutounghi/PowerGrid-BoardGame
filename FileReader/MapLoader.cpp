/*
 * MapLoaderB.cpp
 *
 * 	MICHAEL GARNER
 * 	26338739
 * 	COMP 345
 * 	WINTER 2019
 *
 * 	ASSIGNMENT 1
 * 	POWER GRID
 *
 */

#include "MapLoader.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "FileReader.h"
#include "../Map/Map.h"
#include "../Map/Vertex.h"
#include "../Map/Edge.h"

using std::vector;
using std::cout;
using std::endl;

namespace Mike {

//Gets a vector containing all of the strings from the file
    vector<string> MapLoaderB::getMapInfoB(){
        //Variables
        //File being used in File_Reader class
        File_Reader fw;
        vector<string> words = fw.getLines();
        return words;
    }//close getMapInfo

//Uses mapFile.txt to load all data
    Map MapLoaderB::buildMapB() {
        //Declare variables
        vector<string> fileInput;
        Map returnMap;
        bool validMap = true;
        string nextCity;
        string nextRegion;
        int iCount = 3;
        string cityC1, cityC2;
        int connectionCost;

        //Get file contents
        fileInput = getMapInfoB();

        //Authorize file
        if ( !(fileInput.at(0) == ("AUTHORIZEDPOWERGRIDMAP") )) {
            cout << "MAP LOADER ERROR - THE FILE BEING USED IS NOT AN AUTHORIZED MAP FILE" << endl;
            validMap = false;
            return Map();
        }//close if not authorized file

        //READ IN CITIES
        nextCity = fileInput.at(2);
        nextRegion = fileInput.at(3);
        while (nextCity != "CONNECTIONS"){
            //create vertex
            Vertex *vtx = new Vertex( nextCity, nextRegion);
            //add vertex to map
            returnMap.addVertex( *vtx );
            //Update all values for next iteration
            iCount++;
            nextCity = fileInput.at( iCount );
            iCount++;
            nextRegion = fileInput.at(iCount);
        }//close read in cities until CONNECTIONS IS  READ

        //backtrack the counter by 1 place
        cout << "\nFinished reading in cities, now reading in the connections\nThe iCount is currently reading from ";
        iCount--;
        cout << fileInput.at( iCount ) << endl << endl ;
        iCount++;
        do {
            string city1 = fileInput.at(iCount);
            Vertex u = returnMap.findVertex(city1);
            iCount++;
            string city2 = fileInput.at(iCount);
            Vertex v = returnMap.findVertex(city2);
            iCount++;
            int i = std::stoi(fileInput.at(iCount));
            iCount++;
            returnMap.addEdge(u, v, i);
        } while(iCount < fileInput.size());
        if (returnMap.BFS())
            cout << "\n\nThe Map loader is now returning a valid map\n\n";
        else
            cout << "\n\nTHE MAP LOADER READ AN INVALID MAP TYPE FILE\nPLEASE LOAD A VALID MAP FILE!\n\n";
        //return map
        return returnMap;
    }//close map builder

    MapLoaderB::MapLoaderB() {}
    MapLoaderB::~MapLoaderB() {}

} /* namespace Mike */