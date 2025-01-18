#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

string domain[4]={"Arithmetic","Logical","Series Completion", "Problem Solving"};
class database
{
protected:
    string method[20];
    string ans[20] = {"c", "b", "c", "c", "a", "d", "b", "c", "b", "c",
                    "c", "d", "a", "c", "a","a", "d", "a", "c", "c"
                   };
    string quest[100];

public:
    string qdup[100];
    string instructions()
    {
        string reply;
        cout << "\n\n\n\n\t\t\t\t-------------- WELCOME TO TEST ANALYZER APTITUDE TEST --------------- " << endl
             << endl;
        cout << "\t\t\t\t---This test will analyze your aptitude in 4 domains: ---\n"<< endl;
        cout << "\t\t\t\tInstructions:"<< endl;
        cout << "\t\t\t\tThere are 20 MCQ questions in total "<< endl;
        cout << "\t\t\t\tThe duration of the test is 5 minutes"<< endl;
        cout << "\t\t\t\tA timer will show you the amount of time remaining after every question solved"<< endl;
        cout << "\t\t\t\tOnce the time elapses the test will end automatically"<< endl;
        cout << "\t\t\t\tOnce you have gone to the next question, you can't go back."<< endl;
        cout << "\t\t\t\tTo progress to the next question, answer the question by typing the appropriate option letter"<< endl;;
        cout << "\t\t\t\tType 'ready' once you are ready to begin the test" << endl;
        cin>>reply;
        return reply;
        cout<<"\n\n\n";
    }
    float n1 = 1;
    int n = 1;

    void print_quest()
    {
        ifstream in;
        in.open("answers.txt");
        if (in.fail())
        {
            cout << "Couldn't open file";
            exit(0);
        }
        else
        {
            for (int i = 0; i < 100 && !in.eof(); ++i)
            {
                getline(in, quest[i]);
                qdup[i] = quest[i];
            }
            do
            {
                cout << qdup[n-1];
                cout << endl;
                n1 = n % 5;
                n++;
            }
            while (n1 != 0);
        }
        in.close();
    }

    void print_method(int n)
    {
        int i=0;
        ifstream in;
        in.open("method.txt");
        if (in.fail())
        {
            cout << "Couldn't open file";
            exit(0);
        }
        else
            for (i; i < 20 && !in.eof(); i++)
            {
                string method2[20];
                getline(in, method2[i]);
                method[i]=method2[i];
                // Close the file after reading
            }
        cout<<method[n];
        cout<<endl;
        in.close();
    }
} d;

string input[20];

class User : public database
{
public:
    void store_ans(int i) // store user answer
    {
        bool val = true;
        while(val)
        {
            cin.ignore();
            cout << "Enter the answer : ";
            cin >> input[i];
            if(input[i]=="a"||input[i]=="b"||input[i]=="c"||input[i]=="d")
            {
                val=false;
            }
            else
                cout<<"Enter valid option only, numerical, or any other answer will not be accepted"<<endl;
        }

    }
};
float section_wise[4];
class Timer :  public User
{
public:
    clock_t start[4];
    clock_t stop[4];
    float total_time;
 //   float speed;

public:
    void print_time() // will print at intervals using threads
    {
        const int TIME_LIMIT = 300;
        total_time = 0;
        int c=0;
        time_t startTime = time(0);
        for (int i = 0; i < 4; i++)
        {
             //Stopwatch starts
            start[i] = clock(); //time calculation starts
            // questions will be called here
            for (int s = 0; s < 5; s++)
            {

                d.print_quest();
                cout << endl;
                store_ans(c);
                system("cls");
                c++;
                time_t currentTime = time(0); //stopwatch ends
                int elapsedTime = difftime(currentTime, startTime);
                int remainingTime = TIME_LIMIT - elapsedTime;
                if (remainingTime < 0) {remainingTime = 0; break; }
                cout << "Time Remaining: " << remainingTime << " seconds" << endl;
                this_thread::sleep_for(chrono::seconds(1)); // Wait for 1 second
                remainingTime--;
            }
            stop[i] = clock(); //time calculation end
            section_wise[i] = static_cast<float>(stop[i] - start[i]) / CLOCKS_PER_SEC;
            cout << "Time taken for the "<<domain[i]<<" section: " << section_wise[i] << " sec\n\n";
            total_time += section_wise[i];
        }
            cout << "\t\t\tTotal time taken: " << total_time << " sec" << endl;
    }
};

