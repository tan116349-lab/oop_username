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
	Vehicle(int ma, string loai, int gio, int tg) {
	    vehicleID = ma;
	    vehicleType = loai;
	    entryTime = gio;
	    parkingDuration = tg;
	    parkingFee = 0;
	    isOccupied = false;
	    calculateFee();
	}

    void Setters(int ID, string type, int time, int Duration){
    	vehicleID = ID;
    	vehicleType = type;
    	entryTime = time;
    	parkingDuration = Duration;
}
    int getID() const{
    	return vehicleID;
	}
	string getType()const{
		return vehicleType;
	}
	int getTime() const{
		return entryTime;
	}
	int getDuration() const{
		return parkingDuration;
	}
	double getFee() const{
		return parkingFee;
	}
	bool getOccupied()const{
		return isOccupied;
	}
	
	void calculateFee(){
		double phi=0;
		int a = 0;
		double tien =0;
		int Duration = parkingDuration;
		int Time = entryTime;
		string type = toUpper(vehicleType);
		if(type=="CAR"){
			phi=6.00;
		}
		else if(type=="MOTORCYCLE"){
			phi = 4.00;
		}
		else if(type=="BICYCLE"){
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
		
	void display() const{
		cout << fixed << setprecision(2);
		cout << vehicleID << "\n"
		 << vehicleType << "\n" 
		 << entryTime << "\n" 
		 << parkingDuration << "\n"
		 << parkingFee << "\n" 
		 << isOccupied << endl;
	}
	void setOccupied(bool status);
};

void Vehicle::setOccupied(bool status) {
    isOccupied = status;
}


class ParkingLot {
private:
    int parkID;
    char size;
    Vehicle pt1, pt2, pt3;
    bool co1, co2, co3;

public:
    ParkingLot();
    ParkingLot(int parkID, char size);

    int getID() const;

    bool them(Vehicle v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
};


ParkingLot::ParkingLot() {
    parkID = 0;
    size = 'S';
    co1 = co2 = co3 = false;
}

ParkingLot::ParkingLot(int ma, char kt) {
    parkID = ma;
    size = kt;
    co1 = co2 = co3 = false;
}

int ParkingLot::getID() const {
    return parkID;
}

bool ParkingLot::them(Vehicle v) {
    int cap = (size == 'S') ? 1 :
              (size == 'M') ? 2 : 3;

    v.setOccupied(true);

    if (cap >= 1 && !co1) {
        pt1 = v;
        co1 = true;
        return true;
    }

    if (cap >= 2 && !co2) {
        pt2 = v;
        co2 = true;
        return true;
    }

    if (cap >= 3 && !co3) {
        pt3 = v;
        co3 = true;
        return true;
    }

    return false;
}

bool ParkingLot::xoa(int ma_xe) {
    if (co1 && pt1.getID() == ma_xe) {
        if (co2) {
            pt1 = pt2;

            if (co3) {
                pt2 = pt3;
                co3 = false;
            }
            else {
                co2 = false;
            }
        }
        else {
            co1 = false;
        }

        return true;
    }

    if (co2 && pt2.getID() == ma_xe) {
        if (co3) {
            pt2 = pt3;
            co3 = false;
        }
        else {
            co2 = false;
        }

        return true;
    }

    if (co3 && pt3.getID() == ma_xe) {
        co3 = false;
        return true;
    }

    return false;
}

bool ParkingLot::chua(int ma_xe) const {
    if (co1 && pt1.getID() == ma_xe) return true;
    if (co2 && pt2.getID() == ma_xe) return true;
    if (co3 && pt3.getID() == ma_xe) return true;

    return false;
}

void ParkingLot::hien_thi() const {
    int cap = (size == 'S') ? 1 :
              (size == 'M') ? 2 : 3;

    int so_xe = co1 + co2 + co3;

    cout << "Bai " << parkID << " [" << size << "] "
         << so_xe << "/" << cap << " xe\n";

    if (co1) pt1.display();
    if (co2) pt2.display();
    if (co3) pt3.display();
}

bool ParkingLot::co_loai(string loai, int& dem, double& tong) const {
    dem = 0;
    tong = 0;

    loai = toUpper(loai);

    if (co1 && toUpper(pt1.getType()) == loai) {
        dem++;
        tong += pt1.getFee();
    }

    if (co2 && toUpper(pt2.getType()) == loai) {
        dem++;
        tong += pt2.getFee();
    }

    if (co3 && toUpper(pt3.getType()) == loai) {
        dem++;
        tong += pt3.getFee();
    }

    return dem > 0;
}


class SystemInterface {
private:
    ParkingLot bai1, bai2, bai3;
    bool co1, co2, co3;

public:
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface() {
    co1 = false;
    co2 = false;
    co3 = false;
}

void SystemInterface::runMenu() {
    int chon;

    while (true) {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";
        cin >> chon;

        switch (chon) {
        case 1: {
            int ma;
            char kt;

            cout << "Ma bai: ";
            cin >> ma;

            cout << "Kich thuoc (S/M/L): ";
            cin >> kt;

            kt = toupper(kt);

            if (co1 && bai1.getID() == ma ||
                co2 && bai2.getID() == ma ||
                co3 && bai3.getID() == ma) {
                cout << "Ma bai da ton tai!\n";
            }
            else if (!co1) {
                bai1 = ParkingLot(ma, kt);
                co1 = true;
                cout << "Da tao bai " << ma << "\n";
            }
            else if (!co2) {
                bai2 = ParkingLot(ma, kt);
                co2 = true;
                cout << "Da tao bai " << ma << "\n";
            }
            else if (!co3) {
                bai3 = ParkingLot(ma, kt);
                co3 = true;
                cout << "Da tao bai " << ma << "\n";
            }
            else {
                cout << "Da dat gioi han bai xe!\n";
            }

            break;
        }

        case 2: {
            int ma, gio, tg;
            string loai;

            cout << "Ma xe: ";
            cin >> ma;

            cout << "Loai (Car/Motorcycle/Bicycle): ";
            cin >> loai;

            cout << "Gio vao (0-23): ";
            cin >> gio;

            cout << "Thoi luong (1-23): ";
            cin >> tg;

            Vehicle v(ma, loai, gio, tg);

            bool ok = false;

            if (co1 && !ok) ok = bai1.them(v);
            if (co2 && !ok) ok = bai2.them(v);
            if (co3 && !ok) ok = bai3.them(v);

            if (ok) {
                cout << "Da them xe " << ma
                     << " | Phi: $" << fixed << setprecision(2)
                     << v.getFee() << "\n";
            }
            else {
                cout << "Tat ca bai da day!\n";
            }

            break;
        }

        case 3: {
            int ma;

            cout << "Ma bai can xoa: ";
            cin >> ma;

            if (co1 && bai1.getID() == ma) {
                if (co2) {
                    bai1 = bai2;

                    if (co3) {
                        bai2 = bai3;
                        co3 = false;
                    }
                    else co2 = false;
                }
                else co1 = false;

                cout << "Da xoa bai " << ma << "\n";
            }
            else if (co2 && bai2.getID() == ma) {
                if (co3) {
                    bai2 = bai3;
                    co3 = false;
                }
                else co2 = false;

                cout << "Da xoa bai " << ma << "\n";
            }
            else if (co3 && bai3.getID() == ma) {
                co3 = false;
                cout << "Da xoa bai " << ma << "\n";
            }
            else {
                cout << "Khong tim thay bai xe!\n";
            }

            break;
        }

        case 4: {
            int ma;

            cout << "Ma xe can lay ra: ";
            cin >> ma;

            bool ok = false;

            if (co1 && !ok) ok = bai1.xoa(ma);
            if (co2 && !ok) ok = bai2.xoa(ma);
            if (co3 && !ok) ok = bai3.xoa(ma);

            cout << (ok ? "Da lay xe ra!\n" : "Khong tim thay xe!\n");

            break;
        }

        case 5: {
            if (co1) bai1.hien_thi();
            if (co2) bai2.hien_thi();
            if (co3) bai3.hien_thi();

            if (!co1 && !co2 && !co3)
                cout << "Chua co bai xe!\n";

            break;
        }

        case 6: {
            int ma;

            cout << "Ma bai: ";
            cin >> ma;

            if (co1 && bai1.getID() == ma)
                bai1.hien_thi();
            else if (co2 && bai2.getID() == ma)
                bai2.hien_thi();
            else if (co3 && bai3.getID() == ma)
                bai3.hien_thi();
            else
                cout << "Khong tim thay bai xe!\n";

            break;
        }

        case 7: {
            string loai;

            cout << "Loai xe: ";
            cin >> loai;

            int dem;
            double tong;

            bool tim = false;

            if (co1 && bai1.co_loai(loai, dem, tong)) {
                bai1.hien_thi();
                tim = true;
            }

            if (co2 && bai2.co_loai(loai, dem, tong)) {
                bai2.hien_thi();
                tim = true;
            }

            if (co3 && bai3.co_loai(loai, dem, tong)) {
                bai3.hien_thi();
                tim = true;
            }

            if (!tim)
                cout << "Khong co xe thuoc loai nay!\n";

            break;
        }

        case 8: {
            string loai_arr[3] = {
                "Car", "Motorcycle", "Bicycle"
            };

            for (int i = 0; i < 3; i++) {
                int dem = 0;
                double tong = 0;
                int d;
                double s;

                if (co1) {
                    bai1.co_loai(loai_arr[i], d, s);
                    dem += d;
                    tong += s;
                }

                if (co2) {
                    bai2.co_loai(loai_arr[i], d, s);
                    dem += d;
                    tong += s;
                }

                if (co3) {
                    bai3.co_loai(loai_arr[i], d, s);
                    dem += d;
                    tong += s;
                }

                cout << loai_arr[i] << ": ";

                if (dem == 0)
                    cout << "Khong co xe\n";
                else
                    cout << dem << " xe | TB: $"
                         << fixed << setprecision(2)
                         << tong / dem << "\n";
            }

            break;
        }

        case 9:
            cout << "Ket thuc chuong trinh!\n";
            return;

        default:
            cout << "Lua chon khong hop le!\n";
        }
    }
}
int main(){
	SystemInterface sys;
	sys.runMenu();
	return 0;
}





