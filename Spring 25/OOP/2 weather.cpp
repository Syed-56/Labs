#include <iostream>
using namespace std;

float calcAvgAqi(int aqi[][7], string city[]) {
    float avgAqi[4];
    for(int i=0; i<4; i++) {
        int sum = 0;
        for(int j=0; j<7; j++) {
            sum += aqi[i][j];
        }
        avgAqi[i] = sum/7.0;
    }
    float max = avgAqi[0];
    for(int i=0; i<4; i++) {
        cout << "Avg AQI in " << city[i] << " = " << avgAqi[i] << endl;
        if(avgAqi[i] > max) max = avgAqi[i];
    }
    return max;
}

void criticalPollutionDays(int aqi[][7], string city[], string day[]) {
    cout << "\n\nInstances of AQI over 150";
    for(int i=0; i<4; i++) {
        for(int j=0; j<7; j++) {
            if(aqi[i][j]>150) {
                cout << "\nCity : " << city[i] << "\tDay : " << day[j] << "\tAQI : " << aqi[i][j];
            }
        }
    }
}

void dataViz(int aqi[][7], string day[], string city[]) {
    cout << "\nAQI level each day\n";
    for(int i=0; i<4; i++) {
        cout << endl << city[i] << ":-\n\n";
        cout << "Day\n";
        for(int j=0; j<7; j++) {
            cout << j+1 << " : ";
            for(int k=0; k < (aqi[i][j]/50); k++) {
                cout << "* ";
            }
            cout << endl;
        }
        cout << "  ";
        for(int k=0; k<40; k++) cout << "..";
        cout << endl << "    ";
        for(int k=0; k<30; k++) cout << k+1 << " ";
        cout << "\n  AQI(instance over 50)\n";
    }
}

void monthlyAqi(int aqi[][7], string city[], string day[]) {
    cout << "We have AQI of 1st week of month, now input for remaining 3 weeks\n";
    int newArr[4][28];
    for(int i=0; i<4; i++) {
        for(int j=0; j<7; j++) {
            newArr[i][j] = aqi[i][j];
        }
        cout << "\nInput " << city[i] << " AQI\n";
        for(int j=7; j<28; j++) {
            cout << "Enter " << day[j%7] << " AQI : "; 
            cin >> newArr[i][j];
        }
    }

    float avgMonth[4];
    for(int i=0; i<4; i++) {
        int sum = 0;
        for(int j=0; j<28; j++) {
            sum += newArr[i][j];
        }
        avgMonth[i] = sum/28.0;
    }

    float min = avgMonth[0];
    int store = 0;
    for(int i=1; i<4; i++) {
        if(avgMonth[i] < min) {
            min = avgMonth[i];
            store = i;
        }
    }
    cout << "Improved AQI of City " << city[store] << " . Notable Difference of " << min << endl;
}
void summarizedData(int aqi[][7], string city[], string day[]) {
    for(int i=0; i<4; i++) {
        cout << "\nSummary for " << city[i] << ":\n";
        
        float weeklyAvg[4] = {0};  
        for(int week=0; week<4; week++) {
            int sum=0;
            for(int dayIndex=0; dayIndex<7; dayIndex++) {
                sum += aqi[i][week*7 + dayIndex];
            }
            weeklyAvg[week] = sum/7.0;
            cout << "Week " << (week+1) << " Avg AQI: " << weeklyAvg[week] << endl;
        }

        cout << "\nCritical Pollution Days (AQI > 150):\n";
        for(int week=0; week<4; week++) {
            for(int dayIndex=0; dayIndex<7; dayIndex++) {
                int currentAqi = aqi[i][week*7 + dayIndex];
                if(currentAqi>150) {
                    cout << "Day: " << day[dayIndex] << ", AQI: " << currentAqi << endl;
                }
            }
        }

        int highest = aqi[i][0];
        int lowest = aqi[i][0];
        for(int j=1; j<28; j++) {
            if(aqi[i][j] > highest) {
                highest = aqi[i][j];
            }
            if(aqi[i][j] < lowest) {
                lowest = aqi[i][j];
            }
        }
        cout << "\nComparison of Highest and Lowest AQI:\n";
        cout << "Highest AQI: " << highest << ", Lowest AQI: " << lowest << endl;
        cout << "Difference: " << (highest-lowest) << endl;
    }
}

int main() {
	//task 1
    int aqi[4][7];
    string city[4] = {"Karachi", "Lahore", "Hyderabad", "Multan"};
    string day[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    
    for(int i=0; i<4; i++) {
        cout << "\nInput " << city[i] << " AQI\n";
        for(int j=0; j<7; j++) {
            cout << "Enter " << day[j] << " AQI : ";
            cin >> aqi[i][j];
        }
    }
    float avg = calcAvgAqi(aqi, city);
    cout << "Worst Air Quality: " << avg << endl;
    //task 2
    criticalPollutionDays(aqi, city, day);
    //task 3
    dataViz(aqi, day, city);
    //task 4
    monthlyAqi(aqi, city, day);
    //task5
    summarizedData(aqi, city, day);
return 0;
}