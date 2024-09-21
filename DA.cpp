#include<iostream>
#include<string>
#include<string.h>
#include<ctype.h>
#include<climits>
#include<math.h>
#include<stdlib.h>     // This line includes the fstream library, which provides functions for file handling, such as reading from or writing to files.
#include<fstream>      // Overall, these lines include various libraries required for different purposes, integer limits, mathematical calculations,file handling.

using namespace std;

int nr[5];
int op[5];
int mc[5];
int sr[5];

int arr[475];

string room_no;

void roomallotment(){           // This function is responsible for room allotment based on certain conditions.
    ifstream in;
    in.open("rooms.txt");
    int fl1=0;
    int fl2=0;
    string str;                 // The first line of the file is read and stored in the str variable using the getline() function.
    fflush(stdin);
    getline(in,str);
    for(int i=0;i<99;i++){       // A loop is initiated to read the remaining lines of the file.
        if(str!="0"){
            arr[i]=i+1;
            fl1=1;               // Inside the loop, if the current line is not equal to "0", the room number is assigned to the corresponding index in the array "arr" and fl1 is set to 1
        }
        else{
            arr[i]=0;           // If the current line is equal to "0", the corresponding index in the array "arr" is set to 0.
        }
        fflush(stdin);
        getline(in,str);
    }
    if(str!="0"){
        arr[99]=106;           // If the last line is not equal to "0", the room number 106 is assigned to the last index of the array "arr".
    }
    else{
        arr[99]=0;
    }
    for(int i=100;i<475;i++){            // Inside the loop, the room numbers are read from the file and stored in the array "arr".
        in>>arr[i];
        if(arr[i]!=0 && i<225){
            fl2=1;                       // If the room number is not equal to 0 and the index is less than 225, fl2 is set to 1.
        }
        else if(arr[i]!=0 && i>225){
            fl1=1;                       // If the room number is not equal to 0 and the index is greater than 225, fl1 is set to 1.
        }
    }
    int type;                               // The user is prompted to enter a choice between ICU (1) and Normal Room (2)
    cout<<"1.ICU\n2.Normal Room"<<endl;
    cin>>type;
    if(fl1>0 && type==2){                      // If there are available normal rooms (fl1>0) and the user selected Normal Room (type==2):
        if(fl1==1){
            int fl=0;
            for(int i=0;i<99;i++){
                if(arr[i]!=0){
                    cout<<"G"<<arr[i]<<endl;
                    room_no="G";
                    room_no+=to_string(arr[i]);
                    arr[i]=0;
                    fl=1;                        //The "fl" variable is set to 1 to indicate a room has been allocated.
                    break;
                }
            }
            if(fl==0){                                // - If "fl" is still 0 after the loop, it means no room was found in the first part of the array.
                for(int i=225;i<475;i++){             // Another loop is initiated to find an available room from the second part of the array.
                    if(arr[i]!=0){
                        cout<<arr[i]<<endl;
                        room_no+=to_string(arr[i]);
                        arr[i]=0;                            // Once an available room is found, it is printed and assigned to the "room_no" variable.
                        break;
                    }
                }
            }
        }
        else if(fl2==1){
            cout<<"No normal rooms available. Alloting ICU room"<<endl;     // If there are no available normal rooms and the user selected Normal Room, A message is printed to indicate that no normal rooms are available.
            for(int i=99;i<225;i++){                                        // - A loop is initiated to find an available ICU room from the second part of the array.
                if(arr[i]!=0){
                    cout<<arr[i]<<endl;
                    room_no+=to_string(arr[i]);
                    arr[i]=0;
                    break;
                }
            }
        }
    }
    else if(type==1 && fl1>0){                     // This part of the code is executed when the user selects ICU (type==1) and there are available rooms (fl1>0).
        if(fl2==1){
            for(int i=99;i<225;i++){               // - A loop is initiated to find an available ICU room from the second part of the array
                if(arr[i]!=0){
                    cout<<arr[i]<<endl;           // - Once an available room is found, it is printed and assigned to the "room_no" variable.
                    room_no+=to_string(arr[i]);
                    arr[i]=0;
                    break;
                }
            }
        }                                         //The same process continues for all the nested if else statements
        else if(fl1==1){
            cout<<"No ICU rooms available. Alloting normal room"<<endl;
            int fl=0;
            for(int i=0;i<99;i++){
                if(arr[i]!=0){
                    cout<<"G"<<arr[i]<<endl;
                    room_no="G";
                    room_no+=to_string(arr[i]);
                    arr[i]=0;
                    fl=1;
                    break;
                }
            }
            if(fl==0){
                for(int i=225;i<475;i++){
                    if(arr[i]!=0){
                        cout<<arr[i]<<endl;
                        room_no+=to_string(arr[i]);
                        arr[i]=0;
                        break;
                    }
                }
            }
        }
    }
    else if(fl1==0){
        cout<<"No room available"<<endl;
    }
    ofstream out;
    out.open("rooms.txt");
    for(int i=0;i<99;i++){
        if(arr[i]!=0){
            out<<"G"<<arr[i]<<endl;
        }
        else{
            out<<arr[i]<<endl;
        }

    }
    for(int i=99;i<475;i++){
        out<<arr[i]<<endl;
    }
    out.close();
}
void calbill(string name, string id, int days){        // Calculating and writing the billing information to a file
    int amt=0;                                          // Initialize the variable "amt" to hold the calculated amount
    amt=100*days;                                      // Calculate the amount by multiplying the number of days by 100
    ofstream out;
    out.open("precription.txt");                        //The details of the patient is to be printed
    out<<"---------------------------CITY HOSPITAL-----------------------------"<<endl;
    out<<"Patient ID: "<<id<<endl;
    out<<"Patient Name: "<<name<<endl;
    out<<"Room No.: "<<room_no<<endl;
    out<<"Total Amount: Rs."<<amt<<endl;
    out.close();                                        //The file will be closed
}

void discharge(){                                  // Discharging a patient and updating the room availability
    string room;
    cout<<"Enter Patients Room Number"<<endl;
    cin>>room;
    int roomno=0;
    if(room[0]=='G'){                                // If the room number starts with 'G', it indicates a normal room
        int j=1;
        while(room[j]!='\0' && room[j]!='\n' && room[j]!=' '){                 // Convert the numeric part of the room number to an integer
           roomno*=10;
           roomno=roomno+((int)room[j]-(int)'0');
           j++;
        }
    }
    else{
        roomno=(((int)room[2]-(int)'0')) +(((int)room[1]-(int)'0')*10)+(((int)room[0]-(int)'0')*100);   // Convert the room number to an integer
    }
    ifstream in;                          // Create an ifstream object named "in" for reading from a file
    in.open("rooms.txt");                  // Open the file "rooms.txt" for reading
    int fl1=0;
    int fl2=0;
    string str;
    fflush(stdin);
    getline(in,str);
    for(int i=0;i<99;i++){
        if(str!="0"){
            arr[i]=i+1;
        }
        else{
            arr[i]=0;
        }
        fflush(stdin);
        getline(in,str);
    }
    if(str!="0"){
        arr[99]=106;                       // Assign the room number 106 (ICU) to the last element
    }
    else{
        arr[99]=0;                         // Mark the room as unallocated (0)
    }
    for(int i=100;i<475;i++){               // Process the second part of the array (indexes 100 to 474)
        in>>arr[i];                          // Read the room number from the file
    }
    in.close();
    ofstream out;
    out.open("rooms.txt");
    int fl=0;
    for(int i=0;i<99;i++){                        // Updating the room allocation status after discharging a patient
        if(roomno==i+1 && arr[i]==0){
            out<<"G"<<roomno<<endl;
            fl=1;
        }
        else{
            if(arr[i]!=0){
                out<<"G"<<arr[i]<<endl;
            }
            else{
                out<<arr[i]<<endl;
            }
        }
    }
    int h=106;
    for(int i=99;i<193;i++){         // Updating the room allocation status after discharging a patient
        if(roomno==h){
            out<<h<<endl;
        }
        else{
            out<<arr[i]<<endl;
        }
        h++;
    }
    h=206;
    for(int i=193;i<287;i++){         // Updating the room allocation status after discharging a patient
        if(roomno==h){
            out<<h<<endl;
        }
        else{
            out<<arr[i]<<endl;
        }
        h++;
    }
    h=306;
    for(int i=287;i<381;i++){          // Updating the room allocation status after discharging a patient
        if(roomno==h){
            out<<h<<endl;
        }
        else{
            out<<arr[i]<<endl;
        }
        h++;
    }
    h=406;
    for(int i=381;i<475;i++){         // Updating the room allocation status after discharging a patient
        if(roomno==h){
            out<<h<<endl;
        }
        else{
            out<<arr[i]<<endl;
        }
        h++;
    }
    out.close();
}

