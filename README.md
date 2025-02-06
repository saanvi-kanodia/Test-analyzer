# Test Analyzer

Test Analyzer is a C++ project designed to evaluate and analyze a user's aptitude in four domains: Arithmetic, Logical, Series Completion, and Problem Solving. The project includes a timed multiple-choice questionnaire, as well as detailed analysis and feedback on the user's performance.

## Description

This project aims to provide a comprehensive analysis of test data using C++. It includes various functionalities to read, process, and analyze test results, providing insightful metrics and reports. The test consists of 20 multiple-choice questions, and the user is given 5 minutes to complete the test. After the test, the user can review their answers and receive detailed analysis and feedback on their performance.

## Instructions
- The test consists of 20 multiple-choice questions.
- The duration of the test is 5 minutes.
- A timer will show you the amount of time remaining after every question is solved.
- Once the time elapses, the test will end automatically.
- Once you have gone to the next question, you can't go back.
- To progress to the next question, answer the question by typing the appropriate option letter.
- Type 'ready' once you are ready to begin the test.

## Classes
### Database Class
- string instructions(): Displays the test instructions and returns the user's response.
- void print_quest(): Prints the questions from the file.
- void print_method(int n): Prints the explanation for the given question.

### User Class (Inherits from database)
- void store_ans(int i): Stores the user's answer for the given question.
Timer Class (Inherits from User)
- void print_time(): Manages the timer and prints the remaining time.

### Calculate Class (Inherits from User)
- void review(): Reviews the user's answers, correct answers, and explanations.
- int check(): Compares the user's answers with the correct answers and calculates the total score.
- void analysis(): Prints the total time, section time, section marks, and accuracy.
- void strength_weak(): Provides feedback on the user's strengths and weaknesses.

### Time_Analysis Class (Inherits from Timer)
- void section_time(): Prints the time taken for each section.

## Getting Started

### Dependencies

- C++ compiler (e.g., g++)
- Make (optional, for building the project)

### Installing

Clone the repository:

```bash
git clone https://github.com/saanvi-kanodia/Test-analyzer.git
cd Test-analyzer
