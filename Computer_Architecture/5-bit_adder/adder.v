///////////////////////////////////////////////////
//adder.v, 137 Verilog Programming Assignment #3
//Adding Number, 5-bit maximum
//Nick Wantz
//CSc137
//Prof. Chang
//
//written 10/3/2016
//
///////////////////////////////////////////////////




//Borrowed following from example code

module TestMod;
//0x80000000 is channel of stdin,
//console input from kb

	parameter STDIN = 32'h8000_0000; //32-bit hex

	reg [7:0] str[1:3];		//taking in 2 chars at a time		
	reg [4:0] x, y;			//input vars
	wire [4:0] s;			//sum for output
	wire c5;			//carry bit

	BigAdder myBigAdder(x,y,s,c5);


	initial begin
			
		$display("Enter a 5 bit integer for X then press 'Enter':");

		str[1] = $fgetc(STDIN);	//get input for x
		str[2] = $fgetc(STDIN); //get second input for x
		str[3] = $fgetc(STDIN); //get enter/EOL
		
		//checking x constraints.
		if(str[3] != 10) begin
			$display("Too many input characters...");
			$finish;
		end
		
		if(str[1]>51) begin
			$display("Input greater than 5-bit");
			$finish;
		end

		if(str[1]==51 && str[2] > 49) begin
			$display("Input greater than 5-bit");
			$finish;
		end


		str[1] = (str[1] - 48) * 10; 		//converts from ascii to int
		str[2] = str[2] - 48;
		x = str[1] + str[2];
			

		if(x>31) begin
			$display("X input is larger than 5-bit integer... BYE FELICIA!");
			$finish;
		end

		$display("Enter a 5 bit integer for Y to add to X then press 'Enter':");

		str[1] = $fgetc(STDIN);	//get input for y
		str[2] = $fgetc(STDIN); //get second input for y
		str[3] = $fgetc(STDIN); //get enter/EOL
		//checking y constraints
		if(str[3] != 10) begin
			$display("Too many input characters...");
			$finish;
		end
		
		if(str[1]>51) begin
			$display("Input greater than 5-bit");
			$finish;
		end

		if(str[1]==51 && str[2] > 49) begin
			$display("Input greater than 5-bit");
			$finish;
		end
		

		str[1] = (str[1] - 48) * 10; 		//converts from ascii to int
		str[2] = str[2] - 48;
		y = str[1] + str[2];

		if(y>31) begin
			$display("Y input is larger than 5-bit integer... BYE FELICIA!");
			$finish;
		end
		
		#1;
		
		$display("X = %d (%b) Y = %d (%b)\nResult = %d (%b)  C5 = %d", x, x, y, y, s, s, c5);
		
	end
endmodule

module BigAdder(x,y,s,c5);
	input [4:0] x,y;	//two 5-bit input items
	output [4:0] s;
	output c5;

	wire [3:0] c;

	FullAdderMod bit0(x[0],y[0],s[0],0,c[0]);
	FullAdderMod bit1(x[1],y[1],s[1],c[0],c[1]);
	FullAdderMod bit2(x[2],y[2],s[2],c[1],c[2]);
	FullAdderMod bit3(x[3],y[3],s[3],c[2],c[3]);
	FullAdderMod bit4(x[4],y[4],s[4],c[3],c5);

endmodule

module FullAdderMod(x,y,s,cIn,cOut);
	input  x,y, cIn;
	output s, cOut;

	wire s1,andXY, carryAnd;

	and(andXY, x, y);
	xor(s1, x, y);
	xor(s, cIn, s1);
	and(carryAnd, cIn, s1);
	or(cOut, carryAnd, andXY); 

endmodule


