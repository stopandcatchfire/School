//Nick Wantz
//CSc 135 T/Th 10:30-11:45am
//Homework#1 ~ Syntax Recognizer
//Prof. Gordon
//
//***********************************
//
//This program is design to interpret 
//a basic programming language to 
//determine whether or not inputed 
//stream from a given user is valid 
//or not within the grammar.
//Borrowed from Prof. Gordon's 
//example code to get started.
//
//
//
//
//
//
//
//
//
//
//***********************************
import java.io.*;
import java.util.Scanner;




public class Recognizer{


	static String inputStream;
	public int index = 0;
	public int errflg = 0;


	private char token() {
		return (inputStream.charAt(index));
	}

	private void advancePtr() {
		if (index < (inputStream.length()-1))
			index++;
	}

	private void match(char T) {
		if (T == token())
			advancePtr();
		else
			error();
	}


	private void error() {
		System.out.println("error @ position: " + index);
		errflg = 1;
		advancePtr();
	}

//************************************
//Methods for terminals and non-terms.
//************************************
	private void program() {
		
		do {
			statement();
		} while (token() == "X" || "Y" || "Z" || 0 || 1 || 2 || 3 || 4 || 5 || 6 || 7 || 8 || 9 || "I" || "F" || "N" || "O");			
	}

	private void statement() {

		if (token() == "X" || "Y" || "Z"){
			assignment();
		}
		else if (token() == "I"){
			ifstmt();
		}
		else if (token() == "F"){
			forloop();
		}
		else if (token() == "N"){
			input();
		}
		else if (token() == "O"){
			output();
		}
	}

	private void assignment() {
		
		identifier();
		match("~");
		expression();
		match(";");
	}

	private void ifstmt() {
		
		match("I");
		comprsn();
		match("@");
			
		while (token() == "X" || "Y" || "Z" || 0 || 1 || 2 || 3 || 4 || 5 || 6 || 7 || 8 || 9 || "I" || "F" || "N" || "O") {
			statement();
		}

		if (token() == "%") {
						
			while (token() == "X" || "Y" || "Z" || 0 || 1 || 2 || 3 || 4 || 5 || 6 || 7 || 8 || 9 || "I" || "F" || "N" || "O") {
				statement();
			}
		}
		
		match("&");
	}

	private void forloop() {
		
		match("F");
		match("(");
		assignment();
		match(")");
		match("(");
		comprsn();
		match(")");
		match("L");
		
		while (token() == "X" || "Y" || "Z" || 0 || 1 || 2 || 3 || 4 || 5 || 6 || 7 || 8 || 9 || "I" || "F" || "N" || "O") {
			statement();
		}

		match("\\");

	}

	private void input() {
		
		match("N");
		identifier();
		while (token() == ",") {
			identifier();
		}
		
		match(";");
	
	}

	private void output() {

		match("O");
		identifier();

		while (token() == ",") {
			identifier();
		}

		match(";");

	}

	private void comprsn() {
	
		match("(");
		opernd();
		operatr();
		opernd();
		match(")");
	
	}

	private void exprsn() {

		factor();
		while (token() == "+" || "-" ) { 
			sumop();
			factor();
		}

	}

	private void factor() {

		opernd();	
		while (token() == "*" || "/" ) {
			prodop();
			opernd();
		}

	}

	private void sumop() {
		
		if (token() != "+" || "-" ) {
			error();
		}
	}

	private void prodop() {

		if (token() != "*" || "/" ) {
			error();
		}
	}

	private void opernd() {

		if (token() == "(" ) {
			exprsn();
			match(")");
		}

		else if (token() == 0 || 1 || 2 || 3 || 4 || 5 || 6 || 7 || 8 || 9 ) {
			integer();
		}
		
		else {
			ident();
		}

	}

	private void opratr() {
		
		if (token() != "<" || ">" || "=" || "!" ) {
			error();
		}
	
	}

	private void ident() {
		
		letter(); 
		while (token() == "X" || "Y" || "Z" || 0 || 1 || 2 || 3 || 4 || 5 || 6 || 7 ) {
			character();
		}

	}

	private void character() {
	
		if (token() == "X" || "Y" || "Z" ) {
			letter();
		}
		else if (token() == 0 || 1 || 2 || 3 || 4 || 5 || 6 || 7 ) {
			digit();
		}
		else
			error();
	
	}

	private void integer() {
	
		digit();
		while (token() == 0 || 1 || 2 || 3 || 4 || 5 || 6 || 7 ) {
			digit();
		}

	}

	private void letter() {

		if (token() != "X" || "Y" || "Z" ) {
			error();
		}
		else 
			match(token());
	
	}

	private void digit() {
		
		if (token() != 0 || 1 || 2 || 3 || 4 || 5 || 6 || 7 ) {
			error();
		}
		else
			match(token());
	
	}




 
//************************************
//Start point @ Program after call to 
//start.
//************************************
	private void start() {
		
		program();
		match('$');

		if (errflg == 0)
			System.out.println("Program legal." + "\n");
		else
			System.out.println("Program illegal." + "\n");

	}


//************************************
//Main, Scanner and initializer, 
//object creation.
//************************************
	public static void main (String[] args) throws IOException {
		
		Recognizer rec = new Recognizer();

		Scanner input = new Scanner(System.in);  //may be changed based on user input

		System.out.print("\n" + "Enter an expression: ");
		inputStream = input.nextLine();

		rec.start();   //Start of program
	
	}
}		