void appointments(){              // Reading and processing appointment data from a file

    int i=0;
    string str;
    ifstream in;
    in.open("app.txt");
    fflush(stdin);
    getline(in,str);
    while(str[0]!='N'){         // Read the file and skip lines until the line starting with 'N'
        fflush(stdin);
        getline(in,str);
    }
    int num1=0;
    while(i<5){                // Process the next 5 lines to extract numeric values for nr[] array
        fflush(stdin);
        getline(in,str);
        num1=0;
        int j=0;
        while(str[j]!='\0'){
            num1*=10;
            num1+=(int)str[j]-(int)'0';
            j++;
        }
        nr[i]=num1;
        i++;
    }
    while(str[0]!='O'){               // Skip lines until the line starting with 'O'
        fflush(stdin);
        getline(in,str);
    }
    num1=0;                           // Process the next 5 lines to extract numeric values for op[] array
    i=0;
    while(i<5){
        fflush(stdin);
        getline(in,str);
        num1=0;
        int j=0;
        while(str[j]!='\0'){
            num1*=10;
            num1+=(int)str[j]-(int)'0';
            j++;
        }
        op[i]=num1;
        i++;
    }
    while(str[0]!='M'){                    // Skip lines until the line starting with 'M'
        fflush(stdin);
        getline(in,str);
    }
    num1=0;                   // Process the next 5 lines to extract numeric values for mc[] array
    i=0;
    while(i<5){
        fflush(stdin);
        getline(in,str);
        num1=0;
        int j=0;
        while(str[j]!='\0'){
            num1*=10;
            num1+=(int)str[j]-(int)'0';
            j++;
        }
        mc[i]=num1;
        i++;
    }
    while(str[0]!='S'){                 // Skip lines until the line starting with 'S'
        fflush(stdin);
        getline(in,str);
    }
    num1=0;
    i=0;
    while(i<5){                          // Process the next 5 lines to extract numeric values for sr[] array
        fflush(stdin);
        getline(in,str);
        num1=0;
        int j=0;
        while(str[j]!='\0'){
            num1*=10;
            num1+=(int)str[j]-(int)'0';
            j++;
        }
        sr[i]=num1;
        i++;
    }
}

class Patient                            // Patient class definition
{
protected:
    string name;
    string age;
    string blood;
    string phone_no;
    string gender;
    string patientID;
    string illness;
    string address;
    public:
    int app_no;
    int doc;
    virtual void patient_id_generate()=0;        // Method to generate appointment number based on the department and doctor
    virtual void choose_doctor()=0;                // - Updates the respective appointment counter and sets the appointment number for the patient
    virtual void input()=0;
    virtual void Display()=0;
    virtual void print_prescription()=0;
    virtual void patient_data()=0;                   // - Updates the respective appointment counter and sets the appointment number for the patient

    void generate_appointmentNo(int department){              // - Writes the updated appointment counters to the "app.txt" file
        if(department==1){                                    // Update the appointment counter based on the department and doctor
            nr[doc-1]+=1;
            app_no=nr[doc-1];
        }
        else if(department==2){
            op[doc-1]+=1;
            app_no=op[doc-1];
        }
        else if(department==3){
            mc[doc-1]+=1;
            app_no=mc[doc-1];
        }
        else if(department==4){
            sr[doc-1]+=1;
            app_no=sr[doc-1];
        }

        ofstream out;
        out.open("app.txt");                                                                   // Write the updated appointment counters to the "app.txt" file
        out<<"--------------------APPOINMENT DETAILS--------------------"<<endl;
        out<<"\nNEUROLOGY"<<endl;
        out<<nr[0]<<"\n"<<nr[1]<<"\n"<<nr[2]<<"\n"<<nr[3]<<"\n"<<nr[4]<<endl;
        out<<"\nORTHOPEDICS"<<endl;
        out<<op[0]<<"\n"<<op[1]<<"\n"<<op[2]<<"\n"<<op[3]<<"\n"<<op[4]<<endl;
        out<<"\nMEDICINE"<<endl;
        out<<mc[0]<<"\n"<<mc[1]<<"\n"<<mc[2]<<"\n"<<mc[3]<<"\n"<<mc[4]<<endl;
        out<<"\nSURGERY"<<endl;
        out<<sr[0]<<"\n"<<sr[1]<<"\n"<<sr[2]<<"\n"<<sr[3]<<"\n"<<sr[4]<<endl;
    }
};

struct doctor                    //definition of structure for doctor
{
    string ID;
    int empID;
    string name;
    string qualification;
    int cabinNo;
    string mobileNo;
    static int no_of_appointments;
};

struct ID{                              //definition of structure for their ID
    string dep;
    string first;
    string second;
    string num;
};

struct ID val[5];

