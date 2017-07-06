///////////////////////////////////////////////////
//adder.v, 137 Verilog Programming Assignment #4
//Adding/subtracting Number, 5-bit maximum
//Nick Wantz
//CSc137
//Prof. Chang
//
//written 10/13/2016
//
///////////////////////////////////////////////////




//Borrowed following from example code

module TestMod;
//0x80000000 is channel of stdin,
//console input from kb

	parameter STDIN = 32'h8000_0000; //32-bit hex

	reg [7:0] str[1:3];		//taking in 2 chars at a time		
	reg [4:0] x, y;			//input vars
	reg c0;
	wire [4:0] s;			//sum for output
	wire c4,c5,e;			//carry bit

	BigAdder myBigAdder(x,y,s,c0,c5,e);


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
			

		if(x>15) begin
			$display("X input is larger than 5-bit signed integer... BYE FELICIA!");
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

		if(y>15) begin
			$display("Y input is larger than 5-bit signed integer... BYE FELICIA!");
			$finish;
		end
		
		$display("Choose '+' or '-' as operatior");
		
		str[1] = $fgetc(STDIN);
		str[2] = $fgetc(STDIN);

		if(str[1] != 43 && str[1] != 45) begin
			$display("Did not select correct operator...");
			$finish;
		end

		if(str[1] == 43) begin
			c0 = 0;			
		end

		if(str[1] == 45) begin
			c0 = 1;
		end

		#1;
		
		$display("X = %d (%b) Y = %d (%b)\n\nResult=%d (%b)\nC5=%b E=%b\n", x, x, y, y, s, s, c5, e);
		
	end
endmodule

module BigAdder(x,y,s,c0,c5,e);
	input [4:0] x,y;	//two 5-bit input items
	input c0;
	output [4:0] s;
	output c5, e;

	wire [3:0] c;
	wire [4:0] ys;

	xor(ys[0],c0,y[0]);
	xor(ys[1],c0,y[1]);
	xor(ys[2],c0,y[2]);
	xor(ys[3],c0,y[3]);
	xor(ys[4],c0,y[4]);
	FullAdderMod bit0(x[0],ys[0],s[0],c0,c[0]);
	FullAdderMod bit1(x[1],ys[1],s[1],c[0],c[1]);
	FullAdderMod bit2(x[2],ys[2],s[2],c[1],c[2]);
	FullAdderMod bit3(x[3],ys[3],s[3],c[2],c[3]);
	FullAdderMod bit4(x[4],ys[4],s[4],c[3],c5);
	xor(e,c5,c[3]);
	
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