class Calculate : public User
{
protected:
    int score[20], sect_mrks[4]= {0};
    int total = 0;
    double accuracy;
    string indicator;

public:
    void review() // question,user answer,correct answer,next option
    {
        //cout<<input[1]<<input[3];
        for (int i = 0; i < 20; i++)
        {
            print_quest();
            while (n1 != 0);
            cout << "Your answer: " << input[i] << endl;
            cout << "Correct answer: " << ans[i] << endl;
            cout << "Explanation: \n";
            print_method(i);
            cout<<endl;
        }
    }
    int check() // compare input[] with ans[]
    {
        int i = 0;
        for (i; i < 20; i++)
        {
            if (input[i] == ans[i])
            {
                score[i] = 1;
                total = total + 1;
            }
        }

        return total;
    }
    void analysis() // prints total time,section_time,section_mrks,accuracy,
    {
        for (int i = 0; i < 20; i++)
        {
            if (score[i] == 1)
            {
                accuracy += 1;
            }
        }
        accuracy = accuracy * 5; // (accuracy/20)*100
        cout << "Your accuracy of correct answers: " << accuracy << " %" << endl<<endl;

        int i=1;
        for (int n = 0; n < 4; n++)
        {
            float i2=1;
            do
            {
                sect_mrks[n] = sect_mrks[n] + score[i-1];
                  i2 = i % 5;
                  i++;
            }
            while(i2!=0);
            cout<<"Marks in "<<domain[n]<<" section : "<<sect_mrks[n]<<endl;

        }
    }

    void strength_weak() // based on sect_mrks[4]assign strength or weakness //
    // indicator
    {
        cout<<"This are your strength and weaknesses for each section\n";
        for (int n = 0; n < 4; n++)
        {
            if (sect_mrks[n] == 4 || sect_mrks[n] == 5)
                cout <<domain[n]<<":\nThis domain is your Strength. Make sure to utilize this in your career " << endl;
            else if (sect_mrks[n] == 3)
                cout <<domain[n]<<":\nGood, work on improving your skills in this domain" << endl;
            else if (sect_mrks[n] == 1 || sect_mrks[n] == 2)
                cout <<domain[n]<<":\nThis domain is your Weakness. You need to work harder." << endl;
            else
                cout <<domain[n]<<":\nVery poor performance" << endl;
        }
    }
};

class Time_Analysis : public Timer // Time based calculation
{

public:

    void section_time() // section wise time taken
    {
           cout<<"Your speed of answering the domains\n";
        for (int i = 0; i < 4; i++)
           cout<<domain[i]<<" domain: "<<section_wise[i]<<endl;
    }
};

int main()
{
    database data;
    User use;
    User use1;
    Calculate cal;
    Time_Analysis tim;
    Timer t;
    int i = 1;
    while (i == 1)
    {
        if (data.instructions() == "ready")
        {
            cout<<"The test will begin now\n\n";
            t.print_time();
            i = 0;
        }
        else
            i = 1;
    }

         cout<<"\n\t\t\tYou have scored: "<<cal.check()<<"/20"<<endl;
         string var;
         cout << "\t\t\tCongratulations!! You have finished the test"<<endl<<endl;
    do
    {
        cout<<"enter one of the option numbers to analyze or review your answers"<< endl;
        cout << "1. Review" << endl;
        cout << "2. Analysis" << endl;
        cout << "3. Exit" << endl;
        bool val = true;
        while(val)
        {
            cin >> var;
            if(var=="1"||var=="2"||var=="3")
            {
                val=false;
            }
            else
                cout<<"Your answer will not be accepted. Enter valid options: ";
        }
        if(var=="1")
            cal.review();
        else if(var=="2")
        {
            cal.analysis();
            cout<<endl<<endl;
            tim.section_time();
            cout<<endl<<endl;
            cal.strength_weak();
            cout<<endl<<endl;
        }
        else
            cout << "Ending Analysis. Thank you for using our program." << endl;
    }
    while(var!="3");

    return 0;
}