class Emergency : public Patient{
    public:
    void input()                                        // Method to input patient details
    {
        cout<<"---------------- Patient Details ----------------"<<endl;         // - Prompts the user to enter patient information
        cout << "Name: " << endl;                                                 // Prompt and input patient details
        fflush(stdin);
        getline(cin, name);
        cout << "Age: " << endl;
        cin >> age;
        cout << "Blood Type: " << endl;
        cin >> blood;
        cout<<"Illness Type:"<<endl;
        fflush(stdin);
        getline(cin,illness);
        cout << "Phone Number: " << endl;
        cin >> phone_no;
        cout << "Gender: " << endl;
        cin >> gender;
        cout << "Address: " << endl;
        fflush(stdin);
        getline(cin, address);
        room_no="115";
    }
    void patient_id_generate(){
        int n=0;                                       // Method to display patient details
        ifstream in;                                    // - Displays patient information on the console
        in.open("Patient_ID.txt");
        string str;
        int j=0;
        in>>str;
        while(str!="Emergency"){
            val[j].dep=str;
            in>>str;
            val[j].first=str;
            in>>str;
            val[j].second=str;
            in>>str;
            val[j].num=str;
            in>>str;
            j++;
        }
        val[j].dep=str;
        string str1;
        string str2;
        in>>str1;
        in>>str2;
        in>>str;
        int i=0;
        while(str[i]!='\0' && str[i]!='\n' && str[i]!=' '){
            n*=10;
            n+=((int)str[i])-((int)'0');
            i++;
        }
        n++;
        if(n==10000){
            cout<<"hii1"<<endl;
            if(str2=="Z"){
                int num=str1[0]+1;
                char str_1=(char)num;
                char str_2='A';
                patientID="CHEM";
                patientID=patientID+str_1+str_2;
                n=1;
                val[j].first=str_1;
                val[j].second=str_2;
                val[j].num=to_string(n);
            }
            else{
                int num=str2[0]+1;
                char str_2=(char)num;
                patientID="CHEM";
                patientID=patientID+str1+str_2;
                n=1;
                val[j].first=str1;
                val[j].second=str_2;
                val[j].num=to_string(n);
            }

        }
        else{
            patientID="CHEM";
            patientID=patientID+str1+str2;
            val[j].first=str1;
                val[j].second=str2;
                val[j].num=to_string(n);
        }
        if(n/10==0){
            patientID+="000";
            string num=to_string(n);
            patientID+=num;
        }
        else if(n/100==0){
            patientID+="00";
            string num=to_string(n);
            patientID+=num;
        }
        else if(n/1000==0){
            patientID+="0";
            string num=to_string(n);
            patientID+=num;
        }
        else if(n/10000==0){
            string num=to_string(n);
            patientID+=num;
        }
        j++;
        in>>str;
        while(j<5){
            val[j].dep=str;
            in>>str;
            val[j].first=str;
            in>>str;
            val[j].second=str;
            in>>str;
            val[j].num=str;
            in>>str;
            j++;
        }
        ofstream out;
        out.open("Patient_ID.txt");
        j=0;
        while(j<5){
            out<<val[j].dep<<endl;
            out<<val[j].first<<endl;
            out<<val[j].second<<endl;
            out<<val[j].num<<endl;
            j++;
        }
    }
    void Display()
    {
        cout<<"---------------- Patient Details ----------------"<<endl;
        cout << "Patient ID: " << patientID << endl;
        //cout << "Appointment Number:"<<app_no<<endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Blood Type: " << blood << endl;
        cout << "Gender: " << gender << endl;
    }
    void choose_doctor(){                                      // Method to choose a doctor
        doc=0;                                                 // - Displays the room number and a message to the patient
        cout << "\n\nPlease Go To Room Number" << " 015A" << "\nThe Appointed Doctor Will Arrive Soon"<<endl;
    }
    void patient_data(){                                        // Method to store patient data
        ofstream out;
        out.open("Patient_Details.txt",ios::app);                // - Writes patient details to "Patient_Details.txt" file
        out<<"\n\n---------------- Patient Details ----------------"<<endl;
        out << "Patient ID:\n" << patientID << endl;
        //out << "Appointment Number:\n"<<app_no<<endl;
        out << "\nName:\n" << name << endl;
        out << "\nAge:\n" << age << endl;
        out << "\nBlood Type:\n" << blood << endl;
        out << "\nGender:\n" << gender << endl;
        out << "\nAddress:\n" << address << endl;
        out << "\nIllness Type:\n" << illness << endl;
        out << "---------------- Doctor's Details ----------------" << endl;
        out << "Employee ID:\n" << "CHEM1003" << endl;
        out << "\nName:\n" << "Divya Jain" << "  " << "MS" << endl;
        out << "\nCabin Number:\n" << "020" << endl;
        out << "\nMobile Number:\n" << "8011719088" << endl;
        out.close();
    }
    void print_prescription(){
        ofstream out;                                                  // Method to print prescription
        out.open("precription.txt");                                   // - Writes the prescription details to "prescription.txt" file
        out<<"---------------------------CITY HOSPITAL-----------------------------"<<endl;
        out<<"---------------- Patient Details ----------------"<<endl;
        out << "Patient ID: " << patientID << endl;
        //out << "Appointment Number:"<<app_no<<endl;
        out << "Name: " << name << endl;
        out << "Age: " << age << endl;
        out << "Blood Type: " << blood << endl;
        out << "Gender: " << gender << endl;
        out << "\nPlease Go To Room Number" << " 015A" << "\nThe Appointed Doctor Will Arrive Soon"<<endl;
        out<<"\nWishing You A Speedy Recovery"<<endl;
        out.close();
    }
};
struct doctor neuroDoctor[5] = {{"CHNR",1001,"Dr Sanjay Gupta","MS",101,"9864903412"},
{"CHNR",1002,"Dr Rajesh Kumar","DM Neurology",102,"8864854312"},
{"CHNR",1003,"Dr Shweta Tiwari","MCh Neurology",103,"9760653412"},
{"CHNR",1004,"Dr Sanjana Mehta","MD",104,"8864964398"},
{"CHNR",1005,"Dr Alok Ranjan","DM Neurology",105,"8876193412"}
};
class Neuro : public Patient                     // Neuro class definition

