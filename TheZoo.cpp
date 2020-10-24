#include <iostream>
#include <jni.h>
#include <fstream> //input from a file
#include <vector>  //using vectors
#include <string>
using namespace std;

vector<string> zooFile;  //Do i put this up top to be global??

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

void AddAnimal()
{

	string trackNum;
	string anName;
	string anType;
	string subType;
	int eggs;
	int nurse;
	string newString;
	char saveDel;

	cout << "enter track number" << endl;
	cin >> trackNum;
	cout << "enter animal name" << endl;
	cin >> anName;
	cout << "enter animal type" << endl;
	cin >> anType;
	if(anType == "Oviparous"){
		nurse = 0;
		cout << "enter amount of eggs" << endl;
		cin >> eggs;
	}
	if(anType == "Mammal"){
		eggs = 0;
		cout << "enter 0 for not nursing or 1 for nursing" << endl;
		cin >> nurse;
	}
	cout << "enter sub-type" << endl;
	cin >> subType;


//check for errors in input, if so, prompt user
	while(trackNum.length()!=6){
		cout << "Track number can only have 6 numbers, enter track number" << endl;
		cin >> trackNum;

	}
	while(anType != "Oviparous" && anType!= "Mammal"){
		cout << "Animal type must be Oviparous or Mammal, re-enter type" << endl;
		cin >> anType;
	}
	while(nurse != 0 && nurse != 1){
		cout << "nursing must be 0 for not nursing or 1 for nursing, enter 0 or 1" << endl;
		cin >> nurse;
	}

	trackNum.append(15-trackNum.length(), ' '); //padding variables to display better
	anName.append(15-anName.length(), ' ');
	anType.append(15-anType.length(), ' ');
	subType.append(15-subType.length(), ' ');

	newString = trackNum + anName + anType + subType + to_string(eggs) + " " + to_string(nurse);

	cout << "would you like to save this new animal? Enter y for yes or n for no." << endl;
	cin >> saveDel;
	if (saveDel == 'y' || 'Y'){
	//add string to vector
		zooFile.push_back(newString);  //save new animal to vector
	}

}


void RemoveAnimal()
{
	string userTrack;
	char userCon;

	int i =0;

	cout << "Enter track number to delete" << endl;
	cin >> userTrack;

	while (userTrack.length() != 6){
		cout << "Track number must be 6 characters, re-enter track number" << endl;
		cin >> userTrack;
	}

	for(i =0; i<zooFile.size(); ++i){  //iterate through vector
		if(zooFile.at(i).compare(0, 6, userTrack, 0, 6) == 0){
			cout << "Press y to confirm deletion" << endl;
			cin >> userCon;
			if(userCon =='y'){
			zooFile.erase(zooFile.begin() + i);
			cout << "Animal successfully deleted" << endl;
		}
	}


}
}

void LoadDataFromFile()
{

	ifstream in("zoodata.txt");
	zooFile.clear();

	string line;
	while(getline(in, line)){
		zooFile.push_back(line);
	}
in.close();
	cout << "Load complete." << endl;
}

void SaveDataToFile()
{
	ofstream outFS;
	 outFS.open("zoodata.txt", ios::out);
	 int i;


	 for(i=0; i<zooFile.size(); ++i){   //write vector to file
	 outFS << zooFile.at(i)<< endl;
	 }

	 outFS.close();

	 cout << "Save successfully completed" << endl;

}

void DisplayMenu()
{
     cout << "1. Load Animal Data" << endl;
     cout << "2. Generate Data" << endl;
     cout << "3. Display Animal Data" << endl;
     cout << "4. Add Record" << endl;
     cout << "5. Delete Record" << endl;
     cout << "6. Save Animal Data" << endl;
     cout << "7. Quit" << endl;
}

void DisplayAnimalData(){
	int i;
	i = 0;

	for (i=0; i < zooFile.size(); ++i){  //output vector
		cout << zooFile.at(i) << endl;
	}

}



int main()
{
	int userInput;
	while(1){
	DisplayMenu();

	cin >> userInput;   // user menu selection


	if(userInput == 1){
		LoadDataFromFile();
	}
	if(userInput == 2){
		GenerateData();
	}
	if(userInput == 3){
		DisplayAnimalData();
	}
	if(userInput == 4){
		AddAnimal();
	}
	if(userInput == 5){
		RemoveAnimal();
	}
	if(userInput == 6){
		SaveDataToFile();
	}
	if(userInput == 7){
		return 0;
	}
	}
	return 1;
}
