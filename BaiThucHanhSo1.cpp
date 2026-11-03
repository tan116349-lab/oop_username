#include<bits/stdc++.h>
using namespace std;

string toUpper(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = toupper(s[i]);
    }
    return s;
}

class Vehicle {
private:
    int vehicleID;
    string vehicleType;
    int entryTime;
    int parkingDuration;
    double parkingFee;
    bool isOccupied;

public:
    Vehicle(){
    	vehicleID=0;
    	vehicleType="";
    	entryTime=0;
    	parkingDuration=0;
    	parkingFee=0;
    	isOccupied=false;
	};
    Vehicle(int ma, string loai, int gio, int tg);

    void Setters(int ID, string type, int time, int Duration){
    	vehicleID = ID;
    	vehicleType = type;
    	entryTime = time;
    	parkingDuration = Duration;
}
    int getID(){
    	return vehicleID;
	}
	string getType(){
		return vehicleType;
	}
	int getTime(){
		return entryTime;
	}
	int getDuration(){
		return parkingDuration;
	}
	double getFee(){
		return parkingFee;
	}
	bool getOccupied(){
		return isOccupied;
	}
	
	void calculateFee(){
		double phi=0;
		int a = 0;
		double tien =0;
		int Duration = parkingDuration;
		int Time = entryTime;
		string type = toUpper(vehicleType);
		if(vehicleType=="CAR"){
			phi=6.00;
		}
		else if(vehicleType=="MOTORCYCLE"){
			phi = 4.00;
		}
		else if(vehicleType=="BICYCLE"){
			phi = 2.00;
		}
		for(int i = Time; i < (Time + Duration) ; i++){
                if(a < 2){
                     if(i==6||i==7||i==8||i==9||i==15||i==16||i==17||i==18){
                     tien += phi*1.3;
                     a++;
                     }
                     else{
                      tien += phi*0.95;
                      a++;
                      }
                  }
                      if(a>=2){
                        tien+= phi*0.9;
                    }
             }                                                                                                                                             
			parkingFee = tien;
		}		
		
	void display(){
		cout << fixed << setprecision(2);
		cout << vehicleID << "\n"
		 << vehicleType << "\n" 
		 << entryTime << "\n" 
		 << parkingDuration << "\n"
		 << parkingFee << "\n" 
		 << isOccupied << endl;
	}
		
};




class ParkingLot {
private:
    int parkID;
    char size;
    Vehicle pt1, pt2, pt3;
    bool co1, co2, co3;

public:
    ParkingLot();
    ParkingLot(int parkID, char size);

    bool them(Vehicle v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
};

class SystemInterface {
private:
    ParkingLot bai1, bai2, bai3;   
    bool co1, co2, co3;

public:
    SystemInterface();
    void runMenu();
};




