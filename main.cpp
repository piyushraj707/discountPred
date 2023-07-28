#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <map>
using namespace std;

int find_mu (int start, int end, int I);           //to find the membership function
void update_m1 (map<string,float>& map, int I);
void update_m2 (map<string,float>& map, int I);
void update_m3 (map<string,float>& map, int I);


int main() {
    //Taking Inputs
    int I1, I2, I3;
    cout<<"What is the number of sales per week for the product? :"; cin>>I1;
    cout<<"How large is the stock of product? :"; cin>>I2;
    cout<<"How long has the product been in the warehouse? :"; cin>>I3;

    map<string,float> m1, m2, m3; //map to store membership value for each linguistic term
    update_m1(m1,I1);
    update_m2(m2,I2);
    update_m3(m3,I3);

    string lings1[]={"VLOW","LOW","MID","HIGH"};  //Very LOW, LOW, MIDdle, HIGH
    string lings2[]={"HF","SM","MID","BK"};  //HandFul, SMall, MIDdle, BulK
    string lings3[]={"NEW","OLD","VOLD"};  //NEW, OLD, Very OLD
    vector<float> weights; //to calculate weights of each possible solution

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            for (int k=0; k<3; k++) {
                weights.push_back( m1[lings1[i]] * m2[lings2[j]] * m3[lings3[k]] );
            }
        }
    }

    vector<float> y_value;
    float coeff1[]={5,4,2,1};
    float coeff2[]={1,3,5,7};
    float coeff3[]={0.1,1,3};

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            for (int k=0; k<3; k++) {
                y_value.push_back( coeff1[i]*I1 + coeff2[j]*I2 + coeff3[k]*I3 );
            }
        }
    }

    float result=0;
    float weights_sum=0;
    for (int i=0; i<weights.size(); i++) {
        result+=weights[i]*y_value[i];
        weights_sum+=weights[i];
    }
    result=(result/weights_sum);
    cout<<"Discount for the product: "<<endl;
    cout<< result;
    return 0;
}


void update_m1(map<string,float>& m, int I) {
    if (I>0 && I<=20) {
        m["VLOW"]=find_mu(20,0,I);
        m["LOW"]=find_mu(0,20,I);
    }
    else if (I<=100) {
        m["MID"]=find_mu(20,100,I);
        m["LOW"]=find_mu(100,20,I);
    }
    else if (I<200) {
        m["HIGH"]=find_mu(100,200,I);
        m["MID"]=find_mu(200,100,I);
    }
    else
        cout<<"Please enter correct value of I1 (0 to 200) and try again.";
}

void update_m2(map<string,float>& m, int I) {
    if (I>0 && I<=20) {
        m["HF"]=find_mu(20,0,I);  //HF=HandFul
        m["SM"]=find_mu(0,20,I);  //SM=SMall
    }
    else if (I<=250) {
        m["MID"]=find_mu(20,250,I);  
        m["SM"]=find_mu(250,20,I);
    }
    else if (I<500) {
        m["MID"]=find_mu(250,500,I);
        m["BK"]=find_mu(500,250,I);  //BK=BulK
    }
    else
        cout<<"Please enter correct value of I2 (0 to 500) and try again.";
}

void update_m3(map<string,float>& m, int I) {
    if (I>0 && I<=6) {
        m["OLD"]=find_mu(0,6,I);
        m["NEW"]=find_mu(6,0,I);
    }
    else if (I<=24) {
        m["VOLD"]=find_mu(6,24,I);
        m["OLD"]=find_mu(24,6,I);
    }
    else
        cout<<"Please enter correct value of I3 (0,24) and try again.";
}

int find_mu(int s, int e, int I) {
    return ( (I-s)/(e-s) );
}