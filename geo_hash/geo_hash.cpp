//
// Created by xiejiaqi.01 on 2018/4/23.
//

#include <string>
#include <iostream>
#include <vector>

using namespace std;
const int GEO_CODE_LEN = 10;
const int GEO_CODE_ITEM_LEN = 5;

int intToChar[32];
int charToInt[256];

void init() {
    for (int i=0;i<10;i++) {
        intToChar[i] = '0' + i;
        charToInt['0' + i] = i;
    }
    int index = 10;
    for (char ch = 'b';ch <= 'z'; ch++) {
        if (ch == 'i' || ch == 'l' || ch == 'o') {
            continue;
        }
        intToChar[index] = ch;
        charToInt[ch] = index;
        index++;
    }
//    for (auto a : intToChar) {
//        cout << (char)a << " ";
//    }
//    cout << endl;
}

void geoHashEncode(double lat, double lon, string &geoCode) {
    double latInterval[2], lonInterval[2];
    latInterval[0] = -90;
    latInterval[1] = 90;
    lonInterval[0] = -180;
    lonInterval[1] = 180;
    int charCodeLen = GEO_CODE_ITEM_LEN * GEO_CODE_LEN;
    vector<int> geoBitVec((unsigned long)charCodeLen, 0);
    for (int i=0;i<charCodeLen;i++) {
        if (i % 2 == 0) {
            // lon
            double midLon = (lonInterval[0] + lonInterval[1]) / 2.0;
            if (lon > midLon) {
                geoBitVec[i] = 1;
                lonInterval[0] = midLon;
            } else {
                geoBitVec[i] = 0;
                lonInterval[1] = midLon;
            }
        } else {
            double midLat = (latInterval[0] + latInterval[1]) / 2.0;
            if (lat > midLat) {
                geoBitVec[i] = 1;
                latInterval[0] = midLat;
            } else {
                geoBitVec[i] = 0;
                latInterval[1] = midLat;
            }
        }
    }
    geoCode.resize(GEO_CODE_LEN);
    for (int i=0;i<GEO_CODE_LEN;i++) {
        int bitNum = 0;
        for (int j=i*GEO_CODE_ITEM_LEN;j<(i+1)*GEO_CODE_ITEM_LEN;j++) {
            bitNum = (bitNum << 1) + geoBitVec[j];
        }
        geoCode[i] = (char)intToChar[bitNum];
    }
}

void geoHashDecode(const string &geoCode, double &lat, double &lon) {
    int bitLen = GEO_CODE_ITEM_LEN * geoCode.size();
    vector<int> geoBitVec(bitLen);
    for (int i=0;i<geoCode.size();i++) {
        int bitNum = charToInt[geoCode[i]];
        for (int j=0;j<GEO_CODE_ITEM_LEN;j++) {
            if (bitNum & (1 << j)) {
                geoBitVec[i*GEO_CODE_ITEM_LEN + GEO_CODE_ITEM_LEN - 1 - j] = 1;
            } else {
                geoBitVec[i*GEO_CODE_ITEM_LEN + GEO_CODE_ITEM_LEN - 1 - j] = 0;
            }
        }
    }
    double latInterval[2], lonInterval[2];
    latInterval[0] = -90;
    latInterval[1] = 90;
    lonInterval[0] = -180;
    lonInterval[1] = 180;
    for (int i=0;i<geoBitVec.size();i++) {
        if (i % 2 == 0) {
            // lon
            if (geoBitVec[i] == 1) {
                lonInterval[0] = (lonInterval[0] + lonInterval[1]) / 2.0;
            } else {
                lonInterval[1] = (lonInterval[0] + lonInterval[1]) / 2.0;
            }
        } else {
            if (geoBitVec[i] == 1) {
                latInterval[0] = (latInterval[0] + latInterval[1]) / 2.0;
            } else {
                latInterval[1] = (latInterval[0] + latInterval[1]) / 2.0;
            }
        }
    }
    lon = (lonInterval[0] + lonInterval[1]) / 2.0;
    lat = (latInterval[0] + latInterval[1]) / 2.0;
}

int main() {
    init();
    int n, m;
    cin >> n >> m;
    double lat, lon;
    string geoCode;
    for (int i=0;i<n;i++) {
        cin >> lat >> lon;
        geoHashEncode(lat, lon, geoCode);
        cout << geoCode << endl;
    }
    for (int i=0;i<m;i++){
        cin >> geoCode;
        geoHashDecode(geoCode, lat, lon);
        printf("%.6lf %.6lf\n", lat, lon);
    }
}