// Array of neuro doctors
// - Contains details of neuro doctors
{
public:
    
    void patient_id_generate(){
        int n=0;
        ifstream in;
        in.open("Patient_ID.txt");
        string str;
        int j=0;
        in>>str;
        while(str!="Neurology"){
            val[j].dep=str;
            in>>str;
            val[j].first=str;
            in>>str;
            val[j].second=str;
            in>>str;
            val[j].num=str;
            in>>str;
            j++;
        }
        val[j].dep=str;
        string str1;
        string str2;
        in>>str1;
        in>>str2;
        in>>str;
        int i=0;
        while(str[i]!='\0' && str[i]!='\n' && str[i]!=' '){
            n*=10;
            n+=((int)str[i])-((int)'0');
            i++;
        }
        n++;
        if(n==10000){
            cout<<"hii1"<<endl;
            if(str2=="Z"){
                int num=str1[0]+1;
                char str_1=(char)num;
                char str_2='A';
                patientID="CHNR";
                patientID=patientID+str_1+str_2;
                n=1;
                val[j].first=str_1;
                val[j].second=str_2;
                val[j].num=to_string(n);
            }
            else{
                int num=str2[0]+1;
                char str_2=(char)num;
                patientID="CHNR";
                patientID=patientID+str1+str_2;
                n=1;
                val[j].first=str1;
                val[j].second=str_2;
                val[j].num=to_string(n);
            }

        }
        else{
            patientID="CHNR";
            patientID=patientID+str1+str2;
            val[j].first=str1;
                val[j].second=str2;
                val[j].num=to_string(n);
        }
        if(n/10==0){
            patientID+="000";
            string num=to_string(n);
            patientID+=num;
        }
        else if(n/100==0){
            patientID+="00";
            string num=to_string(n);
            patientID+=num;
        }
        else if(n/1000==0){
            patientID+="0";
            string num=to_string(n);
            patientID+=num;
        }
        else if(n/10000==0){
            string num=to_string(n);
            patientID+=num;
        }
        j++;
        in>>str;
        while(j<5){
            val[j].dep=str;
            in>>str;
            val[j].first=str;
            in>>str;
            val[j].second=str;
            in>>str;
            val[j].num=str;
            in>>str;
            j++;
        }
       ofstream out;
        out.open("Patient_ID.txt");
        j=0;
        while(j<5){
            out<<val[j].dep<<endl;
            out<<val[j].first<<endl;
            out<<val[j].second<<endl;
            out<<val[j].num<<endl;
            j++;
        }
    }
    void Display()
    {
      // Display patient details        cout<<"---------------- Patient Details ----------------"<<endl;
        cout << "Patient ID: " << patientID << endl;
        cout << "Appointment Number: "<<app_no<<endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Blood Type: " << blood << endl;
        cout << "Gender: " << gender << endl;
        //cout << "Room No.: " << room_no << endl;
        // Display doctor's details
        cout << "---------------- Doctor's Details ----------------" << endl;
        cout << "Employee ID: " << neuroDoctor[doc-1].ID <<neuroDoctor[doc-1].empID << endl;
        cout << "Name: " << neuroDoctor[doc-1].name << "  " <<neuroDoctor[doc-1].qualification<< endl;
        cout << "Cabin Number: " << neuroDoctor[doc-1].cabinNo << endl;
        cout << "Mobile Number: " << neuroDoctor[doc-1].mobileNo << endl<<endl<<endl;
    }
    void input()
    {
      // Get patient details from the user
        cout<<"---------------- Patient Details ----------------"<<endl;
        cout << "Name: " << endl;
        fflush(stdin);
        getline(cin, name);
        cout << "Age: " << endl;
        cin >> age;
        cout << "Blood Type: " << endl;
        cin >> blood;
        cout<<"Illness Type:"<<endl;
        fflush(stdin);
        getline(cin,illness);
        cout << "Phone Number: " << endl;
        cin >> phone_no;
        cout << "Gender: " << endl;
        cin >> gender;
        cout << "Address: " << endl;
        fflush(stdin);
        getline(cin, address);
    }
    void choose_doctor(){
       // Allow the patient to choose a doctor
        cout<<"Choose Your Doctor"<<endl;
        //cout<<"\n1.Dr Sanjay Gupta\n2.Dr Rajesh Kumar\n3.Dr Shweta Tiwari\n4.Dr Sanjana Mehta\n5.Dr Alok Ranjan"<<endl;
        cout<<"\n1.Dr Sanjay Gupta ";
        if(nr[0]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<"\n2.Dr Rajesh Kumar ";
        if(nr[1]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<"\n3.Dr Shweta Tiwari ";
        if(nr[2]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<"\n4.Dr Sanjana Mehta ";
        if(nr[3]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<"\n5.Dr Alok Ranjan ";
        if(nr[4]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<endl;
        cin>>doc;
    }
    void print_prescription(){
       // Generate and print the prescription details
        ofstream out;
        out.open("precription.txt");
        out<<"---------------------------CITY HOSPITAL-----------------------------"<<endl;
        out<<"---------------- Patient Details ----------------"<<endl;
        out << "Patient ID: " << patientID << endl;
        out << "Appointment Number: "<<app_no<<endl;
        out << "Name: " << name << endl;
        out << "Age: " << age << endl;
        out << "Blood Type: " << blood << endl;
        out << "Gender: " << gender << endl;
        //out << "Room No.: " << room_no << endl;
        out << "---------------- Doctor's Details ----------------" << endl;
        out << "Name: " << neuroDoctor[doc-1].name << "  " <<neuroDoctor[doc-1].qualification<< endl;
        out << "Cabin Number: " << neuroDoctor[doc-1].cabinNo << endl;
        out << "Mobile Number: " << neuroDoctor[doc-1].mobileNo << endl<<endl<<endl;
        out<<"\n\n\n";
        out<<"Total Consultation Fee: Rs.500"<<endl;
        out<<"\nWishing You A Speedy Recovery"<<endl;
        out.close();
    }
    void patient_data(){
      // Open the file in append mode to add patient data
        ofstream out;
        // Write patient details to the file
        out.open("Patient_Details.txt",ios::app);
        out<<"\n\n---------------- Patient Details ----------------"<<endl;
        out << "Patient ID:\n" << patientID << endl;
        //out << "\nRoom No.:\n" << room_no << endl;
        //out << "Appointment Number:\n"<<app_no<<endl;
        out << "\nName:\n" << name << endl;
        out << "\nAge:\n" << age << endl;
        out << "\nBlood Type:\n" << blood << endl;
        out << "\nIllness Type:\n" << illness << endl;
        out << "\nGender:\n" << gender << endl;
        out << "\nAddress:\n" << address << endl;
        // Write doctor's details to the file
        out << "---------------- Doctor's Details ----------------" << endl;
        out << "Doctor ID:\n" << neuroDoctor[doc-1].ID << neuroDoctor[doc-1].empID << endl;
        out << "\nName:\n" << neuroDoctor[doc-1].name << "  " <<neuroDoctor[doc-1].qualification<< endl;
        out << "\nCabin Number:\n" << neuroDoctor[doc-1].cabinNo << endl;
        out << "\nMobile Number:\n" << neuroDoctor[doc-1].mobileNo << endl<<endl<<endl;
        out.close();
    }
};
struct doctor orthoDoctor[5]={{"CHOP",1001,"Dr Ashutosh Shukla","MD",201,"8009978373"},
{"CHOP",1002,"Dr Riddhi Rathi","MS",202,"8864853433"},
{"CHOP",1003,"Dr Pradeep Rai","MCh Orthopedics",203,"8430653413"},
{"CHOP",1004,"Dr Ashish Gupta","DM Orthopedics",204,"8483203413"},
{"CHOP",1005,"Dr Sania Sharma","MCH Orthopedics",205,"8430662918"}
};
class Ortho : public Patient {
public:
 // Structure to store orthopedic doctor details
    
    void patient_id_generate(){
       // Function to generate patient ID
        // Reads patient ID details from "Patient_ID.txt" file, updates the ID, and writes back to the file
        // Uses the 'val' array to store and manipulate the ID details
        int n=0;
        ifstream in;
        in.open("Patient_ID.txt");
        string str;
        int j=0;
        in>>str;
        while(str!="Orthopedics"){
            val[j].dep=str;
            in>>str;
            val[j].first=str;
            in>>str;
            val[j].second=str;
            in>>str;
            val[j].num=str;
            in>>str;
            j++;
        }
        val[j].dep=str;
        string str1;
        string str2;
        in>>str1;
        in>>str2;
        in>>str;
        int i=0;
        while(str[i]!='\0' && str[i]!='\n' && str[i]!=' '){
            n*=10;
            n+=((int)str[i])-((int)'0');
            i++;
        }
        n++;
        if(n==10000){
            cout<<"hii1"<<endl;
            if(str2=="Z"){
                int num=str1[0]+1;
                char str_1=(char)num;
                char str_2='A';
                patientID="CHOP";
                patientID=patientID+str_1+str_2;
                n=1;
                val[j].first=str_1;
                val[j].second=str_2;
                val[j].num=to_string(n);
            }
            else{
                int num=str2[0]+1;
                char str_2=(char)num;
                patientID="CHOP";
                patientID=patientID+str1+str_2;
                n=1;
                val[j].first=str1;
                val[j].second=str_2;
                val[j].num=to_string(n);
            }

        }
        else{
            patientID="CHOP";
            patientID=patientID+str1+str2;
            val[j].first=str1;
                val[j].second=str2;
                val[j].num=to_string(n);
        }
        if(n/10==0){
            patientID+="000";
            string num=to_string(n);
            patientID+=num;
        }
        else if(n/100==0){
            patientID+="00";
            string num=to_string(n);
            patientID+=num;
        }
        else if(n/1000==0){
            patientID+="0";
            string num=to_string(n);
            patientID+=num;
        }
        else if(n/10000==0){
            string num=to_string(n);
            patientID+=num;
        }
        j++;
        in>>str;
        while(j<5){
            val[j].dep=str;
            in>>str;
            val[j].first=str;
            in>>str;
            val[j].second=str;
            in>>str;
            val[j].num=str;
            in>>str;
            j++;
        }
        ofstream out;
        out.open("Patient_ID.txt");
        j=0;
        while(j<5){
            out<<val[j].dep<<endl;
            out<<val[j].first<<endl;
            out<<val[j].second<<endl;
            out<<val[j].num<<endl;
            j++;
        }
    }
    void Display()
    {
      // Function to display patient and doctor details
        cout<<"---------------- Patient Details ----------------"<<endl;
        cout << "Patient ID: " << patientID << endl;
        cout << "Appointment Number: "<<app_no<<endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Blood Type: " << blood << endl;
        cout << "Gender: " << gender << endl;
        //cout << "Room No.: " << room_no << endl;
        cout << "---------------- Doctor's Details ----------------" << endl;
        cout << "Employee ID: " << orthoDoctor[doc-1].ID <<orthoDoctor[doc-1].empID << endl;
        cout << "Name: " << orthoDoctor[doc-1].name << "  " << orthoDoctor[doc-1].qualification<< endl;
        cout << "Cabin Number: " << orthoDoctor[doc-1].cabinNo << endl;
        cout << "Mobile Number: " << orthoDoctor[doc-1].mobileNo << endl<<endl<<endl;
    }
    void input()
    {
      // Function to input patient details
        cout<<"---------------- Patient Details ----------------"<<endl;
        cout << "Name: " << endl;
        fflush(stdin);
        getline(cin, name);
        cout << "Age: " << endl;
        cin >> age;
        cout << "Blood Type: " << endl;
        cin >> blood;
        cout<<"Illness Type:"<<endl;
        fflush(stdin);
        getline(cin,illness);
        cout << "Phone Number: " << endl;
        cin >> phone_no;
        cout << "Gender: " << endl;
        cin >> gender;
        cout << "Address: " << endl;
        fflush(stdin);
        getline(cin, address);
    }
    void choose_doctor(){
       // Function to choose a doctor
        cout<<"Choose Your Doctor"<<endl;
        // Display the available doctors and their appointment status
        //cout<<"\n1.Dr Ashutosh Shukla\n2.Dr Riddhi Rathi\n3.Dr Pradeep Rai\n4.Dr Ashish Gupta\n5.Dr Sania Sharma"<<endl;
        cout<<"\n1.Dr Ashutosh Shukla ";
        // Display information for other doctors as well
        if(op[0]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<"\n2.Dr Riddhi Rathi ";
        if(op[1]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<"\n3.Dr Pradeep Rai ";
        if(op[2]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<"\n4.Dr Ashish Gupta ";
        if(op[3]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<"\n5.Dr Sania Sharma ";
        if(op[4]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<endl;
        cin>>doc;
        // User input for doctor selection
    }
    void print_prescription(){
        ofstream out;
        out.open("precription.txt");
        out<<"---------------------------CITY HOSPITAL-----------------------------"<<endl;
        out<<"---------------- Patient Details ----------------"<<endl;
        out << "Patient ID: " << patientID << endl;
        out << "Appointment Number: "<<app_no<<endl;
        out << "Name: " << name << endl;
        out << "Age: " << age << endl;
        out << "Blood Type: " << blood << endl;
        out << "Gender: " << gender << endl;
        //out << "Room No.: " << room_no << endl;
        out << "---------------- Doctor's Details ----------------" << endl;
        out << "Name: " << orthoDoctor[doc-1].name << "  " << orthoDoctor[doc-1].qualification<< endl;
        out << "Cabin Number: " << orthoDoctor[doc-1].cabinNo << endl;
        out << "Mobile Number: " << orthoDoctor[doc-1].mobileNo << endl<<endl<<endl;
        out<<"\n\n\n";
        out<<"Total Consultation Fee: Rs.500"<<endl;
        out<<"\nWishing You A Speedy Recovery"<<endl;
        out.close();
        // Writes the doctor's details, consultation fee, and wishes for a speedy recovery to the file
    }
    void patient_data(){
        ofstream out;
        out.open("Patient_Details.txt",ios::app);
        out<<"\n\n---------------- Patient Details ----------------"<<endl;
        out << "Patient ID:\n" << patientID << endl;
        //out << "\nRoom No.: \n" << room_no << endl;
        //out << "Appointment Number:\n"<<app_no<<endl;
        out << "\nName:\n" << name << endl;
        out << "\nAge:\n" << age << endl;
        out << "\nBlood Type:\n" << blood << endl;
        out << "\nIllness Type:\n" << illness << endl;
        out << "\nGender:\n" << gender << endl;
        out << "\nAddress:\n" << address << endl;
        out << "---------------- Doctor's Details ----------------" << endl;
        out << "Doctor ID:\n" << orthoDoctor[doc-1].ID << orthoDoctor[doc-1].empID << endl;
        out << "\nName:\n" << orthoDoctor[doc-1].name << "  " <<orthoDoctor[doc-1].qualification<< endl;
        out << "\nCabin Number:\n" << orthoDoctor[doc-1].cabinNo << endl;
        out << "\nMobile Number:\n" << orthoDoctor[doc-1].mobileNo << endl<<endl<<endl;
        out.close();
        // Appends the patient details, doctor's details, and other information to the "Patient_Details.txt" file
    }
};
struct doctor medicineDoctor[5]={{"CHMC",1001,"Dr Vikram Patel","MD",301,"9987364245"},
{"CHMC",1002,"Dr Atul Pathak","MD",302,"9948372245"},
{"CHMC",1003,"Dr Ashok Sen","MD",303,"9987483925"},
{"CHMC",1004,"Dr Lakshmi Narayan","MD",304,"9987338294"},
{"CHMC",1005,"Dr Neeraj Sharma","MD",305,"9987334261"}
};
 
class Medicine : public Patient {
   // Inherits from the Patient class
public:
       void patient_id_generate(){
      // Generates the patient ID for medicine patients
        int n=0;
        ifstream in;
        in.open("Patient_ID.txt");
        //Reads the values from the input file and stores them in the val array

        // Reads the remaining values from the input file and stores them in the val array
        string str;
        int j=0;
        in>>str;
        while(str!="Medicine"){
            val[j].dep=str;
            in>>str;
            val[j].first=str;
            in>>str;
            val[j].second=str;
            in>>str;
            val[j].num=str;
            in>>str;
            j++;
        }
        val[j].dep=str;
        string str1;
        string str2;
        in>>str1;
        in>>str2;
        in>>str;
        // Reads the values for str1, str2, and str
        int i=0;
        while(str[i]!='\0' && str[i]!='\n' && str[i]!=' '){
            n*=10;
            n+=((int)str[i])-((int)'0');
            i++;
        }
        n++;
         // Converts str to an integer value
        if(n==10000){
            cout<<"hii1"<<endl;
            if(str2=="Z"){
                int num=str1[0]+1;
                char str_1=(char)num;
                char str_2='A';
                patientID="CHMC";
                patientID=patientID+str_1+str_2;
                n=1;  // Sets n to 1
                val[j].first=str_1;
                val[j].second=str_2;
                val[j].num=to_string(n);
            }
            else{
                int num=str2[0]+1;
                char str_2=(char)num;
                patientID="CHMC";// Sets the patientID with "CHMC" + str_1 + str_2
                patientID=patientID+str1+str_2;
                // Updates the values in the val array
                val[j].first=str1;
                val[j].second=str_2;
                val[j].num=to_string(n);
            }

        }
        else{
            patientID="CHMC";
            patientID=patientID+str1+str2;
            val[j].first=str1;
                val[j].second=str2;
                val[j].num=to_string(n);
        }
        if(n/10==0){
            patientID+="000";
            string num=to_string(n);
            patientID+=num;
        }
        else if(n/100==0){
            patientID+="00";
            string num=to_string(n);
            patientID+=num;
        }
        else if(n/1000==0){
            patientID+="0";
            string num=to_string(n);
            patientID+=num;
        }
        else if(n/10000==0){
            string num=to_string(n);
            patientID+=num;
        }
        j++;
        in>>str;
        while(j<5){
            val[j].dep=str;
            in>>str;
            val[j].first=str;
            in>>str;
            val[j].second=str;
            in>>str;
            val[j].num=str;
            in>>str;
            j++;
        }
        ofstream out;
        out.open("Patient_ID.txt");
        j=0;
        while(j<5){
            out<<val[j].dep<<endl;
            out<<val[j].first<<endl;
            out<<val[j].second<<endl;
            out<<val[j].num<<endl;
            j++;
        }
    }
    void Display()
    {
        cout<<"---------------- Patient Details ----------------"<<endl;
        cout << "Patient ID: " << patientID << endl;
        cout << "Appointment Number: "<<app_no<<endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Blood Type: " << blood << endl;
        cout << "Gender: " << gender << endl;
        //cout << "Room No.: " << room_no << endl;
        cout << "---------------- Doctor's Details ----------------" << endl;
        cout << "Employee ID: " << medicineDoctor[doc-1].ID <<medicineDoctor[doc-1].empID << endl;
        cout << "Name: " << medicineDoctor[doc-1].name << "  " << medicineDoctor[doc-1].qualification<< endl;
        cout << "Cabin Number: " << medicineDoctor[doc-1].cabinNo << endl;
        cout << "Mobile Number: " << medicineDoctor[doc-1].mobileNo << endl<<endl<<endl;
    }
    void input()
    {
        cout<<"---------------- Patient Details ----------------"<<endl;
        cout << "Name: " << endl;
        fflush(stdin);
        getline(cin, name);
        cout << "Age: " << endl;
        cin >> age;
         // Read the patient's age from the user
        cout << "Blood Type: " << endl;
        cin >> blood;
        // Read the patient's blood type from the user
        cout<<"Illness Type:"<<endl;
        fflush(stdin);
        getline(cin,illness);
        // Read the type of illness from the user
        cout << "Phone Number: " << endl;
        cin >> phone_no;
        // Read the patient's phone number from the user
        cout << "Gender: " << endl;
        cin >> gender;
         // Read the patient's gender from the user
        cout << "Address: " << endl;
        fflush(stdin);
        getline(cin, address);
        // Read the patient's address from the user
    }
    void choose_doctor(){
        cout<<"Choose Your Doctor"<<endl;
        // Display the available doctors and their appointment status
        //cout<<"\n1.Dr Vikram Patel\n2.Dr Atul Pathak\n3.Dr Ashok Sen\n4.Dr Lakshmi Narayan\n5.Dr Neeraj Sharma"<<endl;
        cout<<"\n1.Dr Vikram Patel ";
        if(mc[0]>=30){
            cout<<"------- Appoinments are full for today";
        }
         // Check if appointments for Dr Vikram Patel are full, and display a message accordingly
        cout<<"\n2.Dr Atul Pathak ";
        if(mc[1]>=30){
            cout<<"------- Appoinments are full for today";
        }
        // Check if appointments for Dr Atul Pathak are full, and display a message accordingly
        cout<<"\n3.Dr Ashok Sen ";
        if(mc[2]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<"\n4.Dr Lakshmi Narayan";
        if(mc[3]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<"\n5.Dr Neeraj Sharma ";
        if(mc[4]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<endl;
        cin>>doc;
        // Check if appointments for Dr Ashok Sen are full, and display a message accordingly
    // Repeat the above steps for the remaining doctors
    }
    void print_prescription(){
      // Open a file to write the prescription
        ofstream out;
        out.open("precription.txt");
        // Write the hospital name and patient details
        out<<"---------------------------CITY HOSPITAL-----------------------------"<<endl;
        out<<"---------------- Patient Details ----------------"<<endl;
        out << "Patient ID: " << patientID << endl;
        out << "Appointment Number: "<<app_no<<endl;
        out << "Name: " << name << endl;
        out << "Age: " << age << endl;
        out << "Blood Type: " << blood << endl;
        out << "Gender: " << gender << endl;
        //out << "Room No.: " << room_no << endl;
        // Write the doctor's details
        out << "---------------- Doctor's Details ----------------" << endl;
        out << "Name: " << medicineDoctor[doc-1].name << "  " << medicineDoctor[doc-1].qualification<< endl;
        out << "Cabin Number: " << medicineDoctor[doc-1].cabinNo << endl;
        out << "Mobile Number: " << medicineDoctor[doc-1].mobileNo << endl<<endl<<endl;
        out<<"\n\n\n";
        // Write the consultation fee and recovery message
        out<<"Total Consultation Fee: Rs.500"<<endl;
        out<<"\nWishing You A Speedy Recovery"<<endl;
        // Close the file
        out.close();
    }
    void patient_data(){
      // Open a file to append patient details
        ofstream out;
        out.open("Patient_Details.txt",ios::app);
         // Write the patient details
        out<<"\n\n---------------- Patient Details ----------------"<<endl;
        out << "Patient ID:\n" << patientID << endl;
        //out << "\nRoom No.:\n" << room_no << endl;
        //out << "Appointment Number:"<<app_no<<endl;
        out << "\nName:\n" << name << endl;
        out << "\nAge:\n" << age << endl;
        out << "\nBlood Type:\n" << blood << endl;
        out << "\nIllness Type:\n" << illness << endl;
        out << "\nGender:\n" << gender << endl;
        out << "\nAddress:\n" << address << endl;
        out << "---------------- Doctor's Details ----------------" << endl;
        out << "Doctor ID:\n" << medicineDoctor[doc-1].ID << medicineDoctor[doc-1].empID << endl;
        out << "\nName:\n" << medicineDoctor[doc-1].name << "  " <<medicineDoctor[doc-1].qualification<< endl;
        out << "\nCabin Number:\n" << medicineDoctor[doc-1].cabinNo << endl;
        out << "\nMobile Number:\n" << medicineDoctor[doc-1].mobileNo << endl<<endl<<endl;
        out.close();
        // Close the file
    }
};
 struct doctor surgeryDoctor[5]={{"CHSR",1001,"Dr Ashok Sen","MS",401,"9938366345"},
 {"CHSR",1002,"Dr Ashok Rajagopal","MS",402,"9932816445"},
 {"CHSR",1003,"Dr Alwin Kurian","MS",403,"9938343287"},
 {"CHSR",1004,"Dr Ajeesh Chacko","MS",404,"9938312345"},
 {"CHSR",1005,"Dr Melvin Salvius","MS",405,"9938309876"}
 };

class Surgery : public Patient {
public:
       void patient_id_generate(){
        int n=0;
        ifstream in;
        in.open("Patient_ID.txt");
        string str;
        int j=0;
        in>>str;
        while(str!="Surgery"){
          // Read patient ID values until "Surgery" is encountered
            val[j].dep=str;
            in>>str;
            val[j].first=str;
            in>>str;
            val[j].second=str;
            in>>str;
            val[j].num=str;
            in>>str;
            j++;
        }
        val[j].dep=str;
        string str1;
        string str2;
        in>>str1;
        in>>str2;
        in>>str;
        int i=0;
        while(str[i]!='\0' && str[i]!='\n' && str[i]!=' '){
            n*=10;
            n+=((int)str[i])-((int)'0');
            i++;
        }
        n++;
        if(n==10000){
            cout<<"hii1"<<endl;
            if(str2=="Z"){
               // Increment the first character of str1 and set str2 to 'A' to generate the patient ID
                int num=str1[0]+1;
                char str_1=(char)num;
                char str_2='A';
                patientID="CHSR";
                patientID=patientID+str_1+str_2;
                n=1;
                val[j].first=str_1;
                val[j].second=str_2;
                val[j].num=to_string(n);
            }
            else{
               // Increment the second character of str2 to generate the patient ID
                int num=str2[0]+1;
                char str_2=(char)num;
                patientID="CHSR";
                patientID=patientID+str1+str_2;
                n=1;
                val[j].first=str1;
                val[j].second=str_2;
                val[j].num=to_string(n);
            }

        }
        else{
            patientID="CHSR";
            patientID=patientID+str1+str2;
            val[j].first=str1;
                val[j].second=str2;
                val[j].num=to_string(n);
        }
        if(n/10==0){
            patientID+="000";
            string num=to_string(n);
            patientID+=num;
        }
        else if(n/100==0){
            patientID+="00";
            string num=to_string(n);
            patientID+=num;
        }
        else if(n/1000==0){
            patientID+="0";
            string num=to_string(n);
            patientID+=num;
        }
        else if(n/10000==0){
            string num=to_string(n);
            patientID+=num;
        }
        // Generates the patient ID based on the value of n

        j++;
        in>>str;
        // Increments j by 1 and reads the next string from the input file

        while(j<5){
            val[j].dep=str;
            in>>str;
            val[j].first=str;
            in>>str;
            val[j].second=str;
            in>>str;
            val[j].num=str;
            in>>str;
            j++;
        }

// Writes the updated values from the val array to the output file
        ofstream out;
        out.open("Patient_ID.txt");
        j=0;
        while(j<5){
            out<<val[j].dep<<endl;
            out<<val[j].first<<endl;
            out<<val[j].second<<endl;
            out<<val[j].num<<endl;
            j++;
        }
    }
    void Display()
    {
        cout<<"---------------- Patient Details ----------------"<<endl;
        cout << "Patient ID: " << patientID << endl;
        cout << "Appointment Number: "<<app_no<<endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Blood Type: " << blood << endl;
        cout << "Gender: " << gender << endl;
        //cout << "Room No.: " << room_no << endl;
        cout << "---------------- Doctor's Details ----------------" << endl;
        cout << "Employee ID: " << surgeryDoctor[doc-1].ID <<surgeryDoctor[doc-1].empID << endl;
        cout << "Name: " << surgeryDoctor[doc-1].name << "  " << surgeryDoctor[doc-1].qualification<< endl;
        cout << "Cabin Number: " << surgeryDoctor[doc-1].cabinNo << endl;
        cout << "Mobile Number: " << surgeryDoctor[doc-1].mobileNo << endl<<endl<<endl;
    // Displays the patient and doctor details
    }
    void input()
    {
      // Reads the patient details from the user
        cout<<"---------------- Patient Details ----------------"<<endl;
        cout << "Name: " << endl;
        fflush(stdin);
        getline(cin, name);
        cout << "Age: " << endl;
        cin >> age;
        cout << "Blood Type: " << endl;
        cin >> blood;
        cout<<"Surgery Type:"<<endl;
        fflush(stdin);
        getline(cin,illness);
        cout << "Phone Number: " << endl;
        cin >> phone_no;
        cout << "Gender: " << endl;
        cin >> gender;
        cout << "Address: " << endl;
        fflush(stdin);
        getline(cin, address);
    }
    void choose_doctor(){
      // Allows the user to choose a doctor
        cout<<"Choose Your Doctor"<<endl;
        //cout<<"\n1.Dr Ashok Sen\n2.Dr Ashok Rajagopal\n3.Dr Alwin Kurian\n4.Dr Ajeesh Chacko\n5.Dr Melvin Salvius"<<endl;
        cout<<"\n1.Dr Ashok Sen ";
        if(sr[0]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<"\n2.Dr Ashok Rajagopal ";
        if(sr[1]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<"\n3.Dr Alwin Kurian ";
        if(sr[2]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<"\n4.Dr Ajeesh Chacko ";
        if(sr[3]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<"\n5.Dr Melvin Salvius ";
        if(sr[4]>=30){
            cout<<"------- Appoinments are full for today";
        }
        cout<<endl;
        cin>>doc;
    }
    void print_prescription(){
        ofstream out;
        out.open("precription.txt");
        out<<"---------------------------CITY HOSPITAL-----------------------------"<<endl;
        out<<"---------------- Patient Details ----------------"<<endl;
        out << "Patient ID: " << patientID << endl;
        out << "Appointment Number: "<<app_no<<endl;
        out << "Name: " << name << endl;
        out << "Age: " << age << endl;
        out << "Blood Type: " << blood << endl;
        out << "Gender: " << gender << endl;
        //out << "Room No.: " << room_no << endl;
        out << "---------------- Doctor's Details ----------------" << endl;
        out << "Name: " << surgeryDoctor[doc-1].name << "  " << surgeryDoctor[doc-1].qualification<< endl;
        out << "Cabin Number: " << surgeryDoctor[doc-1].cabinNo << endl;
        out << "Mobile Number: " << surgeryDoctor[doc-1].mobileNo << endl<<endl<<endl;
        out<<"\n\n\n";
        out<<"Total Consultation Fee: Rs.500"<<endl;
        out<<"\nWishing You A Speedy Recovery"<<endl;
        out.close();
    }
    void patient_data(){
        ofstream out;
         // Write patient details to the file
        out.open("Patient_Details.txt",ios::app);
        out<<"\n\n---------------- Patient Details ----------------"<<endl;
        out << "Patient ID:\n" << patientID << endl;
        //out << "\nRoom No.:\n" << room_no << endl;
        //out << "Appointment Number:"<<app_no<<endl;
        out << "Name:\n" << name << endl;
        out << "\nAge:\n" << age << endl;
        out << "\nBlood Type:\n" << blood << endl;
        out << "\nSurgery Type:\n" << illness << endl;
        out << "\nGender:\n" << gender << endl;
        out << "\nAddress:\n" << address << endl;
        // Write doctor's details to the file
        out << "---------------- Doctor's Details ----------------" << endl;
        out << "Doctor ID:\n" << surgeryDoctor[doc-1].ID << surgeryDoctor[doc-1].empID << endl;
        out << "\nName:\n" << surgeryDoctor[doc-1].name << "  " <<surgeryDoctor[doc-1].qualification<< endl;
        out << "\nCabin Number:\n" << surgeryDoctor[doc-1].cabinNo << endl;
        out << "\nMobile Number:\n" << surgeryDoctor[doc-1].mobileNo << endl<<endl<<endl;
        // Close the file stream
        out.close();
    }
};

struct test_available{
    string Test_name ;// Holds the name of the available test
    int cost ;// Holds the cost of the test
    int room_no ; // Holds the room number where the test can be conducted
};
struct test_available test_req[10] = {{"X-Ray",700,521},
{"Blood Test",500,011},
{"MRI",4000,520},
{"Urinalysis",150,512},
{"Lipid Profile",500,513},
{"Endoscopy",2000,522},
{"Mamography",2000,533},
{"Biospy",1000,534},
{"Ultra-Sound",1000,544},
{"Stool-Analysis",500,545}};

class Test{
    public :
 // Array of available tests and their details
          // Function to generate the test bill
    void bill(){
        string patient_id;
        string patient_name;
        // Prompt user to enter patient ID and name
        cout<<"Enter Patient ID: ";
        cin>>patient_id;
        cout<<"Enter Patient's Name: ";
        fflush(stdin);
        getline(cin,patient_name);
        int total=0;
         // Display available tests and prompt user to select
        cout<<"Select the required tests:\n1.X-Ray\n2.Blood Test\n3.MRI\n4.Urinalysis\n5.Lipid Profile\n6.Endoscopy\n7.Mamography\n8.Biospy\n9.Ultra-Sound\n10.Stool-Analysis\n11.End"<<endl;
        int tests=0;
        cin>>tests;
        ofstream out;
        out.open("precription.txt");
        out<<"---------------------------CITY HOSPITAL-----------------------------"<<endl;
        out<<"Patient ID: "<<patient_id<<endl;
        out<<"Patient Name: "<<patient_name<<endl;
        out<<"\n\n\n";
        out<<"Test Name                     Amount                       Room"<<endl;
         // Iterate over selected tests and calculate total amount
        while(tests<11 && tests>0){
            out<<test_req[tests-1].Test_name<<"---------------------------"<<test_req[tests-1].cost<<"----------------------"<<test_req[tests-1].room_no<<endl;
            total+=test_req[tests-1].cost;
            cin>>tests;
        }
        // Write total amount to the prescription file and display it on the console
        out<<"TOTAL AMOUNT: "<<total<<endl;
        cout<<"TOTAL AMOUNT: "<<total<<endl;
        out.close();
    }
};

int main(){
  // Call the appointments function to update appointment details
    appointments();
    appointments();
    // Prompt user for the choice of operation
    int choice_1;
    cout<<"ENTER:\n1.EMERGENCY\n2.NORMAL CONSULTATION\n3.HOSPITALISATION\n4.DISCHARGE\n5.TESTS\n6.END OF THE DAY"<<endl;
    cin>>choice_1;
    // Perform operations based on user's choice
    if(choice_1==1){
      // Handle emergency case
        Emergency patient1;
        Patient *ptr=&patient1;
        ptr->input();
        ptr->patient_id_generate();
        ptr->Display();
        ptr->choose_doctor();
        ptr->print_prescription();
        ptr->patient_data();
    }
    else if(choice_1==2){
      // Handle normal consultation case
        int choice_2;
        cout<<"ENTER THE TYPE:\n1.NEUROLOGY\n2.ORTHOPEDICS\n3.MEDICINE\n4.SURGERY"<<endl;
        cin>>choice_2;
        int fl=0;
        int i;
        while(fl==0){
        if(choice_2==1){
           // Handle neurology case

            int choice_3;
            i=0;
            Neuro patient1;
            Patient *ptr=&patient1;
            ptr->input();
            ptr->patient_id_generate();
            ptr->choose_doctor();
            ptr->generate_appointmentNo(choice_2);
            while(ptr->app_no>30 && i<=5){
                cout<<"Doctor Not Available.\n1.To choose another doctor\n2.Come next day"<<endl;
                int choice_3;
                cin>>choice_3;
                if(choice_3==1){
                    nr[(ptr->doc)-1]-=1;
                    i++;
                    cout<<"Please choose another doctor"<<endl;
                    ptr->choose_doctor();
                    ptr->generate_appointmentNo(choice_2);
                }
                else{
                    i=-1;
                    break;
                }
            }
            if(i<=5 && i!=-1){
                ptr->Display();
                ptr->print_prescription();
                ptr->patient_data();
            }
            else if(i==-1){
                cout<<"Your chosen Doctor is not available.Please come tomorrow"<<endl;
            }
            else{
                cout<<"No Doctor Available.Please Come Tomorrow"<<endl;
                fl=1;
            }
            break;
        }
        else if(choice_2==2){
           // Handle orthopedics case
            i=0;
            Ortho patient1;
            Patient *ptr=&patient1;
            ptr->input();
            ptr->patient_id_generate();
            ptr->choose_doctor();
            ptr->generate_appointmentNo(choice_2);
            while(ptr->app_no>30 && i<=5){
                cout<<"Doctor Not Available.\n1.To choose another doctor\n2.Come next day"<<endl;
                int choice_3;
                cin>>choice_3;
                if(choice_3==1){
                    op[(ptr->doc)-1]-=1;
                    i++;
                    cout<<"Please choose another doctor"<<endl;
                    ptr->choose_doctor();
                    ptr->generate_appointmentNo(choice_2);
                }
                else{
                    i=-1;
                    break;
                }
            }
            if(i<=5 && i!=-1){
                ptr->Display();
                ptr->print_prescription();
                ptr->patient_data();
            }
            else if(i==-1){
                cout<<"Your chosen Doctor is not available.Please come tomorrow"<<endl;
            }
            else{
                cout<<"No Doctor Available.Please Come Tomorrow"<<endl;
                fl=1;
            }
            break;
        }
        else if(choice_2==3){
           // Handle medicine case
            i=0;
            Medicine patient1;
            Patient *ptr=&patient1;
            ptr->input();
            ptr->patient_id_generate();
            ptr->choose_doctor();
            ptr->generate_appointmentNo(choice_2);
            while(ptr->app_no>30 && i<=5){
                cout<<"Doctor Not Available.\n1.To choose another doctor\n2.Come next day"<<endl;
                int choice_3;
                cin>>choice_3;
                if(choice_3==1){
                    mc[(ptr->doc)-1]-=1;
                    i++;
                    cout<<"Please choose another doctor"<<endl;
                    ptr->choose_doctor();
                    ptr->generate_appointmentNo(choice_2);
                }
                else{
                    i=-1;
                    break;
                }
            }
            if(i<=5 && i!=-1){
                ptr->Display();
                ptr->print_prescription();
                ptr->patient_data();
            }
            else if(i==-1){
                cout<<"Your chosen Doctor is not available.Please come tomorrow"<<endl;
            }
            else{
                cout<<"No Doctor Available.Please Come Tomorrow"<<endl;
                fl=1;
            }
            break;
        }
        else if(choice_2==4){
          // Handle surgery case
            i=0;
            Surgery patient1;
            Patient *ptr=&patient1;
            ptr->input();
            ptr->patient_id_generate();
            ptr->choose_doctor();
            ptr->generate_appointmentNo(choice_2);
            while(ptr->app_no>30 && i<=5){
                cout<<"Doctor Not Available.\n1.To choose another doctor\n2.Come next day"<<endl;
                int choice_3;
                cin>>choice_3;
                if(choice_3==1){
                    nr[(ptr->doc)-1]-=1;
                    i++;
                    cout<<"Please choose another doctor"<<endl;
                    ptr->choose_doctor();
                    ptr->generate_appointmentNo(choice_2);
                }
                else{
                    i=-1;
                    break;
                }
            }
            if(i<=5 && i!=-1){
                ptr->Display();
                ptr->print_prescription();
                ptr->patient_data();
            }
            else if(i==-1){
                cout<<"Your chosen Doctor is not available.Please come tomorrow"<<endl;
            }
            else{
                cout<<"No Doctor Available.Please Come Tomorrow"<<endl;
                fl=1;
            }
            break;
        }
        else{
           // Handle invalid input
            cout<<"Invalid Input"<<endl;
            cout<<"ENTER THE TYPE:\n1.NEUROLOGY\n2.ORTHOPEDICS\n3.MEDICINE\n4.SURGERY"<<endl;
            cin>>choice_2;
        }
        }
    }
    else if(choice_1==3){
       // Handle hospitalization case
        string patientid;
        cout<<"Enter Patient ID:";
        cin>>patientid;
        string patientname;
        cout<<"Enter Patient's Name: ";
        fflush(stdin);
        getline(cin,patientname);
        cout<<"Enter Number of Days: ";
        int days;
        cin>>days;
        roomallotment();
        calbill(patientname,patientid,days);
    }
    else if(choice_1==4){
       // Handle discharge case
        string patientid;
        cout<<"Enter Patient's ID: ";
        cin>>patientid;
        discharge();
    }
    else if(choice_1==5){
      // Handle tests case
        Test patient1;
        patient1.bill();
    }
    else if(choice_1==6){
       // Handle end of the day operations
        ofstream out;
        out.open("app.txt");
        out<<"--------------------APPOINTMENT DETAILS--------------------"<<endl;
        out<<"\nNEUROLOGY"<<endl;
        out<<"0\n0\n0\n0\n0"<<endl;
        out<<"\nORTHOPEDICS"<<endl;
        out<<"0\n0\n0\n0\n0"<<endl;
        out<<"\nMEDICINE"<<endl;
        out<<"0\n0\n0\n0\n0"<<endl;
        out<<"\nSURGERY"<<endl;
        out<<"0\n0\n0\n0\n0"<<endl;
    }
    else{
        cout<<"Invalid Input"<<endl;
    }
return 0;
}